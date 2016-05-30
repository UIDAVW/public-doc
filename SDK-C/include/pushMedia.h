#ifndef __PUSH_MEDIA_H__
#define __PUSH_MEDIA_H__

#ifdef __cplusplus
extern "C"{
#endif

//推视频流(h264)
void* pushVideoFlowProc(void* arg);

//推音频流(AAC)
void* pushAudioFlowProc(void* arg);

#ifdef __cplusplus
}
#endif

#endif