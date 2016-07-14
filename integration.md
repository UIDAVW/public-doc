#羚羊云SDK接入指南

##1. 羚羊云是什么
羚羊云是服务于视频应用领域的云平台，它提供了云平台所需的基础设施，并且为客户提供一切和视频相关的应用和服务。

羚羊云SDK是羚羊云为用户提供的一套应用开发接口，通过这些接口，用户能够接入到羚羊云轻松实现一系列视频相关的应用。羚羊云SDK使得开发者们不必在视频相关的应用开发上耗费精力，只需调用SDK提供的接口，就能轻松实现他们想要的视频相关应用，这样开发者们就能专注在他们所需的其他业务功能。

##2. 羚羊云应用场景
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


##3. 相关术语和名词
- **羚羊云用户**
是调用羚羊云开发接口接入到羚羊云、开发并实现视频应用的开发者，并非最终的个人终端用户。文档将以“用户”作为简称。

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

##4. 羚羊云服务架构
![Alt text](./images/struct.png "羚羊云服务架构") 

##5. 集成羚羊云SDK(五步)

###5.1 成为羚羊云的开发者
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[注册羚羊云开发者账号](http://console.topvdn.com/register)

###5.2 拥有自己的应用
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[创建自己的应用](http://doc.topvdn.com/api/index.html#!public-doc/createapp.md)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这一步可以获取到该应用在羚羊云的`appid`和`appkey`。

###5.3 获取应用的ID段
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[申请应用的ID段](http://doc.topvdn.com/api/index.html#!public-doc/createids.md)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;从申请到的ID段内抽取一个ID值作为设备的唯一标识，这个标识是设备的`羚羊cid`。

###5.4 快速接入
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[将应用接入到羚羊云](http://doc.topvdn.com/api/index.html#!public-doc/joinup.md)

###5.5 集成示例
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不同应用场景下的集成SDK示例：
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[视频通话](http://doc.topvdn.com/api/index.html#!public-doc/appfunc_facetime.md)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[视频直播](http://doc.topvdn.com/api/index.html#!public-doc/appfunc_livevideo.md)


<br />
#### 相关链接
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)

