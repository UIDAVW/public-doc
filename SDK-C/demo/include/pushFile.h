#ifndef __PUSH_FILE_H__
#define __PUSH_FILE_H__
#endif

#ifdef __cplusplus
extern "C"{
#endif

//����Ƶ����H264ѹ����ʽ��
void* pushVideoFlowProc(void* arg);

//����Ƶ����AACѹ����ʽ��
void* pushAudioFlowProc(void* arg);

//�طŶԽ���Ƶ�߳�
void* playBackAudioProc(void* arg);

#ifdef __cplusplus
}
#endif