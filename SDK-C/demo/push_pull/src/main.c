#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <assert.h>
#include <time.h>

//��غ���Makefile�ж���
#include "transportMedia.h"

//ͷ�ļ�����
#ifdef QSTP
#include "LYQstpAPI.h"
#else
#include "cJSON.h"
#include "LYPlatformAPI.h"
#include "lyUtils.h"
#endif

char* videoName = NULL;
char* audioName = NULL;


#ifdef LY_PLATFORM
/*********************ƽ̨���**************************/

typedef struct _lyWorkFlag
{
	int working;
	int waitMessage;
	int msgid;
	pthread_t pidWork;
	pthread_t pidMsgProc;
}lyWorkFlag;
lyWorkFlag workFlag = {1,1,-1,NULL,NULL};

typedef struct _tranportConfig 
{
	int publicLiveFlag;//ֱ�����أ�device����Ϊֱ����Ϊ1������Ϊ0
	int isRecording;//�ƴ洢���أ�device���ƴ洢Ϊ1������Ϊ0
	int qstpOpenFlag;//qstp���أ����ƴ洢����ֱ��Ϊ1������Ϊ0
}tranportConfig;

typedef struct _config
{
	int type;//�豸���������͡�0:qsupЭ�飬2:qstpЭ��ֱ����3:�ƴ洢��4:qstpֱ�����ƴ洢,//5:qstpЭ��ǹ��ڲ����ƴ洢
	int audioFlag;
	int bitrate;//�������ʡ�1:1M,2:500K,3:300K��
	int typeChanged;//��ʶ�豸�������Ƿ�ı䣬���ֻ��˸ı����ú󣬻���popMessage�ص�����������Ϊ1��
	int fds[MAX_CHANNEL];
	int curWorkChannelCount;
	int pushing;
	tranportConfig trans_config;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}deviceConfig;
deviceConfig endPointConfig;
/*********************ƽ̨��ء�end**************************/
//��ʼ����ز���
static int deviceConfigInit(deviceConfig* config)
{
	int i = 0;
	config->type = 0;
	config->audioFlag = 0;
	config->bitrate = 0;
	config->trans_config.publicLiveFlag = 0;
	config->trans_config.isRecording = 0;
	config->trans_config.qstpOpenFlag = 0;
	for(;i<MAX_CHANNEL;i++)
		config->fds[i] = -1;
	config->curWorkChannelCount = 0;
	config->typeChanged = 0;
	config->pushing = 0;
	pthread_cond_init(&config->cond,NULL);
	pthread_mutex_init(&config->mutex,NULL);
}

//�ֻ������豸�˵����ӽ���
int connectEstablished()
{
	int fd = -1;
	if(endPointConfig.curWorkChannelCount <= MAX_CHANNEL)
	{
		if(!endPointConfig.pushing)
		{
			endPointConfig.fds[0] = 0;//QSUPЭ��ʹ��Ĭ��ʹ��0
			if(startPushMedia(endPointConfig.fds[0],endPointConfig.audioFlag)==0)
				endPointConfig.pushing = 1;
		}
		return 0;
	}
	else
	{
		printf("already start max channel count,can't start a channel any more\n");
		return -1;
	}
}

//�ֻ������豸�˵����ӹرա�
void connectClose()
{
	if(endPointConfig.pushing == 1 && !endPointConfig.trans_config.qstpOpenFlag)
	{
		stopPushMedia(endPointConfig.fds[0]);
		endPointConfig.pushing = 0;
	}
}


int startLyCloudService(char* token,char* configStr)
{
	int ret = -1;
	if(!token || !configStr)
	{
		printf("token or configstring is NULL\n");
		return -1;
	}

	if(workFlag.msgid == -1)//��ֹ��ε���
	{
		deviceConfigInit(&endPointConfig);//��ʼ��������ؽṹ��

		//������Ϣ���д�����ƽ̨����������Ϣ
		if((workFlag.msgid = createMsgId('h')) != -1)
		{
			if(pthread_create(&workFlag.pidMsgProc,NULL,msgProc,NULL) != 0)
			{
				//ʧ��������Ӧƽ̨����Ϣ��Ӧ���˳�����
				printf("create msgProc thread failed\n");
				return -1;
			}
		}

		//��������ģʽ���Ĵ����߳�
		ret = pthread_create(&workFlag.pidWork,NULL,configChangeProc,NULL);
		if(ret != 0)
		{
			printf("start configChangeProc thread failed\n");//�����߳�ʧ�ܽ�������Ӧ����ģʽ�ı䴦��
		}

		while(1)
		{
			//������ƽ̨���񣬲�ע����Ϣ�ص�����,���ô˺���֮����ܵ�����ƽ̨���������������ĸ�����Ϊ�Խӳ����Զ������ݣ�û������
			ret = LY_startCloudService(token,configStr,popMessage,NULL);
			if(ret == 0)//����0��ʾ�����ɹ�
			{
				break;
			} 
			printf("StartCloudService failed!  ret = %d  retry...\n",ret );
			sleep(1); 
		}
		printf("start lingyang cloud service success\n");
	}
	return 0;
}


void stopLyCloudService()
{
	printf("clean app\n");
	myMsg tmp = {100,"cancel"};
	workFlag.waitMessage = 0;
	if(msgsnd(workFlag.msgid,&tmp,sizeof(myMsg),0) != 0)//ʹ�÷�������ʽ������Ϣ
	{
		perror("send cancel msg failed");
	}
	pthread_join(workFlag.pidMsgProc,NULL);
	printf("join msgProc success\n");
	workFlag.working = 0;
	endPointConfig.typeChanged = 1;
	pthread_cond_broadcast(&endPointConfig.cond);
	pthread_join(workFlag.pidWork,NULL);
	printf("join configChanged success\n");
	if(msgctl(workFlag.msgid,IPC_RMID,0))//ɾ���ں˵���Ϣ����
	{
		printf("remove msg_que failed\n");
	}
	//step4.���ô˽ӿڹر���ƽ̨�����ˣ���ƽ̨�����ӿڵ���ʧЧ��
	LY_stopCloudService();
}

#endif

static void signalproc(int signo)
{
	printf("signal num:%d\n",signo);
}


int main(int argc,char** argv)
{
	int ret;
	int fd = -1;
	signal(SIGPIPE,signalproc);//����SIGPIPE�źţ�����Ҫ
#ifdef QSTP //===========================ֻ����QSTP����=============================================================
	int isPushAudio = 0;
	//����������������Ҫ���̨��������ȡtoken������������IP���˿ڣ�Ȼ���������url������Ҫָ������������������url ip�Ͷ˿��ֶ�ָ������������ip�Ͷ˿�
	//ʹ��������ȵ���������������urlʾ����
	char* url = "topvdn://183.57.151.111:1935?protocolType=2&connectType=1&token=1003791_3222536192_1493481600_b118f1066b417b6751a4804253d6d236&mode=2";

	if(argc < 2)
	{
		printf("usage:./%s [videoName] [audioName]\n",argv[0]);
		return 0;
	}
	
	if(argc > 2)
	{
		isPushAudio = 1;
	}
	while(1)
	{
		fd = LY_connectToRelayServer(url);
		if(fd < 0)
		{
			printf("connect to lingyang cloud relay server failed,retry...\n");
			usleep(300*1000);
			continue;
		}
		break;
	}
	
	videoName = argv[1];
	if(argc > 2)
	{
		audioName = argv[2];
	}

	if(startPushMedia(fd,isPushAudio) != 0)
	{
		printf("start push failed\n");
		return -1;
	}
	while(1)
	{
		sleep(3);
	}
//======================================������ƽ̨====================================================//
#elif defined(LY_PLATFORM)
	if(argc < 2)
	{
		printf("Usage:%s <videoFileName> [audioFileName]\n",argv[0]);
		return -1;
	}
	videoName = argv[1];
	if(argc > 2)
		audioName = argv[2];
	//step1.���̨��ȡtoken��configString,�������Խӳ��̣����ﰴ���Լ�ҵ���߼�ʵ�֡�
	//����ʾ����
	char* deviceToken = "1003791_3222536192_1493481600_b118f1066b417b6751a4804253d6d236";
	char* configStr = "[Config]\r\nIsDebug=0\r\nLocalBasePort=8200\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nU \
					  dpSendInterval=2\r\nConnectTimeout=10000\r\nTransferTimeout=10000\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80 \
					  \r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n[LogServer]\r\nCount=1\r\nIP1=120.26.74.53\r\nPort1=80\r\n";
	
	//step2.���������Ʒ���
	ret = startLyCloudService(deviceToken,configStr);
	if(ret != 0)
	{
		printf("!!!start ly cloud service failed\n");
		return 0;
	}
	
	//step3.���������ƵĻص���Ϣʵ���Լ���ҵ���߼�
#if 1
	//��������Ϊû�кͺ�̨������������ģ���̨����������Ϣ
	sleep(3);
	pthread_mutex_lock(&endPointConfig.mutex);
	endPointConfig.audioFlag = 1;//��Ƶ����
	endPointConfig.type = 2;//����ģʽ
	endPointConfig.trans_config.qstpOpenFlag = 1;
	endPointConfig.typeChanged = 1;
	pthread_cond_broadcast(&endPointConfig.cond);
	pthread_mutex_unlock(&endPointConfig.mutex);
	sleep(3);
	//startPushAudio(endPointConfig.fds[0]);
	sleep(10);
	printf("main stop push audio\n");
	//stopPushAudio(endPointConfig.fds[0])
#endif
	while(1)
	{
		//keep alive
		sleep(1);
	}
	//step4.ֹͣ�����Ʒ���
	stopLyCloudService();
#endif
	printf("app exit\n");
	return 0;
}
