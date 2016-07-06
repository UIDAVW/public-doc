#羚羊云Android API手册
##1 数据类型
###1.1 媒体参数类型
```
public interface IMediaParamProtocol {
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
    //7.获取QSTP转发ip地址
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

###1.2 画面缩放比例
```
public interface IScreenRatioChanger {
    //视频等比最佳
    int TYPE_PLAYER_RATIO_PROP_BEST = 0;
    //视频等比全屏
    int TYPE_PLAYER_RATIO_PROP_FULL = 1;
    //16x9
    int TYPE_PLAYER_RATIO_PROP_16X9 = 2;
    //5x4
    int TYPE_PLAYER_RATIO_PROP_5X4 = 3;
    //4x3
    int TYPE_PLAYER_RATIO_PROP_4X3 = 4;
    //3x4
    int TYPE_PLAYER_RATIO_PROP_3X4 = 5;
    //9x16
    int TYPE_PLAYER_RATIO_PROP_9X16 = 6;
}
```

###1.3 SessionConfig配置直播推流参数
```
    // 设置图像的旋转角度 只能是 0,90,180,270       
    public Builder withCameraDisplayOrientation(int displayOrientation) ;
    // 是否需要使用音频
    public Builder useAudio(boolean use) ;
    //是否需要使用视频
    public Builder useVideo(boolean use) ;
    // 期望摄像机
    public Builder withDesireadCamera(int camera);
    //设置视频宽高
    public Builder withVideoResolution(int width, int height) ;
    // 使用视频硬编码
    public Builder useHardVideoEncode(boolean encode);
    //使用音频硬编码
    public Builder useHardAudioEncode(boolean encode);
    //使用视频硬编码
    public Builder useAudioEffect(boolean use) ;
    // 设置视频码率
    public Builder withVideoBitrate(int bitrate) ;
    //设置音频采样频率
    public Builder withAudioSampleRateInHz(int samplerate) ;
    //设置音频采样码率
    public Builder withAudioBitrate(int bitrate);
    //设置省道数 1代表单声道，2代表立体声
    public Builder withAudioChannels(int numChannels);
```

###1.4 预览View形状参数
```
public enum SurfaceFrameShape {
    RECTANGLE, //四边形
    TRIANGLE, //三角形
    CIRCLE   //圆形
}
```

###1.5 播放缓冲时长参数
```
    //atlp播放最小缓冲时长 
    public Builder withMinAtlpBufferTime(int time) ;
    //atlp播放最大缓冲时长 
    public Builder withMaxAtlpBufferTime(int time);
    //aulp播放最小缓冲时长 
    public Builder withMinAulpBufferTime(int time) ;
    //aulp播放最大缓冲时长 
    public Builder withMaxAulpBufferTime(int time) ;
    //是否静音
    public Builder withMute(boolean isMute) ;
```

###1.6 错误信息
```
public class LYException extends Exception {
    //错误信息
    private String mMessage; 
    //错误码
    private int mCode; 
    //获取错误信息
    public String getMessage() {
        return mMessage;
    }
    //获取错误码
    public int getCode() {
        return mCode;
    }
}
```

##2 云服务接口
接口名称：LYService
    
###2.2 启动云服务
```
void startCloudService(String userToken, String configString, CallBackListener<Long> listener);
```
| - | - |
|-------|----|
| 接口名 | startCloudService |
| 功能 | 调用了此api之后,平台相关凭证及资源开始准备，并且在回调接口通知云服务是否启动成功！ 建议在客户端登录验证逻辑通过之后即刻调用。服务启动之后，相关的平台接口才能正常使用。 |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|userToken|String|in|必须|设备token，由第三方后台生成。|
|configString|String|in|必须|配置串，从第三方后台获取。|
|listener|CallBackListener<Long>|in|必须|启动结果监听回调，返回成功或失败|

**注意**：

**userToken**：设备token，由应用后台生成，格式如下：<br>
2147549953\_1458979882\_1469999882\_bad3686a62a7aba595df3fb4c9c400e9。<br>
token的内容格式及意义请见[羚羊云token认证机制](http://doc.topvdn.com/api/#!public-doc/token_format.md)

**configString**：配置串，从后台获取(无需解析)，格式如下：
[Config]\r\nIsDebug=0\r\nLocalBasePort=8200\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nUdpSendInterval=2\r\nConnectTimeout=10000\r\nTransferTimeout=10000\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n[LogServer]\r\nCount=1\r\nIP1=120.26.74.53\r\nPort1=80\r\n<br>
调用者不必知道该字符串内容所表示的意义。
应用后台调用[Web API的'查询设备状态'接口](http://doc.topvdn.com/api/#!web_api_v2.md#2.1.1_%E6%9F%A5%E8%AF%A2%E8%AE%BE%E5%A4%87%E7%8A%B6%E6%80%81)获取，接口返回的"init_string"字段即配置串。

###2.3 停止云服务
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
String getSDKVersion();
```
| - | - |
|-------|----|
| 接口名 | getSDKVersion |
| 功能 | 获取Android SDK和平台版本号； |
| 返回值 | 返回Android SDK和平台版本号 |
| 参数列表 | 无 |

###2.5 日志打印开关
```
void setNativeLoggingEnabled(boolean enabled);
```
| - | - |
|-------|----|
| 接口名 | setNativeLoggingEnabled |
| 功能 | 是否开启底层日志打印，设置开启的时候，开发者可在log中看到底层日志，tag:[JPlayer] |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|enabled|boolean|in|必须|true为开启,false为不开启(默认)|

###2.6 用户是否在线
```
boolean isOnline();
```
| - | - |
|-------|----|
| 接口名 | isOnline |
| 功能 | 获取用户在线状态； |
| 返回值 | 返回用户在线状态 true: 在线  false: 为离线|
| 参数列表 | 无 |


###2.7 消息结构定义
```
    /**
     * 平台消息回调
     */
    class CloudMessage {
        public String Name;
        public String Message;
        public String SrcID;

        public CloudMessage(String name,
                            String message,
                            String srcID) {

            this.Name = name;
            this.Message = message;
            this.SrcID = srcID;
        }
    }
```

###2.8 设置消息接收回调
```
void setCloudMessageListener(AcceptMessageListener acceptCloudMessageListener);
```
| - | - |
|-------|----|
| 接口名 | setCloudMessageListener |
| 功能 | 设置云消息接收回调，建议开启云服务后即刻调用，设置了该监听才能收到关闭、设备绑定确认、设备配置状态等云消息； |
| 返回值 | 无|
| 参数列表 | 请参见下面的消息接收回调函数 |

###2.9 消息接收回调函数
```
    interface AcceptMessageListener {
        void accept(CloudMessage message);
    }
```
| - | - |
|-------|----|
| 接口名 | AcceptMessageListener |
| 功能 | 视频通话、关闭、设备绑定确认、设备配置状态等云消息接收回调监听； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|message|CloudMessage|out|--|请参见本文数据类型章节的消息结构定义|

##3 预览器接口
接口名称：LYGLCameraView

预览控件可用于设备直播，互联等的本地预览，可设置成四边形，圆形，三角形等形状。

###3.1 预览View布局
该布局是基于GLSurfaceView的自定义预览控件，在使用过程中，只需要引入预览控件的相应的layout界面即可。

    <com.lingyang.sdk.view.LYGLCameraEncoderView
        android:id="@+id/ly_preview"
        android:layout_width="match_parent"
        android:layout_height="match_parent" />

###3.2 设置预览形状
```
void setShape(SurfaceFrameShape shape);
```
| - | - |
|-------|----|
| 接口名 | setShape |
| 功能 | 设置本地预览控件形状，在设置预览之前调用|
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|shape|SurfaceFrameShape|in|必须|预览形状参数，目前有四边形，三角形和圆形三种，详见:数据类型_预览View形状参数|

###3.3 将预览View设置为视图最外层
```
void setZOrderOnTop(boolean onTop);
```
| - | - |
|-------|----|
| 接口名 | setShape |
| 功能 | 将预览View设置为视图最外层，在圆形预览和三角形预览时必须调用此方法才能看到预览下层的View|
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|onTop|boolean|in|必须|是否将预览View设置为视图最外层，true：设置为最外层；false：不设置为最外层|


##4 直播推流接口
接口名称：LYLiveBroadcast
  

###4.1 设置本地预览视图
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

###4.2 开始直播推流
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

###4.3 停止直播推流
```
void stopBroadcasting();
```
| - | - |
|-------|----|
| 接口名 | stopBroadcasting |
| 功能 | 关闭广播，除手动点击停止调用外，在onPause()方法里也要调用该接口停止直播 |
| 返回值 | 无 |

###4.4 释放接口资源
```
void release();
```
| - | - |
|-------|----|
| 接口名 | release |
| 功能 | 释放编码器，音视频采集器，相关工作线程等资源. 必须在停止直播推流后调用，该实例不能再被使用。 |
| 返回值 | 无 |

###4.5 是否正在直播
```
boolean isBroadcasting();
```
| - | - |
|-------|----|
| 接口名 | isBroadcasting |
| 功能 | 判断是否正在直播 |
| 返回值 | 返回直播状态 true: 正在直播  false: 已停止直播 |

###4.6 设置推流状态变化回调
```
void setBroadcastListener(BroadcastStateChangeListener listener);
```
| - | - |
|-------|----|
| 接口名 | setBroadcastListener |
| 功能 | 设置广播状态变化监听回调 |
| 返回值 | 无 |
| 参数列表 | 参见下面的推流状态变化回调函数 |

###4.7 推流状态变化回调函数
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

###4.8 停止视频采集发送
```
void stopVideoRecording();
```
| - | - |
|-------|----|
| 接口名 | stopVideoRecording |
| 功能 | 在直播页面调用此方法，摄像头会继续采集数据，但不发送；在切到后台的时候调用此方法，当前应用会停止采集，释放对摄像头的锁定；如果切到后台的时候，不调用此方法，摄像头会继续采集发送视频数据(Android 4.3及以上版本)； |
| 返回值 | 无 |

###4.9 恢复视频采集发送
```
void startVideoRecording();
```
| - | - |
|-------|----|
| 接口名 | startVideoRecording |
| 功能 | 直播中重新开始视频数据发送 |
| 返回值 | 无 |

###4.10 恢复音频采集发送
```
void startAudioRecording();
```
| - | - |
|-------|----|
| 接口名 | startAudioRecording |
| 功能 | 直播过程中重新开始视频数据发送 |
| 返回值 | 无 |

###4.11 关闭音频采集发送
```
void stopAudioRecording();
```
| - | - |
|-------|----|
| 接口名 | stopAudioRecording |
| 功能 | 直播过程中停止声音采集发送，释放对麦克风的锁定 |
| 返回值 | 无 |

###4.12 重置采集编码参数
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

###4.13 暂停以切入后台
```
void onHostActivityPaused();
```
| - | - |
|-------|----|
| 接口名 | onHostActivityPaused |
| 功能 | 在宿主Activity onPause()回调时使用，节省系统资源 仅语音通讯时无需调用，支持后台语音。若要放弃对camera的使用权，先停止采集再调用此方法，否则，不会释放camera，而且会继续采集。|
| 返回值 | 无 |

###4.14 从后台恢复播放
```
void onHostActivityResumed();
```
| - | - |
|-------|----|
| 接口名 | onHostActivityResumed |
| 功能 | 在宿主Activity onResume()回调时使用，仅语音通讯时无需调用，支持后台语音。若暂停前已停止采集，则调用此方法获取对camera的使用权，再调用'开始采集'方法。 |
| 返回值 | 无 |

###4.15 获取摄像机列表
```
List<Camera.Size> getSupportedPreviewSizes();
```
| - | - |
|-------|----|
| 接口名 | getSupportedPreviewSizes |
| 功能 | 获取当前摄像机支持的预览列表； |
| 返回值 | 当前摄像机支持的预览列表； |

###4.16 获取当前摄像机编号
```
int getCurrentCamera();
```
| - | - |
|-------|----|
| 接口名 | getCurrentCamera |
| 功能 | 获取当前摄像机编号； |
| 返回值 | 当前摄像机编号； |

###4.17 获取期望的摄像机编号
```
int getDesiredCamera();
```
| - | - |
|-------|----|
| 接口名 | getDesiredCamera |
| 功能 | 获取期望的摄像机编号； |
| 返回值 | 摄像机编号； |

###4.18 切换摄像头
```
void switchCamera();
```
| - | - |
|-------|----|
| 接口名 | switchCamera |
| 功能 | 切换至另一个摄像头，从摄像机列表中循环切换，设置效果在预览状态下立即生效； |
| 返回值 | 无 |

###4.19 设置摄像头类型
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

###4.20 获取闪光灯模式
```
String getFlashMode();
```
| - | - |
|-------|----|
| 接口名 | getFlashMode |
| 功能 | 获取当前闪光灯模式； |
| 返回值 | 无 |

###4.21 切换闪光灯
```
String toggleFlash();
```
| - | - |
|-------|----|
| 接口名 | toggleFlash |
| 功能 | 若当前闪光灯为关闭，调用后打开，反之同理； |
| 返回值 | 无 |

###4.22 设置闪光灯类型
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

##5 视频通话接口
接口名称：LYFaceTime
 
###5.1 设置本地预览
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

###5.2 设置远程播放器
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
|remoteUrl|String|In|--|远程播放地址，目前传null；|
|view|VideoPlayerView|In|--|播放展示View；|

###5.3 打开链接并推送数据
```
public void openRemote(String remoteUrl, CallBackListener<Integer> callBackListener);
```
| - | - |
|-------|----|
| 接口名 | openRemote |
| 功能 | 打开链接并推送数据,被连接方无需此操作； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|remoteUrl|String|In|--|远程连接，内容格式和意义请参见[羚羊云播放源url格式解析](http://doc.topvdn.com/api/#!public-doc/url_format.md)|
|callBackListener|CallBackListener|In|--|监听结果回调，onSuccess(T t)成功，onError(LYException exception)失败；|

###5.4 断开连接
```
public void closeRemote(String remoteUrl);
```
| - | - |
|-------|----|
| 接口名 | openRemote |
| 功能 | 打开链接并推送数据,被连接方无需此操作； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|remoteUrl|String|In|--|远程连接地址，目前传null;|

###5.5 释放接口资源
```
public void release();
```
| - | - |
|-------|----|
| 接口名 | release |
| 功能 | 释放编码器，音视频采集器，相关工作线程等资源. 必须在断开连接后调用，该实例不能再被使用。 |
| 返回值 | 无 |

###5.6 停止视频采集发送
```
public void stopVideoRecording();
```
| - | - |
|-------|----|
| 接口名 | stopVideoRecording |
| 功能 | 在直播页面调用此方法，摄像头会继续采集数据，但不发送；在切到后台的时候调用此方法，当前应用会停止采集，释放对摄像头的锁定；如果切到后台的时候，不调用此方法，摄像头会继续采集发送视频数据(Android 4.3及以上版本)； |
| 返回值 | 无 |

###5.7 恢复视频采集发送
```
public void startVideoRecording();
```
| - | - |
|-------|----|
| 接口名 | startVideoRecording |
| 功能 | 互联中重新开始视频数据发送 |
| 返回值 | 无 |

###5.8 恢复音频采集发送
```
public void startAudioRecording();
```
| - | - |
|-------|----|
| 接口名 | startAudioRecording |
| 功能 | 互联过程中重新开始视频数据发送 |
| 返回值 | 无 |

###5.9 关闭音频采集发送
```
public void stopAudioRecording();
```
| - | - |
|-------|----|
| 接口名 | stopAudioRecording |
| 功能 | 互联过程中停止声音采集发送，释放对麦克风的锁定 |
| 返回值 | 无 |

###5.10 关闭音频播放
```
public void mute(String remoteUrl);
```
| - | - |
|-------|----|
| 接口名 | mute |
| 功能 | 互联过程中关闭音频播放 |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|remoteUrl|String|In|--|远程连接地址，目前传null|

###5.11 开启音频播放
```
public void unmute(String remoteUrl);
```
| - | - |
|-------|----|
| 接口名 | unmute |
| 功能 | 互联过程中开启音频播放 |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|remoteUrl|String|In|--|远程连接地址，目前传null|

###5.12 重置采集编码参数
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

###5.13 暂停以切入后台
```
void onHostActivityPaused();
```
| - | - |
|-------|----|
| 接口名 | onHostActivityPaused |
| 功能 | 在宿主Activity onPause()回调时使用，节省系统资源 仅语音通讯时无需调用，支持后台语音。若要放弃对camera的使用权，先停止采集再调用此方法，否则，不会释放camera，而且会继续采集。|
| 返回值 | 无 |

###5.14 从后台恢复播放
```
void onHostActivityResumed();
```
| - | - |
|-------|----|
| 接口名 | onHostActivityResumed |
| 功能 | 在宿主Activity onResume()回调时使用，仅语音通讯时无需调用，支持后台语音,若暂停前已停止采集，则调用此方法获取对camera的使用权，再调用开始采集. |
| 返回值 | 无 |

###5.15 动态设置视频是否自适应
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

###5.16 动态设置码率
```
public void setVideoBitrate(int aBitrate);
```
| - | - |
|-------|----|
| 接口名 | setVideoBitrate |
| 功能 | 互联过程中动态设置码率 |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aBitrate|int|In|--|期望设置的码率，单位是kbps,没有限制范围，建议设置200、500、800，分别对应普通、标清、高清 |

###5.17 获取摄像机列表
```
List<Camera.Size> getSupportedPreviewSizes();
```
| - | - |
|-------|----|
| 接口名 | getSupportedPreviewSizes |
| 功能 | 获取当前摄像机支持的预览列表； |
| 返回值 | 当前摄像机支持的预览列表； |

###5.18 获取当前摄像机编号
```
int getCurrentCamera();
```
| - | - |
|-------|----|
| 接口名 | getCurrentCamera |
| 功能 | 获取当前摄像机编号； |
| 返回值 | 当前摄像机编号； |

###5.19 获取期望的摄像机编号
```
int getDesiredCamera();
```
| - | - |
|-------|----|
| 接口名 | getDesiredCamera |
| 功能 | 获取期望的摄像机编号； |
| 返回值 | 摄像机编号； |

###5.20 切换摄像头
```
void switchCamera();
```
| - | - |
|-------|----|
| 接口名 | switchCamera |
| 功能 | 切换至另一个摄像头，从摄像机列表中循环切换，设置效果在预览状态下立即生效； |
| 返回值 | 无 |

###5.21 设置摄像头类型
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

###5.22 获取闪光灯模式
```
String getFlashMode();
```
| - | - |
|-------|----|
| 接口名 | getFlashMode |
| 功能 | 获取当前闪光灯模式； |
| 返回值 | 无 |

###5.23 切换闪光灯
```
String toggleFlash();
```
| - | - |
|-------|----|
| 接口名 | toggleFlash |
| 功能 | 若当前闪光灯为关闭，调用后打开，反之同理； |
| 返回值 | 无 |

###5.24 设置闪光灯类型
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


##6 播放器接口
接口名称：LYPlayer

播放器模块可单独实现直播播放，摄像头直播播放，云存储播放，本地录像等功能。

###6.1 播放器布局
该布局是基于SurfaceView的自定义播放器控件，在使用过程中，只需要引入播放器控件的相应的layout界面即可。

    <com.lingyang.sdk.player.widget.LYPlayer
        android:id="@+id/ly_player"
        android:layout_width="match_parent"
        android:layout_height="match_parent" />
 
###6.2 设置播放源
```
public void setDataSource(String url)
```
| - | - |
|-------|----|
| 接口名 | setDataSource |
| 功能 | 根据传入的url判断播放类型，实例化IPlayer播放控制器，设置播放模式； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|url|String|In|--|地址，从第三方后台获取。内容格式和意义请参见[羚羊云播放源url格式解析](http://doc.topvdn.com/api/#!public-doc/url_format.md)|

###6.3 设置播放缓冲时长
```
void setPlayOptions(PlayOptions playOptions);
```
| - | - |
|-------|----|
| 接口名 | setPlayOptions |
| 功能 | 配置播放缓冲时长，可选择性调用。必须在开始播放前调用； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|playOptions|PlayOptions|In|必须|缓冲数据，缓冲时长等相关配置，详见：数据类型_播放缓冲时长参数。|

###6.4 开始播放
```
void start();
```
| - | - |
|-------|----|
| 接口名 | start |
| 功能 |开始播放； |
| 返回值 | 无 |

###6.5 停止播放
```
void stop();
```
| - | - |
|-------|----|
| 接口名 | stop |
| 功能 | 停止播放，必须在开始播放后调用； |
| 返回值 | 无 |

###6.6 是否正在播放
```
boolean isPlaying();
```
| - | - |
|-------|----|
| 接口名 | isPlaying |
| 功能 | 测试当前对象是否处于started状态； |
| 返回值 | 返回当前播放状态，true：正在播放   false：其他状态，比如Prepared，Paused和PlaybackCompleted等状态 |

###6.7 设置画面显示比例
```
void setScreenRatio(int screenType);
```
| - | - |
|-------|----|
| 接口名 | setScreenRatio |
| 功能 | 设置画面显示比例； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|screenType|int|In|必须|详见：数据类型IScreenRatioChanger画面缩放比例；|

###6.8 设置全屏
```
void setFullScreen(boolean isFullScreen);
```
| - | - |
|-------|----|
| 接口名 | setFullScreen |
| 功能 | 设置画面显示比例,默认为false； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|isFullScreen|boolean|In|必须|True：全屏 False：非全屏|

###6.9 获取窗口宽
```
int getMinWidth();
```
| - | - |
|-------|----|
| 接口名 | getMinWidth |
| 功能 | 获取非全屏的宽 |
| 返回值 | 无 |

###6.10 获取窗口高
```
int getMinHeight();
```
| - | - |
|-------|----|
| 接口名 | getMinHeight |
| 功能 | 获取非全屏的高 |
| 返回值 | 无 |

###6.11 暂停播放
```
void pause();
```
| - | - |
|-------|----|
| 接口名 | pause |
| 功能 | 暂停播放，仅在点播状态下有效； |
| 返回值 | 无 |

###6.12 暂停以切入后台
```
void pauseToBackground();
```
| - | - |
|-------|----|
| 接口名 | pauseToBackground |
| 功能 | 切入后台时，在宿主Activity的onPause方法中调用此方法暂停播放，节省资源； |
| 返回值 | 无 |

###6.13 从后台恢复播放
```
void resumeFromBackground();
```
| - | - |
|-------|----|
| 接口名 | resumeFromBackground |
| 功能 | 后台进入前台时,在宿主Activity的onResume方法中调用此方法恢复播放； |
| 返回值 | 无 |

###6.14 设置播放位置
```
void seekTo(int pos);
```
| - | - |
|-------|----|
| 接口名 | seekTo |
| 功能 | 调整到特定的时间位置(相对时间)，必须在开始播放后调用，仅在点播状态下有效； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|pos|int|In|必须|播放时间点，单位毫秒，从开始播放到指定时间点的毫秒数。|

###6.15 获取流媒体信息
```
String getMediaParam(int paramType);
```
| - | - |
|-------|----|
| 接口名 | getMediaParam |
| 功能 | 根据传入的参数获取相应的流媒体信息； |
| 返回值 |返回相应的流媒体信息 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|paramType|int|In|必须|流媒体信息对应的协议参数，详见：数据类型IMediaParamProtocol的媒体参数协议|

###5.16 动态设置视频是否自适应
```
public void setFitScreen(boolean isFit);
```
| - | - |
|-------|----|
| 接口名 | setFitScreen |
| 功能 | 设置视频是否自适应，如果播放器view和获取的视频流宽高比不一致时，设置为true，则将将画面进行裁剪以适应View，设置为false，则不裁剪画面，可能导致画面变形。|
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|isFit|boolean|In|--|true 为自适应，false 为不自适应 |

###6.17 获取时长
```
int getDuration();
```
| - | - |
|-------|----|
| 接口名 | getDuration |
| 功能 | 获取播放的时长 ，仅在点播状态下有效； |
| 返回值 |返回录像时长，单位毫秒 |

###6.18 获取当前播放位置
```
int getCurrentPosition();
```
| - | - |
|-------|----|
| 接口名 | getCurrentPosition |
| 功能 | 获取当前播放位置，仅在点播状态下有效； |
| 返回值 |无 |

###6.19 获取当前缓冲进度
```
int getBufferPercentage();
```
| - | - |
|-------|----|
| 接口名 | getBufferPercentage |
| 功能 | 获取当前缓冲进度的百分比，仅在点播状态下有效； |
| 返回值 |返回当前缓冲进度的百分比 |

###6.20 是否能暂停
```
boolean canPause();
```
| - | - |
|-------|----|
| 接口名 | canPause |
| 功能 | 测试当前对象是否能暂停，仅在点播状态下有效； |
| 返回值 |返回boolean类型结果，true：能  false：不能 |

###6.21 是否能后退
```
boolean canSeekBackward();
```
| - | - |
|-------|----|
| 接口名 | canSeekBackward |
| 功能 | 测试当前对象是否能后退，仅在点播状态下有效； |
| 返回值 |返回boolean类型结果，true：能  false：不能 |

###6.22 是否能快进
```
boolean canSeekForward();
```
| - | - |
|-------|----|
| 接口名 | canSeekForward |
| 功能 | 测试当前对象是否能快进，仅在点播状态下有效； |
| 返回值 |返回boolean类型结果，true：能  false：不能 |

###6.23 注册播放进度回调
```
void setOnPlayProgressListener(OnPlayProgressListener playProgressListener);
```
| - | - |
|-------|----|
| 接口名 | setOnPlayProgressListener |
| 功能 | 注册播放进度回调监听，仅在云存储播放时调用； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|playProgressListener|OnPlayProgressListener|In|必须|详见：播放进度回调监听|

###6.24 播放进度回调接口
```
public interface OnPlayProgressListener {
        void onPlayProgress(int playProgress);
    }
```
| - | - |
|-------|----|
| 接口名 | OnPlayProgressListener |
| 功能 | 媒体文件播放结束后调用的回调接口； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|playProgress|int|out|--|播放进度时间，单位毫秒|

###6.25 注册连接状态的回调
```
void setOnPreparedListener(OnPreparedListener preparedListener);
```
| - | - |
|-------|----|
| 接口名 | setOnPreparedListener |
| 功能 | 媒体文件即将播放时调用的回调函数； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|preparedListener|OnPreparedListener|In|必须|详见：媒体文件即将播放时调用的回调函数|

###6.26 连接状态的回调接口
```
interface OnPreparedListener {
        void onPrepared( int time);
    }
```
| - | - |
|-------|----|
| 接口名 | OnPreparedListener |
| 功能 | 媒体文件装载时或即将播放时调用的回调接口； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|time|int|out|--|准备时长|

###6.27 视频截图
```
void snapshot(String path, String name, OnSnapshotListener listener);
```
| - | - |
|-------|----|
| 接口名 | snapshot |
| 功能 | 创建视频截图； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|path|String|In|必须|保存路径(必须是已创建的文件夹的绝对路径)；|
|name|String|In|必须|截图名称，不需要填写格式名称，保存为jpg格式|
|listener|OnSnapshotListener|In|必须|详见：视频截图结果通知回调|

###6.28 视频截图结果通知回调
```
//截图返回的参数错误
int ERROR_RETURN_PARAM = -101;
//存储空间不足
int ERROR_NOT_ENOUGH_SPACE = -102;
//不能解码成jpeg
int ERROR_NOT_DECODE_TO_JPEG = -103;

//截图成功时回调函数；
//输出参数:saveFullPath 保存的完整路径
void onSnapshotSuccess(String saveFullPath)；

//截图失败时回调函数；
//输出参数:errorCode 错误码，详见创建视频截图结束时回调接口_结构定义
void onSnapshotFail(int errorCode);
```

###6.29 注册本地录像状态回调
```
void setLocalRecordListener(OnLocalRecordListener onLocalRecordListener);
```
| - | - |
|-------|----|
| 接口名 | setLocalRecordListener |
| 功能 | 录像时回调函数； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|onLocalRecordListener|OnLocalRecordListener|In|必须|详见：本地录像状态回调函数|

###6.30 本地录像状态回调接口
```
void onRecordSizeChange(long size, long time);
```
| - | - |
|-------|----|
| 接口名 | onRecordSizeChange |
| 功能 | 录制每一KB都会回调此函数； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|size|long|out|--|录制大小，单位：KB|
|time|long|out|--|制时长，单位：S|

###6.31 录像时发生错误时调用的回调函数
```
void onRecordError(LYException e);
```
| - | - |
|-------|----|
| 接口名 | onRecordError |
| 功能 | 录像时发生错误时调用的回调函数； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|e|LYException|out|--|错误信息|

###6.32 开始本地录像
```
void startLocalRecord(String filePath);
```
| - | - |
|-------|----|
| 接口名 | startLocalRecord |
| 功能 | 开始本地录像，在开始播放后调用； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|filePath|String|In|必须|保存路径；|

###6.33 结束本地录像   
```
void stopLocalRecord();
```
| - | - |
|-------|----|
| 接口名 | stopLocalRecord |
| 功能 | 结束本地录像； |
| 返回值 |无 |

###6.34 重置播放器配置
```
void reset();
```
| - | - |
|-------|----|
| 接口名 | reset |
| 功能 | 将播放器的所有配置清空，回到初始化状态，但保留播放器实例，用户可重新设置播放器配置，重新设置播放源进行播放； |
| 返回值 |无 |

###6.35 注册播放结束后事件的回调
```
void setOnCompletionListener(OnCompletionListener completionListener);
```
| - | - |
|-------|----|
| 接口名 | setOnCompletionListener |
| 功能 | 媒体文件播放结束后调用的回调函数； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|completionListener|OnCompletionListener|In|必须|详见：媒体文件播放结束后调用的回调函数|

###6.36 播放结束后事件的回调接口
```
interface OnCompletionListener {
        void onCompletion();
    }
```
| - | - |
|-------|----|
| 接口名 | OnCompletionListener |
| 功能 | 媒体文件播放结束后调用的回调接口； |
| 返回值 |无 |

###6.37 注册播放错误事件的回调
```
void setOnErrorListener(OnErrorListener errorListener);
```
| - | - |
|-------|----|
| 接口名 | setOnErrorListener |
| 功能 | 在播放和建立播放期间发生错误被调用的回调函数 如果回调函数没有注册，或者回调函数返回错误, 将不返回用户任何错误； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|errorListener|OnErrorListener|In|必须|详见：播放和建立播放期间发生错误的回调函数|

###6.38 播放错误事件的回调接口
```
interface OnErrorListener {
        boolean onError(int code, String msg);
    }
```
| - | - |
|-------|----|
| 接口名 | OnErrorListener |
| 功能 | 播放和建立播放期间发生错误时的回调接口；|
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|code|int|out|--|错误码|
|msg|String|out|--|错误信息|

###6.39 注册播放缓冲的回调       
```
void setOnPlayingBufferCacheListener(OnPlayingBufferCacheListener bufferListener);
```
| - | - |
|-------|----|
| 接口名 | setOnPlayingBufferCacheListener |
| 功能 | 播放时缓存的回调函数，仅在点播状态下有效；|
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|bufferListener|OnPlayingBufferCacheListener|In|必须|详见：播放时缓存的回调函数|

###6.40 播放缓冲的回调接口
```
interface OnPlayingBufferCacheListener {
	void onPlayingBufferCache(int percent);
	void onBufferStart();
	void onBufferEnd();
}
```
####6.40.1 当前缓冲的百分比
```
void onPlayingBufferCache(int percent)；
```
| - | - |
|-------|----|
| 接口名 | onPlayingBufferCache |
| 功能 | 正在缓冲时每个百分比都会对调此函数返回当前百分比；|
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|percent|int|out|--|当前缓冲的百分比|

####6.40.2 开始缓冲
```
void onBufferStart();
```
| - | - |
|-------|----|
| 接口名 | onBufferStart |
| 功能 | 开始缓冲时回调函数；|
| 返回值 |无 |

####6.40.3 缓冲结束
```
void onBufferEnd();
```
| - | - |
|-------|----|
| 接口名 | onBufferEnd |
| 功能 | 缓冲结束时回调函数；|
| 返回值 |无 |

###6.41 注册seek结束事件的回调       
```
void setOnSeekCompleteListener(OnSeekCompleteListener seekCompleteListener);
```
| - | - |
|-------|----|
| 接口名 | setOnSeekCompleteListener |
| 功能 | Seek完成时调用的回调函数，仅在点播状态下有效；|
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|seekCompleteListener|OnSeekCompleteListener|In|必须|详见：播放定位查找结束时调用的回调接口|

###6.42 seek结束事件的回调接口
```
interface OnSeekCompleteListener {
        void onSeekSuccess( int time);
        void onSeekError(LYException exception);
    }
```
####6.42.1 seek成功回调
```
void onSeekSuccess( int time);
```
| - | - |
|-------|----|
| 接口名 | onSeekSuccess |
| 功能 | Seek完成时调用的回调函数，仅在点播状态下有效；|
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|time|int|out|必须|seek耗时|

####6.42.2 seek失败回调
```
void onSeekError(LYException exception);
```
| - | - |
|-------|----|
| 接口名 | onSeekError |
| 功能 | Seek失败时调用的回调函数，仅在点播状态下有效；|
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|exception|LYException|out|必须|错误对象，包括错误码和错误信息，详见：数据类型_错误信息|


#### 相关链接
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/integ_case.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)