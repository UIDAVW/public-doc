#include <pthread.h>
#include "aacUtil.h"
#include "h264Util.h"
#include "lyUtils.h"

#ifdef __cplusplus
extern "C"{
#endif

static int loopPush = 1;
static pthread_mutex_t avMutex = PTHREAD_MUTEX_INITIALIZER;

	//推视频流(h264)
void* pushVideoFlowProc(void* arg)
{
	extern int pushVideoing;
	extern char* videoName;
	int ret;
	unsigned long long time_gap = 66000;//66毫秒间隔
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
	pushVideoing = 1;
	printf("start to push video,videoName=%s,bufferSize=%d\n",videoName,helper.bufferSize);
	timeStamp = getUSec();
	while (pushVideoing)
	{
		if(helper.sendDoneFlag == 0)
		{
			now = getUSec();
			if(getH264Frame(&helper) == 0)
			{
				//pthread_mutex_lock(&avMutex);
				timeStamp = now;
				//printf("get frameNum:%3d,type:%d,frameSize:%5d\n",frameNum++,helper.naluType,helper.frameSize);
				ret = PushData(0,helper.data,helper.frameSize,timeStamp,helper.naluType);
				if(ret != 0)
					printf("send video failed nal %d frame ret:%d,frameSize=%d\n",helper.naluType,ret,helper.frameSize);
				//else
					//printf("send success now %llu  nal %d frame size:%d,ret=%d\n",now,helper.naluType,helper.frameSize,ret);
				//pthread_mutex_unlock(&avMutex);
			}
			last_time = getUSec();
			st = (last_time - now);
			if(st < time_gap)
				usleep(time_gap - st);//实时流出来一帧推一帧即可，无需sleep
			else
				printf("get frame and send cost time=%llu,now=%llu,last_time=%llu\n",st,now,last_time);
		}
		else if(helper.readFileEof)
		{
			if(loopPush)//循环推录像
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
				pushVideoing = 0;
			}
		}
	}
	h264HelperFree(&helper);
	printf("stop push video\n");
}

//推音频流(AAC)
void* pushAudioFlowProc(void* arg)
{
	extern int pushAudioing;
	extern char* audioName;
	int ret;
	AACHelper aacHelper;
	char aacData[AAC_BUFFER] = {0};
	int aacLen = AAC_BUFFER;

	unsigned long long time_gap = 142000;
	unsigned long long last_time = 0;
	unsigned long long now = 0;
	unsigned long long st = 0;
	char sendAACConfig = 0;

	initAACHelper(&aacHelper,audioName);
	pushAudioing = 1;
	printf("start to push audio,audioName=%s,bufferSize=%d\n",audioName,aacHelper.buffer_size);
	while (pushAudioing)
	{
		aacLen = AAC_BUFFER;
		ret = getAACFrame(&aacHelper,aacData,&aacLen);
		if(ret == 0)
		{
			//pthread_mutex_lock(&avMutex);
			now = getUSec();
			if(sendAACConfig == 0)
			{
				ret = PushData(0,aacHelper.config,2,now,129);
				if(ret != 0)
				{
					printf("send aac config failed,audio can't play\n");
				}
				else
				{
					printf("push aacConfig success\n");
					sendAACConfig = 1;
				}
			}
			ret = PushData(0,aacData,aacLen,now,129);
			if(ret != 0)
				printf("send audio failed ret:%d\n",ret);
			last_time = getUSec();
			//pthread_mutex_unlock(&avMutex);
			st = time_gap - (last_time - now);
			//printf("should sleep st = %llu\n",st);
			if(st < 142000)
				usleep(st);//实时流出来一帧推一帧即可，无需sleep
		}
		else if(aacHelper.readFileEof)
		{
			if(loopPush)
			{
				printf("push audio file again\n");
				fseek(aacHelper.fp,0,SEEK_SET);
				//aacHelper.frameSize = 0;
				aacHelper.offset = 0;
				aacHelper.readFileEof = 0;
			}
			else
			{
				pushAudioing = 0;
			}
		}
	}
	freeAACHelper(&aacHelper);
	printf("stop push audio\n");
	return 0;
}

#ifdef __cplusplus
}
#endif