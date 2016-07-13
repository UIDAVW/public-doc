#羚羊云iOS API手册-数据类型

##1 接口执行的状态
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
    LYstatusCodePlayerErrorStartLocalRecord      = -4009,//本地录像失败
    LYstatusCodePlayerErrorNoSetPlayerConfig     = -4010,//没设置播放器配置
    LYstatusCodePlayerErrorLocalRecording        = -4011,//正在进行本地录像，需要先停止录制才可以开启
    LYstatusCodePlayerErrorSavePathSuffix        = -4012,//地址后缀是.mp4
    //视频通话错误码
    LYstatusCodePlayerErrorNOFacetime            = -4013,//没有进行视频通话
    
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

##2 媒体参数协议
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

##3 接口block
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

##4 播放器blcok
```
	typedef void(^playerCallBackBlock)(NSDictionary *playerMessageDic);
	playerMessageDic：回调播放器状态信息字典，详细如下：
	#define kLY_PLAYER_MESSAGE_TYPE_KEY            @"messageType"   //1开始播放 2连接中断 3数据源错误 4关闭播放器
	#define kLY_PLAYER_PARAM_1_KEY                 @"param1"
	#define kLY_PLAYER_PARAM_2_KEY                 @"param2"
```

##5 解码枚举类型
```
typedef NS_ENUM(NSInteger, LYPlayerDecodeMode) {
    LYPlayerDecodeModeHard = 1, //硬解
    LYPlayerDecodeModeSoft = 2  //软解
};
```

##6 摄像头枚举类型
```
typedef NS_ENUM(NSInteger, LYCaptureCameraMode) {
    LYCaptureCameraModeFront = 1,  //前置摄像头
    LYCaptureCameraModeBack  = 2,  //后置摄像头
};
```

##7 编码枚举类型
```
typedef NS_ENUM(NSInteger, LYCaptureDataEncodeMode) {
    LYCaptureDataEncodeModeSoft = 1,    //软编码
    LYCaptureDataEncodeModeHard = 2,    //硬编码
};
```

##8 视频流质量枚举类型
```
typedef NS_ENUM(NSInteger, LYVideoStreamingQualityLevel) {
    LYVideoStreamingQualityModeLevelLow         = 1,  //普通
    LYVideoStreamingQualityModeLevelMedium      = 2,  //标清
    LYVideoStreamingQualityModeLevelHigh        = 3,  //高清
};
```

##9 直播枚举类型
```
typedef NS_ENUM(NSInteger, LYLiveBroadcastMode) {
    LYLiveBroadcastModeLiving = 2,  //不带录像的直播
    LYLiveBroadcastModeRecord = 4   //带录像的直播
};
```

##10 视频流配置类
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

##11 音频流配置类
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

##12 播放器配置类
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
