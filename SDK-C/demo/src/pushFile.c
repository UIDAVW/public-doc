#ifdef __cplusplus
extern "C"{
#endif

#include "aacUtil.h"
#include "h264Util.h"
#include "transportMedia.h"
#ifdef QSTP
#include "lingyang/LYQstpAPI.h"
#elif defined(LY_PLATFORM)
#include "lingyang/LYPlatformAPI.h"
#endif

static int loopPush = 1;//�Ƿ�ѭ������

//����Ƶ����H264ѹ����ʽ��
void* pushVideoFlowProc(void* arg)
{
	if(arg == NULL)
	{
		printf("!!!error,thread arg is NULL\n");
		return;
	}
	int fd = *(int*)arg;
	transportChannel* channel = getChannel(fd);
	if(channel == NULL)
	{
		printf("no such channel\n");
		return;
	}
	extern char* videoName;//��main.c�ж���
	int ret;
	unsigned long long time_gap = 66000;//66������
	unsigned long long last_time = 0;
	unsigned long long now = 0;
	unsigned long long timeStamp = 0;
	unsigned long long st = 0;
	int lastTimeCost = 0;
	int frameNum = 0;
	h264Helper helper;
	if(h264HelperInit(&helper,videoName) != 0)
	{
		printf("init h264 helper faield\n");
		return;
	}
	printf("start to push video,videoName=%s,bufferSize=%d,fd=%d\n",videoName,helper.bufferSize,fd);
	timeStamp = getMSec();
	MediaFrame_t frame = {0};
	while (channel->pushVideoing)
	{
		if(helper.sendDoneFlag == 0)
		{
			now = getMSec();
			if(getH264Frame(&helper) == 0)
			{
				timeStamp = now;
				frame.frameType = helper.naluType;//֡���Ͳο�common_define.h
				frame.frameBuffer = helper.data;
				frame.frameLength = helper.frameSize;
				frame.frameTime = timeStamp;
#ifdef QSTP
				ret = LY_sendQSTPMediaFrame(fd,&frame);
#elif defined(LY_PLATFORM)
				ret = LY_sendMediaFrame(fd,&frame);
#endif
				if(ret != 0)
					printf("send video failed fd=%d nal %d frame ret:%d,frameSize=%d\n",fd,helper.naluType,ret,helper.frameSize);
				//else
				//printf("send success now %llu  nal %d frame size:%d,ret=%d\n",now,helper.naluType,helper.frameSize,ret);
			}
			last_time = getMSec();
			st = (last_time - now);
			if(st < time_gap)
				usleep(time_gap - st);//ʵʱ������һ֡��һ֡���ɣ�����sleep
			else
				printf("get frame and send cost time=%llu,now=%llu,last_time=%llu\n",st,now,last_time);
		}
		else if(helper.readFileEof)
		{
			if(loopPush)//ѭ����¼��
			{
				printf("push video file again\n");
				fseek(helper.fp,0,SEEK_SET);
				helper.frameSize = 0;
				helper.offset = 0;
				helper.readFileEof = 0;
				helper.sendDoneFlag = 0;
				helper.naluType = 0;
			}
			else
			{
				channel->pushVideoing = 0;
			}
		}
	}
	h264HelperFree(&helper);
	printf("stop push video,thread exit\n");
}

//����Ƶ����AACѹ����ʽ��
void* pushAudioFlowProc(void* arg)
{
	if(arg == NULL)
	{
		printf("!!!error,thread arg is NULL\n");
		return;
	}
	int fd = *(int*)arg;
	transportChannel* channel = getChannel(fd);
	if(channel == NULL)
	{
		printf("no such channel\n");
		return;
	}
	extern char* audioName;//��main.c�ж���
	int ret;
	AACHelper aacHelper;
	char aacData[AAC_BUFFER] = {0};
	int aacLen = AAC_BUFFER;

	unsigned long long time_gap = 142000;
	unsigned long long last_time = 0;
	unsigned long long now = 0;
	unsigned long long st = 0;
	char sendAACConfig = 0;

	if(initAACHelper(&aacHelper,audioName) != 0)
	{
		printf("init aac helper failed\n");
		return;
	}
	MediaFrame_t frame = {0};
	printf("start to push audio,audioName=%s,bufferSize=%d,fd=%d,ch->fd=%d\n",audioName,aacHelper.buffer_size,fd,channel->fd);
	while (channel->pushAudioing)
	{
		aacLen = AAC_BUFFER;
		ret = getAACFrame(&aacHelper,aacData,&aacLen);
		if(ret == 0)
		{
			now = getMSec();
			frame.frameBuffer = aacData;
			frame.frameLength = aacLen;
			frame.frameTime = now;
			frame.frameType = AAC_TYPE_SAMPLE;//��Ƶ����
#ifdef QSTP
			ret = LY_sendQSTPMediaFrame(fd,&frame);
#elif defined(LY_PLATFORM)
			ret = LY_sendMediaFrame(fd,&frame);
#endif
			if(ret != 0)
				printf("send audio failed fd=%d ret:%d\n",fd,ret);
			last_time = getMSec();
			st = time_gap - (last_time - now);
			if(st < 142000)
			{
				usleep(st);//ʵʱ������һ֡��һ֡���ɣ�����sleep
			}
		}
		else if(aacHelper.readFileEof)
		{
			if(loopPush)
			{
				printf("push audio file again\n");
				fseek(aacHelper.fp,0,SEEK_SET);
				aacHelper.offset = 0;
				aacHelper.readFileEof = 0;
			}
			else
			{
				channel->pushAudioing = 0;
			}
		}
	}
	freeAACHelper(&aacHelper);
	printf("stop push audio\n");
	return 0;
}

//�طŶԽ���Ƶ�߳�
void* playBackAudioProc(void* arg)
{
	if(arg == NULL)
	{
		printf("!!!error,thread arg is NULL\n");
		return;
	}
	int fd = *(int*)arg;
	transportChannel* channel = getChannel(fd);
	if(channel == NULL)
	{
		printf("no such channel\n");
		return;
	}
	MediaFrame_t frame = {0};
	frame.frameBuffer = (char*)malloc(RECV_AUDIO_BUF_SIZE);
	if(frame.frameBuffer == NULL)
	{
		printf("play back audio proc malloc buffer failed\n");
		return;
	}
	while (channel->playBacking)
	{
		frame.frameLength = RECV_AUDIO_BUF_SIZE;//�����ճ���,��������ʱ����ʵ�����ݳ���
		if(popFrameFromQue(channel->playBackBufHandle,frame.frameBuffer,&frame.frameLength,frame.frameTime,frame.frameType,1) != 0)
		{
			//�Ӷ�����pop����ʧ��
			printf("pop data failed\n");
			usleep(1000*200);
			continue;
		}
		printf("fd =%d recv audio frame len=%u\n",channel->fd,frame.frameLength);
		//����ʵ�ֲ����߼�
	}
	printf("playBackAudioProc thread exit\n");
}

#ifdef __cplusplus
};
#endif