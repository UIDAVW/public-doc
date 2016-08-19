#羚羊云Android API手册-直播推流接口

接口名称：LYLiveBroadcast

##1 设置本地预览视图
```
void setLocalPreview(LYGLCameraView glSurfaceView);
```
| - | - |
|-------|----|
| 接口名 | setLocalPreview |
| 功能 | 设置本地预览视图,建议在OnResume()方法中调用该接口,如无需本地预览，则无需调用该接口，且布局文件中也不要设置预览控件 |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|glSurfaceView|LYGLCameraView|in|必须|对glsurfaceview进行了封装的自定义View，用来显示视频直播推流的本地预览，详见：预览器接口|

##2 开始直播推流
```
void startBroadcasting(String remoteUrl);
```
| - | - |
|-------|----|
| 接口名 | startBroadcasting |
| 功能 | 开始直播推流 |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|remoteUrl|String|in|必须|远程播放地址；内容格式和意义请参见[羚羊云播放源url格式解析](http://doc.topvdn.com/api/#!public-doc/url_format.md)|

##3 支持直播录制
该功能需要在调用`startBroadcasting`接口方法时传入特定格式的URL，按照[羚羊云推拉流URL格式](http://doc.topvdn.com/api/public-doc/#!url_format.md)设置`protocolType`、`connectType`和`mode`字段。例如：
```
topvdn://183.57.151.161:1935?protocolType=2&connectType=1&token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069&mode=4
```
其中：
- `protocolType` 必须为2，表示使用QSTP协议推流。
- `connectType` 必须为1，表示推流端。
- `mode` 值可为3，表示使用QSTP协议推流，私有模式，并开启云存储；也可为4，表示使用QSTP协议推流，公众模式，并开启云存储。

##4 停止直播推流
```
void stopBroadcasting();
```
| - | - |
|-------|----|
| 接口名 | stopBroadcasting |
| 功能 | 关闭广播，除手动点击停止调用外，在onPause()方法里也要调用该接口停止直播 |
| 返回值 | 无 |

##5 是否正在直播
```
boolean isBroadcasting();
```
| - | - |
|-------|----|
| 接口名 | isBroadcasting |
| 功能 | 判断是否正在直播 |
| 返回值 | 返回直播状态 true: 正在直播  false: 已停止直播 |

##6 设置推流状态变化回调
```
void setBroadcastListener(BroadcastStateChangeListener listener);
```
| - | - |
|-------|----|
| 接口名 | setBroadcastListener |
| 功能 | 设置广播状态变化监听回调 |
| 返回值 | 无 |
| 参数列表 | 参见下面的推流状态变化回调函数 |

##7 推流状态变化回调函数
```
    interface BroadcastStateChangeListener {
        void onBroadcastStart();
        void onBroadcastLive();
        void onBroadcastStop();
        void onBroadcastError(LYException exception);
    }
```
| - | - |
|-------|----|
| 接口名 | BroadcastStateChangeListener |
| 功能 | 广播状态变化回调监听，包括直播开始，正在直播，直播停止，错误等 |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|exception|LYException|out|--|包含错误信息和错误码。详见：数据类型-错误信息 |

##8 直播控制

###8.1 开始视频采集发送
```
void startVideoRecording();
```
| - | - |
|-------|----|
| 接口名 | startVideoRecording |
| 功能 | 开始视频数据发送 |
| 返回值 | 无 |

###8.2 停止视频采集发送
```
void stopVideoRecording();
```
| - | - |
|-------|----|
| 接口名 | stopVideoRecording |
| 功能 | 在直播页面调用此方法，摄像头会继续采集数据，但不发送；在切到后台的时候调用此方法，当前应用会停止采集，释放对摄像头的锁定；如果切到后台的时候，不调用此方法，摄像头会继续采集发送视频数据(Android 4.3及以上版本)； |
| 返回值 | 无 |

###8.3 开始音频采集发送
```
void startAudioRecording();
```
| - | - |
|-------|----|
| 接口名 | startAudioRecording |
| 功能 | 开始音频数据发送 |
| 返回值 | 无 |

###8.4 停止音频采集发送
```
void stopAudioRecording();
```
| - | - |
|-------|----|
| 接口名 | stopAudioRecording |
| 功能 | 直播过程中停止声音采集发送，释放对麦克风的锁定 |
| 返回值 | 无 |

###8.5 重置采集编码参数
```
 void reset(SessionConfig config);
```
| - | - |
|-------|----|
| 接口名 | reset |
| 功能 | 重新初始化直播推流相关参数. 必须在停止直播推流后调用。 |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|config|SessionConfig|In|必须|配置直播推流和采集相关属性，包括音视频编码等相关信息。详见：数据类型_直播流和采集相关属性配置|

###8.6 暂停以切入后台
```
void onHostActivityPaused();
```
| - | - |
|-------|----|
| 接口名 | onHostActivityPaused |
| 功能 | 在宿主Activity onPause()回调时使用，节省系统资源 仅语音通讯时无需调用，支持后台语音。若要放弃对camera的使用权，先停止采集再调用此方法，否则，不会释放camera，而且会继续采集。|
| 返回值 | 无 |

###8.7 从后台恢复播放
```
void onHostActivityResumed();
```
| - | - |
|-------|----|
| 接口名 | onHostActivityResumed |
| 功能 | 在宿主Activity onResume()回调时使用，仅语音通讯时无需调用，支持后台语音。若暂停前已停止采集，则调用此方法获取对camera的使用权，再调用'开始采集'方法。 |
| 返回值 | 无 |

##9 设备控制

###9.1 获取摄像机列表
```
List<Camera.Size> getSupportedPreviewSizes();
```
| - | - |
|-------|----|
| 接口名 | getSupportedPreviewSizes |
| 功能 | 获取当前摄像机支持的预览列表； |
| 返回值 | 当前摄像机支持的预览列表； |

###9.2 获取当前摄像机编号
```
int getCurrentCamera();
```
| - | - |
|-------|----|
| 接口名 | getCurrentCamera |
| 功能 | 获取当前摄像机编号； |
| 返回值 | 当前摄像机编号； |

###9.3 获取期望的摄像机编号
```
int getDesiredCamera();
```
| - | - |
|-------|----|
| 接口名 | getDesiredCamera |
| 功能 | 获取期望的摄像机编号； |
| 返回值 | 摄像机编号； |

###9.4 切换摄像头
```
void switchCamera();
```
| - | - |
|-------|----|
| 接口名 | switchCamera |
| 功能 | 切换至另一个摄像头，从摄像机列表中循环切换，设置效果在预览状态下立即生效； |
| 返回值 | 无 |

###9.5 设置摄像头类型
```
void setCameraType(int camera);
```
| - | - |
|-------|----|
| 接口名 | setCameraType |
| 功能 | 传入指定的摄像机编号设置相应的摄像头 |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|camera|int|In|必须|{android.hardware.Camera.CameraInfo#CAMERA_FACING_BACK} or {android.hardware.Camera.CameraInfo#CAMERA_FACING_FRONT}|

###9.6 获取闪光灯模式
```
String getFlashMode();
```
| - | - |
|-------|----|
| 接口名 | getFlashMode |
| 功能 | 获取当前闪光灯模式； |
| 返回值 | 无 |

###9.7 切换闪光灯
```
String toggleFlash();
```
| - | - |
|-------|----|
| 接口名 | toggleFlash |
| 功能 | 若当前闪光灯为关闭，调用后打开，反之同理； |
| 返回值 | 无 |

###9.8 设置闪光灯类型
```
void setFlashMode(String desiredFlash);
```
| - | - |
|-------|----|
| 接口名 | setFlashMode |
| 功能 | 根据传入的参数设置相应的闪光灯类型； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|desiredFlash|String|In|必须|{android.hardware.Camera.Parameters#FLASH_MODE_TORCH} or {android.hardware.Camera.Parameters#FLASH_MODE_OFF} ect|

##10 释放接口资源
```
void release();
```
| - | - |
|-------|----|
| 接口名 | release |
| 功能 | 释放编码器，音视频采集器，相关工作线程等资源. 必须在停止直播推流后调用，该实例不能再被使用。 |
| 返回值 | 无 |


#### 相关链接
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)