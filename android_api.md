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
    //7.rtmp
    int STREAM_MEDIA_PARAM_RTMP = 7;
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
    int STREAM_MEDIA_RTMP_SEND_PERCENT = 16;
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

###1.3 直播推流参数
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

###1.4 播放缓冲时长参数
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

###1.5 错误信息
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
>接口名称：LYService
    
###2.2 启动云服务
```
void startCloudService(String userToken, String configString, CallBackListener<Long> listener);
```
|  |  |
|-------|----|
| 接口名 | startCloudService |
| 功能 | 调用了此api之后,平台相关凭证及资源开始准备，并且在回调接口通知云服务是否启动成功！ 建议在客户端登录验证逻辑通过之后即刻调用。服务启动之后，相关的平台接口才能正常使用。 |
| 返回值 | 无 |
> 

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|userToken|String|in|必须|用户token，由第三方后台生成。|
|configString|String|in|必须|配置串，从第三方后台获取。|
|listener|CallBackListener<Long>|in|必须|启动结果监听回调，返回成功或失败|
>**注意**：
>
**userToken**：用户token，由应用后台生成，格式如下：<br>
2147549953_1458979882_1469999882_bad3686a62a7aba595df3fb4c9c400e9。<br>
token的内容格式及意义请见《羚羊云token认证机制》(给出导航链接)
>
**configString**：配置串，从后台获取(无需解析)，格式如下：
[Config]\r\nIsDebug=0\r\nLocalBasePort=8200\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nUdpSendInterval=2\r\nConnectTimeout=10000\r\nTransferTimeout=10000\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n[LogServer]\r\nCount=1\r\nIP1=120.26.74.53\r\nPort1=80\r\n
调用者不必知道该字符串内容所表示的意义。

###2.3 停止云服务
     void stopCloudService();
接口	stopCloudService
调用了此api之后，相应的底层资源完全释放，建议在应用退出的时候调用，节省系统资源；
返回值	无
参数列表	无

6.3.3获取SDK和平台版本号
    String getSDKVersion();
接口	getSDKVersion
获取Android SDK和平台版本号；
返回值	返回Android SDK和平台版本号
参数列表	无

6.3.4日志打印开关
     void setNativeLoggingEnabled(boolean enabled);
接口	setNativeLoggingEnabled
是否开启底层日志打印，设置开启的时候，开发者可在log中看到底层日志，tag:[JPlayer]；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
enabled	boolean	in	必须	True为开启
false为不开启(默认)

6.3.5用户是否在线
    boolean isOnline();
接口	isOnline
获取用户在线状态；
返回值	返回用户在线状态    true: 在线  false: 为离线
参数列表	无

6.3.6消息结构定义
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

6.3.7设置消息接收回调
  void setCloudMessageListener(AcceptMessageListener acceptCloudMessageListener);
接口	setCloudMessageListener
设置云消息接收回调，建议开启云服务后即刻调用，设置了该监听才能收到关闭、设备绑定确认、设备配置状态等云消息；
返回值	无
参数列表	详见：消息接收回调函数

6.3.8消息接收回调函数
    interface AcceptMessageListener {
        void accept(CloudMessage message);
    }
接口	AcceptMessageListener 
视频互联接收，关闭，设备绑定确认，设备配置状态等云消息接收回调监听；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
message	CloudMessage	out	--	详见：消息结构定义

6.4 直播推流接口
接口名称：LYLiveBroadcast
  
6.4.1结构定义
    /**
     * rtmp直播
     */
    int MODE_LIVE = 2;
    /**
     * 录像直播
     */
    int MODE_LIVE_AND_RECORD = 4;
6.4.2设置本地预览视图
    void setLocalPreview(LYGLCameraView glSurfaceView);
接口	setLocalPreview
设置本地预览视图,建议在OnResume()方法中调用该接口
返回值	无
参数列表	类型	In/Out	可选/必须	描述
glSurfaceView	LYGLCameraView 	in	必须	对glsurfaceview进行了封装的自定义View，用来显示视频直播推流的本地预览

6.4.3开始直播推流
   void startBroadcasting(int mode,String token);
接口	startBroadcasting
开始直播推流
返回值	无
参数列表	类型	In/Out	可选/必须	描述
token	String 	in	必须	用户token，用户从第三方后台获取。格式如下：
2147549953_1458979882_1469999882_bad3686a62a7aba595df3fb4c9c400e9。
token的内容格式及意义请见《羚羊云token认证机制》(给出导航链接)
mode	int	in	必须	直播类型，详见：结构定义

6.4.4停止直播推流
  void stopBroadcasting();
接口	stopBroadcasting
关闭广播，除手动点击停止调用外，在onPause()方法里也要调用该接口停止直播
返回值	无
参数列表	无

6.4.5释放接口资源
  void release();
接口	release
释放编码器，音视频采集器，相关工作线程等资源. 必须在停止直播推流后调用，该实例不能再被使用；

返回值	无
参数列表	无

6.4.6是否正在直播
  boolean isBroadcasting();
接口	isBroadcasting
判断是否正在直播；
返回值	返回直播状态    true: 正在直播  false: 已停止直播
参数列表	无

6.4.7设置推流状态变化回调
  void setBroadcastListener(BroadcastStateChangeListener listener);
接口	setBroadcastListener
设置广播状态变化监听回调；
返回值	无
参数列表	详见：推流状态变化回调函数 

6.4.8推流状态变化回调函数 
    interface BroadcastStateChangeListener {
        void onBroadcastStart();
        void onBroadcastLive();
        void onBroadcastStop();
        void onBroadcastError(LYException exception);
    }
接口	BroadcastStateChangeListener 
广播状态变化回调监听，包括直播开始，正在直播，直播停止，错误等
返回值	无
参数列表	类型	In/Out	可选/必须	描述
exception	LYException 	out	--	包含错误信息和错误码。详见：数据类型_错误信息

6.4.9重置流参数
   void reset(SessionConfig config);
接口	reset
重新初始化直播推流相关参数. 必须在停止直播推流后调用
返回值	无
参数列表	类型	In/Out	可选/必须	描述
config	SessionConfig	In	必须	配置直播推流和采集相关属性，包括音视频编码等相关信息。
详见：数据类型_直播流和采集相关属性配置

6.4.10停止视频采集发送
  void stopVideoRecording();
接口	stopVideoRecording
在直播页面调用此方法，摄像头会继续采集数据，但不发送；
在切到后台的时候调用此方法，当前应用会停止采集，释放对摄像头的锁定；
如果切到后台的时候，不调用此方法，摄像头会继续采集发送视频数据(Android 4.3及以上版本)；
返回值	无
参数列表	无

6.4.11恢复视频采集发送
  void startVideoRecording();
接口	startVideoRecording
直播中重新开始视频数据发送
返回值	无
参数列表	无

6.4.12恢复音频采集发送
  void startVideoRecording();
接口	startVideoRecording
直播过程中重新开始视频数据发送
返回值	无
参数列表	无

6.4.13关闭音频采集发送
  void stopAudioRecording();
接口	muteLocal
 直播过程中停止声音采集发送，释放对麦克风的锁定；
返回值	无
参数列表	无

6.4.14 获取摄像机列表
  List<Camera.Size> getSupportedPreviewSizes();
接口	getSupportedPreviewSizes
获取当前摄像机支持的预览列表；
返回值	当前摄像机支持的预览列表；
参数列表	无

6.4.15 获取当前摄像机编号
  int getCurrentCamera();
接口	getCurrentCamera
获取当前摄像机编号；
返回值	当前摄像机编号；
参数列表	无
6.4.16 获取期望的摄像机编号
  int getDesiredCamera();
接口	getDesiredCamera
获取期望的摄像机编号；
返回值	摄像机编号；
参数列表	无

6.4.17切换摄像头
  void switchCamera();
接口	switchCamera
切换至另一个摄像头，从摄像机列表中循环切换，设置效果在预览状态下立即生效；
返回值	无
参数列表	无

6.4.18设置摄像头类型
  void setCameraType(int camera);
接口	setCameraType
传入指定的摄像机编号设置相应的摄像头,设置效果在预览状态下立即生效；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
camera	int	In	必须	{android.hardware.Camera.CameraInfo#CAMERA_FACING_BACK}
or {android.hardware.Camera.CameraInfo#CAMERA_FACING_FRONT}；
6.4.19获取闪光灯模式
  String getFlashMode();
接口	getFlashMode
获取当前闪光灯模式；
返回值	无
参数列表	无

6.4.20切换闪光灯
  void toggleFlash();
接口	toggleFlash
若当前闪光灯为关闭，调用后打开，反之同理；
返回值	无
参数列表	无

6.4.21设置闪光灯类型
  void setFlashMode(String desiredFlash);
接口	setFlashMode
根据传入的参数设置相应的闪光灯类型；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
desiredFlash	String	In	必须	{android.hardware.Camera.Parameters#FLASH_MODE_TORCH}
 or {android.hardware.Camera.Parameters#FLASH_MODE_OFF} ect；


6.5 播放器接口
接口名称：LYPlayer
播放器模块可单独实现直播播放，摄像头直播播放，云存储播放，本地录像等功能。
6.5.1播放器布局
     该布局是基于SurfaceView的自定义播放器控件，在使用过程中，只需要引入播放器控件的相应的layout界面即可。
<com.lingyang.sdk.player.widget.LYPlayer
        android:id="@+id/ly_player"
        android:layout_width="match_parent"
        android:layout_height="match_parent" />
 
6.5.2设置播放源
       public void setDataSource(String url) 
接口	setDataSource
根据传入的url判断播放类型，实例化IPlayer播放控制器，设置播放模式；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
url	String	int	--	地址，从第三方后台获取。内容格式和意义请参见羚羊云播放源url格式解析

6.5.3设置播放缓冲时长
     void setPlayOptions(PlayOptions playOptions);
接口	setPlayOptions
配置播放缓冲时长，可选择性调用。必须在开始播放前调用；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
playOptions	PlayOptions 	In	必须	缓冲数据，缓冲时长等相关配置 。
详见：数据类型_播放缓冲时长参数

6.5.4开始播放
     void start();
接口	start
开始播放；
返回值	无
参数列表	无

6.5.5停止播放
  void stop();
接口	stopPlayback
停止播放，必须在开始播放后调用；
返回值	无
参数列表	无
6.5.16是否正在播放
   boolean isPlaying();
接口	isPlaying
测试当前对象是否处于started状态；
返回值	返回当前播放状态，true：正在播放   false：其他状态，比如Prepared，Paused和PlaybackCompleted等状态
参数列表	无

6.5.6设置画面显示比例
     void setScreenRatio(int screenType);
接口	setScreenRatio
设置画面显示比例；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
screenType	int	In	必须	详见：数据类型IScreenRatioChanger画面缩放比例；

6.5.7设置全屏
     void setFullScreen(boolean isFullScreen);
接口	setFullScreen
设置画面显示比例,默认为false；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
isFullScreen	boolean	In	必须	True：全屏
False：非全屏

6.5.8获取窗口宽高
     int getMinWidth();
     int getMinHeight();
接口	getMinWidth;  getMinHeight
获取非全屏的宽高；
返回值	无
参数列表	无

6.5.11暂停播放
     void pause();
接口	pause
暂停播放，仅在点播状态下有效；
返回值	无
参数列表	无

6.5.9暂停以切入后台
     void pauseToBackground();
接口	pauseToBackground
切入后台时，在宿主Activity的onPause方法中调用此方法暂停播放，节省资源；
返回值	无
参数列表	无

6.5.10从后台恢复播放
     void resumeFromBackground();
接口	pauseToBackground
后台进入前台时,在宿主Activity的onResume方法中调用此方法恢复播放；
返回值	无
参数列表	无

6.5.15设置播放位置
    void seekTo(int pos);
接口	seekTo
调整到特定的时间位置(相对时间)，必须在开始播放后调用，仅在点播状态下有效；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
pos	int	In	必须	播放时间点，单位毫秒，从开始播放到指定时间点的毫秒数。

6.5.12获取流媒体信息
    String getMediaParam(int paramType);
接口	getMediaParam
根据传入的参数获取相应的流媒体信息；
返回值	返回相应的流媒体信息
参数列表	类型	In/Out	可选/必须	描述
paramType	int	In	必须	流媒体信息对应的协议参数，详见：数据类型IMediaParamProtocol的媒体参数协议
6.5.13获取时长
    int getDuration();
接口	getDuration
获取播放的时长 ，仅在点播状态下有效；
返回值	返回录像时长，单位毫秒
参数列表	无

6.5.14获取当前播放位置
    int getCurrentPosition();
接口	getCurrentPosition
获取当前播放位置，仅在点播状态下有效；
返回值	无 
参数列表	无


6.5.17获取当前缓冲进度
   int getBufferPercentage();
接口	getBufferPercentage
获取当前缓冲进度的百分比，仅在点播状态下有效；
返回值	返回当前缓冲进度的百分比;
参数列表	无

6.5.18是否能暂停
boolean canPause(); 
接口	canPause; 
测试当前对象是否能暂停，仅在点播状态下有效；
返回值	返回boolean类型结果，true：能  false：不能
参数列表	无

6.5.19是否能后退
boolean canSeekBackward(); 
接口	canSeekBackward;  
测试当前对象是否能后退，仅在点播状态下有效；
返回值	返回boolean类型结果，true：能  false：不能
参数列表	无
6.5.20是否能快进
boolean canSeekForward();
接口	 canSeekForward
测试当前对象是否能快进，仅在点播状态下有效；
返回值	返回boolean类型结果，true：能  false：不能
参数列表	无


6.5.21注册播放进度回调
    void setOnPlayProgressListener(OnPlayProgressListener playProgressListener);
接口	setOnPlayProgressListener
注册播放进度回调监听，仅在云存储播放时调用；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
playProgressListener	OnPlayProgressListener 	In	必须	详见：播放进度回调监听

6.5.22播放进度回调接口
         public interface OnPlayProgressListener {
        void onPlayProgress(int playProgress);
    }
接口	OnPlayProgressListener 
媒体文件播放结束后调用的回调接口；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
playProgress	int	out	--	播放进度时间，单位毫秒
6.5.23注册连接状态的回调
      void setOnPreparedListener(OnPreparedListener preparedListener);
接口	setOnPreparedListener
媒体文件即将播放时调用的回调函数；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
preparedListener	OnPreparedListener 	In	必须	详见：媒体文件即将播放时调用的回调函数

6.5.24连接状态的回调接口
         interface OnPreparedListener {
        void onPrepared( int time);
    }
接口	OnPreparedListener 
媒体文件装载时或即将播放时调用的回调接口；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
time	int	out	--	准备时长

6.5.25视频截图
      void snapshot(String path, String name, OnSnapshotListener listener);
接口	snapshot
创建视频截图；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
path	String	In	必须	保存路径(必须是已创建的文件夹的绝对路径)；
name	String 	In	必须	截图名称，不需要填写格式名称，保存为jpg格式
listener	OnSnapshotListener 	in	必须	详见：视频截图结果通知回调

6.5.26视频截图结果通知回调
    6.5.26.1 结构定义
     //截图返回的参数错误
        int ERROR_RETURN_PARAM = -101;
     //存储空间不足
        int ERROR_NOT_ENOUGH_SPACE = -102;
     //不能解码成jpeg
        int ERROR_NOT_DECODE_TO_JPEG = -103;

    6.5.26.2 截图成功时回调函数
      void onSnapshotSuccess(String saveFullPath)；
接口	onSnapshotSuccess
截图成功时回调函数；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
saveFullPath	String	out	--	保存的完整路径

   6.5.26.3 截图失败时回调函数
       void onSnapshotFail(int errorCode);
接口	onSnapshotFail
截图失败时回调函数；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
errorCode	int	out	--	错误码，详见创建视频截图结束时回调接口_结构定义
6.5.28注册本地录像状态回调
       void setLocalRecordListener(OnLocalRecordListener onLocalRecordListener);
接口	setLocalRecordListener
录像时回调函数；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
onLocalRecordListener	OnLocalRecordListener	In	必须	详见：本地录像状态回调函数

6.5.29本地录像状态回调接口
   6.5.29.1 录像内容大小改变时回调函数
        void onRecordSizeChange(long size, long time);
接口	onRecordSizeChange
录制每一KB都会回调此函数；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
size	long 	out	--	录制大小，单位：KB
time	long	out	--	制时长，单位：S

   6.5.29.2 录像时发生错误时调用的回调函数
         void onRecordError(LYException e);
接口	onRecordError
录像时发生错误时调用的回调函数；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
e	LYException 	out	--	错误信息
详见：数据类型_错误信息
6.5.27开始本地录像
       void startLocalRecord(String filePath);
接口	startLocalRecord
开始本地录像，在开始播放后调用；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
filePath	String	In	必须	保存路径；

6.5.30结束本地录像   
       void stopLocalRecord();
接口	stopLocalRecord
结束本地录像；
返回值	无
参数列表	无

6.5.31重置播放器配置
      void reset();
接口	reset
将播放器的所有配置清空，回到初始化状态，但保留播放器实例，用户可重新设置播放器配置，重新设置播放源进行播放；
返回值	无
参数列表	无

6.5.32注册播放结束后事件的回调
       void setOnCompletionListener(OnCompletionListener completionListener);
接口	setOnCompletionListener
媒体文件播放结束后调用的回调函数；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
completionListener	OnCompletionListener 	In	必须	详见：媒体文件播放结束后调用的回调函数

6.5.33播放结束后事件的回调接口
       interface OnCompletionListener {
        void onCompletion();
    }
接口	OnCompletionListener 
媒体文件播放结束后调用的回调接口；
返回值	无
参数列表	无
6.5.34注册播放错误事件的回调
       void setOnErrorListener(OnErrorListener errorListener);
接口	setOnErrorListener
在播放和建立播放期间发生错误被调用的回调函数 如果回调函数没有注册，或者回调函数返回错误, 将不返回用户任何错误；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
errorListener	OnErrorListener 	In	必须	详见：播放和建立播放期间发生错误的回调函数

6.5.35播放错误事件的回调接口
         interface OnErrorListener {
        boolean onError(int code, String msg);
    }
接口	OnErrorListener 
播放和建立播放期间发生错误时的回调接口；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
code	int	out	--	错误码
msg	String	out	--	错误信息

6.5.36注册播放缓冲的回调       
 void setOnPlayingBufferCacheListener(OnPlayingBufferCacheListener bufferListener);
接口	setOnPlayingBufferCacheListener
播放时缓存的回调函数，仅在点播状态下有效；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
bufferListener	OnPlayingBufferCacheListener 	In	必须	详见：播放时缓存的回调函数

6.5.37播放缓冲的回调接口
        6.5.37.1 当前缓冲的百分比
      void onPlayingBufferCache(int percent)；
接口	onPlayingBufferCache
正在缓冲时每个百分比都会对调此函数返回当前百分比；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
percent	int	out	--	当前缓冲的百分比

   6.5.37.2 开始缓冲
       void onBufferStart();
接口	onBufferStart
开始缓冲时回调函数；
返回值	无
参数列表	无

  6.5.37.3 缓冲结束
       void onBufferEnd();
接口	onBufferEnd
缓冲结束时回调函数；
返回值	无
参数列表	无
6.5.38注册seek结束事件的回调       
 void setOnSeekCompleteListener(OnSeekCompleteListener seekCompleteListener);
接口	setOnSeekCompleteListener
Seek完成时调用的回调函数，仅在点播状态下有效；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
seekCompleteListener	OnSeekCompleteListener 	In	必须	详见：播播放定位查找结束时调用的回调接口

6.5.39seek结束事件的回调接口
         interface OnSeekCompleteListener {
        void onSeekComplete( int time);
    }
接口	OnSeekCompleteListener 
点播播放定位查找结束时调用的回调接口；
返回值	无
参数列表	类型	In/Out	可选/必须	描述
time	int	out	--	查找时长





