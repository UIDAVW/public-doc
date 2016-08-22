#羚羊云iOS API手册-直播推流接口

>接口名称：LYLiveBroadCast

##1 初始化
```
-(instancetype)initWithVideoConfiguration:(LYVideoStreamingConfiguration *)videoConfiguration audioConfiguration:(LYAudioStreamingConfiguration *)audioConfiguration;
```
| - | - |
|-------|----|
| 接口名 | initWithVideoConfiguration: audioConfiguration: |
| 功能 | 根据音视频配置信息对象初始化直播类，调用该方法实现采集和编码的资源准备。 |
| 返回值 | LYLiveBroadCast实例对象 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|videoConfiguration|LYVideoStreamingConfiguration *|in|必须|视频流配置类对象|
|audioConfiguration|LYAudioStreamingConfiguration *|in|必须|音频流配置类对象|

##2 释放资源
```
- (void) destroy;
```
| - | - |
|-------|----|
| 接口名 | destroy |
| 功能 | 释放资源：销毁所有直播使用的资源。退出直播时一定要调用。 |
| 返回值 | 无 |

##3 重设配置参数
```
- (void) resetVideoConfig: (LYVideoStreamingConfiguration *)videoConfig
              audioConfig: (LYAudioStreamingConfiguration *)audioConfig;
```
| - | - |
|-------|----|
| 接口名 | resetVideoConfig: audioConfig: |
| 功能 | 重新设置音视频配置参数，2.0.2版本该接口无效 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|videoConfiguration|LYVideoStreamingConfiguration *|in|必须|视频流配置类对象|
|audioConfiguration|LYAudioStreamingConfiguration *|in|必须|音频流配置类对象|

##4 设置预览
```
- (void) setPreview: (UIView *)preview
              frame: (CGRect)frame;
```
| - | - |
|-------|----|
| 接口名 | setPreview: frame: |
| 功能 | 展示当前摄像头采集的视频。 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|preview|UIView * |in|必须|预览画布|
|frame|CGRect|in|必须|预览画布大位置|

##5 开始直播
```
- (void) startLiveBroadcast: (NSString *)dataSourceAddress
                 startBlock: (void (^)(LYstatusCode statusCode, NSString *errorString))startBlock;
```
| - | - |
|-------|----|
| 接口名 | startLiveBroadcast: startBlock: |
| 功能 | 开始直播，调用之后开始准备直播相关资源，回调状态码为LYstatusCodeSuccess之后调用开始推流即可。 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
| dataSourceAddress |NSString *|in|必须|直播推流地址，用户从[应用服务器](http://doc.topvdn.com/api/index.html#!public-doc/start_archit.md#3._%E7%9B%B8%E5%85%B3%E6%9C%AF%E8%AF%AD%E5%92%8C%E5%90%8D%E8%AF%8D)获取。内容格式和意义请参见[羚羊云播放源url格式解析](http://doc.topvdn.com/api/#!public-doc/url_format.md)|
|startBlock|void (^)(LYstatusCode statusCode, NSString *errorString)|in|必须|直播状态回调|

##6 直播录制
该功能需要在调用上节`startLiveBroadcast`接口方法时传入特定格式的URL，按照[羚羊云推拉流URL格式](http://doc.topvdn.com/api/public-doc/#!url_format.md)设置`protocolType`、`connectType`和`mode`字段。例如：
```
topvdn://183.57.151.161:1935?protocolType=2&connectType=1&token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069&mode=4
```
其中：
- `protocolType` 必须为2，表示使用QSTP协议推流。
- `connectType` 必须为1，表示推流端。
- `mode` 值可为3，表示使用QSTP协议推流，私有模式，并开启云存储；也可为4，表示使用QSTP协议推流，公众模式，并开启云存储。

##7 停止直播
```
- (void) stopLiveBroadcast;
```
| - | - |
|-------|----|
| 接口名 | stopLiveBroadcast |
| 功能 | 和开始直播对应调用，内部释放开始直播准备的底层资源。 |
| 返回值 | 无 |

##8 直播控制

###8.1 开始推视频流 
```
- (void) startSendVideoData；
```
| - | - |
|-------|----|
| 接口名 | startSendVideoData |
| 功能 | 开始推视频流。 |
| 返回值 | 无 |

###8.2 停止推视频流 
```
- (void) stopSendVideoData；
```
| - | - |
|-------|----|
| 接口名 | stopSendVideoData |
| 功能 | 停止推视频流。 |
| 返回值 | 无 |

###8.3 开始推音频流 
```
- (void) startSendAudioData；
```
| - | - |
|-------|----|
| 接口名 | startSendAudioData |
| 功能 | 开始推音频流。 |
| 返回值 | 无 |

###8.4 停止推音频流 
```
- (void) stopSendAudioData；
```
| - | - |
|-------|----|
| 接口名 | stopSendAudioData |
| 功能 | 停止推音频流。 |
| 返回值 | 无 |

##9 设备控制

###9.1 切换摄像头
```
- (void) switchCamera: (LYCaptureCameraMode)cameraMode
          switchBlock: (void (^)(LYstatusCode statusCode, NSString *errorString))switchBlock;
```
| - | - |
|-------|----|
| 接口名 | switchCamera: switchBlock: |
| 功能 | 切换前后置摄像头 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|cameraMode|LYCaptureCameraMode|in|必须|前置/后置|
|switchBlock|void (^)(LYstatusCode statusCode, NSString *errorString))|in|可选|切换状态回调|

###9.2 开关闪光灯 
```
- (void) turnTorchAndFlashOn: (BOOL)on
                      status: (void (^)(LYstatusCode statusCode, NSString *errorString))turnBlock;
```
| - | - |
|-------|----|
| 接口名 | turnTorchAndFlashOn: status: |
| 功能 | 打开闪光灯：前置摄像头的时候不可以开启闪光灯。 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|on|BOOL|in|必须|前置/后置|
|turnBlock|void (^)(LYstatusCode statusCode, NSString *errorString))|in|可选|打开状态回调|

###9.3 获取当前采集图片 
```
- (void) getCurrentFrameImage: (void (^)(UIImage *image, char *imageBuffer, int bufferLength))success;
```
| - | - |
|-------|----|
| 接口名 | getCurrentFrameImage: |
| 功能 | 获取当前摄像头采集的视频图像转换为UIImage返回 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|success|void (^)(UIImage \*image, char \*imageBuffer, int bufferLength)|in|必须|image:UIImage图片 imageBuffer:图片数据 bufferLength:数据长度|

###9.4 获取错误信息 
```
- (NSString *) getCurrentErrorInfo
```
| - | - |
|-------|----|
| 接口名 | getCurrentErrorInfo |
| 功能 | 可以在执行过程中获取之前的操作是否存在错误信息。 |
| 返回值 | 调用之前所产生的错误信息字符串 |


#### 相关链接
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)