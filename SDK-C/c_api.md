#羚羊云C API手册
##1 数据类型
###1.1 返回值
```
#define LY_SUCCESS 0//操作成功
#define LY_FAILED -1//操作失败
```

###1.2 服务器信息
```
typedef struct ServerInfo
{
	unsigned char server_ip[32];//服务器IP，点分十进制格式字符串
	unsigned int  server_port;//服务器端口
	unsigned char extradata[256];//服务器拓展信息
}ServerInfo_t;
```

###1.3 多媒体帧信息
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

###1.4 多媒体帧类型
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

###1.5 客户端状态枚举类型
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

##2 云服务接口
    
###2.1 启动云服务
```
int	LY_startCloudService(const char* const apToken, const char* const apConfig, const PlatformMessageCallBack apMessageCallBack, void *apUserData);
```
| - | - |
|-------|----|
| 接口名 | LY_startCloudService |
| 功能 | 启动云服务。调用了此api之后,平台相关凭证及资源开始准备，平台的回调消息通过回调函数apMessageCallBack通知调用者，其他接口必须在云服务启动成功之后才能正常使用。 |
| 返回值 | 0表示成功，非0表示失败。 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|apToken|char*|in|必须|设备token，由第三方应用后台生成。|
|apConfig|char*|in|必须|配置串，从第三方应用后台获取。|
|apMessageCallBack|PlatformMessageCallBack|in|必须|平台消息回调函数，该函数用来处理云平台返回的消息|
|apUserData|void*|in|可选|由SDK保存，平台每次调用aPMessageCallBack这个回调函数作为第一个参数传递进去，可传递一些用户自定义信息|
**注意**：

**apToken**：设备token，由应用后台生成，格式：2147549953\_3222536192\_1469999882\_bad3686a62a7aba595df3fb4c9c400e9。

token的内容格式及意义请见[羚羊云token认证机制](http://doc.topvdn.com/api/#!public-doc/token_format.md)

**apConfig**：配置串，从后台获取(无需解析)，格式如下：
[Config]\r\nIsDebug=0\r\nLocalBasePort=8200\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nUdpSendInterval=2\r\nConnectTimeout=10000\r\nTransferTimeout=10000\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n[LogServer]\r\nCount=1\r\nIP1=120.26.74.53\r\nPort1=80\r\n

调用者不必知道该字符串内容所表示的意义。
应用后台调用[Web API的'查询设备状态'接口](http://doc.topvdn.com/api/#!web_api_v2.md#2.1.1_%E6%9F%A5%E8%AF%A2%E8%AE%BE%E5%A4%87%E7%8A%B6%E6%80%81)获取，接口返回的"init_string"字段即配置串。

平台消息回调函数:
```
typedef void (*PlatformMessageCallBack)(void* apUserData, const char* constaMessage);
```
|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|apUserData|void*|in|必须|用户自定义数据，对于羚羊云透明，羚羊云只做保存和传递。|
|aMessage|char*|in|必须|羚羊云的回调数据，cJSON格式，需要解析，解析示例请参照羚羊云C接口DEMO。|

###2.2 停止云服务
```
void LY_stopCloudService();
```
| - | - |
|-------|----|
| 接口名 | LY_stopCloudService |
| 功能 | 调用了此api之后，相应的底层资源完全释放，建议在应用退出的时候调用，节省系统资源； |
| 返回值 | 无 |
| 参数列表 | 无 |

##3 推拉流接口
    
###3.1 建立传输通道
```
int LY_connect (const char *aUrl, const char *aDataSourceInfo)
```
| - | - |
|-------|----|
| 接口名 | LY_connect |
| 功能 | 和交互端（包括手机APP，羚羊云的服务器）建立连接，根据传入的aUrl参数判断类型，建立媒体传输通道。如果是观看录像使用此接口连接服务器，则第二个参数需要传录像磁盘信息；否则传入第二个参数传NULL即可。该函数与 LY_disconnect配套使用。 |
| 返回值 | 大于等于0表示成功，且返回传输通道句柄fd；否则失败 |
| 参数列表 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aUrl|char*|in|必须|目标服务器的url地址，连接类型（推流或拉流），使用的协议等。|
|aDataSourceInfo|char*|in|可选|如果是观看录像时调用，则此参数为必须。此参数内容从羚羊云后台或者第三方厂商后台获取，对调用者透明。|
**注意**：

**aUrl**：连接地址，从后台获取到IP、端口和token，按照如下格式组合：

topvdn://183.57.151.161:1935?protocolType=2&connectType=1&mode=2&token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069

topvdn://ip=%s:port=%d?protocolType=%d&connectType=%d&mode=%u&token=%s&begin=%lu&end=%lu&play=%lu

Url各字段意义及详解请见[羚羊云Url格式解析](http://doc.topvdn.com/api/public-doc/#!url_format.md)

###3.2 断开通道连接
```
int	LY_disconnect(const int aFd);
```
| - | - |
|-------|----|
| 接口名 | LY_disconnect |
| 功能 | 根据传入的fd参数，断开对应传输通道的连接，与 LY_connect配套使用。 |
| 返回值 | 0表示成功，非0表示失败 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aFd|int|in|必须|传输通道句柄|

###3.3 发送媒体帧
```
int	LY_sendMediaFrame(const int aFd, MediaFrame_t * apMediaFrame);
```
| - | - |
|-------|----|
| 接口名 | LY_sendMediaFrame |
| 功能 | 以数据帧为单位向已连接成功的传输通道发送音视频数据。 |
| 返回值 | 0表示成功，非0表示失败|
| 参数列表 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aFd|int|in|必须|传输通道句柄|
|apMediaFrame|MediaFrame_t|in|必须|多媒体数据帧结构体指针，详细参考数据类型中的媒体帧信息|

###3.4 接收媒体帧
```
int	LY_recvMediaFrame(const int aFd, MediaFrame_t * apMediaFrame);
```
| - | - |
|-------|----|
| 接口名 | LY_recvMediaFrame |
| 功能 | 从传输通道接收媒体数据。该接口在没有数据到来时会阻塞，且需要外面管理接收数据的内存空间。 |
| 返回值 | 0表示成功，非0表示失败|

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aFd|int|in|必须|传输通道句柄|
|apMediaFrame|MediaFrame_t|in|必须|多媒体数据帧结构体指针，详细参考数据类型中的媒体帧信息|

###3.5 获取在线状态
```
int	LY_getOnlineStatus(void);
```
| - | - |
|-------|----|
| 接口名 | LY_getOnlineStatus |
| 功能 | 获取本方在云平台的在线状态（网络正常情况下，获取到的状态的是准确无误的；如果网络状况不好，延时比较大(触发超时更改状态)，可能出现实际状态和获取到的状态不一致，可通过平台回调函数的"Online"和"Offline"消息同步状态。） |
| 返回值 | 0表示离线，1表示在线 |

###3.6 更新token信息
```
int LY_updateToken(const char *aDeviceToken, int maxLen);
```
| - | - |
|-------|----|
| 接口名 | LY_updateToken |
| 功能 | token过期后可调用此接口更新token信息。|
| 返回值 | 0表示成功，非0表示失败 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aDeviceToken|char*|Out|必须|接收token信息的内存空间的指针。|
|maxLen|int|In|必须|接受token信息内存空间的最大长度。|
**注意**：

**aDeviceToken**：设备token，由应用后台生成，格式如下：2147549953_3222536192_1469999882_bad3686a62a7aba595df3fb4c9c400e9。

token的内容格式及意义请见[羚羊云token认证机制](http://doc.topvdn.com/api/public-doc/#!token_format.md)

###3.7 定位录像到指定时间点
```
int LY_seek(const int aFd, const unsigned int aCurrentTime);
```
| - | - |
|-------|----|
| 接口名 | LY_seek |
| 功能 | 定位录像到指定的时间点，定位的时间点范围在打开该录像通道的开始时间和结束时间内。时间单位为秒。 |
| 返回值 | 0表示成功，非0表示失败 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aFd|int|in|必须|建立录像传输通道时的通道句柄fd|
|aCurrentTime|unsigned int|in|必须|要定位的时间点，该时间点为相对于建立录像传输通道时传入的begin的差值，必须大于等于0 |

###3.8 设置指定网卡IP
```
int LY_setLocalIP(const char *aFirstIP, const int aFirstIpLength, const char *aSecondIP, const int aSecondIpLength);
```
| - | - |
|-------|----|
| 接口名 | LY_setLocalIP |
| 功能 | 在双网卡情况下，可调用此接口设置两个网卡的IP，数据从两个网卡同时发送，避免某个网卡网络差的时候出现延时或者丢包，由另外一个网卡发送确保数据的及时送达。由调用者保证IP不冲突。不调用时随机选择一个网卡发送数据。IP的格式是点分十进制的字符串格式。在使用QSTP协议下调用有效。 |
| 返回值 | 0表示成功，非0表示失败 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aFirstIP|const char *|in|必须|第一个IP|
|aFirstIpLength|int|in|必须|第一个IP的长度 |
|aSecondIP|const char *|in|必须|第二个IP |
|aSecondIpLength|int|in|必须|第二个IP的长度 |

###3.9 设置媒体编解码信息
```
int LY_setMediaInfo(const int aFd, const MediaInfo_t aMediaInfo); 
```
| - | - |
|-------|----|
| 接口名 | setMediaInfo |
| 功能 | 设置媒体流编解码信息 |
| 返回值 | 0表示成功，非0表示失败 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aFd|const int|in|必须|传输通道fd|
|aMediaInfo|const MediaInfo_t|in|必须|多媒体编解码信息 |

###3.10 设置加密密钥
```
int	LY_setQSUPEncryptKey(const unsigned int aEncryptType,const char * const apEncryptKey, const int aEncryptKeyLength);
```
| - | - |
|-------|----|
| 接口名 | LY_setQSUPEncryptKey |
| 功能 | 设置加密密钥，密钥最长不能超过128个字节。加密、解密在SDK内部算法实现，外部无需关心。如果没有设置加密秘钥，使用加密功能时会使用羚羊云默认的加密秘钥。QSUP协议默认是使用羚羊云默认加密秘钥加密的，如果需要取消加密，则可调用此接口，第一个参数设置为0即可。QSTP协议如果使用云存储功能，则使用羚羊云默认加密秘钥加密；否则不加密。公众模式下，设置与否都不加密。 |
| 返回值 | 0表示成功，非0表示失败 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aEncryptType|int|in|必须|加密类型（0：无加密；1：AES加密）|
|apEncryptKey|const char*|in|必须|加密秘钥内容指针,自定义秘钥|
|aEncryptKeyLength|int|in|必须|加密秘钥内容长度, 密钥最长不能超过128个字节|


##4 相关链接
[C SDK使用说明](http://doc.topvdn.com/api/index.html#!public-doc/SDK-C/c_guide.md)
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/integration.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)
