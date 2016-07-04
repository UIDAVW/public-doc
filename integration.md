#羚羊云SDK接入指南

##1. 文档目的
为用户提供接入并使用羚羊云的总引导入口，介绍羚羊云的概况、服务架构、应用功能，以便用户能够快速理解羚羊云、顺利调用羚羊云接口、轻松实现所需的应用功能。建议新用户按照顺序阅读，这样有利于理解；老用户可按照内容导航选择性查阅所需了解的内容。

##2. 羚羊云是什么
羚羊云是服务于视频应用领域的云平台，它提供了云平台所需的基础设施，并且为客户提供一切和视频相关的应用和服务。

羚羊云SDK是羚羊云为用户提供的一套应用开发接口，通过这些接口，用户能够接入到羚羊云轻松实现一系列视频相关的应用。羚羊云SDK使得开发者们不必在视频相关的应用开发上耗费精力，只需调用SDK提供的接口，就能轻松实现他们想要的视频相关应用，这样开发者们就能专注在他们所需的其他业务功能。

##3. 羚羊云应用场景
羚羊云支持各种智能硬件设备的接入，包括智能手机、传统的监控摄像机、家庭摄像机、行车记录仪、智能眼镜等一切具备视频采集或展示的设备。利用羚羊云所提供的功能和服务，用户可应用于一切和视频应用相关的场景。

- **视频通话**
为机器人、智能手机、电脑、智能硬件等设备等提供给高品质的视频传输服务和低延时的双向视频通话服务。

- **远程视频服务**
为传统的监控摄像机、家庭摄像机、行车记录仪、智能眼镜、4G智能设备等提供高性能的视频远程查看、存储以及分析服务。

- **视频云存储**
为视频监控、视频直播等各类应用提供视频流存储与点播服务。

- **手机直播**
为手机直播应用提供底层视频传输与存储服务。

- **视频直播**
为各类互联网视频应用提供低成本、高性能的视频直播、存储、点播服务。


##4. 相关术语和名词
- **羚羊云用户**
调用羚羊云开发接口接入到羚羊云，开发并实现视频应用的开发者，并非最终的个人终端用户。文档将以“用户”作为简称。

- **设备**
接入到羚羊云的程序化设备，承载着用户开发的客户端应用程序，从视频流向的角度不同可分为推流设备和拉流设备。

- **应用**
羚羊云用户调用开发接口，利用羚羊云提供的视频服务而开发的应用软件。

- **应用客户端**
用户开发的客户端应用程序，如手机app、PC桌面应用、嵌入在智能硬件设备中的应用程序等等。

- **应用服务器**
用户开发的服务端应用程序，为客户端程序提供后台数据、后台业务处理等服务。

- **appid和appkey**
由羚羊云提供给用户的凭证，用户接入羚羊云平台时，平台会对id和key进行验证。

##5. 羚羊云服务架构
![Alt text](./images/struct.png "羚羊云服务架构") 

##5. 集成羚羊云SDK(四步)

###5.1 成为羚羊云的开发者
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[注册羚羊云开发者账号](http://console.topvdn.com/register)

###5.2 拥有自己的应用
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[创建自己的应用](http://doc.topvdn.com/api/index.html#!public-doc/createapp.md)

###5.3 快速接入
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[将应用接入到羚羊云](http://doc.topvdn.com/api/index.html#!public-doc/joinup.md)

###5.4 集成示例
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[不同应用场景下的集成SDK示例](http://doc.topvdn.com/api/index.html#!public-doc/integ_case.md)

##6. 使用羚羊云SDK

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Web API使用说明](http://doc.topvdn.com/api/public-doc/Web-API/#!web_api_v2.md "Web API")

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[SDK使用说明-C版](http://doc.topvdn.com/api/#!public-doc/SDK-C/c_guide.md "C版SDK")
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[SDK使用说明-iOS版](http://doc.topvdn.com/api/#!public-doc/SDK-iOS/ios_guide.md "iOS版SDK")
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[SDK使用说明-Anroid版](http://doc.topvdn.com/api/#!public-doc/SDK-Android/android_guide.md "Anroid版SDK")
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[SDK使用说明-Windows版](http://doc.topvdn.com/api/#!public-doc/SDK-Windows/windows_guide.md "Windows版SDK")

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[API手册-C版](http://doc.topvdn.com/api/#!public-doc/SDK-C/c_api.md)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[API手册-iOS版](http://doc.topvdn.com/api/#!public-doc/SDK-iOS/ios_api.md)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[API手册-Android版](http://doc.topvdn.com/api/#!public-doc/SDK-Android/android_api.md)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[API手册-Windows版](http://doc.topvdn.com/api/#!public-doc/SDK-Windows/windows_api.md)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Demo-C版](http://doc.topvdn.com/api/public-doc/SDK-C/zipdown/ly_sdk_c.zip)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Demo-iOS版](http://doc.topvdn.com/api/public-doc/SDK-iOS/zipdown/ly_sdk_ios.zip)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Demo-Android版](http://doc.topvdn.com/api/public-doc/SDK-Android/zipdown/ly_sdk_android.zip)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Demo-Windows版](http://doc.topvdn.com/api/public-doc/SDK-Windows/zipdown/ly_sdk_windows.zip)

##7. 常见问题

1. 什么是`appid`？怎么获取`appid`？
答：`appid`是羚羊云用户和羚羊云建立合作关系后，由羚羊云分配的唯一标识第三方友商的4字节长度的字符串。第三方友商使用羚羊云SDK必须有appid才能正常使用。

2. 什么是`cid`？怎么获取？
答：`cid`是羚羊云这边唯一标识终端设备的4个字节长度的unsigned int，根据第三方友商提供设备的SN(必须唯一)由应用后台生成，第三方友商可使用羚羊云的应用后台，也可以使用自己的应用后台。

3. 羚羊云提供了`设备端SDK`吗？`设备端SDK`的功能包含哪些？
答：设备端就是本文所说的应用客户端，所谓的设备分为推流设备和播放设备。从文中的SDK功能用例图和功能列表中可以看到客户端的功能包含了推流和播放，设备可以具备推流或播放中的一种功能，也可同时具备两种功能。比如：设备没有显示屏，则没有播放功能；设备既有视频采集器又有显示屏，则同时具备推流和播放的功能。

4. `羚羊id`是什么？如何获取？
答：羚羊id就是文中所说的cid，获取方式也是文中提到的：先调用Web API获取羚羊云平台下该用户厂商所属的id段，然后由用户自己在这个id段内选择一个没有被分配的id作为这个设备的cid(也就是羚羊id)。

5. 用户应用客户端接入流程中，'记录`cid`与该客户端的对应关系'这句话，这个对应关系如何建立。是我们的用户体系跟`cid`绑定，还是`cid`跟客户端唯一标识绑定。
答：若应用客户端是给移动终端的用户所使用，则cid绑定的是该终端用户的唯一标识，如：手机号；若应用客户端是嵌入到视频采集设备的程序，则`cid`绑定的是该设备的唯一标识，如SN号。

6. `视频监控`和`视频通话`调用哪些接口？
答：视频监控调用SDK的`播放器`接口，视频通话调用SDK的`视频通话`接口。播放器接口调用示例：[iOS版](http://doc.topvdn.com/api/#!public-doc/SDK-iOS/ios_guide.md#5.4_%E6%92%AD%E6%94%BE%E5%99%A8)、[Android版](http://doc.topvdn.com/api/#!public-doc/SDK-Android/android_guide.md#5.4_%E6%92%AD%E6%94%BE%E5%99%A8)；视频通话接口调用示例：[iOS版](http://doc.topvdn.com/api/#!public-doc/SDK-iOS/ios_guide.md#5.6_%E8%A7%86%E9%A2%91%E9%80%9A%E8%AF%9D)、[Android版](http://doc.topvdn.com/api/#!public-doc/SDK-Android/android_guide.md#5.6_%E8%A7%86%E9%A2%91%E9%80%9A%E8%AF%9D)。

7. 每台设备都需要有一个羚羊云的id，需要在羚羊云注册，注册羚羊云需要调用什么接口，传入什么参数，以及回调是什么？.
答：由第三方友商应用服务器调用羚羊云[Web-API的获取设备id段接口](http://doc.topvdn.com/api/#!web_api_v2.md#2.1.2_%E6%9F%A5%E8%AF%A2%E8%AE%BE%E5%A4%87_ID_%E6%AE%B5)，获取到一个id段，然后从这个id段中各个id对应到不同的设备，应用后台服务器必须保证每台设备分配到唯一的id。

8. 视频通话需要调用什么接口，传什么参数？
答：实现视频通话功能需要调用羚羊云SDK视频通话的接口，不同开发语言版本的SDK接口不一样。可参见[iOS视频通话接口调用示例](http://doc.topvdn.com/api/#!public-doc/SDK-iOS/ios_guide.md#5.6_%E8%A7%86%E9%A2%91%E9%80%9A%E8%AF%9D)、[Android视频通话接口调用示例](http://doc.topvdn.com/api/#!public-doc/SDK-Android/android_guide.md#5.6_%E8%A7%86%E9%A2%91%E9%80%9A%E8%AF%9D)。

9. 如何实现`录像回放`的功能？录像存在羚羊云端的列表我们如何查看？找到视频列表后又如何按指定时间点播放录像？
答：通过[Web API的查询设备录像时间轴接口](http://doc.topvdn.com/api/#!web_api_v2.md#2.2.1_%E8%AE%BE%E5%A4%87%E5%BD%95%E5%83%8F%E6%97%B6%E9%97%B4%E8%BD%B4)，可以查询到某个视频设备存放在羚羊云端的录像时间列表，然后调用羚羊云客户端SDK的播放器接口([iOS播放器接口调用示例](http://doc.topvdn.com/api/#!public-doc/SDK-iOS/ios_guide.md#5.4_%E6%92%AD%E6%94%BE%E5%99%A8)、[Android播放器接口调用示例](http://doc.topvdn.com/api/#!public-doc/SDK-Android/android_guide.md#5.4_%E6%92%AD%E6%94%BE%E5%99%A8))，传入指定格式的url参数，这个url参数需要通过应用服务器去获取。

## 相关链接
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)

