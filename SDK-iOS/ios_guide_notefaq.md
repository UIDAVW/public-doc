#羚羊云iOS SDK注意事项及FAQ

##1. 注意事项
 
1. sdk只支持iOS 8.0以上的版本； 
2. 播放器打开之后就不能重新设置解码方式；
3. 音视频流配置类生产的类方法均不是单例，每次调用都会生成一个新的配置；
4. 直播推流暂不支持单独推音频流，开始推流的时候一定要音视频流一起开启，否则播放端拉不到视频流无法播放；
5. 功能模块代码务必按照使用说明流程中的进行，否则会不能正常实现；
6. 推流暂不支持动态切换分辨率，可支持动态切换码率。

##2. 常见问题
 
1. 我调用了SDK的接口，但是始终无法实现该接口的功能。
答:请检查平台是否启动。

2. 成功启动云服务，调用推流接口成功，但是无音视频数据采集。
答:请检查摄像头已经麦克风权限是否得到授权。

3. 启动云服务、播放器接口异常返回。
答:请检查参数的正确性。

#### 相关链接
[羚羊云SDK服务架构](http://doc.topvdn.com/api/index.html#!public-doc/start_archit.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)

