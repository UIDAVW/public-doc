#羚羊云C SDK注意事项及FAQ

##1. 注意事项
1. libPusher.so中包含cJSON库，用户可直接使用相关函数，不需要再自行编译和链接此库。
2. 此SDK接口是C风格的，但是libPusher.so中使用到了C++的标准库函数，所以如果使用C的编译器编译，请链接SDK包中提供的libstdc++.so.6库

##2. FAQ
1. 什么是`appid`？怎么获取`appid`？
答：`appid`是用户(开发者)在羚羊云创建应用后，由羚羊云分配的唯一字符串，是该应用在羚羊云中的唯一标识。用户拿到appid后才能有效调用羚羊云SDK提供的接口。获取appid请参考本文前面的'[将应用接入到羚羊云](http://doc.topvdn.com/api/index.html#!public-doc/joinup.md)'。

2. 什么是`cid`？怎么获取？
答：`cid`是一个4个字节长度的无符号整型数，是羚羊云用来标识唯一的用户终端设备。获取的方式请参照'[将应用接入到羚羊云](http://doc.topvdn.com/api/index.html#!public-doc/joinup.md)'。

3. 什么是`QSUP`协议？什么是`QSTP`协议？两者有什么区别？我该用什么协议？
答：`QSUP`（Quick Streaming UdpProtocol）和`QSTP`（Quick Streaming TcpProtocol）协议都是羚羊云自定义的网络传输协议。QSUP是基于UDP的P2P传输协议，如果设备端只需要传送数据给设备的拥有者，可使用此协议，此协议传输延时比RTMP、HTTP等协议更低；QSTP是基于TCP的传输协议，如果需要开启直播给多人观看，或者需要使用云存储功能，则需要使用此协议。

4. 羚羊云SDK支持哪些视频压缩格式和音频压缩格式？
答：目前羚羊云传输通道视频压缩格式支持H264，音频压缩格式支持AAC和OPUS。

5. 羚羊云消息通道最大支持的长度是多少？是否安全？
答：羚羊云目前支持的消息最大长度为256个字节，羚羊云消息通道为透明传输，不会保存任何数据，且会对用户的消息进行加密出来。

6. 羚羊云发送数据接口是否会阻塞？
答：羚羊云发送数据接口是同步接口，发送完数据才会返回，网络较差情况会超时返回，超时时间为5秒。

7. 设备网络较差，连接断开的时候SDK会不会自动重连？
答：使用QSTP协议调用发送数据的接口时，SDK内部会自动重连，重连操作对使用者是透明的；使用QUSP协议时，如果连接断开，则需要主动去调用重连。

8. 网络较差，发送数据较慢时，SDK内部是否有缓存机制？
答：网络环境较差，发送数据较慢时，SDK内部每个通道有1M的缓存队列来缓存数据。

9. 使用羚羊云发送音视频的码流格式是什么样的？
答：SDK发送H264码流，需要带起始头的NALU，每次发送一个NALU，SDK支持SPS PPS SEI I帧以一个NALU为单位进行传输。SDK发送AAC格式的音频要求调用者发送带ADTS头的AAC数据帧，每次发送一帧。

10.	什么是fd，fd的作用？
答：羚羊SDK从版本V2.0后支持多路数据传输，fd为创建传输通道时返回的句柄，唯一标识传输通道。收发数据和断开连接均需要此参数。

#### 相关链接
[羚羊云SDK服务架构](http://doc.topvdn.com/api/index.html#!public-doc/start_archit.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)

