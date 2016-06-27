#### 常见问题
1. 什么是`appid`？怎么获取`appid`？
答：`appid`是第三方友商和羚羊云建立合作关系后，由羚羊云分配的唯一标识第三方友商的4字节长度的字符串。第三方友商使用羚羊云SDK必须有`appid`才能正常使用。

2. 什么是`cid`？怎么获取？
答：`cid`是羚羊云这边唯一标识终端设备的4个字节长度的unsigned int，根据第三方友商提供设备的SN(必须唯一)由应用后台生成，第三方友商可使用羚羊云的应用后台，也可以使用自己的应用后台。

3. 羚羊云提供了`设备端SDK`吗？`设备端SDK`的功能包含哪些？
答：设备端就是本文所说的应用客户端，所谓的设备分为推流设备和播放设备。从文中的SDK功能用例图和功能列表中可以看到客户端的功能包含了推流和播放，设备可以具备推流或播放中的一种功能，也可同时具备两种功能。比如：设备没有显示屏，则没有播放功能；设备既有视频采集器又有显示屏，则同时具备推流和播放的功能。

4. `羚羊id`是什么？如何获取？
答：羚羊id就是文中所说的`cid`，获取方式也是文中提到的：先调用[Web API](http://doc.topvdn.com/api/#!web_api_v2.md#2.1.2_%E6%9F%A5%E8%AF%A2%E8%AE%BE%E5%A4%87_ID_%E6%AE%B5)获取羚羊云平台下该用户厂商所属的`id段`，然后由用户自己在这个id段内选择一个`没有被分配的id`作为这个设备的`cid`(也就是`羚羊id`)。

5. 每台设备都需要有一个羚羊云的id，需要在羚羊云注册，注册羚羊云需要调用什么接口，传入什么参数，以及回调是什么？.
答：由第三方友商应用服务器调用羚羊云[Web-API的获取设备id段接口](http://doc.topvdn.com/api/#!web_api_v2.md#2.1.2_%E6%9F%A5%E8%AF%A2%E8%AE%BE%E5%A4%87_ID_%E6%AE%B5)，获取到一个id段，然后从这个id段中各个id对应到不同的设备，应用后台服务器必须保证每台设备分配到唯一的id。

6. 用户应用客户端接入流程中，`'记录cid与该客户端的对应关系'`这句话，这个对应关系如何建立。是我们的`用户体系`跟cid绑定，还是cid跟`客户端唯一标识`绑定。
答：若应用客户端是给移动终端的用户所使用，则cid绑定的是该终端用户的唯一标识，如：手机号；若应用客户端是嵌入到视频采集设备的程序，则cid绑定的是该设备的唯一标识，如SN号。

7. `视频监控`和`视频通话`调用哪些接口？
答：`视频监控`调用SDK的`播放器`接口，`视频通话`调用SDK的`视频通话`接口。播放器接口调用示例：[iOS版](http://doc.topvdn.com/api/public-doc/SDK-iOS/#!ios_guide.md#5.4_%E6%92%AD%E6%94%BE%E5%99%A8)、[Android版](http://doc.topvdn.com/api/public-doc/SDK-Android/#!android_guide.md#5.4_%E6%92%AD%E6%94%BE%E5%99%A8)；视频通话接口调用示例：[iOS版](http://doc.topvdn.com/api/public-doc/SDK-iOS/#!ios_guide.md#5.6_%E8%A7%86%E9%A2%91%E9%80%9A%E8%AF%9D)、[Android版](http://doc.topvdn.com/api/public-doc/SDK-Android/#!android_guide.md#5.6_%E8%A7%86%E9%A2%91%E9%80%9A%E8%AF%9D)。

8. `视频通话`需要调用什么接口，传什么参数？
答：实现视频通话功能需要调用羚羊云SDK视频通话的接口，不同开发语言版本的SDK接口不一样。可参见[iOS视频通话接口调用示例](http://doc.topvdn.com/api/public-doc/SDK-iOS/#!ios_guide.md#5.6_%E8%A7%86%E9%A2%91%E9%80%9A%E8%AF%9D)、[Android视频通话接口调用示例](http://doc.topvdn.com/api/public-doc/SDK-Android/#!android_guide.md#5.6_%E8%A7%86%E9%A2%91%E9%80%9A%E8%AF%9D)。

9. 如何实现`录像回放`的功能？录像存在羚羊云端的列表我们如何查看？找到视频列表后又如何按指定时间点播放录像？
答：通过[Web API的查询设备录像时间轴接口](http://doc.topvdn.com/api/#!web_api_v2.md#2.2.1_%E8%AE%BE%E5%A4%87%E5%BD%95%E5%83%8F%E6%97%B6%E9%97%B4%E8%BD%B4)，可以查询到某个视频设备存放在羚羊云端的录像时间列表，然后调用羚羊云客户端SDK的播放器接口([iOS播放器接口调用示例](http://doc.topvdn.com/api/public-doc/SDK-iOS/#!ios_guide.md#5.4_%E6%92%AD%E6%94%BE%E5%99%A8)、[Android播放器接口调用示例](http://doc.topvdn.com/api/public-doc/SDK-Android/#!android_guide.md#5.4_%E6%92%AD%E6%94%BE%E5%99%A8))，传入指定格式的url参数，这个url参数需要通过应用服务器去获取。

#### 相关链接
- [羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/integration.md)
- [羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
- [羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)
- [羚羊云WebAPI使用指南](http://doc.topvdn.com/api/#!web_api_v2.md)
