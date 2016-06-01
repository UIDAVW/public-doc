#ifndef __TRANSPORT_MEDIA_H__
#define __TRANSPORT_MEDIA_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifndef QSTP_BASE_FD_VALUE
#define QSTP_BASE_FD_VALUE 200 //QSTPЭ��ʹ�õ�fdΪ200��ʼ��
#endif
#define RECV_AUDIO_BUF_SIZE 128*1024 //������Ƶ���ݻ�������С

#define MAX_CHANNEL 10
typedef struct _transportChannel
{
	int fd;//��Ӧ����ͨ����fd
	int isAudioOpen;
	int pushVideoing;//����Ƶ����־λ
	int pushAudioing;//����Ƶ����־λ
	int recvAudioing;//���նԽ���Ƶ��־λ
	int playBacking;//������Ƶ�̱߳�־λ
	pthread_t pidPushVideo;//����Ƶ���߳�id
	pthread_t pidPushAudio;//����Ƶ���߳�id
	pthread_t pidRecvAudioing;//���նԽ���Ƶ���߳�id
	pthread_t pidPlayBacking;//������Ƶ���߳�id
	void*	playBackBufHandle;//������Ƶ������о��
}transportChannel;

transportChannel* getChannel(int fd);

//��ʼһ��ͨ��������
int startPushMedia(int fd,int isPushAudio);

//ֹͣһ��ͨ����������ֹͣ������ر�ͨ������Ӧ�Ľ������ݲ���Ҳ��ر�
void stopPushMedia(int fd);

//��������Ƶ����һ�����豸�տ�ʼֻ����Ƶ��Ȼ��ͨ��app���ô���Ƶ���أ�Ȼ��ʼ����Ƶ��
int startPushAudio(int fd);

//ֹͣ����Ƶ����һ��ͨ��APP�˵���Ƶ�������ã����Թر���Ƶ��������
void stopPushAudio(int fd);

//��ʼ����ƽ̨���͹��������ݣ�������Ƶ��������
int startRecvAudio(int fd);



#ifdef __cplusplus
}
#endif

#endif