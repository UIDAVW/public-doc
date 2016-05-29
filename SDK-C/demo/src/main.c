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

#include "cJSON.h"
#include "CloudOpenAPI.h"
#include "pushMedia.h"

/*********************ƽ̨���**************************/
static RTMPMetaData rtmpData = {0,0,0,0,};
static int working = 1;
static int waitMessage = 1;
static int p2pRecvAudioFlag = 0;
static pthread_t pidP2PRecvAudioProc = NULL;
volatile int isCaptureOpen = 0;
int msgid = -1;

char* videoName = NULL;
char* audioName = NULL;
volatile int pushVideoing = 0;
volatile int pushAudioing = 0;
pthread_t pidPushVideo = NULL;
pthread_t pidPushAudio = NULL;

typedef struct _myMsg
{
	long type;
	char buffer[256];
}myMsg;

typedef struct _tranportConfig 
{
	int publicLiveFlag;//ֱ�����أ�device����Ϊֱ����Ϊ1������Ϊ0
	int isRecording;//�ƴ洢���أ�device���ƴ洢Ϊ1������Ϊ0
	int rtmpOpenFlag;//rtmp���أ����ƴ洢����ֱ��Ϊ1������Ϊ0
}tranportConfig;

typedef struct _config
{
	tranportConfig trans_config;

	int type;//�豸���������͡�0:˽�����ã�2:����ֱ����3:�ƴ洢��4:���ڴ��ƴ洢��
	int audioFlag;
	int bitrate;//�������ʡ�1:1M,2:500K,3:300K��
	int typeChanged;//��ʶ�豸�������Ƿ�ı䣬���ֻ��˿���ֱ���󣬻���popMessage�ص�����������Ϊ1��
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	//pthread_cond_t audioCond;
	//pthread_cond_t bitrateCond;
}device_config;
device_config cam_config;

volatile int bitrateChange;
/*********************ƽ̨��ء�end**************************/

static int deviceConfigInit(device_config* config)
{
	config->type = 0;
	config->audioFlag = 0;
	config->bitrate = 0;
	bitrateChange = 0;
	config->trans_config.publicLiveFlag = 0;
	config->trans_config.isRecording = 0;
	config->trans_config.rtmpOpenFlag = 0;

	config->typeChanged = 0;
	//config->cond = PTHREAD_COND_INITIALIZER;
	//config->mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_init(&config->cond,NULL);
	pthread_mutex_init(&config->mutex,NULL);
}


//ʵ�ֿ�ʼ�����߼�
int openCapture()
{
	if(!isCaptureOpen)
	{
		pushVideoing = 1;
		//pushVideoFlowProc����������pushMedia.h��
		if(pthread_create(&pidPushVideo,NULL,pushVideoFlowProc,NULL) != 0)
		{
			printf("\033[31mstart audio thread failed\n\033[0m");
		}
		printf("openCapture audioFlag=%d\n",cam_config.audioFlag);
		if(cam_config.audioFlag)//�������Ƶ��������Ƶ��������
		{
			pushAudioing = 1;
			//pushAudioFlowProc����������pushMedia.h��
			if(pthread_create(&pidPushAudio,NULL,pushAudioFlowProc,NULL) != 0)
			{
				printf("\033[31mstart audio thread failed\n\033[0m");
			}
		}

		isCaptureOpen = 1;
	}
	return 0;
}

//ʵ��ֹͣ�����߼�
int closeCapture()
{
	if(isCaptureOpen == 1)//���⹫���л���˽��(���׳�һ��ConnectClose��Ϣ)��ʱ���������
	{
		isCaptureOpen = 0 ;
		if(NULL != pidPushVideo)
		{
			pushVideoing = 0;
			pthread_join(pidPushVideo,NULL);
		}
		if(NULL != pidPushAudio)
		{
			pushAudioing = 0;
			pthread_join(pidPushAudio,NULL);
		}
		printf("close capture success\n");
	}
	return 0;
}

void connectEstablished()
{
	openCapture();
}

//�ֻ������豸�˵����ӹرա�����������ƴ洢���߹���ֱ�������ܹر��豸�����ݵ����͡�
void connectClose()
{
	if(!cam_config.trans_config.rtmpOpenFlag)
	{
		closeCapture(); 
	}
	if(NULL != pidP2PRecvAudioProc)
	{
		p2pRecvAudioFlag = 0;//ֹͣ��Ƶ��������
		pthread_join(pidP2PRecvAudioProc,NULL);
	}
}

//����ģʽ�Ļص�����������ͨ���˺���������Ƶ����
void rtmp_dataCallBack(void *apData,char* aData,int aLen, char aType)
{
	if(aType == 1)//������Ƶ����
	{
		printf("recv aac data len=%d\n",aLen);

	}
	else if(aType == 2)
	{
		printf("recv alarm info\n");
	}
}

//˽��ģʽ��Ƶ�ش�
void* recvAudioData(void* arg)
{
	char *pFrame;
	unsigned long frameSampleLength= 0;
	unsigned long timeStamp = 0;
	unsigned long lastTimeStamp = -1;
	unsigned char frameSampleType;
	p2pRecvAudioFlag = 1;
	printf("p2p recv audio data thread start\n");
	while(p2pRecvAudioFlag)
	{
		//������ƽ̨ͨ������˽��Э�鷢�͵�����
		frameSampleLength = 0;
		pFrame = PopData(0, &frameSampleLength, &timeStamp, &frameSampleType);//û�����ݻ�����,ʱ���Ϊ���ʱ�������һ���յ���ʱ���Ϊ0
		if(frameSampleLength)
		{
			printf("recv audiao data len = %d,timeStamp= %d,type=%d\n",frameSampleLength,timeStamp,frameSampleType);

		}
		free(pFrame);
	}
	printf("p2p recv audio data thread exit\n");
}

//����ʹ�ý����յ�����Ϣ���͵�ר�Ŵ�����Ϣ���̣߳���������ƽ̨��
int PopMessage(void *apData, const char *aMessage)
{
	if(!aMessage)
		return 0;
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
		//���յ��������Զ�����Ϣ,��Ҫ�����������Լ��������ݸ�ʽ
		printf("PopMessage PopMessage\n");
		tmpMsg.type = 4;
		message = cJSON_GetObjectItem(root,"message");
		memcpy(tmpMsg.buffer , message->valuestring,256);//�˴�����ʹ��strcpy,message->valuestring�����Զ������Ϣ���ݣ����ȹ̶�Ϊ256
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
		if(msgsnd(msgid,&tmpMsg,sizeof(myMsg),IPC_NOWAIT) != 0)//ʹ�÷�������ʽ������Ϣ
		{
			perror("send msg failed");
		}
	}
	if(root)
		cJSON_Delete(root);//����ʹ��free�����ͷ�root,��������ڴ�й¶
	return 0;
}

void* msgProc(void* arg)
{
	myMsg rcvMsg;
	int msg_type;
	waitMessage = 1;
	//pthread_detach(pthread_self());
	while(waitMessage)
	{
		memset(&rcvMsg,0,sizeof(rcvMsg));
		if(msgrcv(msgid,&rcvMsg,sizeof(myMsg),0,0) == -1)
		{
			perror("msgrcv failed errno");
		}
		msg_type  = rcvMsg.type;
		switch(msg_type)
		{
		case 1:
			printf("msgProc accept\n");
			connectEstablished();//˽��ģʽ����ConnectionAcceptted��صĲ������������������ʵ�֡�
			break;
		case 2:
			printf("msgProc close\n");
			connectClose();//˽��ģʽ����ConnectionClosed��صĲ����������������ʵ�֡�
			break;
		case 3:
			printf("msgProc start pop data\n");//��������˽��ģʽ�µ�APP�Խ���Ƶ�߳�
			if (pidP2PRecvAudioProc == NULL)
			{
				pthread_create(&pidP2PRecvAudioProc,NULL,recvAudioData,NULL);
			}

			break;
		case 4:
			//�������Զ�����Ϣ
			printf("msgProc pop message\n");
			printf("custom message:%s\n",rcvMsg.buffer);
			break;
		case 5:
			{
				//�豸����ģʽ����
				printf("msgProc config\n");
				int type = rcvMsg.buffer[4];
				pthread_mutex_lock(&cam_config.mutex);
				//cam_config.bitrate = rcvMsg.buffer[0];//˽��Э�����ֻ�APP�˷����ı���ƽ̨�����ŷ���"ConnectionClosed"��"ConnectionAcceptted"����
				if(cam_config.type != type)
				{
					switch(type)
					{
					case 0:
						cam_config.trans_config.publicLiveFlag = 0;
						cam_config.trans_config.isRecording = 0;
						cam_config.trans_config.rtmpOpenFlag = 0;
						break;
					case 2:
						cam_config.trans_config.publicLiveFlag = 1;
						cam_config.trans_config.isRecording = 0;
						cam_config.trans_config.rtmpOpenFlag = 1;
						break;
					case 3:
						cam_config.trans_config.publicLiveFlag = 0;
						cam_config.trans_config.isRecording = 1;
						cam_config.trans_config.rtmpOpenFlag = 1;
						break;
					case 4:
						cam_config.trans_config.publicLiveFlag = 1;
						cam_config.trans_config.isRecording = 1;
						cam_config.trans_config.rtmpOpenFlag = 1;
						break;
					default:
						break;
					}
					cam_config.audioFlag = rcvMsg.buffer[1];
					cam_config.bitrate = rcvMsg.buffer[0];
					cam_config.type = type;
					cam_config.typeChanged = 1;
					pthread_cond_broadcast(&cam_config.cond);
					pthread_mutex_unlock(&cam_config.mutex);
					break;
				}
				if(cam_config.audioFlag != rcvMsg.buffer[1])
				{
					cam_config.audioFlag = rcvMsg.buffer[1];
					pushAudioing = cam_config.audioFlag;
					printf("audioFlag change,audioFlag = %d\n",cam_config.audioFlag);
					//pthread_cond_signal(&cam_config.audioCond);
					//������������أ�������������Ƶ������ǹرգ��ڷ�����Ƶ�̴߳���
					if(pushAudioing && isCaptureOpen)//isCaptureOpen��ֹ˽��Э��û����������ͷ��ʱ��������ÿ����������߳�
					{
						if(pthread_create(&pidPushAudio,NULL,pushAudioFlowProc,NULL) != 0)
						{
							printf("\033[31mstart audio thread failed\n\033[0m");
						}
					}
				}
				if(cam_config.bitrate != rcvMsg.buffer[0])
				{
					//APP���޸���Ƶ����,ʵ�������޸��߼���bitrate��ֵ,1:1M,2:500K,3:300K
					//�Ƽ�����ʽ�ǲ��Ͽ�ԭ�����������ӡ�
					printf("bitrate changed,new bitrate=%d\n",cam_config.bitrate);
				}
				pthread_mutex_unlock(&cam_config.mutex);
				break;
			}
		default:
			printf("other msg,not support\n");
			break;
		}
	}
}

void* configChangeProc(void* arg)
{
	int ret = 0; 
	while(working)
	{
		pthread_mutex_lock(&cam_config.mutex);
		while(cam_config.typeChanged == 0)
		{
			ret = pthread_cond_wait(&cam_config.cond,&cam_config.mutex);
			if(ret != 0)
			{
				printf("cond wait failed\n");
				pthread_mutex_unlock(&cam_config.mutex);
				return NULL;
			}

		} 
		if( isCaptureOpen )
		{
			closeCapture();
		}
		Disconnect();
		if( cam_config.trans_config.rtmpOpenFlag )
		{ 
			while(1)
			{
				ret = ConnectToServer(cam_config.type,rtmpData);//����ģʽ�ı䣬���µĹ���ģʽ���ӵ�rtmp������
				//int ConnectToServerEx(const char*,int , char,RTMPMetaData);
				//ret = ConnectToServerEx("192.168.2.113",1935,"rtmp5.public.topvdn.cn",cam_config.type,rtmpData);
				if(ret != 0)
				{
					usleep(1000);
					continue;
				}
				break;
			}
			//SetDropBufferTimeOnReconnect(5);
			if(!isCaptureOpen) 
				openCapture();
		}
		cam_config.typeChanged = 0;
		pthread_mutex_unlock(&cam_config.mutex);
		printf("work mode changed success\n");
	}
	if(isCaptureOpen)
		closeCapture(); 
	if(cam_config.trans_config.rtmpOpenFlag)
		Disconnect();
}

static void signalproc(int signo)
{
	printf("signal num:%d\n",signo);
}


int main(int argc,char** argv)
{
	if(argc < 4)
	{
		printf("Usage:%s <hashid> <sn> <videoFileName> [audioFileName]\n",argv[0]);
		return 0;
	}
	int ret;
	videoName = argv[3];
	audioName = argv[4];
	pthread_t pid_rtmp = NULL;
	pthread_t pid_msgProc = NULL;
	signal(SIGPIPE,signalproc);//����SIGPIPE�źţ�����Ҫ

	deviceConfigInit(&cam_config);//��ʼ��������ؽṹ��
	do 
	{
		//������Ϣ���д�����ƽ̨����������Ϣ
		if((msgid = createMsgId('h')) != -1)
		{
			if(pthread_create(&pid_msgProc,NULL,msgProc,NULL) != 0)
			{
				//ʧ��������Ӧƽ̨����Ϣ���˳�����
				printf("create msgProc thread failed\n");
				break;
			}
		}

		//��������ģʽ���Ĵ����߳�
		ret = pthread_create(&pid_rtmp,NULL,configChangeProc,NULL);
		if(ret != 0)
		{
			printf("start configChangeProc thread failed\n");//�����߳�ʧ�ܽ�������Ӧ����ģʽ�ı䴦��
		}

		while(1)
		{
			//������ƽ̨���񣬲�ע����Ϣ�ص�����,���ô˺���֮����ܵ�����ƽ̨����������
			ret = StartCloudService("Test", argv[2], argv[1], NULL, PopMessage);
			if(ret == 0)//����0��ʾ�����ɹ�
			{
				break;
			} 
			printf("StartCloudService failed!  ret = %d  retry...\n",ret );
			sleep(1); 
		}

		D_SetRtmpCallBack(NULL,rtmp_dataCallBack);//����rtmp���ݻص�����

		while(1)
		{
			sleep(3);
		}
	} while (0);


	printf("clean app\n");
	myMsg tmp = {100,"cancel"};
	waitMessage = 0;
	if(msgsnd(msgid,&tmp,sizeof(myMsg),0) != 0)//ʹ�÷�������ʽ������Ϣ
	{
		perror("send cancel msg failed");
	}
	pthread_join(pid_msgProc,NULL);
	printf("join msgProc success\n");
	working = 0;
	cam_config.typeChanged = 1;
	pthread_cond_broadcast(&cam_config.cond);
	pthread_join(pid_rtmp,NULL);
	printf("join configChanged success\n");
	p2pRecvAudioFlag = 0;
	if(pidP2PRecvAudioProc)
		pthread_join(pidP2PRecvAudioProc,NULL);
	if(msgctl(msgid,IPC_RMID,0))//ɾ���ں˵���Ϣ����
	{
		printf("remove msg_que failed\n");
	}
	//���ô˽ӿڹر���ƽ̨�����ˣ���ƽ̨�����ӿڵ���ʧЧ��
	StopCloudService();

	printf("app exit\n");
	return 0;

}