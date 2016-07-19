#羚羊云Android SDK示例-视频通话

声明：本示例仅仅展示了SDK视频通话接口的调用方法和示例，若想实现完整的视频通话应用请参考[羚羊云视频通话应用开发](http://doc.topvdn.com/api/index.html#!public-doc/appfunc_facetime.md)。

## 接口调用流程
在使用本示例实现视频通话的应用之前，必须先完成[开启羚羊云服务](http://doc.topvdn.com/api/#!public-doc/SDK-Android/android_guide_cloudservice.md)接口的调用。

![Alt text](./../images/callflow_facetime_android.png "视频通话接口调用流程")

##1. 创建视频通话对象

```
//音视频和摄像机的初始化配置，用户可根据实际需要进行配置。
mSessionConfig = new SessionConfig.Builder()
	.withVideoBitrate(512000)//码率
	.withVideoResolution(640, 480)//分辨率  默认720p
    .withDesireadCamera(Camera.CameraInfo.CAMERA_FACING_BACK)//摄像头类型
	.withCameraDisplayOrientation(90)//旋转角度
	.withAudioChannels(1)//声道 1单声道  2双声道
	.useHardAudioEncode(false)//是否音频硬编
	.useHardVideoEncode(false)//是否视频硬编
	.useAudio(true)//是否开启音频
    .useVideo(true)//是否开启视频
	.build();
    
//创建视频通话对象
LYFaceTime mLYFaceTime = new LYFaceTime（mContext,mSessionConfig）；

```
SessionConfig类配置直播推流的参数，包括是否使用音、视频，是否使用硬编码，视频旋转角度等多种配置，用户可根据需要查看更多进行配置。<br>
**注意**：更多的参数配置详见[API手册](http://doc.topvdn.com/api/index.html#!public-doc/SDK-Android/android_api.md#1.3_SessionConfig%E9%85%8D%E7%BD%AE%E7%9B%B4%E6%92%AD%E6%8E%A8%E6%B5%81%E5%8F%82%E6%95%B0 "Android API")中的数据类型-直播推流相关属性配置。

##2. 设置本地预览视图

```
<!-- 预览布局 -->
<com.lingyang.sdk.view.LYGLCameraEncoderView
    android:id="@+id/ly_preview"
    android:layout_width="150dp"
    android:layout_height="200dp" />
    
// 设置本地预览
mLYFaceTime.setLocalPreview(camera_preview);
```

##3. 设置播放器视图
 
```
<!-- 播放器布局 -->
<com.lingyang.sdk.player.widget.LYPlayer
    android:id="@+id/ly_player"
    android:layout_width="150dp"
    android:layout_height="200dp"" />

// 设置播放器视图
mLYFaceTime.setRemoteView(null, playerview);
```
注：播放器是指播放对方视频图像。

##4. 建立通话连接

```
/**
 * 被叫方：
 * 从消息透传通道收到对方发送过来的的连接串主动发起连接，连接成功自动推流
 */
mLYFaceTime.openRemote("topvdn://203.195.157.248:80?token=2147550101_3356753920_1685865782_5e66341ab86fa3becec154f71dd4095f&protocolType=1",
    new CallBackListener<Integer>() {
        @Override
    public void onSuccess(Integer t) {
// 连接成功   }
        @Override
    public void onError(final LYException exception) {
// 连接失败   }
            });
```
```
/**
 * 主叫方：用户需要接入羚羊后台实现消息透传功能，将连接串发给被叫方。
 * 设置连接监听和互联监听
 */
LYService.getInstance().setCloudMessageListener(
        new LYService.AcceptMessageListener() {
            @Override
            public void accept(
            LYService.CloudMessage message) {
            if (message.Name.equals("ConnectionAcceptted")) {
                //对方收到连接串并连接成功
                        } 
            if (message.Name.equals("ConnectionClosed")) {      	 
                //对方已挂断，己方也需断开连接
               mLYFaceTime.closeRemote(null);
                                }});
                        
mLYFaceTime.setCallBackListener(new CallBackListener<Integer>() {

        @Override
        public void onSuccess(Integer t) {
            //开始互联
        }

        @Override
        public void onError(LYException exception) {
            //互联失败
        }
```

##5. 关闭通话连接

```
mLYFaceTime.closeRemote(null);
```

##6. 释放视频通话对象
```
mLYFaceTime.release();
```

#### 相关链接
[羚羊云SDK服务架构](http://doc.topvdn.com/api/index.html#!public-doc/start_archit.md)
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)
