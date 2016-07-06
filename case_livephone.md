# 手机直播功能开发指南
以下展示手机直播应用场景的例子。

![Alt text](./images/flow-livephone.png "手机直播应用场景下SDK的调用流程") 

##1 推流端
以Android手机推流为例。需要调用羚羊云Android版SDK接口来实现直播推流的功能。

###1.1 启动云服务
启动羚羊云服务，该接口函数分配并初始化本地系统资源，登录到羚羊云平台，在平台端进行安全认证。

    /**
     * 开启云服务
     */
    public void startCloudServiceWithFacetime(String userToken) {
        LYService.getInstance().startCloudService(
        	userToken
            , Const.CONFIG
            , new CallBackListener<Long>() {
                @Override
                public void onSuccess(Long aLong) {
                        CLog.v("long-" + aLong);
                        showToast("登录成功" );
                }
                
                @Override
                public void onError(LYException exception) {
                    CLog.v("exception-" + exception.toString());
                    showToast("登录失败"+exception.getMessage());
                }
            }
        );
    }

###1.2 设置流参数
```
//音视频和摄像机的初始化配置，用户可根据实际需要进行配置。
mSessionConfig = new SessionConfig.Builder()
	.withVideoBitrate(512000)//码率
	.withVideoResolution(480, 640)//分辨率  默认480p
    .withDesireadCamera(Camera.CameraInfo.CAMERA_FACING_BACK)//摄像头类型
	.withCameraDisplayOrientation(90)//旋转角度
	.withAudioChannels(1)//声道 1单声道  2双声道
	.useHardAudioEncode(false)//是否音频硬编
	.useHardVideoEncode(false)//是否视频硬编
	.useAudio(true)//是否开启音频
    .useVideo(true)//是否开启视频
	.build();

```
SessionConfig类配置直播推流的参数，包括是否使用音、视频，是否使用硬编码，视频旋转角度等多种配置，用户可根据需要查看更多进行配置。<br>
**注意**：更多的参数配置详见[API手册](http://doc.topvdn.com/api/index.html#!public-doc/SDK-Android/android_api.md#1.3_SessionConfig%E9%85%8D%E7%BD%AE%E7%9B%B4%E6%92%AD%E6%8E%A8%E6%B5%81%E5%8F%82%E6%95%B0 "Android API")中的数据类型-直播推流相关属性配置。

###1.3 设置本地预览布局
```
<com.lingyang.sdk.view.LYGLCameraEncoderView
    android:id="@+id/ly_preview"
    android:layout_width="match_parent"
    android:layout_height="match_parent"/>

LYGLCameraEncoderView mPreview = (LYGLCameraEncoderView)findViewById(R.id.ly_preview);
```
我们对surfaceview封装了的自定义View，用来预览本地采集的图像。

###1.4 设置本地预览视图
```
//设置本地预览
mLiveBroadcast.setLocalPreview(mPreview);
```
###1.5 设置推流状态监听
```
mLiveBroadcast.setBroadcastListener(new BroadcastListener() {
	@Override
	public void onBroadcastStart() {
		showToast("马上开始直播");
	}
	@Override
	public void onBroadcastLive() {
		showToast("正在直播");
	}
	@Override
	public void onBroadcastStop() {
		showToast("停止直播");
	}
	@Override
	public void onBroadcastError(LYException exception) {
		showToast("直播出错" + exception.getCode() + "--"
				+ exception.getMessage());
	}
});
```
###1.6 开始推流直播
```
// 开始直播
//IBroadcastOpenAPI.MODE_LIVE  :直播
//IBroadcastOpenAPI.MODE_LIVE_AND_RECORD   :录像直播
			
mLiveBroadcast.startBroadcasting(ILiveBroadcast.MODE_LIVE,
	"3000000185_3356753920_1492163431_cc3acc347784f3e30cd4713acec615b1");
```

###1.7 结束推流直播
当不再推流时可以调用接口结束推流。
```
//结束直播
mLiveBroadcast.stopBroadcasting();
//资源释放
mLiveBroadcast.release();
```
**注意**：在调用stopBroadcasting 之后，必须调用release以释放系统资源。

##2 播放端
以iOS手机拉流播放为例。需要调用羚羊云iOS版SDK接口来完成播放功能。

###2.1 创建播放器类
```
LYPlayer *m_player = [[LYPlayer alloc] init];
```

###2.2 创建播放配置
```
LYPlayerConfiguration *m_playerConfig = [[LYPlayerConfiguration alloc] initWithPlayView:playview
                                                                                  frame:CGRectMake(0, 0, 640  , 480)
                                                                             decodeMode:LYPlayerDecodeModeHard];
```

###2.3 设置播放配置
```
[m_player setViewWithConfiguration:m_playerConfig];
```

###2.4 打开播放器
```
[m_player open: @"topvdn://203.195.157.248:80?protocolType=1&token=1003182_3222536192_1467302400_b862e6a09c7c12022794a18aa61e71bb"
    openStatus: ^(LYstatusCode statusCode, NSString *errorString) {
        //打开播放器的状态回调
    }
  playerStatus: ^(NSDictionary *playerMessageDic) {
        //播放过程中的状态回调
    }
];

```
播放地址由应用向应用后台获取。
应用后台生成播放源url的方法和步骤如下：

(1)调用[Web API的'查询设备状态'接口](http://doc.topvdn.com/api/#!web_api_v2.md#2.1.1_%E6%9F%A5%E8%AF%A2%E8%AE%BE%E5%A4%87%E7%8A%B6%E6%80%81)获取羚羊云的tracker ip/port或者relay ip/port；

(2)根据[羚羊云token格式](http://doc.topvdn.com/api/#!public-doc/token_format.md)生成token；

(3)按照[羚羊云URL格式解析](http://doc.topvdn.com/api/#!public-doc/url_format.md)生成羚羊云格式的URL。

###2.5 关闭播放器
```
[m_player close];
```

<br />
### 相关链接
[Web API使用指南](http://doc.topvdn.com/api/public-doc/Web-API/#!web_api_v2.md "Web API")
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)

