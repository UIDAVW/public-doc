#ifndef __CAMERA_API_H__
#define __CAMERA_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif
    
    
    //���ⷢ����Ϣ�Ļص�������
    //���÷�����յ����ȷ������Ŀ�ʼ��������ʱ �ᷢ����Ϣ֪ͨ��ǵ���PushData���������� json��ʽ��{"Name":"ConnectionAcceptted"}
    //����Ҫֹͣ������ʱ ֹͣ������ json��ʽ��{"Name":"ConnectionClosed"}
    //���÷�����յ�ʱ �Է����͵�ý������ʱ���ᷢ����Ϣ֪ͨ��ǵ���PopData���������� json��ʽ��{"Name":"StartPopData"}
    // ���豸��¼�ɹ��������ñ任ʱ   {"Name":"PopConfig","Message":"HexConfigString(256�ֽ� 512�ַ�)"}
    //���豸�յ�������Ϣʱ          {"Name":"PopMessage","Message":"HexMessageString(�䳤)","SrcID":"���ͷ�ID"}
    //���豸�յ�������Ϣʱ          {"Name":"PopOffLineMessage","Message":"HexMessageString(�䳤)","SrcID":"���ͷ�ID"} 
#if 1   
 
		//��ǰ״̬
		typedef enum {
			CLIENT_STATUS_CODE_READY              =     1,      //��ʼ״̬
			CLIENT_STATUS_CODE_REQUEST_RELAY      =     2,      //��������ת��
			CLIENT_STATUS_CODE_CONNECTING_LIVE    =     3,      //����������
			CLIENT_STATUS_CODE_LIVEING            =     4,      //����ֱ��
			CLIENT_STATUS_CODE_STOPING            =     5,      //ֹͣ������ 
			CLIENT_STATUS_CODE_ERROR              =     255     //�쳣״̬
		} ClientStatusEm;

    
		//����֡����
		typedef enum {
			NALU_TYPE_SLICE = 1,
			NALU_TYPE_DPA = 2,
			NALU_TYPE_DPB = 3,
			NALU_TYPE_DPC = 4,
			NALU_TYPE_IDR = 5,
			NALU_TYPE_SEI = 6,
			NALU_TYPE_SPS = 7,
			NALU_TYPE_PPS = 8,
			NALU_TYPE_AUD = 9,
			NALU_TYPE_EOSEQ = 10,
			NALU_TYPE_EOSTREAM = 11,
			NALU_TYPE_FILL = 12,
			NALU_TYPE_PREFIX = 14,
			NALU_TYPE_SUB_SPS = 15,
			NALU_TYPE_SLC_EXT = 20,
			NALU_TYPE_VDRD = 24,
			AAC_TYPE_INFO = 128,
			AAC_TYPE_SAMPLE = 129
		} FrameSampleTypeEm;

	//RTMP Metadata 
	typedef struct _RTMPMetaData
        {
                double  duration;
                double  width;
                double  height;
                double  videodatarate;
                double  framerate;
                double  videocodecid;
                double  audiodatarate;
                double  audiosamplerate;
                double  audiosamplesize;
                double  stereo;                         //0 for false
                double  audiocodecid;
        }RTMPMetaData;

#endif  
/*******************************************************************************************************
//SKD�½ӿ�,�ð汾�����½ӿں;ɽӿڣ��½ӿں;ɽӿڹ���һ��ֻ��ʹ��ֻ��Ҫѡ������һ������;
//�����ĵ����µĽӿ�Ϊ׼���������ͳһ���½ӿ�Ϊ��׼
*******************************************************************************************************/
    //ƽ̨��Ϣ�ص�����
    typedef int (*MessageCallBack)(void* apData, const char* aMessage);
    //RTMP���ݻص�����(��������Ƶ���ݺͱ���¼����Ϣ) 
    typedef void (*RtmpDataCallBack)(void* apData, char* aDataBuffer, int aDataLength, char aDataType);
 
 	//ע��rtmp���ݻص�(��������Ƶ���ݺͱ���¼����Ϣ),; aDataType: 1 ��Ƶ����; 2:����¼����Ϣ
    void SetRtmpDataCallBack(void *apData, RtmpDataCallBack aRtmpDataCallBack); 

	//
	char *DeviceRegister(const char *aAppID, const char *aUID, const char *aDeviceSN);
	//return: hashid --- success, NULL --- failed

    //��ʼ�Ʒ��� ���յ�������    ƽ̨��Ϣ�ص�����
    int StartCloudService(const char* aAppID, const char* aDeviceSN, const char* aCid, void* apData, MessageCallBack apMessageCallBack);
    //return: 0---success ; -1 --failed 

	int  StartCloudServiceEx(const char* aDeviceToken, const char* aConfigString, void *apData, MessageCallBack apMessageCallBack); 
 
    //ֹͣ�Ʒ���
    void StopCloudService();

    //��ȡ�豸״̬
    //�汾��version,��¼״̬login,����״̬online,�������SendLostCount(ÿ�����ݰ�����1k������)
    char* GetDeviceStatus();

	//get socket sending buffer(SIOCOUTQ)
	long GetSocketSendCountQueue();

    //��ȡ��ǰ��ƽ̨�汾��(platform version)
    float GetPlatformVersion();
 
    //��ȡ�豸��token���豸token���ڿͻ��˻��ߺ�̨ϵͳ���ʲ������豸�����ڰ�ȫУ��
    int GetDeviceToken(char *apTokenBuffer, unsigned int aBufferLength);
    //return -1 -- failed; token length ----success(56�ַ�)
 
    //���÷�����������Ƶ��������  ���ݲ����� ��ǰ�̶�Ϊ0   ����Ƶ����������  ����Ƶ��������������    64λʱ�����λ΢�루����ʱ�����  ��������h264 NALU_TYPE ���� ��Ƶ����
    int PushData(unsigned long aDataLevelPos, const char *aDataBuffer, unsigned long aBufferLength, unsigned long long aTimeStamp, unsigned char apFrameSampleType);
    //return: 0---success ; other --failed 
    
    //����һ������Ƶ���������� ���ݲ����� ��ǰ�̶�Ϊ0    �������ݳ���   32λʱ��������ʱ�����  �������� h264 NALU_TYPE ���� ��Ƶ����
    char* PopData(unsigned long aDataLevelPos, unsigned long* apFrameSampleLength, unsigned long* apTimestamp, unsigned char* apFrameSampleType);
    //return: DataBuffer ---success ; NULL --failed 
    
    //type	int	��ͼ������ 1: ¼���ͼ��2:�����ͼ��3:�澯��ͼ; aTimeOut:ȱʡĬ�ϳ�ʱ10s 
    int PostPicture(char* aDataBuffer, unsigned long aBufferLength, int aTimeStamp, int aImageType, int aTimeOut);
    //return: 0---success ; other --failed 

	//��Ϣ͸��ͨ�����豸�˷�����Ϣ���ͻ��ˣ�256�ֽڳ��ȶ�������Ϣ�壻
	//aNotifyThirdPartyPlatform ������Ϣ�Ƿ�֪ͨ��������̨ϵͳ��1��֪ͨ��0����֪ͨ��
    int PushMessage(const char* aMessage, unsigned long aMessageLength, int aNotifyThirdPartyPlatform);
    //return: 0---success ; -1 --failed 
     
    //����
    //����rtmp����;aMetaData:rtmpԪ������Ϣ
    // aMode :0�Ǵ��� 1��udp�㲥 2��rtmp�㲥(����) 3��¼��(�ƴ洢) 4��¼��㲥(����+�ƴ洢)
    int ConnectToServer(char aMode, RTMPMetaData aMetaData);
    int ConnectToServerEx(const char *aServerIP, int aPort,const char* aHostName, char aMode, RTMPMetaData aMetadata);
	//return: 0 ---success , -1 --- failed
	
    //�Ͽ�����
    //�ر�rtmp����
    int Disconnect();
    //return: 0---success ; -1 --failed 
    
    //�ϴ��豸���ò���,256�ֽڵ�ƽ̨���ô�
    int SetDeviceConfig(const char* aConfig, unsigned int aConfigLength);
    //return: 0---success ; -1 --failed 

    //�ϴ��豸�Զ������������Ϣ������ͷ�����Եȣ������ݶ�ƽ̨͸����ƽֻ̨�ǽ��б��档
    int SetDeviceInfo(const char* aDataInfo, unsigned int aDataLength);	
    //return: 0---success ; -1 --failed 

	//param: seconds
	void SetDropBufferTimeOnReconnect(int aDropBufferTime);

	//����¼�񱨾�������Ϣ,¼��������Ϣ������rtmp���ݻص������и���
	//���ڿͻ��˲�����ʵʱ���ű���¼��������Ϣ
	char *QueryAlarmRecordInfo(unsigned int *aDataLength);
	//return NULL -- failed	

	//��ȡ��һ�β���״ֵ̬
	int GetLastErrorNo();
 	//return: error no
 
	void SetEncryptKey(char *aEncryptKeyValue,int aEncryptKeyLength, unsigned int aEncryptType);
	
 
/***************************************************************************************
 //�Ͻӿ�
****************************************************************************************/

 // ˽��ֱ����Ϣ�ص����� 
    typedef int (*D_MessageCallBack)(void *apData, const char *aMessage);
    //RTMP��Ϣ�ص����� 
    typedef void (*D_RtmpCallBack)(void *apData, char* aDataBuffer,int aDataLength, char aDataType);

        //ע��rtmp��Ƶ���ݻص�
    void D_SetRtmpCallBack(void *apData,D_RtmpCallBack apRtmpCallBack);

    //��ʼ�Ʒ��� ���յ�������         ini��ʽ�����ô�       ��ʼ�ɼ���ѹ������Ƶ���ݵĻص�����
    //return: 0---success ; other --failed 
	//int  D_StartCloudService(const char* aDeviceToken, const char* aConfigString, void *apData, MessageCallBack apMessageCallBack);
	int D_StartCloudService(const char* aAppID, const char* aDeviceSN, const char* aCid, void* apData, MessageCallBack apMessageCallBack);

    //ֹͣ�Ʒ���
    void  D_StopCloudService();
    //get device status:version,login,online,packet lost count
    char* D_GetStatus();

    //get platform version
    float D_GetPlatformVersion();

    //���÷�����������Ƶ��������  ���ݲ����� ��ǰ�̶�Ϊ0    ����Ƶ����������          ����Ƶ��������������    32λʱ�����λ����  ��������h264
    int   D_PushData(unsigned long aDataLevelPos, const char *aDataBuffer, unsigned long aBufferLength, unsigned long long aTimestamp, unsigned char apFrameSampleType);

    //����һ������Ƶ���������� ���ݲ����� ��ǰ�̶�Ϊ0           �������ݳ���              32λʱ���  �� ������h264 NALU_TYPE ���� ��Ƶ����
    char* D_PopData(unsigned long aDataLevelPos, unsigned long *apFrameSampleLength, unsigned long *apTimestamp, unsigned char *apFrameSampleType);

    //type  int ��ͼ������ 1: ¼���ͼ��2:�����ͼ��3:�澯��ͼ 
    int  D_HttpPostPicture(int timestamp,char* image_buffer, long image_size, int image_type);

    int D_PushMessage(char **aAccessTokens,const char *aMessage, unsigned long aMessageLen, int is_callServer);

    //����
    //����rtmp����;return: 0 ---success , other --- failed
    // Mode :0�Ǵ��� 1��udp�㲥 2��rtmp�㲥 3��¼�� 4��¼��㲥
    int D_StartConnectToServer(char aMode, RTMPMetaData aMetaData);
	int D_StartConnectToServerEx(const char *aServerIP, int aPort, const char *aHostName, char aMode, RTMPMetaData aMetaData);

    //�Ͽ�����
    //�ر�rtmp����
    int D_Disconnect();
	//
	void D_setEncryptKey(char *aEncryptKeyValue,int aEncryptKeyLength, unsigned int aEncryptType);

	char *D_QueryAlarmRecordInfo(unsigned int *aDataLength);
	//return NULL -- failed	

 
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* End of #ifndef __CAMERA_API_H__ */
