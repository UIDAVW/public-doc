#羚羊云iOS API手册
##1 数据类型
###1.1 接口执行的状态
```
typedef NS_ENUM(NSInteger, LYstatusCode) {
    LYstatusCodeSuccess                          = 0,  //成功
    
    //统一的错误码
    LYstatusCodeUnityErrorParamInvalid           = -2000,//传入的参数为nil或者null(主要用于检测token等连接参数)
    LYstatusCodeUnityErrorOperaterNil            = -2004,//调用对应操作的对象为nil
    LYstatusCodeUnityErrorIsStarting             = -2005,//调用的某个操作正在进行中(还未执行完成)ServiceOutline
    LYstatusCodeUnityErrorIsSuccess              = -2006,//调用的某个操作已经成功，再次调用的时候需要调用其对应的停止和关闭接口(已经成功返回再调用状态)
    LYstatusCodeUnityErrorServiceOutline         = -2007,//调用的接口需要云服务时，云服务离线或者未启动云服务
    
    //启动云服务错误码
    LYstatusCodeStartCloudServiceError           = -3000,//启动云服务失败
    LYstatusCodeStartCloudServiceIsBusy          = -3001,//服务繁忙中(正在启动云服务中，还未返回)
    LYstatusCodeStartCloudServiceIsSuccess       = -3002,//云服务已经启动成功,要重新调用启动云服务则需要先调用stop云服务
    
    //播放器(LYPlayer)错误码
    LYstatusCodePlayerErrorScheme                = -4000,//播放地址格式不对(只判断头信息uri:scheme)
    LYstatusCodePlayerErrorType                  = -4001,//播放类型不正确(type)
    LYstatusCodePlayerErrorOpenProtocol          = -4002,//打开播放协议失败
    LYstatusCodePlayerErrorOpenPlayer            = -4003,//打开播放器失败
    LYstatusCodePlayerErrorRecordFromToInvalid   = -4004,//观看录像的from || to 为0
    LYstatusCodePlayerErrorRequestRecordInfo     = -4005,//获取录像信息错误
    LYstatusCodePlayerErrorSeekTimestamp         = -4006,//seek失败
    LYstatusCodePlayerErrorSavePathInvalid       = -4007,//截图或者本地录像路径为空
    LYstatusCodePlayerErrorSnapshot              = -4008,//截图失败
    LYstatusCodePlayerErrorStartLoaclRecord      = -4009,//本地录像失败
    
    //视频采集错误码
    LYstatusCodeVideoCaptureErrorNoDevice        = -5000,//获取摄像头设备列表失败(系统默认采集摄像头也获取不到)
    LYstatusCodeVideoCaptureErrorInput           = -5001,//对应采集设备获取输入流失败(deviceInputWithDevice)
    LYstatusCodeVideoCaptureCameraStarting       = -5002,//摄像头正在开启中，
    LYstatusCodeVideoCaptureStartFaild           = -5003,//摄像头开启失败
    LYstatusCodeVideoCaptureCameraIsFront        = -5004,//打开闪光灯失败，前置摄像头无法开启闪关灯，
    LYstatusCodeVideoCaptureErrorCameraTorch     = -5005,//当前设备不支持闪光灯或者闪光灯打开失败。
    
    //直播错误码
    LYstatusCodeLiveBroadcastErrorGetRelayInfo    = -6000,//获取relay info error
    LYstatusCodeLiveBroadcastErrorOpenProtocol    = -6001,//打开协议失败
    LYstatusCodeLiveBroadcastErrorInitEncoder     = -6002,//初始化编码器失败
    
    LYstatusCodeLiveBroadcastErrorSwitchCamera    = -6020,//切换摄像头失败(1.摄像头获取失败；2.切换的和当前工作的是同一设备)
};
```

###1.2 媒体参数协议
```
typedef NS_ENUM(NSInteger, LYStreamMediaParam) {
    LYStreamMediaParamVideoDownloadSpeed        = 1,//当前视频下载速度
    LYStreamMediaParamAudioDownloadSpeed        = 2,//当前音频下载速度
    LYStreamMediaParamVideoRate                 = 3,//当前视频帧率
    LYStreamMediaParamAudioRate                 = 4,//当前音频帧率
    LYStreamMediaParamVideoAverageDownloadSpeed = 5,//平均视频下载速度
    LYStreamMediaParamAudioAverageDownloadSpeed = 6,//平均音频下载速度
    LYStreamMediaParamRTMPAddress               = 7,//RTMP地址
    LYStreamMediaParamDeviceUploadFrame         = 8,//上行帧率
    LYStreamMediaParamDeviceUploadSpeed         = 9,//上行速度
    LYStreamMediaParamBufferTime                = 10,//缓冲时长（毫秒）
    LYStreamMediaParamBufferFrame               = 11,//缓冲区帧数
    LYStreamMediaParamFrameDelay                = 12,//当前帧延时（毫秒）
    LYStreamMediaParamBufferDelay               = 13,//缓冲区延时（毫秒）
    LYStreamMediaParamRatioWidth                = 14,//分辨率宽
    LYStreamMediaParamRatioHeight               = 15,//分辨率高
    LYStreamMediaParamRTMPSendPercent           = 16,//发送时间比
    LYStreamMediaParamOnlineNumber              = 17 //在线人数
};
```

###1.3 接口block
```
    //状态block
	typedef void(^startCloudServiceBlock)(LYstatusCode statusCode, NSString *errorString);
	statusCode：启动云服务状态，详见上面的接口执行状态。
	errorString；启动失败的错误信息。

	//平台消息block
	typedef void(^cloudServicePopMessageBlock)(NSDictionary *dictionary);
	dictionary：消息字典，详细如下：
    
	//dictionary字典健
	#define kMESSAGENAME_KEY    @"messageName"  //消息名称-->用来区分当前消息是什么回调,对应值为字典
	#define kMESSAGEBODY_KEY    @"messageBody"  //消息体  -->透传消息的具体数据(互联时候用户自定义数据)//是一个字符串，具体字符串要转什么格式调用者自行转换
	#define kMESSAGESRCID_KEY   @"messageSrcID" //srcID
    
	//messageName字典健
	#define kMESSAGENAME_ONLINE_KEY                     @"Online"               //登录成功之后的推送消息-->告知平台在线
	#define kMESSAGENAME_CONNECTION_ACCEPTTED_KEY       @"ConnectionAcceptted"  //代表互联连接方连接成功之后(被叫方)，等待连接方(主叫方)收到的消息-->表示连接成功
	#define kMESSAGENAME_CONNECTION_CLOSED_KEY          @"ConnectionClosed"     //代表①私有直播时中途出现断开；②互联双方出现断开的消息
	#define kMESSAGENAME_POP_MESSAGE_KEY                @"PopMessage"           //代表互联被叫方接收的推送消息-->比如接收到主叫的呼叫信息、主叫断开等消息
	#define kMESSAGENAME_POP_OFFLINE_MESSAGE_KEY        @"PopOffLineMessage"    //代表设备状态的推送消息
	#define kMESSAGENAME_START_POP_DATA_KEY             @"StartPopData"         //开始取流
	#define kMESSAGENAME_POP_CONFIG_KEY                 @"PopConfig"            //配置信息(私有设备状态更改，建立连接和断开的时候设备状态变动的消息)
	#define kMESSAGENAME_POP_CONFIG_RESULT_KEY          @"PopConfigResult"      //自己添加获取配置栏
	#define kMESSAGENAME_DEVICE_BIND_CONFIRM_KEY        @"DeviceBindConfirm"    //设备绑定配置信息
	
    //messageBody默认健值
	#define kMESSAGEBODY_DEFAULT_KEY    @"messageBodyNoKey"
	#define kMESSAGEBODY_DEFAULT_VALUE  @"messageBodyNoValue"
```

###1.4 播放器blcok
```
	typedef void(^playerCallBackBlock)(NSDictionary *playerMessageDic);
	playerMessageDic：回调播放器状态信息字典，详细如下：
	#define kLY_PLAYER_MESSAGE_TYPE_KEY            @"messageType"   //1开始播放 2连接中断 3数据源错误 4关闭播放器
	#define kLY_PLAYER_PARAM_1_KEY                 @"param1"
	#define kLY_PLAYER_PARAM_2_KEY                 @"param2"
```

###1.5 解码枚举类型
```
typedef NS_ENUM(NSInteger, LYPlayerDecodeMode) {
    LYPlayerDecodeModeHard = 1, //硬解
    LYPlayerDecodeModeSoft = 2  //软解
};
```

###1.6 摄像头枚举类型
```
typedef NS_ENUM(NSInteger, LYCaptureCameraMode) {
    LYCaptureCameraModeFront = 1,  //前置摄像头
    LYCaptureCameraModeBack  = 2,  //后置摄像头
};
```

###1.7 编码枚举类型
```
typedef NS_ENUM(NSInteger, LYCaptureDataEncodeMode) {
    LYCaptureDataEncodeModeSoft = 1,    //软编码
    LYCaptureDataEncodeModeHard = 2,    //硬编码
};
```

###1.8 视频流质量枚举类型
```
typedef NS_ENUM(NSInteger, LYVideoStreamingQualityLevel) {
    LYVideoStreamingQualityModeLevelLow         = 1,  //普通
    LYVideoStreamingQualityModeLevelMedium      = 2,  //标清
    LYVideoStreamingQualityModeLevelHigh        = 3,  //高清
};
```

###1.9 直播枚举类型
```
typedef NS_ENUM(NSInteger, LYLiveBroadcastMode) {
    LYLiveBroadcastModeLiving = 2,  //不带录像的直播
    LYLiveBroadcastModeRecord = 4   //带录像的直播
};
```

###1.10 视频流配置类
```
	//配置类类名：LYVideoStreamingConfiguration

    //视频的分辨率
	@property (nonatomic, assign) CGSize  videoSize;
	宽高务必设定为 2 的倍数，否则解码播放时可能出现绿边:default 640*480

	//视频的帧率
	@property (nonatomic, assign) NSUInteger videoFrameRate;
	默认值： fps = 30

	//视频的码率
	@property (nonatomic, assign) NSUInteger videoBitRate;
	单位是 kbps :默认 512kbps
	
	//编码方式
	@property (nonatomic, assign) LYCaptureDataEncodeMode encodeMode;
	软编/硬编(iOS 8.0+才支持硬遍)：默认 iOS 8.0+ 硬编码 / iOS 8.0- 软编

	//摄像头类型
	@property (nonatomic, assign) LYCaptureCameraMode cameraMode;
	前/后置默认前置
	
	//错误信息
	@property (weak, nonatomic) NSString *error;
	生成配置时错误信息描述：如果该属性为nil或者为@“”表示参数正确
	
    //方法：生成默认配置
    //描述：该方法不是单例方法，每次调用都会生成一个新的配置，默认情况下对应的参数分辨率为(640, 480)，推流质量为标清。
    //返回值：LYVideoStreamingConfiguration实例对象
    + (instancetype) defaultConfiguration;

    //方法：自定义生成配置
    //描述：该方法不是单例方法，每次调用都会根据分辨率和推流质量生成一个新的配置。
    //返回值：LYVideoStreamingConfiguration实例对象
    //输入参数：videoSize 分辨率
    //输入参数：quality 推流质量 详见视频质量枚举类型
    + (instancetype) defaultConfiguration;
	
    //方法：初始化配置
    //描述：根据全部参数初始化一个配置，务必清楚每一个参数的含义，清楚各个参数的意义和影响才调用该方法进行初始化生成新的配置，内部会判断参数的有效性，调用validate验证参数是否合理。
    //返回值：LYVideoStreamingConfiguration实例对象
    //输入参数：videoSize 分辨率
    //输入参数：frameRate 帧率 详见视频质量枚举类型
    //输入参数：videoBitrate 码率
    //输入参数：encodeMode 编码方式 详见编码方式枚举
    //输入参数：cameraMode 摄像头类型 详见摄像头类型枚举
    - (instancetype) initWithVideoSize: (CGSize)videoSize
                    videoFrameRate: (NSUInteger)frameRate
                      videoBitrate: (NSUInteger)videoBitrate
                        encodeMode: (LYCaptureDataEncodeMode)encodeMode
                        cameraMode: (LYCaptureCameraMode)cameraMode;
	
    //方法：验证参数正确性
    //描述：验证参数的有效性，当更改参数的时候，调用该方法验证参数是否正确，有错则返回错误信息
    //返回值：错误信息
    - (NSString *)validate;
```

###1.11 音频流配置类
```
	//配置类类名：LYAudioStreamingConfiguration。
	
	//音频流的质量
	@property (nonatomic, assign) LYAudioStreamingQualityMode audioQuality;

	//音频流码率
	@property (nonatomic, assign, readonly) LYAudioStreamingBitRate audioBitRate;
	
	//采样率
	@property (nonatomic, assign) NSUInteger audioSampleRate; 	4800 for iPhone 6s family devices, 44100 for others

	//通道号
	@property (nonatomic, assign) UInt32 numberOfChannels;   	默认： 1

	//方法：生成配置方法
    //描述：该方法不是单例方法，每次调用都会生成一个默认新的配置。
    //返回值：LYAudioStreamingConfiguration实例对象
	+ (instancetype)defaultConfiguration;
```

###1.12 播放器配置类
```
	//配置类类名：LYPlayerConfiguration。
	
	//播放器画布
	@property (weak, nonatomic) UIView *playView;
	可以在播放开始之后动态切换。

	//播放器frame
	@property (nonatomic, assign) CGRect  playViewFrame;
	可以在播放开始之后改变view.frame
 
	//解码方式
	@property (nonatomic, assign) LYPlayerDecodeMode decodeMode;

	//软/硬解(iOS 8.0+才支持硬遍)：default iOS 8.0+ ↑hard / iOS 8.0- ↓soft
 	//你也可以自由选择设置。但是视频通话的时候强力建议硬解
	//注意：播放开始之后(暂时不支持)不可以切换解码方式。！！！
 
	//方法：初始化
    //描述：根据对应参数生成播放器配置
    //返回值：LYPlayerConfiguration实例对象
    //输入参数： playView 播放器画布
    //输入参数： playFrame 画布大小
    //输入参数： decodeMode 解码方式 详见解码方式枚举
	- (instancetype) initWithPlayView: (UIView *)playView
                                frame: (CGRect)playFrame
                           decodeMode: (LYPlayerDecodeMode) decodeMode;
```

##2 云服务接口
>接口名称：LYCloudService
    
###2.1 获取单例对象
```
+ (LYCloudService *) sharedLYCloudService;
```
| - | - |
|-------|----|
| 接口名 | sharedLYCloudService |
| 功能 | 单例方法，整个SDK运行期间云服务类只会生成一次。|
| 返回值 | LYCloudService实例对象 |
    
###2.2 启动云服务
```
- (void) startCloudService: (NSString *)token
                    config: (NSString *)config
                startBlock: (startCloudServiceBlock)startBlock
           popMessageBlock: (cloudServicePopMessageBlock)popMessageBlock;

```
| - | - |
|-------|----|
| 接口名 | startCloudService |
| 功能 | 调用了此api之后,平台相关凭证及资源开始准备，并且在回调接口通知云服务是否启动成功！ 建议在客户端登录验证逻辑通过之后即刻调用。服务启动之后，相关的平台接口才能正常使用； |
| 返回值 | 无 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|token|NSString *|in|必须|用户token，由第三方后台生成。|
|config|NSString *|in|必须|配置串，从第三方后台获取。|
|startBlock|startCloudServiceBlock|in|--|启动服务状态回调 详见平台接口block|
|popMessageBlock|cloudServicePopMessageBlock|in|--|消息监听回调，设备状态变更、建立连接消息、自定义消息均通过改block回调，详见平台接口block|
>**注意**：
>
**token**：用户token，由应用后台生成，格式如下：<br>
2147549953_1458979882_1469999882_bad3686a62a7aba595df3fb4c9c400e9。<br>
token的内容格式及意义请见<u>《羚羊云token认证机制》</u>(给出导航链接)
>
**config**：配置串，从后台获取(无需解析)，格式如下：
[Config]\r\nIsDebug=0\r\nLocalBasePort=8200\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nUdpSendInterval=2\r\nConnectTimeout=10000\r\nTransferTimeout=10000\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n[LogServer]\r\nCount=1\r\nIP1=120.26.74.53\r\nPort1=80\r\n<br>
调用者不必知道该字符串内容所表示的意义。

###2.3 停止云服务
```
-(void) stopCloudService;
```
| - | - |
|-------|----|
| 接口名 | stopCloudService |
| 功能 | 调用了此api之后，相应的底层资源完全释放，建议在应用退出的时候调用，节省系统资源； |
| 返回值 | 无 |
| 参数列表 | 无 |

###2.4 获取SDK版本号
```
String getSDKVersion();
```
| - | - |
|-------|----|
| 接口名 | getSDKVersion |
| 功能 | 获取SDK版本号； |
| 返回值 | 返回SDK版本号 |
| 参数列表 | 无 |

###2.5 用户是否在线
```
- (BOOL) isOnline;
```
| - | - |
|-------|----|
| 接口名 | isOnline |
| 功能 | 获取用户在线状态； |
| 返回值 | 返回用户在线状态 YES: 在线  NO: 为离线|
| 参数列表 | 无 |

##3 直播推流接口
>接口名称：LYLiveBroadCast

###3.1 初始化
```
-(instancetype)initWithVideoConfiguration:(LYVideoStreamingConfiguration *)videoConfiguration audioConfiguration:(LYAudioStreamingConfiguration *)audioConfiguration;
```
| - | - |
|-------|----|
| 接口名 | initWithVideoConfiguration |
| 功能 | 根据音视频配置信息对象初始化直播类，调用该方法实现采集和编码的资源准备。 |
| 返回值 | LYLiveBroadCast实例对象 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|videoConfiguration|LYVideoStreamingConfiguration *|in|必须|视频流配置类对象|
|audioConfiguration|LYAudioStreamingConfiguration *|in|必须|音频流配置类对象|

###3.2 重设配置参数
```
- (void) resetVideoConfig: (LYVideoStreamingConfiguration *)videoConfig
              audioConfig: (LYAudioStreamingConfiguration *)audioConfig;
```
| - | - |
|-------|----|
| 接口名 | resetVideoConfig |
| 功能 | 重新设置音视频配置参数 |
| 返回值 | 无 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|videoConfiguration|LYVideoStreamingConfiguration *|in|必须|视频流配置类对象|
|audioConfiguration|LYAudioStreamingConfiguration *|in|必须|音频流配置类对象|

###3.3 开始直播
```
- (void) startLiveBroadcastWithMode: (LYLiveBroadcastMode)mode
                              token: (NSString *)token
                         startBlock: (void (^)(LYstatusCode statusCode, NSString *errorString))startBlock;
```
| - | - |
|-------|----|
| 接口名 | startLiveBroadcastWithMode |
| 功能 | 开始直播，调用之后开始准备直播相关资源，回调状态码为LYstatusCodeSuccess之后调用开始推流即可。 |
| 返回值 | 无 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|mode|LYLiveBroadcastMode |in|必须|直播枚举类型|
|token|NSString *|in|必须|用户token，用户从第三方后台获取|
|startBlock|oid (^)(LYstatusCode statusCode, NSString *errorString)|in|必须|直播状态回调|
>token：用户token，从后台获取，格式如下：<br>
2147549953_1458979882_1469999882_bad3686a62a7aba595df3fb4c9c400e9<br>
Token串各字段所表示的意义请见《羚羊云token认证机制》(给出导航链接)

###4.4 停止直播
```
- (void) stopLiveBroadcast;
```
| - | - |
|-------|----|
| 接口名 | stopLiveBroadcast |
| 功能 | 和开始直播对应调用，内部释放开始直播准备的底层资源。 |
| 返回值 | 无 |

###4.5 设置预览
```
- (void) setPreview: (UIView *)preview
              frame: (CGRect)frame;
```
| - | - |
|-------|----|
| 接口名 | startLiveBroadcastWithMode |
| 功能 | 展示当前摄像头采集的视频。 |
| 返回值 | 无 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|preview|UIView * |in|必须|预览画布|
|frame|CGRect|in|必须|预览画布大小|

###4.6 切换摄像头
```
- (void) switchCamera: (LYCaptureCameraMode)cameraMode
          switchBlock: (void (^)(LYstatusCode statusCode, NSString *errorString))switchBlock;
```
| - | - |
|-------|----|
| 接口名 | switchCamera |
| 功能 | 切换前后置摄像头 |
| 返回值 | 无 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|cameraMode|LYCaptureCameraMode|in|必须|前置/后置|
|switchBlock|void (^)(LYstatusCode statusCode, NSString *errorString))|in|可选|切换状态回调|

###4.7 开关闪光灯 
```
- (void) turnTorchAndFlashOn: (BOOL)on
                      status: (void (^)(LYstatusCode statusCode, NSString *errorString))turnBlock;
```
| - | - |
|-------|----|
| 接口名 | turnTorchAndFlashOn |
| 功能 | 打开闪光灯：前置摄像头的时候不可以开启闪光灯。 |
| 返回值 | 无 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|on|BOOL|in|必须|前置/后置|
|turnBlock|void (^)(LYstatusCode statusCode, NSString *errorString))|in|可选|打开状态回调|

###4.8 开始推视频流 
```
- (void) startSendVideoData；
```
| - | - |
|-------|----|
| 接口名 | startSendVideoData |
| 功能 | 开始推视频流。 |
| 返回值 | 无 |

###4.9 停止推视频流 
```
- (void) stopSendVideoData；
```
| - | - |
|-------|----|
| 接口名 | stopSendVideoData |
| 功能 | 停止推视频流。 |
| 返回值 | 无 |

###4.10 开始推音频流 
	- (void) startSendAudioData；
接口	startSendAudioData
开始推音频流。
返回值	无
参数列表	无
```
- (void) startSendAudioData；
```
| - | - |
|-------|----|
| 接口名 | startSendAudioData |
| 功能 | 开始推音频流。 |
| 返回值 | 无 |

###4.11 停止推音频流 
```
- (void) stopSendAudioData；
```
| - | - |
|-------|----|
| 接口名 | stopSendAudioData |
| 功能 | 停止推音频流。 |
| 返回值 | 无 |

###4.12 获取当前采集图片 
```
- (void) getCurrentFrameImage: (void (^)(UIImage *image, char *imageBuffer, int bufferLength))success;
```
| - | - |
|-------|----|
| 接口名 | getCurrentFrameImage |
| 功能 | 获取当前摄像头采集的视频图像转换为UIImage返回 |
| 返回值 | 无 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|success|void (^)(UIImage *image, char *imageBuffer, int bufferLength)|in|必须|image:UIImage图片 imageBuffer:图片数据 bufferLength:数据长度|

###4.13 获取错误信息 
```
- (NSString *) getCurrentErrorInfo
```
| - | - |
|-------|----|
| 接口名 | getCurrentErrorInfo |
| 功能 | 可以在执行过程中获取之前的操作是否存在错误信息。 |
| 返回值 | 调用之前所产生的错误信息字符串 |

###4.14 释放资源
```
- (void) destroy;
```
| - | - |
|-------|----|
| 接口名 | destroy |
| 功能 | 释放资源：销毁所有直播使用的资源。退出直播时一定要调用。 |
| 返回值 | 无 |

##5 播放器接口
>接口名称：LYPlayer

###5.1 设置播放器配置
```
- (void) setViewWithConfiguration: (LYPlayerConfiguration *)playerConfiguration;
```
| - | - |
|-------|----|
| 接口名 | setViewWithConfiguration |
| 功能 | 设置播放器的配置信息。切忌初始化对象完成之后调用设置，否则后续操作无法进行 |
| 返回值 | 无 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|playerConfiguration|LYPlayerConfiguration *|in|必须|播放器配置类，详见数据类型章节|

###5.2 更改播放器位置 
```
- (void)setViewFrame: (CGRect)frame;
```
| - | - |
|-------|----|
| 接口名 | setViewFrame |
| 功能 | 重新设置或者改变播放器View的Frame |
| 返回值 | 无 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|frame|CGRect|in|必须|播放器大小|

###5.3 打开播放器
```
- (void)open: (NSString *)dataSourceAddreess
  openStatus: (void (^)(LYstatusCode statusCode, NSString *errorString))openBlock
playerStatus: (playerCallBackBlock)playerBlock;
```
| - | - |
|-------|----|
| 接口名 | open |
| 功能 | 打开播放器，根据对应的播放地址进行连接以及渲染，播放状态实时回调 |
| 返回值 | 无 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|dataSourceAddreess|NSString *|in|必须|播放地址|
|openBlock|void (^)(LYstatusCode statusCode, NSString *errorString)|in|必须|打开状态回调|
|playerBlock|playerCallBackBlock|in|必须|播放状态回调|

###5.4 关闭播放器
```
- (void)close;
```
| - | - |
|-------|----|
| 接口名 | close |
| 功能 | 关闭播放器，断开连接以及是否渲染资源，调用opne之后一定要调用close； |
| 返回值 | 无 |

###5.5 打开声音
```
- (NSInteger)unmute;
```
| - | - |
|-------|----|
| 接口名 | unmute |
| 功能 | 打开播放器声音 |
| 返回值 | 打开成功与否。 |

###5.6 关闭声音 
```
- (void)mute;
```
| - | - |
|-------|----|
| 接口名 | mute |
| 功能 | 关闭播放器声音 |
| 返回值 | 无 |

###5.7 获取流媒体数据
```
- (NSString *)getMediaParam:(LYStreamMediaParam)streamMediaParam;
```
| - | - |
|-------|----|
| 接口名 | getMediaParam |
| 功能 | 获取流媒体信息数据 |
| 返回值 | 对应序号的流媒体信息 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|streamMediaParam|LYStreamMediaParam|in|必须|播放地址|

###5.8 获取播放时间
```
- (NSInteger)getCurrentPlayTime;
```
| - | - |
|-------|----|
| 接口名 | getCurrentPlayTime |
| 功能 | 获取观看历史时对应的播放时间戳；只针对观看历史有效 |
| 返回值 | 点播播放位置：时间戳 |

###5.9 播放定位 
```
- (void)seek: (NSInteger)timestamp
      status: (void (^)(LYstatusCode statusCode))seekBlock;
```
| - | - |
|-------|----|
| 接口名 | seek |
| 功能 | 设置播放位置，定位播放时间点：只针对观看历史有效， |
| 返回值 | 无 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|timestamp|NSInteger|in|必须|时间戳|
|seekBlock|void (^)(LYstatusCode statusCode)|in|可选|状态回调|

###5.10 创建视频截图
```
- (void)snapshot: (NSString *)path
          status: (void (^)(LYstatusCode statusCode, NSString *errorString))snapshotBlock;
```
| - | - |
|-------|----|
| 接口名 | snapshot |
| 功能 | 创建视频截图；路径包括文件名，后缀.jpg |
| 返回值 | 无 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|path|NSString *|in|必须|保存路径；|
|snapshotBlock|void (^)(LYstatusCode statusCode, NSString *errorString)|in|必须|截图状态回调|

###5.11 开始本地录像
```
- (void)startLocalRecord: (NSString *)path
                  status: (void (^)(LYstatusCode statusCode, NSString *errorString))startRecordBlock;
```
| - | - |
|-------|----|
| 接口名 | startLocalRecord |
| 功能 | 开始本地录像，在开始播放后调用；路径包括文件名，后缀.mp4 |
| 返回值 | 无 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|filePath|NSString *|in|必须|保存路径；|
|startRecordBlock|void (^)(LYstatusCode statusCode, NSString *errorString)|in|必须|开始录像状态回调|

###5.12 结束本地录像   
   - (void)stopLocalRecord；
接口	stopLocalRecord
结束本地录像；
返回值	无
参数列表	无
```
- (void)stopLocalRecord；
```
| - | - |
|-------|----|
| 接口名 | stopLocalRecord |
| 功能 | 结束本地录像； |
| 返回值 | 无 |
