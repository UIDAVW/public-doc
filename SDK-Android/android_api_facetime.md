#羚羊云Android API手册-视频通话接口

接口名称：LYFaceTime
 
##1 设置本地画面预览
```
public void setLocalPreview(LYGLCameraView previewView);
```
| - | - |
|-------|----|
| 接口名 | setLocalPreview |
| 功能 | 设置本地预览视图,建议在OnCreate()方法中调用该接口,如无需本地预览，则无需调用该接口，且布局文件中也不要设置预览控件； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|previewView|LYGLCameraView|In|--|对glsurfaceview实现了封装的自定义View用来实现本地预览，详见：预览器接口；|

##2 设置远程画面预览
```
public void setRemoteView(String remoteUrl, VideoPlayerView view);
```
| - | - |
|-------|----|
| 接口名 | setRemoteView |
| 功能 | 设置远程播放器； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|remoteUrl|String|In|--|此参数作为预留，目前设置为null；|
|view|VideoPlayerView|In|--|播放展示对方视频的View；|

##3 建立通话连接
```
public void openRemote(String remoteUrl, CallBackListener<Integer> callBackListener);
```
| - | - |
|-------|----|
| 接口名 | openRemote |
| 功能 | 打开通话连接并开始视频通话，主动呼叫方无需调用此接口，被呼叫方一定必须调用此接口； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|remoteUrl|String|In|--|远程连接，内容格式和意义请参见[羚羊云播放源url格式解析](http://doc.topvdn.com/api/#!public-doc/url_format.md)|
|callBackListener|CallBackListener|In|--|监听结果回调，onSuccess(T t)成功，onError(LYException exception)失败；|

##4 关闭通话连接
```
public void closeRemote(String remoteUrl);
```
| - | - |
|-------|----|
| 接口名 | closeRemote |
| 功能 | 关闭视频通话连接，通话的任意一方都可主动调用此接口关闭视频通话；一方调用此接口后，对方会收到一个连接断开的消息，收到该消息后也必须调用此接口。 |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|remoteUrl|String|In|--|远程连接地址，目前传null;|

##5 释放接口资源
```
public void release();
```
| - | - |
|-------|----|
| 接口名 | release |
| 功能 | 释放编码器，音视频采集器，相关工作线程等资源. **必须在断开连接后调用**，该实例不能再被使用。 |
| 返回值 | 无 |

##6 视频通话控制

###6.1 开始视频采集发送
```
public void startVideoRecording();
```
| - | - |
|-------|----|
| 接口名 | startVideoRecording |
| 功能 | 视频通话中重新开始视频数据发送 |
| 返回值 | 无 |

###6.2 停止视频采集发送
```
public void stopVideoRecording();
```
| - | - |
|-------|----|
| 接口名 | stopVideoRecording |
| 功能 | 在直播页面调用此方法，摄像头会继续采集数据，但不发送；在切到后台的时候调用此方法，当前应用会停止采集，释放对摄像头的锁定；如果切到后台的时候，不调用此方法，摄像头会继续采集发送视频数据(Android 4.3及以上版本)； |
| 返回值 | 无 |

###6.3 开始音频采集发送
```
public void startAudioRecording();
```
| - | - |
|-------|----|
| 接口名 | startAudioRecording |
| 功能 | 视频通话过程中开始视频数据发送 |
| 返回值 | 无 |

###6.4 停止音频采集发送
```
public void stopAudioRecording();
```
| - | - |
|-------|----|
| 接口名 | stopAudioRecording |
| 功能 | 视频通话过程中停止声音采集发送，释放对麦克风的锁定 |
| 返回值 | 无 |

###6.5 关闭音频播放
```
public void mute(String remoteUrl);
```
| - | - |
|-------|----|
| 接口名 | mute |
| 功能 | 视频通话过程中关闭音频播放 |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|remoteUrl|String|In|--|远程连接地址，目前传null|

###6.6 开启音频播放
```
public void unmute(String remoteUrl);
```
| - | - |
|-------|----|
| 接口名 | unmute |
| 功能 | 视频通话过程中开启音频播放 |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|remoteUrl|String|In|--|远程连接地址，目前传null|

###6.7 重置采集编码参数
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

###6.8 暂停以切入后台
```
void onHostActivityPaused();
```
| - | - |
|-------|----|
| 接口名 | onHostActivityPaused |
| 功能 | 在宿主Activity onPause()回调时使用，节省系统资源 仅语音通讯时无需调用，支持后台语音。若要放弃对camera的使用权，先停止采集再调用此方法，否则，不会释放camera，而且会继续采集。|
| 返回值 | 无 |

###6.9 从后台恢复播放
```
void onHostActivityResumed();
```
| - | - |
|-------|----|
| 接口名 | onHostActivityResumed |
| 功能 | 在宿主Activity onResume()回调时使用，仅语音通讯时无需调用，支持后台语音,若暂停前已停止采集，则调用此方法获取对camera的使用权，再调用开始采集. |
| 返回值 | 无 |

###6.10 动态设置视频是否自适应
```
public void setFitScreen(boolean isFit);
```
| - | - |
|-------|----|
| 接口名 | setFitScreen |
| 功能 | 设置视频是否自适应，必须在调用设置远程播放器接口之后调用。如果播放器view和获取的视频流宽高比不一致时，设置为true，则将将画面进行裁剪以适应View，设置为false，则不裁剪画面，可能导致画面变形。|
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|isFit|boolean|In|--|true 为自适应，false 为不自适应 |

###6.11 动态设置码率
```
public void setVideoBitrate(int aBitrate);
```
| - | - |
|-------|----|
| 接口名 | setVideoBitrate |
| 功能 | 视频通话过程中动态设置码率 |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aBitrate|int|In|--|期望设置的码率，单位是kbps,没有限制范围，建议设置200、500、800，分别对应普通、标清、高清 |

##7 设备控制

###7.1 获取摄像机列表
```
List<Camera.Size> getSupportedPreviewSizes();
```
| - | - |
|-------|----|
| 接口名 | getSupportedPreviewSizes |
| 功能 | 获取当前摄像机支持的预览列表； |
| 返回值 | 当前摄像机支持的预览列表； |

###7.2 获取当前摄像机编号
```
int getCurrentCamera();
```
| - | - |
|-------|----|
| 接口名 | getCurrentCamera |
| 功能 | 获取当前摄像机编号； |
| 返回值 | 当前摄像机编号； |

###7.3 获取期望的摄像机编号
```
int getDesiredCamera();
```
| - | - |
|-------|----|
| 接口名 | getDesiredCamera |
| 功能 | 获取期望的摄像机编号； |
| 返回值 | 摄像机编号； |

###7.4 切换摄像头
```
void switchCamera();
```
| - | - |
|-------|----|
| 接口名 | switchCamera |
| 功能 | 切换至另一个摄像头，从摄像机列表中循环切换，设置效果在预览状态下立即生效； |
| 返回值 | 无 |

###7.5 设置摄像头类型
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

###7.6 获取闪光灯模式
```
String getFlashMode();
```
| - | - |
|-------|----|
| 接口名 | getFlashMode |
| 功能 | 获取当前闪光灯模式； |
| 返回值 | 无 |

###7.7 切换闪光灯
```
String toggleFlash();
```
| - | - |
|-------|----|
| 接口名 | toggleFlash |
| 功能 | 若当前闪光灯为关闭，调用后打开，反之同理； |
| 返回值 | 无 |

###7.8 设置闪光灯类型
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


#### 相关链接
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)