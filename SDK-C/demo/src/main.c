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


//����ʹ�ý����յ�����Ϣ���͵�ר�Ŵ�����Ϣ���̣߳���������ƽ̨��
void popMessage(void *apData, const char *aMessage)
{
	if(!aMessage)
		return;
	cJSON* root = cJSON_Parse(aMessage);
	cJSON* name = cJSON_GetObjectItem(root,"name");
	cJSON* message;
	myMsg tmpMsg = {0,""};
	if(memcmp("ConnectionAcceptted",name->valuestring,strlen(name->valuestring)) == 0)
	{
		//˽��Э�鿪ʼ����
		printf("PopMessage ConnectionAcceptted\n");
		tmpMsg.type = 1;
		strcpy(tmpMsg.buffer,"ConnectionAcceptted");
	}
	else if(memcmp("ConnectionClosed",name->valuestring,strlen(name->valuestring)) == 0)
	{
		//˽��Э���������
		printf("PopMessage ConnectionClosed\n");
		tmpMsg.type = 2;
		strcpy(tmpMsg.buffer , "ConnectionClosed");
	}
	else if(memcmp("StartPopData",name->valuestring,strlen(name->valuestring)) == 0)
	{
		//˽��Э�鿪ʼ������Ƶ�ش�
		printf("PopMessage StartPopData\n");
		tmpMsg.type = 3;
		strcpy(tmpMsg.buffer , "StartPopData");
	}
	else if(memcmp("PopMessage",name->valuestring,strlen(name->valuestring)) == 0)
	{
#if 0
		//���յ��������Զ�����Ϣ,�����������Լ��������ݸ�ʽ
		printf("PopMessage PopMessage\n");
		message = cJSON_GetObjectItem(root,"message");
		char* cfg = message->valuestring;
		int msgLen = strlen(cfg)/2;
		printf("====================message:%s,len=%d\n",cfg,msgLen);
		char config[256] = {0};
		int i;
		int result;
		for (i=0; i<msgLen; i++) 
		{
			result = 0;//ע��Ҫ��0
			sscanf(cfg+i*2,"%02X",&result);
			config[i] = result & 0xFF;
		}
		printf("====================get msg=%s\n",config);
		memcpy(tmpMsg.buffer,config,msgLen);//�˴�����ʹ��strcpy
#else
		//�����豸������Ϣ����Ƶ���أ�����ģʽ����Ƶ���ʸı�Ȳ���
		printf("PopMessage PopConfig\n");
		message = cJSON_GetObjectItem(root,"message");
		char* cfg = message->valuestring;
		char config[256];
		int i;
		int result;
		for (i=0; i<256; i++) 
		{
			sscanf(cfg+i*2,"%02X",&result);
			config[i] = result & 0xFF;
		}
		if(config[0] == 0)//APP�˽���豸
		{
			//ʵ�ִ����豸����߼�
		}
		else
		{
			tmpMsg.type = 5;
		}
		memcpy(tmpMsg.buffer,config,256);//�˴�������strcpy
		printf("msg type = 5,change  config\n");
#endif
	}
	else if(memcmp("PopConfig",name->valuestring,strlen(name->valuestring)) == 0)
	{
		//�����豸������Ϣ����Ƶ���أ�����ģʽ����Ƶ���ʸı�Ȳ���
		printf("PopMessage PopConfig\n");
		message = cJSON_GetObjectItem(root,"message");
		char* cfg = message->valuestring;
		char config[256];
		int i;
		int result;
		for (i=0; i<256; i++) 
		{
			sscanf(cfg+i*2,"%02X",&result);
			config[i] = result & 0xFF;
		}
		if(config[0] == 0)//APP�˽���豸
		{
			//ʵ�ִ����豸����߼�
		}
		else
		{
			tmpMsg.type = 5;
		}
		memcpy(tmpMsg.buffer,config,256);//�˴�������strcpy
		printf("msg type = 5,change  config\n");
	}
	if(tmpMsg.type != 0)
	{
		if(msgsnd(workFlag.msgid,&tmpMsg,sizeof(myMsg),IPC_NOWAIT) != 0)//ʹ�÷�������ʽ������Ϣ
		{
			perror("send msg failed");
		}
	}
	if(root)
		cJSON_Delete(root);//����ʹ��free�����ͷ�root,��������ڴ�й¶
}

//����ƽ̨���͹�������Ϣ
void* msgProc(void* arg)
{
	myMsg rcvMsg;
	int msg_type;
	workFlag.waitMessage = 1;
	//pthread_detach(pthread_self());
	while(workFlag.waitMessage)
	{
		memset(&rcvMsg,0,sizeof(rcvMsg));
		if(msgrcv(workFlag.msgid,&rcvMsg,sizeof(myMsg),0,0) == -1)
		{
			perror("msgrcv failed errno");
		}
		msg_type  = rcvMsg.type;
		switch(msg_type)
		{
		case 1:
			printf("msgProc accept\n");
			connectEstablished();//QSUPЭ��˽��ģʽ����ConnectionAcceptted��صĲ������������������ʵ�֡�
			break;
		case 2:
			printf("msgProc close\n");
			connectClose();//QSUP˽��ģʽ����ConnectionClosed��صĲ����������������ʵ�֡�
			break;
		case 3:
			printf("msgProc start pop data\n");//��������˽��ģʽ�µ�APP�Խ���Ƶ�߳�
			startRecvAudio(endPointConfig.fds[0]);
			break;
		case 4:
			//�������Զ�����Ϣ
			printf("msgProc pop message\n");
			printf("custom message:%s\n",rcvMsg.buffer);
			break;
		case 5:
			{
				//�豸����ģʽ����
				int type = rcvMsg.buffer[4];
				printf("msgProc config,type=%d\n",type);
				pthread_mutex_lock(&endPointConfig.mutex);
				//cam_config.bitrate = rcvMsg.buffer[0];//˽��Э�����ֻ�APP�˷����ı���ƽ̨�����ŷ���"ConnectionClosed"��"ConnectionAcceptted"����
				if(endPointConfig.type != type)
				{
					switch(type)
					{
					case 0:
						endPointConfig.trans_config.publicLiveFlag = 0;
						endPointConfig.trans_config.isRecording = 0;
						endPointConfig.trans_config.qstpOpenFlag = 0;
						break;
					case 2:
						endPointConfig.trans_config.publicLiveFlag = 1;
						endPointConfig.trans_config.isRecording = 0;
						endPointConfig.trans_config.qstpOpenFlag = 1;
						break;
					case 3:
						endPointConfig.trans_config.publicLiveFlag = 0;
						endPointConfig.trans_config.isRecording = 1;
						endPointConfig.trans_config.qstpOpenFlag = 1;
						break;
					case 4:
						endPointConfig.trans_config.publicLiveFlag = 1;
						endPointConfig.trans_config.isRecording = 1;
						endPointConfig.trans_config.qstpOpenFlag = 1;
						break;
					default:
						break;
					}
					endPointConfig.audioFlag = rcvMsg.buffer[1];
					endPointConfig.bitrate = rcvMsg.buffer[0];
					endPointConfig.type = type;
					endPointConfig.typeChanged = 1;
					pthread_cond_broadcast(&endPointConfig.cond);
					pthread_mutex_unlock(&endPointConfig.mutex);
					break;
				}
				if(endPointConfig.audioFlag != rcvMsg.buffer[1])
				{
					endPointConfig.audioFlag = rcvMsg.buffer[1];
					printf("audioFlag change,audioFlag = %d\n",endPointConfig.audioFlag);
					if(endPointConfig.audioFlag == 0)
					{
						stopPushAudio(endPointConfig.fds[0]);
					}
					else if(endPointConfig.pushing)
					{
						if(startPushAudio(endPointConfig.fds[0]) != 0)
						{
							printf("change config,start push audio failed\n");
						}
					}
				}
				if(endPointConfig.bitrate != rcvMsg.buffer[0])
				{
					//APP���޸���Ƶ����,ʵ�������޸��߼���bitrate��ֵ,1:1M,2:500K,3:300K
					//�Ƽ�����ʽ�ǲ��Ͽ�ԭ�����������ӡ�
					printf("bitrate changed,new bitrate=%d\n",endPointConfig.bitrate);
				}
				pthread_mutex_unlock(&endPointConfig.mutex);
				break;
			}
		default:
			printf("other msg,not support\n");
			break;
		}
	}
}

//������ģʽ�ı�
void* configChangeProc(void* arg)
{
	int ret = 0;
	int fd = -1;
	ServerInfo_t info= {0};
	while(workFlag.working)
	{
		pthread_mutex_lock(&endPointConfig.mutex);
		while(endPointConfig.typeChanged == 0)
		{
			ret = pthread_cond_wait(&endPointConfig.cond,&endPointConfig.mutex);
			if(ret != 0)
			{
				printf("cond wait failed\n");
				pthread_mutex_unlock(&endPointConfig.mutex);
				return NULL;
			}

		} 
		if( endPointConfig.pushing )
		{
			stopPushMedia(endPointConfig.fds[0]);
			endPointConfig.pushing = 0;
			printf("stop push media fd=%d\n",endPointConfig.fds[0]);
		}
		int fd;
		LY_disconnect(endPointConfig.fds[0]);//�����fd���ڵ���LY_connect������������ʱ�ķ���ֵ������ͨ����Ψһ��ʶ
		if( endPointConfig.trans_config.qstpOpenFlag )//ʹ��qstpЭ�鷢��
		{
			while(1)
			{
				//ip�Ͷ˿�Ϊ0ʱ��ʾʹ�������ư���һ���㷨���ȵ���������������������Ҫָ��������IP,����url��ָ��������IP
				char* url = "topvdn://0.0.0.0:0?protocolType=2&connectType=1&token=537067556_3222536192_1493481600_f0399b369aa760362ac4edd224bae23b&mode=2";
				fd = LY_connect(url,NULL);//�������������������ر�ʶ����ͨ����fd,����������Ҫ�������fd
				if(fd < 0)
				{
					printf("connect to lingyang cloud relay server failed,retry...\n");
					usleep(300*1000);
					continue;
				}
				endPointConfig.fds[0] = fd;
				break;
				
			}
			if(!endPointConfig.pushing)
			{
				printf("start push media qstp audioFlag:%d\n",endPointConfig.audioFlag);
				if(startPushMedia(fd,endPointConfig.audioFlag) == 0)
				{
					printf("start push media success,fd=%d\n",fd);
					endPointConfig.pushing = 1;
				}
				else
				{
					printf("start push media failed\n");
				}
			}
		}

		endPointConfig.typeChanged = 0;
		pthread_mutex_unlock(&endPointConfig.mutex);
		printf("work mode changed success\n");
		fd = -1;
	}
	if(endPointConfig.pushing)
		stopPushMedia(endPointConfig.fds[0]); 
	if(endPointConfig.trans_config.qstpOpenFlag)
		LY_disconnect(endPointConfig.fds[0]);
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
	char* url = "topvdn://183.57.151.111:1935?protocolType=2&connectType=1&token=537067556_3222536192_1493481600_f0399b369aa760362ac4edd224bae23b&mode=2";

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
	char* deviceToken = "537067556_3222536192_1493481600_f0399b369aa760362ac4edd224bae23b";
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
