#羚羊云应用接入

羚羊云提供了一系列的功能接口供用户调用，用户按照不同的流程、调用不同的接口可以实现不同的应用场景和功能。

##1 应用场景
**视频通话**

![Alt text](./images/facetime.png "视频通话应用场景") 
<br /><br />

**视频直播**

![Alt text](./images/livevideo.png "视频直播应用场景") 
<br /><br />

**手机直播**

![Alt text](./images/livephone.png "手机直播应用场景") 
<br />

##2 应用体系
![Alt text](./images/app_system.png) 

羚羊云用户都有自己的一套应用体系和架构，通常体系中会含有`应用服务器`和`设备`终端(也称`应用客户端`)，所有的设备都会注册到应用服务器并由服务器来管理。

##3 应用接入
在集成SDK实现特定应用场景的应用功能之前，用户应用体系中的服务器和设备必须先接入羚羊云。

- `应用服务器`
和羚羊云没有视频流式的业务交互，仅仅按需调用羚羊云的Web API以请求数据。

- `设备(即应用客户端)`
接入过程相对复杂，其中很大一部分需要应用服务器来辅助完成。

###3.1 第1步
![Alt text](./images/app_sys_join.png) 

上图中**1**、**2**步是由开发者注册并登录[羚羊云应用管理平台](http://console.topvdn.com)来完成，开发者获取到`appid-appkey`和`id段`之后，将其保存在`应用服务器`；
其他的**3**、**4**、**5**步全都是在`应用服务器`端完成。

**注**：
生成`token`的方法：参考[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)；
获取`config`的方法：通过调用Web API的['查询设备状态接口'](http://doc.topvdn.com/api/index.html#!web_api_v2.md#2.1.1_%E6%9F%A5%E8%AF%A2%E8%AE%BE%E5%A4%87%E7%8A%B6%E6%80%81)获取，该接口返回的`init_string`字段即`config串`。

###3.2 第2步
![Alt text](./images/app_sys_join2.png) 

`连接并启动云服务`需要调用**SDK的开启云服务接口**，该接口需要传入`羚羊token`和`config串`。
[启动云服务-iOS调用方法](http://doc.topvdn.com/api/index.html#!public-doc/SDK-iOS/ios_api.md#2.2_%E5%90%AF%E5%8A%A8%E4%BA%91%E6%9C%8D%E5%8A%A1)
[启动云服务-Android调用方法](http://doc.topvdn.com/api/index.html#!public-doc/SDK-Android/android_api.md#2.2_%E5%90%AF%E5%8A%A8%E4%BA%91%E6%9C%8D%E5%8A%A1)

至此，设备A和设备B就成功接入到羚羊云。

##4. 常见问题

1. 什么是`appid`？怎么获取`appid`？
答：`appid`是用户(开发者)在羚羊云创建应用后，由羚羊云分配的唯一字符串，是该应用在羚羊云中的唯一标识。用户拿到appid后才能有效调用羚羊云SDK提供的接口。获取appid请参考本文前面的'[拥有自己的应用](http://doc.topvdn.com/api/index.html#!public-doc/createapp.md)'。

2. 什么是`cid`？怎么获取？
答：`cid`是一个4个字节长度的无符号整型数，是羚羊云用来标识唯一的用户终端设备。获取的方式请参照'[申请应用的ID段](http://doc.topvdn.com/api/index.html#!public-doc/createids.md)'。

3. 羚羊云提供了`设备端SDK`吗？`设备端SDK`的功能包含哪些？
答：设备端就是本文所说的应用客户端，所谓的设备分为推流设备和播放设备。客户端的功能包含了推流和播放，设备可以具备推流或播放中的一种功能，也可同时具备两种功能。比如：设备没有显示屏，则没有播放功能；设备既有视频采集器又有显示屏，则同时具备推流和播放的功能。

4. `羚羊id`是什么？如何获取？
答：羚羊id就是文中所说的cid，获取方式也是文中提到的：先调用Web API获取羚羊云平台下该用户厂商所属的id段，然后由用户自己在这个id段内选择一个没有被分配的id作为这个设备的cid(也就是羚羊id)。

5. 用户应用客户端接入流程中，'记录`cid`与该客户端的对应关系'这句话，这个对应关系如何建立。是我们的用户体系跟`cid`绑定，还是`cid`跟客户端唯一标识绑定。
答：若应用客户端是给移动终端的用户所使用，则cid绑定的是该终端用户的唯一标识，如：手机号；若应用客户端是嵌入到视频采集设备的程序，则`cid`绑定的是该设备的唯一标识，如SN号。

6. 每台设备都需要有一个羚羊云的id，需要在羚羊云注册，注册羚羊云需要调用什么接口，传入什么参数，以及回调是什么？.
答：由用户的应用服务器调用羚羊云[Web-API的获取设备id段接口](http://doc.topvdn.com/api/#!web_api_v2.md#2.1.2_%E6%9F%A5%E8%AF%A2%E8%AE%BE%E5%A4%87_ID_%E6%AE%B5)，获取到一个id段，然后从这个id段中各个id对应到不同的设备，应用后台服务器必须保证每台设备分配到唯一的id。

### 相关链接
[Web API使用指南](http://doc.topvdn.com/api/public-doc/Web-API/#!web_api_v2.md "Web API")
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)

