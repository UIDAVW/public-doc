#羚羊云SDK接入指南

### 术语名词
- **羚羊云用户**
是调用羚羊云开发接口接入到羚羊云、开发并实现视频应用的开发者，并非最终的个人终端用户。文档将以“用户”作为简称。
- **设备**
接入到羚羊云的程序化设备，承载着用户开发的客户端应用程序，从视频流向的角度不同可分为推流设备和拉流设备。
- **应用**
羚羊云用户调用开发接口，利用羚羊云提供的视频服务而开发的一套应用软件。
- **应用客户端**
用户开发的客户端应用程序，如手机app、PC桌面应用、嵌入在智能硬件设备中的应用程序等等。
- **应用服务器**
用户开发的服务端应用程序，为客户端程序提供后台数据、后台业务处理等服务。
- **appid和appkey**
由羚羊云提供给用户的凭证，用户接入羚羊云平台时，平台会对id和key进行验证。
- **token**
应用客户端调用羚羊云SDK接口需要携带的凭证，羚羊云平台需要验证其安全性。文中的token均指的是接入羚羊云需要验证的token，而并非用户自己应用客户端到应用服务器的验证token。
- **Web API**
为开发者提供http接口，即开发者通过http形式发起数据请求，获取返回json或xml格式的数据。用户可以基于此开发JavaScript、C#、C++、Java、Objective-C等语言的应用。

##1 成为羚羊云的应用开发者
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[注册羚羊云开发者账号](http://console.topvdn.com/register)

##2 拥有自己的应用
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[创建自己的应用](http://doc.topvdn.com/api/index.html#!public-doc/createapp.md)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这一步可以获取到该应用在羚羊云的`appid`和`appkey`。

##3 获取应用的ID段
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[申请应用的ID段](http://doc.topvdn.com/api/index.html#!public-doc/createids.md)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;从申请到的ID段内抽取一个ID值作为设备的唯一标识，这个标识是设备的`羚羊cid`。

##4 快速接入
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[将应用接入到羚羊云](http://doc.topvdn.com/api/index.html#!public-doc/appfunc_joinup.md)

##5 集成示例
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不同应用场景下的集成SDK示例：
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[视频通话](http://doc.topvdn.com/api/index.html#!public-doc/appfunc_facetime.md)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[视频直播](http://doc.topvdn.com/api/index.html#!public-doc/appfunc_livevideo.md)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[视频点播](http://doc.topvdn.com/api/index.html#!public-doc/appfunc_vod.md)
