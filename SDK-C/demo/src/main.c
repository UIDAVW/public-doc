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

//相关宏在Makefile中定义
#include "transportMedia.h"

//头文件包含
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
/*********************平台相关**************************/

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
	int publicLiveFlag;//直播开关，device设置为直播则为1，否则为0
	int isRecording;//云存储开关，device打开云存储为1，否则为0
	int qstpOpenFlag;//qstp开关，打开云存储或者直播为1，否则为0
}tranportConfig;

typedef struct _config
{
	int type;//设备端配置类型。0:qsup协议，2:qstp协议直播，3:云存储，4:qstp直播带云存储,//5:qstp协议非公众不带云存储
	int audioFlag;
	int bitrate;//传输码率。1:1M,2:500K,3:300K。
	int typeChanged;//标识设备端设置是否改变，在手机端改变配置后，会在popMessage回调函数中设置为1；
	int fds[MAX_CHANNEL];
	int curWorkChannelCount;
	int pushing;
	tranportConfig trans_config;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}deviceConfig;
deviceConfig endPointConfig;
/*********************平台相关—end**************************/
//初始化相关参数
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

//手机端与设备端的连接建立
int connectEstablished()
{
	int fd = -1;
	if(endPointConfig.curWorkChannelCount <= MAX_CHANNEL)
	{
		if(!endPointConfig.pushing)
		{
			endPointConfig.fds[0] = 0;//QSUP协议使用默认使用0
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

//手机端与设备端的连接关闭。
void connectClose()
{
	if(endPointConfig.pushing == 1 && !endPointConfig.trans_config.qstpOpenFlag)
	{
		stopPushMedia(endPointConfig.fds[0]);
		endPointConfig.pushing = 0;
	}
}


//这里使用将接收到的消息发送到专门处理消息的线程，避免阻塞平台。
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
#if 0
		//接收到第三方自定义消息,第三方厂商自己解析数据格式
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
			result = 0;//注意要清0
			sscanf(cfg+i*2,"%02X",&result);
			config[i] = result & 0xFF;
		}
		printf("====================get msg=%s\n",config);
		memcpy(tmpMsg.buffer,config,msgLen);//此处避免使用strcpy
#else
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
#endif
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
		if(msgsnd(workFlag.msgid,&tmpMsg,sizeof(myMsg),IPC_NOWAIT) != 0)//使用非阻塞方式发送消息
		{
			perror("send msg failed");
		}
	}
	if(root)
		cJSON_Delete(root);//不可使用free函数释放root,否则造成内存泄露
}

//处理平台发送过来的消息
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
			connectEstablished();//QSUP协议私有模式。和ConnectionAcceptted相关的操作都在这个函数里面实现。
			break;
		case 2:
			printf("msgProc close\n");
			connectClose();//QSUP私有模式。和ConnectionClosed相关的操作在这个函数里面实现。
			break;
		case 3:
			printf("msgProc start pop data\n");//开启接收私有模式下的APP对讲音频线程
			startRecvAudio(endPointConfig.fds[0]);
			break;
		case 4:
			//第三方自定义消息
			printf("msgProc pop message\n");
			printf("custom message:%s\n",rcvMsg.buffer);
			break;
		case 5:
			{
				//设备工作模式配置
				int type = rcvMsg.buffer[4];
				printf("msgProc config,type=%d\n",type);
				pthread_mutex_lock(&endPointConfig.mutex);
				//cam_config.bitrate = rcvMsg.buffer[0];//私有协议在手机APP端发生改变云平台紧接着发送"ConnectionClosed"和"ConnectionAcceptted"命令
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
					//APP端修改视频码率,实现码率修改逻辑。bitrate数值,1:1M,2:500K,3:300K
					//推荐处理方式是不断开原来的推流连接。
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

//处理工作模式改变
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
		LY_disconnect(endPointConfig.fds[0]);//这里的fd是在调用LY_connect函数创建连接时的返回值，传输通道的唯一标识
		if( endPointConfig.trans_config.qstpOpenFlag )//使用qstp协议发送
		{
			while(1)
			{
				//ip和端口为0时表示使用羚羊云按照一定算法调度的最优推流服务器，若需要指定服务器IP,可在url中指定服务器IP
				char* url = "topvdn://0.0.0.0:0?protocolType=2&connectType=1&token=537067556_3222536192_1493481600_f0399b369aa760362ac4edd224bae23b&mode=2";
				fd = LY_connect(url,NULL);//连接推流服务器，返回标识传输通道的fd,发送数据需要依赖这个fd
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

	if(workFlag.msgid == -1)//防止多次调用
	{
		deviceConfigInit(&endPointConfig);//初始化配置相关结构体

		//创建消息队列处理以平台发过来的消息
		if((workFlag.msgid = createMsgId('h')) != -1)
		{
			if(pthread_create(&workFlag.pidMsgProc,NULL,msgProc,NULL) != 0)
			{
				//失败则不能响应平台的消息，应该退出程序
				printf("create msgProc thread failed\n");
				return -1;
			}
		}

		//创建工作模式更改处理线程
		ret = pthread_create(&workFlag.pidWork,NULL,configChangeProc,NULL);
		if(ret != 0)
		{
			printf("start configChangeProc thread failed\n");//创建线程失败将不能响应工作模式改变处理
		}

		while(1)
		{
			//开启云平台服务，并注册消息回调函数,调用此函数之后才能调用云平台的其他函数，第四个参数为对接厂商自定义数据，没有则不填
			ret = LY_startCloudService(token,configStr,popMessage,NULL);
			if(ret == 0)//返回0表示开启成功
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
	if(msgsnd(workFlag.msgid,&tmp,sizeof(myMsg),0) != 0)//使用非阻塞方式发送消息
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
	if(msgctl(workFlag.msgid,IPC_RMID,0))//删除内核的消息队列
	{
		printf("remove msg_que failed\n");
	}
	//step4.调用此接口关闭云平台，至此，云平台其他接口调用失效。
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
	signal(SIGPIPE,signalproc);//忽略SIGPIPE信号，必须要
#ifdef QSTP //===========================只包含QSTP部分=============================================================
	int isPushAudio = 0;
	//第三方友商首先需要向后台服务器获取token和推流服务器IP、端口，然后组成连接url；若需要指定推流服务器，则在url ip和端口字段指定推流服务器ip和端口
	//使用羚羊调度的推流服务器推流url示例：
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
//======================================包含云平台====================================================//
#elif defined(LY_PLATFORM)
	if(argc < 2)
	{
		printf("Usage:%s <videoFileName> [audioFileName]\n",argv[0]);
		return -1;
	}
	videoName = argv[1];
	if(argc > 2)
		audioName = argv[2];
	//step1.向后台获取token和configString,第三方对接厂商，这里按照自己业务逻辑实现。
	//羚羊示例：
	char* deviceToken = "537067556_3222536192_1493481600_f0399b369aa760362ac4edd224bae23b";
	char* configStr = "[Config]\r\nIsDebug=0\r\nLocalBasePort=8200\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nU \
					  dpSendInterval=2\r\nConnectTimeout=10000\r\nTransferTimeout=10000\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80 \
					  \r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n[LogServer]\r\nCount=1\r\nIP1=120.26.74.53\r\nPort1=80\r\n";
	
	//step2.启动羚羊云服务
	ret = startLyCloudService(deviceToken,configStr);
	if(ret != 0)
	{
		printf("!!!start ly cloud service failed\n");
		return 0;
	}
	
	//step3.根据羚羊云的回调消息实现自己的业务逻辑
#if 1
	//这里是因为没有和后台服务器交互，模拟后台服务器的消息
	sleep(3);
	pthread_mutex_lock(&endPointConfig.mutex);
	endPointConfig.audioFlag = 1;//音频开关
	endPointConfig.type = 2;//工作模式
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
	//step4.停止羚羊云服务
	stopLyCloudService();
#endif
	printf("app exit\n");
	return 0;
}
