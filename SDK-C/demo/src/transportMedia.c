#include <pthread.h>
#include "LYQstpAPI.h"
#include "transportMedia.h"
#include "pushFile.h"


#ifdef __cplusplus
extern "C"{
#endif

	//���ļ���ʵ��һ��Ӧ��������C�ӿ�SDK�Ķ�ͨ���������ݵĿ�ܣ����ڵ��������̿��ٶԽ������ƣ����������̿ɸ����Լ�����������޸ġ�
	//һ�����������ֻ�谴���Լ����߼�����Ƶ������������Ƶ��������������Ƶ�����������߳�ִ�к������ɿ��ٽ��������ƴ�������Ƶ���ݡ�
#ifndef QSTP_BASE_FD_VALUE
#define QSTP_BASE_FD_VALUE 200 //QSTPЭ��ʹ�õ�fdΪ200��ʼ��
#endif
#define RECV_AUDIO_BUF_SIZE 128*1024 //������Ƶ���ݻ�������С
static transportChannel channels[MAX_CHANNEL] = {0};//����ͨ������
static curWorkChannelCount = 0;//��¼��ǰʹ��ͨ����
typedef void (*threadProc)(void* arg);//�̺߳���ָ��

transportChannel* getChannel(int fd)
{
	int i = 0;
	for(;i<MAX_CHANNEL;i++)
	{
		if(channels[i].fd == fd)
		{
			return &channels[i];
		}
	}
	return NULL;
}

//ʵ�ֿ�ʼ�����߼�
int startPushMedia(int fd,int isPushAudio)
{
	if(fd < 0)
	{
		printf("fd must >= 0\n");
		return -1;
	}
	if(curWorkChannelCount >= 10)
	{
		printf("already max channel\n");
		return -1;
	}
	transportChannel* ch = &channels[curWorkChannelCount];
	channels[curWorkChannelCount++].fd = fd;
	if(!ch->pushVideoing)
	{
		ch->fd = fd;
		ch->isAudioOpen = isPushAudio;
		threadProc video,audio;

		video = pushVideoFlowProc; //�˴��滻�Լ��������̺߳���
		audio = pushAudioFlowProc; //�˴��滻�Լ��������̺߳���

		ch->pushVideoing = 1;
		if(pthread_create(&ch->pidPushVideo,NULL,video,&ch->fd) != 0)
		{
			printf("\033[31mstart audio thread failed\n\033[0m");
			return -1;
		}
		if(isPushAudio)
		{
			ch->pushAudioing = 1;
			if(pthread_create(&ch->pidPushAudio,NULL,audio,&ch->fd) != 0)
			{
				printf("\033[31mstart audio thread failed\n\033[0m");
				return -1;
			}
		}

	}
	return 0;
}


//ʵ��ֹͣ�����߼�(ֹͣ������᲻�ܼ�����������)
void stopPushMedia(int fd)
{
	if(fd < 0)
	{
		printf("fd must >= 0\n");
		return -1;
	}
	transportChannel* ch = getChannel(fd);
	if(NULL != ch)
	{
		if(ch->pushVideoing == 1)
		{
			if(ch->pidPushVideo != NULL)
			{
				ch->pushVideoing = 0;
				pthread_join(ch->pidPushVideo,NULL);
				ch->pidPushVideo = NULL;
			}
			if(ch->pushAudioing != NULL)
			{
				ch->pushAudioing = 0;
				pthread_join(ch->pidPushAudio,NULL);
				ch->pidPushAudio = NULL;
			}
			ch->fd = -1;
			ch->isAudioOpen = 0;
		}
		curWorkChannelCount--;
	}
}

//��������Ƶ��������������豸�տ�ʼֻ����Ƶ��������Ƶ����ʱ��ͨ��app���ô���Ƶ���أ�Ȼ��ʼ����Ƶ��
int startPushAudio(int fd)
{
	if(fd < 0)
	{
		printf("fd must >= 0\n");
		return -1;
	}
	transportChannel* ch = getChannel(fd);
	if(NULL != ch)
	{
		if(ch->pushVideoing && ch->pushAudioing == 0)
		{
			ch->isAudioOpen = 1;
			threadProc audio;
			audio = pushAudioFlowProc; //�˴��滻�Լ��������̺߳���
			ch->pushAudioing = 1;
			if(pthread_create(&ch->pidPushAudio,NULL,audio,&ch->fd) != 0)
			{
				printf("\033[31mstart audio thread failed\n\033[0m");
				return -1;
			}
		}
	}
	return 0;
}

//ֹͣ����Ƶ����һ��ͨ��APP�˵���Ƶ�������ã����Թر���Ƶ��������
void stopPushAudio(int fd)
{
	if(fd < 0)
	{
		printf("fd must >= 0\n");
		return -1;
	}
	transportChannel* ch = getChannel(fd);
	if(NULL != ch)
	{
		if(ch->pushAudioing != NULL || ch->pushAudioing == 1)
		{
			ch->pushAudioing = 0;
			pthread_join(ch->pidPushAudio,NULL);
			ch->pidPushAudio = NULL;
			ch->isAudioOpen = 0;
		}
	}
}

//���������ƻش�������
static void* recvDataFromLyCloud(void* arg)
{
	if(arg == NULL)
		return;
	int fd = *(int*)arg;
	int ret = 0;
	char* buf;
	MediaFrame_t frame = {0};
	transportChannel* ch = getChannel(fd);
	if(NULL == ch)
	{
		printf("get channel failed by fd=%d\n",fd);
		return;
	}
	ch->recvAudioing = 1;
	frame.frameBuffer = (char*)malloc(RECV_AUDIO_BUF_SIZE);
	if(frame.frameBuffer == NULL)
	{
		printf("malloc frame buffer failed by fd=%d\n",fd);
		return;
	}
	while(ch->recvAudioing)
	{
#ifdef QSTP
		ret = LY_recvQSTPMediaFrame(fd,&frame);
#elif defined(LY_PLATFORM)
		ret = LY_recvMediaFrame(fd,&frame);
#endif
		if(ret != 0)//�������-1�����ʾ�Ѿ�������LY_disconnect��ȡ���������˳��߳�
		{
			printf("LY_recvMediaFrame failed\n");
			ch->recvAudioing = 0;
			break;
		}
#ifdef PLAYBACK//����лطţ������ｫ����ѹ�����Ŷ�����
		if(ret == 0 && pushFrameToQue(ch->playBackBufHandle,frame.frameBuffer,frame.frameLength,frame.frameTime,AAC_TYPE_SAMPLE) != 0)
		{
			printf("push audio frame to playback failed\n");
		}
#else
		printf("recv audio frame,len=%d\n",frame.frameLength);
#endif
	}
#ifdef PLAYBACK
	//������
	if(ch->pidPlayBacking != NULL || ch->playBacking)
	{
		ch->playBacking = 0;
		cancelQue(ch->playBackBufHandle);//��Ҫ��ȡ�����У����������ס
		pthread_join(ch->pidPlayBacking,NULL);
		ch->pidPlayBacking = NULL;
	}
	destroyQue(ch->playBackBufHandle);
	ch->playBackBufHandle = NULL;
#endif
	printf("recv audio data exit fd=%d\n",fd);
}

int startRecvAudio(int fd)
{
	int ret = 0;
	if(fd < 0)
	{
		printf("fd must >= 0\n");
		return -1;
	}
	transportChannel* ch = getChannel(fd);
	if(NULL != ch)
	{
		if(ch->pidRecvAudioing == NULL)
		{
			if(pthread_create(&ch->pidRecvAudioing,NULL,recvDataFromLyCloud,&ch->fd) != 0)
			{
				printf("\033[31mstart recv data thread failed\n\033[0m");
				return -1;
			}
		}
#ifdef PLAYBACK//�����Ҫ�ط�
		if(ch->playBackBufHandle == NULL)
		{
			//����������Ƶ���ݵĶ��У����˶�������������SDKʵ�֣�����������ֱ��ʹ�ü��ɣ�
			ch->playBackBufHandle = createQue("playBack",NULL,RECV_AUDIO_BUF_SIZE);
			if(ch->playBackBufHandle != NULL)
			{
				threadProc playBackProc = playBackAudioProc;//�˴��滻�Լ��Ļط��̺߳���
				ch->playBacking = 1;
				//�����������ݵ��߳�
				if(pthread_create(&ch->pidPlayBacking,NULL,playBackProc,&ch->fd) != 0)
				{
					printf("create play back thread failed\n");
					ret = -1;
				}
			}
		}
#endif
	}
	return ret;
}

#ifdef __cplusplus
}
#endif