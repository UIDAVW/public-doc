#羚羊云C API手册-数据类型

##1 返回值
```
#define LY_SUCCESS 0//操作成功
#define LY_FAILED -1//操作失败
```

##2 服务器信息
```
typedef struct ServerInfo
{
	unsigned char server_ip[32];//服务器IP，点分十进制格式字符串
	unsigned int  server_port;//服务器端口
	unsigned char extradata[256];//服务器拓展信息
}ServerInfo_t;
```

##3 多媒体帧信息
```
typedef struct
{
    unsigned long      capacitySize; /*多媒体帧缓冲区大小*/
    unsigned char      frameType;   /*多媒体帧类型*/
    unsigned char      frameBuffer; /*多媒体帧缓冲区地址*/
    unsigned long      frameLength; /*多媒体帧长度*/
    unsigned long long frameTime;   /*多媒体帧时间戳*/
}MediaFrame_t;
```

##4 多媒体帧类型
```
/*多媒体帧类型*/
typedef enum {
	NALU_TYPE_SLICE = 1,//H264 P帧
	NALU_TYPE_DPA = 2,
	NALU_TYPE_DPB = 3,
	NALU_TYPE_DPC = 4,
	NALU_TYPE_IDR = 5,//H264 I帧
	NALU_TYPE_SEI = 6,//H264 SEI
	NALU_TYPE_SPS = 7,//H264 SPS
	NALU_TYPE_PPS = 8,//H264 PPS帧
	NALU_TYPE_AUD = 9,
	NALU_TYPE_EOSEQ = 10,
	NALU_TYPE_EOSTREAM = 11,
	NALU_TYPE_FILL = 12,
	NALU_TYPE_PREFIX = 14,
	NALU_TYPE_SUB_SPS = 15,
	NALU_TYPE_SLC_EXT = 20,
	NALU_TYPE_VDRD = 24,
	OPUS_TYPE_SAMPLE = 127,//OPUS音频帧
	AAC_TYPE_INFO = 128,//AAC音频配置信息
	AAC_TYPE_SAMPLE = 129//AAC音频帧数据
} FrameSampleType_Em;
```

##5 客户端状态枚举类型
```
typedef enum {
	CLIENT_STATUS_CODE_READY              =     1,      //初始状态
	CLIENT_STATUS_CODE_REQUEST_RELAY      =     2,      //正在请求转发
	CLIENT_STATUS_CODE_CONNECTING         =     3,      //正在连接中
	CLIENT_STATUS_CODE_WORKING            =     4,      //正在直播
	CLIENT_STATUS_CODE_STOPING            =     5,      //停止过程中
	CLIENT_STATUS_CODE_ERROR              =     255     //异常状态
} ClientStatus_Em;
```
