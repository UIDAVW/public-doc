#羚羊云Android SDK注意事项及FAQ

##1. 注意事项
(1)用户在调用直播推流、播放器、消息透传的功能接口之前，必须先调用startCloudService接口。否则这些接口不可正常使用。
(2)本SDK只提供了监听消息的功能，并不提供推送消息的功能，推送消息或者回应消息并不属于本SDK的功能范畴，需要调用羚羊云提供的[Web API接口-设备推送消息](http://doc.topvdn.com/api/index.html#!web_api_v2.md#2.3.1_%E8%AE%BE%E5%A4%87%E6%8E%A8%E9%80%81%E6%B6%88%E6%81%AF)。
(3)播放控制功能中视频截图接口所抓取图片的格式为jpg。
(4)本地录像和截图传入的文件夹路径必须是已经被创建的文件夹的路径；获取文件地址不能用file.toString(),要用file.getAbsolutePath()获取绝对路径。
(5)消息透传功能所支持的消息最大长度为256个字节。

##2. 常见问题
(1)此版本的SDK是否支持在推流的过程中动态更改码率？
答：暂不支持动态切换码率。不能动态切换分辨率

(2)SDK判断设备是否在线的依据是什么？
答：设备是否在线2分钟更新一次，平台2分钟内检测不到设备在线的心跳，则判断为离线。

(3)SDK中有播放云端录像的接口(和播放直播流是一个接口)，但是没发现查询录像列表的功能。
答：播放云端录像时，录像列表信息有Web API接口提供[设备录像时间轴](http://doc.topvdn.com/api/#!web_api_v2.md#2.2.1_%E8%AE%BE%E5%A4%87%E5%BD%95%E5%83%8F%E6%97%B6%E9%97%B4%E8%BD%B4)，SDK不提供。

(4)QSTP协议和QSUP协议分别是什么？
答：QSTP全称quick streaming tcp  protocol，QSUP全称quick streaming udp protocol，是羚羊云针对网络音视频媒体流自主研发的流媒体传协议，具有充分利用节点带宽资源达到高效快速传输的特点。

#### 相关链接
[羚羊云SDK服务架构](http://doc.topvdn.com/api/index.html#!public-doc/start_archit.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)

