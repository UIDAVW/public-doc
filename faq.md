#### 常见问题

1. 什么是`appid`？怎么获取`appid`？
答：`appid`是用户(开发者)在羚羊云创建应用后，由羚羊云分配的唯一字符串，是该应用在羚羊云中的唯一标识。用户拿到appid后才能有效调用羚羊云SDK提供的接口。获取appid请参考本文前面的'[拥有自己的应用](http://doc.topvdn.com/api/index.html#!public-doc/createapp.md)'。

2. 什么是`cid`？怎么获取？
答：`cid`是一个4个字节长度的无符号整型数，是羚羊云用来标识唯一的用户终端设备。获取的方式请参照'[申请应用的ID段](http://doc.topvdn.com/api/index.html#!public-doc/createids.md)'，从获取到的ID段中分配一个id值作为设备在羚羊云的cid。

3. 羚羊云提供了`设备端SDK`吗？`设备端SDK`的功能包含哪些？
答：设备端就是本文所说的应用客户端，所谓的设备分为推流设备和播放设备。客户端的功能包含了推流和播放，设备可以具备推流或播放中的一种功能，也可同时具备两种功能。比如：设备没有显示屏，则没有播放功能；设备既有视频采集器又有显示屏，则同时具备推流和播放的功能。客户端SDK按照平台的不同类型分为C(Linux)、iOS、Android几种版本，设备按照自己所属的系统平台使用相应类别的SDK。

4. `视频监控`和`视频通话`调用哪些接口？
答：视频监控调用SDK的`播放器`接口，视频通话调用SDK的`视频通话`接口。播放器接口调用示例：[iOS版](http://doc.topvdn.com/api/index.html#!public-doc/SDK-iOS/ios_guide_player.md)、[Android版](http://doc.topvdn.com/api/index.html#!public-doc/SDK-Android/android_guide_player.md)；视频通话接口调用示例：[iOS版](http://doc.topvdn.com/api/index.html#!public-doc/SDK-iOS/ios_guide_facetime.md)、[Android版](http://doc.topvdn.com/api/index.html#!public-doc/SDK-Android/android_guide_facetime.md)。

5. 视频通话需要调用什么接口，传什么参数？
答：实现视频通话功能需要调用羚羊云SDK视频通话的接口，不同开发语言版本的SDK接口不一样。可参见[iOS视频通话接口调用示例](http://doc.topvdn.com/api/index.html#!public-doc/SDK-iOS/ios_guide_facetime.md)、[Android视频通话接口调用示例](http://doc.topvdn.com/api/index.html#!public-doc/SDK-Android/android_guide_facetime.md)。

6. 如何实现`录像回放`的功能？录像存在羚羊云端的列表我们如何查看？找到视频列表后又如何按指定时间点播放录像？
答：通过[Web API的查询设备录像时间轴接口](http://doc.topvdn.com/api/index.html#!public-doc/Web-API/web_api_v2_record_loop.md)，可以查询到某个视频设备存放在羚羊云端的录像时间列表，然后调用羚羊云客户端SDK的播放器接口([iOS播放器接口调用示例](http://doc.topvdn.com/api/index.html#!public-doc/SDK-iOS/ios_guide_player.md)、[Android播放器接口调用示例](http://doc.topvdn.com/api/index.html#!public-doc/SDK-Android/android_guide_player.md))，传入指定格式的url参数，这个url参数需要通过应用服务器去获取。

7. 什么是`tracker`？
答：tracker是羚羊云服务端的调度服务器，主要将全球IP网络中众多设备(视频源)和视频转发服务节点之间的传输线路按最优的方案进行选择与调配。

#### 相关链接
- [羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
- [羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
- [羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)
