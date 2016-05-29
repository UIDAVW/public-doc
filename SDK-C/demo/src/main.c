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

/*********************平台相关**************************/
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
	int publicLiveFlag;//直播开关，device设置为直播则为1，否则为0
	int isRecording;//云存储开关，device打开云存储为1，否则为0
	int rtmpOpenFlag;//rtmp开关，打开云存储或者直播为1，否则为0
}tranportConfig;

typedef struct _config
{
	tranportConfig trans_config;

	int type;//设备端配置类型。0:私有配置，2:公众直播，3:云存储，4:公众带云存储。
	int audioFlag;
	int bitrate;//传输码率。1:1M,2:500K,3:300K。
	int typeChanged;//标识设备端设置是否改变，在手机端开启直播后，会在popMessage回调函数中设置为1；
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	//pthread_cond_t audioCond;
	//pthread_cond_t bitrateCond;
}device_config;
device_config cam_config;

volatile int bitrateChange;
/*********************平台相关—end**************************/

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


//实现开始推流逻辑
int openCapture()
{
	if(!isCaptureOpen)
	{
		pushVideoing = 1;
		//pushVideoFlowProc函数声明在pushMedia.h中
		if(pthread_create(&pidPushVideo,NULL,pushVideoFlowProc,NULL) != 0)
		{
			printf("\033[31mstart audio thread failed\n\033[0m");
		}
		printf("openCapture audioFlag=%d\n",cam_config.audioFlag);
		if(cam_config.audioFlag)//如果打开音频，创建音频线推流程
		{
			pushAudioing = 1;
			//pushAudioFlowProc函数声明在pushMedia.h中
			if(pthread_create(&pidPushAudio,NULL,pushAudioFlowProc,NULL) != 0)
			{
				printf("\033[31mstart audio thread failed\n\033[0m");
			}
		}

		isCaptureOpen = 1;
	}
	return 0;
}

//实现停止推流逻辑
int closeCapture()
{
	if(isCaptureOpen == 1)//避免公众切换成私有(会抛出一个ConnectClose消息)的时候调用两次
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

//手机端与设备端的连接关闭。如果开启了云存储或者公众直播，不能关闭设备端数据的推送。
void connectClose()
{
	if(!cam_config.trans_config.rtmpOpenFlag)
	{
		closeCapture(); 
	}
	if(NULL != pidP2PRecvAudioProc)
	{
		p2pRecvAudioFlag = 0;//停止音频接收数据
		pthread_join(pidP2PRecvAudioProc,NULL);
	}
}

//公众模式的回调函数，可以通过此函数接收音频数据
void rtmp_dataCallBack(void *apData,char* aData,int aLen, char aType)
{
	if(aType == 1)//接收音频数据
	{
		printf("recv aac data len=%d\n",aLen);

	}
	else if(aType == 2)
	{
		printf("recv alarm info\n");
	}
}

//私有模式音频回传
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
		//接收云平台通过羚羊私有协议发送的数据
		frameSampleLength = 0;
		pFrame = PopData(0, &frameSampleLength, &timeStamp, &frameSampleType);//没有数据会阻塞,时间戳为相对时间戳，第一个收到的时间戳为0
		if(frameSampleLength)
		{
			printf("recv audiao data len = %d,timeStamp= %d,type=%d\n",frameSampleLength,timeStamp,frameSampleType);

		}
		free(pFrame);
	}
	printf("p2p recv audio data thread exit\n");
}

//这里使用将接收到的消息发送到专门处理消息的线程，避免阻塞平台。
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
		//私有协议开始推流
		printf("PopMessage ConnectionAcceptted\n");
		tmpMsg.type = 1;
		strcpy(tmpMsg.buffer,"ConnectionAcceptted");
	}
	else if(memcmp("ConnectionClosed",name->valuestring,strlen(name->valuestring)) == 0)
	{
		//私有协议结束推流
		printf("PopMessage ConnectionClosed\n");
		tmpMsg.type = 2;
		strcpy(tmpMsg.buffer , "ConnectionClosed");
	}
	else if(memcmp("StartPopData",name->valuestring,strlen(name->valuestring)) == 0)
	{
		//私有协议开始接收音频回传
		printf("PopMessage StartPopData\n");
		tmpMsg.type = 3;
		strcpy(tmpMsg.buffer , "StartPopData");
	}
	else if(memcmp("PopMessage",name->valuestring,strlen(name->valuestring)) == 0)
	{
		//接收到第三方自定义消息,需要第三方厂商自己解析数据格式
		printf("PopMessage PopMessage\n");
		tmpMsg.type = 4;
		message = cJSON_GetObjectItem(root,"message");
		memcpy(tmpMsg.buffer , message->valuestring,256);//此处避免使用strcpy,message->valuestring就是自定义的消息数据，长度固定为256
	}
	else if(memcmp("PopConfig",name->valuestring,strlen(name->valuestring)) == 0)
	{
		//接收设备配置消息，音频开关，工作模式，视频码率改变等操作
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
		if(config[0] == 0)//APP端解绑设备
		{
			//实现处理设备解绑逻辑
		}
		else
		{
			tmpMsg.type = 5;
		}
		memcpy(tmpMsg.buffer,config,256);//此处不可用strcpy
		printf("msg type = 5,change  config\n");
	}
	if(tmpMsg.type != 0)
	{
		if(msgsnd(msgid,&tmpMsg,sizeof(myMsg),IPC_NOWAIT) != 0)//使用非阻塞方式发送消息
		{
			perror("send msg failed");
		}
	}
	if(root)
		cJSON_Delete(root);//不可使用free函数释放root,否则造成内存泄露
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
			connectEstablished();//私有模式。和ConnectionAcceptted相关的操作都在这个函数里面实现。
			break;
		case 2:
			printf("msgProc close\n");
			connectClose();//私有模式。和ConnectionClosed相关的操作在这个函数里面实现。
			break;
		case 3:
			printf("msgProc start pop data\n");//开启接收私有模式下的APP对讲音频线程
			if (pidP2PRecvAudioProc == NULL)
			{
				pthread_create(&pidP2PRecvAudioProc,NULL,recvAudioData,NULL);
			}

			break;
		case 4:
			//第三方自定义消息
			printf("msgProc pop message\n");
			printf("custom message:%s\n",rcvMsg.buffer);
			break;
		case 5:
			{
				//设备工作模式配置
				printf("msgProc config\n");
				int type = rcvMsg.buffer[4];
				pthread_mutex_lock(&cam_config.mutex);
				//cam_config.bitrate = rcvMsg.buffer[0];//私有协议在手机APP端发生改变云平台紧接着发送"ConnectionClosed"和"ConnectionAcceptted"命令
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
					//如果打开声音开关，则启动发送音频。如果是关闭，在发送音频线程处理。
					if(pushAudioing && isCaptureOpen)//isCaptureOpen防止私有协议没有连接摄像头的时候更改配置开启了声音线程
					{
						if(pthread_create(&pidPushAudio,NULL,pushAudioFlowProc,NULL) != 0)
						{
							printf("\033[31mstart audio thread failed\n\033[0m");
						}
					}
				}
				if(cam_config.bitrate != rcvMsg.buffer[0])
				{
					//APP端修改视频码率,实现码率修改逻辑。bitrate数值,1:1M,2:500K,3:300K
					//推荐处理方式是不断开原来的推流连接。
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
				ret = ConnectToServer(cam_config.type,rtmpData);//工作模式改变，以新的工作模式连接到rtmp服务器
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
	signal(SIGPIPE,signalproc);//忽略SIGPIPE信号，必须要

	deviceConfigInit(&cam_config);//初始化配置相关结构体
	do 
	{
		//创建消息队列处理以平台发过来的消息
		if((msgid = createMsgId('h')) != -1)
		{
			if(pthread_create(&pid_msgProc,NULL,msgProc,NULL) != 0)
			{
				//失败则不能响应平台的消息，退出程序
				printf("create msgProc thread failed\n");
				break;
			}
		}

		//创建工作模式更改处理线程
		ret = pthread_create(&pid_rtmp,NULL,configChangeProc,NULL);
		if(ret != 0)
		{
			printf("start configChangeProc thread failed\n");//创建线程失败将不能响应工作模式改变处理
		}

		while(1)
		{
			//开启云平台服务，并注册消息回调函数,调用此函数之后才能调用云平台的其他函数
			ret = StartCloudService("Test", argv[2], argv[1], NULL, PopMessage);
			if(ret == 0)//返回0表示开启成功
			{
				break;
			} 
			printf("StartCloudService failed!  ret = %d  retry...\n",ret );
			sleep(1); 
		}

		D_SetRtmpCallBack(NULL,rtmp_dataCallBack);//设置rtmp数据回调函数

		while(1)
		{
			sleep(3);
		}
	} while (0);


	printf("clean app\n");
	myMsg tmp = {100,"cancel"};
	waitMessage = 0;
	if(msgsnd(msgid,&tmp,sizeof(myMsg),0) != 0)//使用非阻塞方式发送消息
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
	if(msgctl(msgid,IPC_RMID,0))//删除内核的消息队列
	{
		printf("remove msg_que failed\n");
	}
	//调用此接口关闭云平台，至此，云平台其他接口调用失效。
	StopCloudService();

	printf("app exit\n");
	return 0;

}