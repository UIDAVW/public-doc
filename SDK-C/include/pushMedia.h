#ifndef __PUSH_MEDIA_H__
#define __PUSH_MEDIA_H__

#ifdef __cplusplus
extern "C"{
#endif

//����Ƶ��(h264)
void* pushVideoFlowProc(void* arg);

//����Ƶ��(AAC)
void* pushAudioFlowProc(void* arg);

#ifdef __cplusplus
}
#endif

#endif