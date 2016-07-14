#羚羊云iOS API手册-视频通话接口

>接口名称：LYFaceTime

##1 初始化
```
- (instancetype) initWithVideoConfiguration: (LYVideoStreamingConfiguration *)videoConfiguration audioConfiguration: (LYAudioStreamingConfiguration *)audioConfiguration;
```
| - | - |
|-------|----|
| 接口名 | initWithVideoConfiguration: audioConfiguration: |
| 功能 | 初始化直播类 |
| 返回值 | LYFaceTime实例对象 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|videoConfiguration|LYVideoStreamingConfiguration|in|必须|视频采集和推流配置|
|audioConfiguration|LYAudioStreamingConfiguration|in|必须|音频采集和推流配置|

##2 销毁
```
- (void) destroy;
```
| - | - |
|-------|----|
| 接口名 | destroy |
| 功能 | 释放互联底层资源，退出的时候一定要调用|
| 返回值 | 无 |

##3 设置预览View
```
- (void) setPreview: (UIView *)preview
              frame: (CGRect)frame;
```
| - | - |
|-------|----|
| 接口名 | setPreview: frame: |
| 功能 | 设置预览view，本地采集视频预览view，注意该view上不能存在其他控件，否则会被layer重绘掉 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|preview|UIView|in|必须|预览view|
|frame|CGRect|in|必须|view的位置|

##4 设置播放view
```
- (void) setPlayView: (NSString *)dataSourceAddress
 playerConfiguration: (LYPlayerConfiguration *)playerConfiguration;
```
| - | - |
|-------|----|
| 接口名 | setPlayView: playerConfiguration: |
| 功能 | 设置播放view |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|dataSourceAddreess|NSString *|in|必须|播放地址|
|playerConfiguration|LYPlayerConfiguration|in|必须|播放器配置类：如view、frame、解码方式|

##5 更改播放器frame
```
- (void)setPlayViewFrame: (NSString *)dataSourceAddreess frame: (CGRect)frame;
```
| - | - |
|-------|----|
| 接口名 | setPlayViewFrame: frame: |
| 功能 | 更改播放器frame。该接口的应用场景主要在：旋转view、view大小改变等情况下需要重新设置frame，底层根据大小重新在画布上回执。 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|dataSourceAddreess|NSString *|in|必须|播放地址|
|frame|CGRect|in|必须|view的frame播放地址|

##6 建立通话连接
```
- (void)open: (NSString *)dataSourceAddreess
  openStatus: (void (^)(LYstatusCode statusCode, NSString         	*errorString))openBlock
playerStatus: (playerCallBackBlock)playerBlock;
```
| - | - |
|-------|----|
| 接口名 | open: openStatus: playerStatus: |
| 功能 | 播放源直接建立连接 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|dataSourceAddreess|NSString *|in|必须|播放地址：被叫方一定要传入正确，详见[羚羊云url格式解析](http://doc.topvdn.com/api/#!public-doc/url_format.md)|
|openBlock|void (^)(LYstatusCode statusCode, NSString *errorString)|in|必须|statusCode：连接成功与否标识|
|playerBlock|playerCallBackBlock|in|必须|播放过程中的状态回调|
**注意**：该方法只有被叫方才调用，主叫方不调用该方法。

##7 关闭通话连接
```
- (void)close: (NSString *)dataSourceAddreess;
```
| - | - |
|-------|----|
| 接口名 | close: |
| 功能 | 关闭播放 **注意**：该方法关闭播放器，调用open之后一定要调用该方法释放底层资源|
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|dataSourceAddreess|NSString *|in|必须|播放地址|

##8 视频通话控制

###8.1 切换码率
```
- (void) setVideoEncodeBitrateLevel: (LYVideoStreamingQualityLevel)qualityLevel;
```
| - | - |
|-------|----|
| 接口名 | setVideoEncodeBitrateLevel: |
| 功能 | 改接口设置的码率是推流码率。要改变对方的码率请消息通知对方调用该接口让对方传输码率改变 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|qualityLevel|LYVideoStreamingQualityLevel|in|必须|码率等级|

###8.2 开始推视频流
```
- (void) startSendVideoData;
```
| - | - |
|-------|----|
| 接口名 | startSendVideoData |
| 功能 | 视频流开始往平台推送：单独推视频流， |
| 返回值 | 无 |

###8.3 停止推视频流
```
- (void) stopSendVideoData; 
```
| - | - |
|-------|----|
| 接口名 | stopSendVideoData |
| 功能 | 停止推流到平台：单独停止视频流 |
| 返回值 | 无 |

###8.4 开始推音频流
```
- (void) startSendAudioData;
```
| - | - |
|-------|----|
| 接口名 | startSendAudioData |
| 功能 | 开始推音频流：单独开始音频流 |
| 返回值 | 无 |

###8.5 停止推音频流
```
- (void) stopSendAudioData;
```
| - | - |
|-------|----|
| 接口名 | stopSendAudioData |
| 功能 | 开始推音频流：单独开始音频流 |
| 返回值 | 无 |

###8.6 切换前后置摄像头
```
- (void) switchCamera: (LYCaptureCameraMode)cameraMode
          switchBlock: (void (^)(LYstatusCode statusCode, NSString *errorString))switchBlock;	
```
| - | - |
|-------|----|
| 接口名 | switchCamera: switchBlock: |
| 功能 | 切换摄像头类型 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|cameraMode|LYCaptureCameraMode|in|必须|前后置摄像头。|
|switchBlock|void (^)(LYstatusCode statusCode, NSString *errorString)|in|必须|切换成功与否回调|

###8.7 开关闪光灯
```
- (void) turnTorchAndFlashOn: (BOOL)on
                      status: (void (^)(LYstatusCode statusCode, NSString *errorString))turnBlock;	
```
| - | - |
|-------|----|
| 接口名 | turnTorchAndFlashOn: status: |
| 功能 | 打开或者关闭闪光灯 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|on|BOOL|in|必须|是否打开闪光灯|
|turnBlock|void (^)(LYstatusCode statusCode, NSString *errorString)|in|必须|打开或者关闭状态回调|

###8.8 打开声音
```
- (NSInteger)unmute: (NSString *)dataSourceAddreess;
```
| - | - |
|-------|----|
| 接口名 | unmute: |
| 功能 | 打开声音播放|
| 返回值 | 打开成功为0，失败为-1 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|dataSourceAddreess|NSString *|in|必须|播放地址|

###8.9 关闭声音
```
- (void) mute: (NSString *)dataSourceAddreess;
```
| - | - |
|-------|----|
| 接口名 | mute: |
| 功能 | 关闭声音播放|
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|dataSourceAddreess|NSString *|in|必须|播放地址|

###8.10 创建视频截图
```
- (void)snapshot: (NSString *)dataSourceAddreess path: (NSString *)path
          status:(void (^)(LYstatusCode statusCode, NSString *errorString))snapshotBlock; 
```
| - | - |
|-------|----|
| 接口名 | snapshot: status: |
| 功能 | 创建视频截图|
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|dataSourceAddreess|NSString *|in|必须|播放地址|
|path|NSString *|in|必须|路径：包括文件名-->后缀jpg格式|
|snapshotBlock|void (^)(LYstatusCode statusCode, NSString *errorString)|in|必须|截图回调|

###8.11 创建视频录像
```
- (void)startLocalRecord: (NSString *)dataSourceAddreess: (NSString *)path
                  status: (void (^)(LYstatusCode statusCode, NSString *errorString))startRecordBlock;
```
| - | - |
|-------|----|
| 接口名 | startLocalRecord: status: |
| 功能 | 创建视频录像|
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|dataSourceAddreess|NSString *|in|必须|播放地址|
|path|NSString *|in|必须|路径：包括文件名-->后缀mp4格式|
|startRecordBlock|void (^)(LYstatusCode statusCode, NSString *errorString)|in|必须|录像回调|

###8.12 结束视频录像
```
- (void)stopLocalRecord: (NSString *)dataSourceAddreess: (void (^)(NSInteger size, NSInteger time))stopLocalRecordBlock;
```
| - | - |
|-------|----|
| 接口名 | stopLocalRecord: |
| 功能 | 结束视频录像|
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|dataSourceAddreess|NSString *|in|必须|播放地址|
|stopLocalRecordBlock|void (^)(NSInteger size, NSInteger time)|in|必须|录像回调：size:录制大小，单位:KB  time:录制时长，单位：s|

##9 获取错误信息
```
- (NSString *) getCurrentErrorInfo;
```
| - | - |
|-------|----|
| 接口名 | getCurrentErrorInfo |
| 功能 | 获取当前的错误信息，如果为nil或者 |
| 返回值 | 无 |

##10 获取当前采集帧图片
```
- (void) getCurrentFrameImage: (void (^)(UIImage *image, char *imageBuffer, int bufferLength))success;
```
| - | - |
|-------|----|
| 接口名 | getCurrentFrameImage: |
| 功能 | 获取当前摄像头采集的帧数据对应UIImage |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|success|void (^)(UIImage \*image, char \*imageBuffer, int bufferLength)|in|必须|image:UIImage;imageBuffer:图片数据；bufferLength:数据长度|

##11 获取流媒体参数
```
-(NSString *)getMediaParam: (NSString *)dataSourceAddress mediaParam:(LYStreamMediaParam)streamMediaParam;
```
| - | - |
|-------|----|
| 接口名 | getMediaParam: mediaParam: |
| 功能 | 获取播放流媒体信息数据。 |
| 返回值 | 当前流媒体信息数据 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|dataSourceAddreess|NSString *|in|必须|播放地址|
|stremMediaParam|LYStreamMediaParam|in|必须|见流媒体参数枚举|
**注意**：该接口目前预留，获取流媒体参数为空。

#### 相关链接
[羚羊云SDK服务架构](http://doc.topvdn.com/api/index.html#!public-doc/start_archit.md)
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)
