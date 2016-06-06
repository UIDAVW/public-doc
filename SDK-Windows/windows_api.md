#羚羊云Windows API手册
##1 数据类型
###1.1 媒体参数类型
```
enum StreamInfo_Em {
    //1.当前视频下载速度
    int STREAM_MEDIA_PARAM_VIDEO_DOWNLOADSPEED = 1;
    //2.当前音频下载速度
    int STREAM_MEDIA_PARAM_AUDIO_DOWNLOADSPEED = 2;
    //3.当前视频帧率
    int STREAM_MEDIA_PARAM_VIDEO_RATE = 3;
    //4.当前音频帧率
    int STREAM_MEDIA_PARAM_AUDIO_RATE = 4;
    //5.平均视频下载速度
    int STREAM_MEDIA_PARAM_VIDEO_AVERAGEDOWNLOADSPEED = 5;
    //6.平均音频下载速度
    int STREAM_MEDIA_PARAM_AUDIO_AVERAGEDOWNLOADSPEED = 6;
    //7.QSTP
    int STREAM_MEDIA_PARAM_QSTP = 7;
    //8.上行帧率
    int STREAM_MEDIA_PARAM_DEVICE_UPLOADFRAME = 8;
    //9.上行速度
    int STREAM_MEDIA_PARAM_DEVICE_UPLOADSPEED = 9;
    //10. 缓冲时长（毫秒）
    int STREAM_MEDIA_PARAM_BUFFER_TIME = 10;
    //11.缓冲区帧数
    int STREAM_MEDIA_PARAM_BUFFER_FRAME = 11;
    // 12.当前帧延时（毫秒）
    int STREAM_MEDIA_PARAM_FRAME_DELAY = 12;
    //13. 缓冲区延时（毫秒）
    int STREAM_MEDIA_PARAM_BUFFER_DELAY = 13;
    //14.分辨率宽
    int STREAM_MEDIA_PARAM_RATIO_WIDTH = 14;
    //15.分辨率高
    int STREAM_MEDIA_PARAM_RATIO_HEIGHT = 15;
    //16.发送时间比
    int STREAM_MEDIA_QSTP_SEND_PERCENT = 16;
    //17.在线人数
    int STREAM_MEDIA_ONLINE_NUMBER = 17;
}
```

##2 云服务接口
    
###2.1 启动云服务
```
int startCloudService(const std::string & token, const std::string & config, const antelopecloud::PlatformMsgCallBack & handlePlatformMsgCallBack);
```
| - | - |
|-------|----|
| 接口名 | startCloudService |
| 功能 | 调用了此api之后,平台相关凭证及资源开始准备，并且在回调接口通知云服务是否启动成功！ 建议在客户端登录验证逻辑通过之后即刻调用。服务启动之后，相关的平台接口才能正常使用。 |
| 返回值 | 返回调用结果，0：成功 非0值：失败 |
 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|token|std::string|in|必须|设备token，由第三方后台生成。|
|config|std::string|in|必须|配置串，从第三方后台获取。|
|handlePlatformMsgCallBack|antelopecloud::PlatformMsgCallBack|in|必须|启动结果监听回调，返回成功或失败|
**注意**：

**token**：设备token，由应用后台生成，格式如下：
2147549953\_1458979882\_1469999882\_bad3686a62a7aba595df3fb4c9c400e9。
token的内容格式及意义请见[羚羊云token认证机制](http://doc.topvdn.com/api/public-doc/#!token_format.md)

**config**：配置串，从后台获取(无需解析)，格式如下：
[Config]\r\nIsDebug=0\r\nLocalBasePort=8200\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nUdpSendInterval=2\r\nConnectTimeout=10000\r\nTransferTimeout=10000\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n[LogServer]\r\nCount=1\r\nIP1=120.26.74.53\r\nPort1=80\r\n
调用者不必知道该字符串内容所表示的意义。
应用后台调用[Web API的'查询设备状态'接口](http://doc.topvdn.com/api/#!web_api_v2.md#2.1.1_%E6%9F%A5%E8%AF%A2%E8%AE%BE%E5%A4%87%E7%8A%B6%E6%80%81)获取，接口返回的"init_string"字段即配置串。

###2.2 停止云服务
```
void stopCloudService();
```
| - | - |
|-------|----|
| 接口名 | stopCloudService |
| 功能 | 调用了此api之后，相应的底层资源完全释放，建议在应用退出的时候调用，节省系统资源； |
| 返回值 | 无 |
| 参数列表 | 无 |

###2.4 获取SDK和平台版本号
```
std::string & getSDKVersion();
```
| - | - |
|-------|----|
| 接口名 | getSDKVersion |
| 功能 | 获取SDK版本号； |
| 返回值 | 返回SDK版本号 |
| 参数列表 | 无 |

###2.6 用户是否在线
```
int getOnlineStatus();
```
| - | - |
|-------|----|
| 接口名 | isOnline |
| 功能 | 获取用户在线状态； |
| 返回值 | 返回用户在线状态    1: 在线  0: 为离线 |
| 参数列表 | 无 |


###2.7 消息结构定义
```
class CloudMessage
{
public:
	std::string Name;
	std::string Message;
	std::string SrcID;
}
```
平台消息使用Json格式串传递，需要用户自行解析。结构可参考上述定义。

```
//当该服务接收到调度服务器的开始推送命令时,会发出消息通知外壳调用PushData函数塞数据json格式:
{"Name":"ConnectionAcceptted"}
//当需要停止塞数据时 停止收数据 json格式:
{"Name":"ConnectionClosed"}
//当该服务接收到时 对方发送的媒体数据时，会发出消息通知外壳调用PopData函数收数据json格式:
{"Name":"StartPopData"}
//当设备登录成功或者配置变换时:
{"Name":"PopConfig","Message":"HexConfigString(256字节 512字符)"}
//当设备收到在线消息时:
{"Name":"PopMessage","Message":"HexMessageString(变长)","SrcID":"发送方ID"}
//当设备收到离线消息时:
{"Name":"PopOffLineMessage","Message":"HexMessageString(变长)","SrcID":"发送方ID"}   
```

###2.7 消息监听回调定义
```
class __declspec(dllexport) PlatformMsgCallBack : public MsgCallBack
{
public:
    virtual ~PlatformMsgCallBack(){};

public:
    virtual void handleMsg(const char* aMessage){};
};
```
用户继承该类实现，在调用开启云平台服务时传入。设置云消息接收回调，建议开启云服务后即刻调用，设置了该监听才能收到关闭、设备绑定确认、设备配置状态等云消息


##3 播放器接口
播放器模块可单独实现直播播放，摄像头直播播放，云存储播放，本地录像等功能。


 
###3.1 初始化播放器
播放器在初始化过程中需要传入窗体的HANDLE句柄，然后会在该窗体上进行缩放，并铺满该窗体播放。
```
int initPlayer(const HWND & hRenderWnd , const bool playAudio);
```
| - | - |
|-------|----|
| 接口名 | initPlayer |
| 功能 | 初始化播放器相关参数，调用些api后播放器才能正确打开并播放视频，这里的playAudio为打开播放时是否播放音频； |
| 返回值 | 返回调用结果，0：成功 非0值：失败 |
 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|hRenderWnd|HANDLE|In|必须|视频渲染的窗体句柄|
|playAudio|bool|in|必须|是否播放音频|

###3.2 开始播放
```
int open(const std::string & url , const bool hard_decode , const antelopecloud:: PlayerMsgCallBack & handlerMsgCallBack);
```
| - | - |
|-------|----|
| 接口名 | open |
| 功能 | 调用了此api之后,Windows SDK会根据url中包含的请求类型和参数去拉取流并播放(该方法会阻塞调用，请不要放在UI线程调用)； |
| 返回值 | 返回调用结果，0：成功 非0值：失败 |
 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|url|std::string|In|必须|用户请求的流地址|
|hard_decode|bool|In|必须|是否使用硬解码(此版本只提供软解)|
|handlerMsgCallBack|PlayerMsgCallBack|In|必须|播放器出现错误时会回调此类中的handle方法，详细请查看该类定义。用户可继承此类实现自己的播放器消息处理。可以空实现不处理，对播放无影响。|
**注意**:

**aUrl**：连接地址，从后台获取到IP、端口和token，按照如下格式组合：
topvdn://183.57.151.161:1935?protocolType=2&connectType=1&mode=2&token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069&cid=1003469
topvdn://ip=%s:port=%d?protocolType=%d&connectType=%d&mode=%u&token=%s&cid=%lu&begin=%lu&end=%lu&play=%lu
Url各字段意义及详解请见[羚羊云Url格式解析](http://doc.topvdn.com/api/public-doc/#!url_format.md)
 
**PlayerMsgCallBack**定义：
```
class __declspec(dllexport) PlayerMsgCallBack : public MsgCallBack
{
public:
virtual ~PlayerMsgCallBack(){};
public:
virtual void handleMsg(const int & event_id , void * data){};
};
```

###3.3 暂停播放
```
int pause();
```
| - | - |
|-------|----|
| 接口名 | pause |
| 功能 |暂停播放，此接口只对录像播放有效； |
| 返回值 | 返回调用结果，0：成功 非0值：失败 |

###3.4 恢复播放
```
int resume();
```
| - | - |
|-------|----|
| 接口名 | resume |
| 功能 | 返回调用结果，0：成功 非0值：失败 |
| 返回值 | 无 |

###3.5 停止播放
```
void close();
```
| - | - |
|-------|----|
| 接口名 | close |
| 功能 | 关闭播放，对应打开接口，下次播放需要再次调用open方法； |
| 返回值 | 无 |

###3.6 静音
```
void mute();
```
| - | - |
|-------|----|
| 接口名 | mute |
| 功能 | 无 |
| 返回值 | 无 |

###3.7 播放声音
```
void unmute();
```
| - | - |
|-------|----|
| 接口名 | unmute |
| 功能 | 播放声音，对应mute接口； |
| 返回值 | 无 |

###3.8 获取流参数
```
std::string getStreamInfo(const antelopecloud::StreamInfo_Em & streamInfo);
```
| - | - |
|-------|----|
| 接口名 | getStreamInfo |
| 功能 | 获取antelopecloud::StreamInfo_Em枚举类型中的某一种流参数，可参考头文件中该枚举类型的定义； |
| 返回值 | 对应类型的流参数值； |
 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|streamInfo|antelopecloud::StreamInfo_Em|In|必须|要获取的流参数类型|

###3.9 设置播放位置
```
int setPlayPosition(const unsigned long & timeStamp);
```
| - | - |
|-------|----|
| 接口名 | setPlayPosition |
| 功能 | 设置播放位置，该接口对实时流无效； |
| 返回值 | 0 表示设置成功，其它非0值表示失败； |
 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|timeStamp|unsigned long|In|必须|要播放位置的时间戳|

###3.10 获取播放位置
```
int getPlayPosition(unsigned long & timeStamp);
```
| - | - |
|-------|----|
| 接口名 | getPlayPosition |
| 功能 | 获取播放位置，对应setPlayPosition接口； |
| 返回值 | 0 表示获取成功，其它非0值表示失败； |
 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|timeStamp|unsigned long &|Out|必须|当前播放位置的时间戳|

###3.11 截图
```
int snapshot(const std::string & savePath);
```
| - | - |
|-------|----|
| 接口名 | snapshot |
| 功能 | 截取当前播放帧图片； |
| 返回值 | 0 表示获取成功，其它非0值表示失败； |
 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|savePath|std::string|In|必须|截取的图片保存的全地址|

###3.14 开启本地录像
```
int startLocalRecord(const std::string & recordPath);
```
| - | - |
|-------|----|
| 接口名 | startLocalRecord |
| 功能 | 开启本地录像，将PS流写入本地文件； |
| 返回值 | 0 表示获取成功，其它非0值表示失败； |
 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|savePath|std::string|In|必须|录像写入文件的全地址|

###3.15 停止本地录像
```
void stopLocalRecord();
```
| - | - |
|-------|----|
| 接口名 | stopLocalRecord |
| 功能 | 停止本地录像； |
| 返回值 | 无 |
