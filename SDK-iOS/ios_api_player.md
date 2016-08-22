#羚羊云iOS API手册-播放器接口

>接口名称：LYPlayer

播放器模块可单独实现播放直播流、播放存储在羚羊云的录像流等功能。

##1 设置播放器配置
```
- (void) setViewWithConfiguration: (LYPlayerConfiguration *)playerConfiguration;
```
| - | - |
|-------|----|
| 接口名 | setViewWithConfiguration: |
| 功能 | 设置播放器的配置信息。切忌初始化对象完成之后调用设置，否则后续操作无法进行 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|playerConfiguration|LYPlayerConfiguration *|in|必须|播放器配置类，详见数据类型章节|

##2 更改播放器位置 
```
- (void)setViewFrame: (CGRect)frame;
```
| - | - |
|-------|----|
| 接口名 | setViewFrame: |
| 功能 | 重新设置或者改变播放器View的位置 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|frame|CGRect|in|必须|播放器位置|

##3 打开播放器
```
- (void)open: (NSString *)dataSourceAddreess
  openStatus: (void (^)(LYstatusCode statusCode, NSString *errorString))openBlock
playerStatus: (playerCallBackBlock)playerBlock;
```
| - | - |
|-------|----|
| 接口名 | open: openStatus: playerStatus: |
| 功能 | 打开播放器，根据对应的播放地址进行连接以及渲染，播放状态实时回调 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|dataSourceAddreess|NSString *|in|必须|播放地址，详见[羚羊云url格式解析](http://doc.topvdn.com/api/#!public-doc/url_format.md)|
|openBlock|void (^)(LYstatusCode statusCode, NSString *errorString)|in|必须|打开状态回调|
|playerBlock|playerCallBackBlock|in|必须|播放状态回调|

##4 关闭播放器
```
- (void)close;
```
| - | - |
|-------|----|
| 接口名 | close |
| 功能 | 关闭播放器，断开连接以及是否渲染资源，调用opne之后一定要调用close； |
| 返回值 | 无 |

##5 播放控制

###5.1 打开声音
```
- (NSInteger)unmute;
```
| - | - |
|-------|----|
| 接口名 | unmute |
| 功能 | 打开播放器声音 |
| 返回值 | 打开成功与否。 |

###5.2 关闭声音 
```
- (void)mute;
```
| - | - |
|-------|----|
| 接口名 | mute |
| 功能 | 关闭播放器声音 |
| 返回值 | 无 |

###5.3 开始对讲
```
- (void)startTalkWithSampleRate: (NSInteger)sampleRate channel: (NSInteger)channel;
```
| - | - |
|-------|----|
| 接口名 | startTalkWithSampleRate: channel: |
| 功能 | 与当前播放的视频采集设备进行对讲 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
| sampleRate | NSInteger |in|必须|音频采样率|
| channel | NSInteger |in|必须|通道号|

###5.4 停止对讲 
```
- (void)stopTalk;
```
| - | - |
|-------|----|
| 接口名 | stopTalk |
| 功能 | 停止对讲 |
| 返回值 | 无 |

###5.5 播放定位 
```
- (void)seek: (NSInteger)timestamp
      status: (void (^)(LYstatusCode statusCode))seekBlock;
```
| - | - |
|-------|----|
| 接口名 | seek: status: |
| 功能 | 设置播放位置，定位播放时间点：只针对观看历史有效， |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|timestamp|NSInteger|in|必须|相对起始播放时间所移动的秒数|
|seekBlock|void (^)(LYstatusCode statusCode)|in|可选|状态回调|

##6 获取流媒体数据
```
- (NSString *)getMediaParam:(LYStreamMediaParam)streamMediaParam;
```
| - | - |
|-------|----|
| 接口名 | getMediaParam: |
| 功能 | 获取流媒体信息数据 |
| 返回值 | 对应序号的流媒体信息 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|streamMediaParam|LYStreamMediaParam|in|必须|流媒体参数枚举|

##7 获取播放时间
```
- (NSInteger)getCurrentPlayTime;
```
| - | - |
|-------|----|
| 接口名 | getCurrentPlayTime |
| 功能 | 获取观看历史时对应的播放时间戳；只针对观看历史有效 |
| 返回值 | 点播播放位置：时间戳 |

##8 创建视频截图
```
- (void)snapshot: (NSString *)path
          status: (void (^)(LYstatusCode statusCode, NSString *errorString))snapshotBlock;
```
| - | - |
|-------|----|
| 接口名 | snapshot: status: |
| 功能 | 创建视频截图；路径包括文件名，后缀.jpg |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|path|NSString *|in|必须|保存路径；|
|snapshotBlock|void (^)(LYstatusCode statusCode, NSString *errorString)|in|必须|截图状态回调|

##9 开始本地录像
```
- (void)startLocalRecord: (NSString *)path
                  status: (void (^)(LYstatusCode statusCode, NSString *errorString))startRecordBlock;
```
| - | - |
|-------|----|
| 接口名 | startLocalRecord: status: |
| 功能 | 开始本地录像，在开始播放后调用；路径包括文件名，后缀.mp4 |
| 返回值 | 无 |


|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|filePath|NSString *|in|必须|保存路径；|
|startRecordBlock|void (^)(LYstatusCode statusCode, NSString *errorString)|in|必须|开始录像状态回调|

##10 结束本地录像   
```
- (void)stopLocalRecord；
```
| - | - |
|-------|----|
| 接口名 | stopLocalRecord |
| 功能 | 结束本地录像； |
| 返回值 | 无 |

#### 相关链接
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)