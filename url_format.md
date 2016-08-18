#羚羊云推拉媒体流URL格式
##1 术语和名词
- **QSUP**：Quick Streaming UdpProtocol。羚羊云自定义的网络传输协议，是基于UDP的P2P传输协议，如果设备端只需要传送数据给设备的拥有者，可使用此协议，此协议传输延时比RTMP、HTTP等协议更低；
- **QSTP**：Quick Streaming TcpProtocol。羚羊云自定义的网络传输协议，是基于TCP的传输协议，如果需要开启直播给多人观看，或者需要使用云存储功能，则需要使用此协议；
- **公众模式**：视频内容直播给多人观看；
- **私有模式**：视频内容只直播给该设备的拥有者观看。

##2 URL格式
  1.QSTP连接的URL格式：topvdn://relay_ip:port?protocolType=[]&connectType=[]&token=[]
  2.QSUP连接的URL格式：topvdn://traker_ip:port?protocolType=[]&token=[]
  3.云端录像下载的URL格式：topvdn://topvdn.public.cn?cid=[]&protocolType=[]&token=[]&begin=[]&end=[]&play=[]

- <u>ip</u>：羚羊云推流服务器IP,为0.0.0.0则为使用羚羊云选择最优服务器,否则使用指定url中指定IP服务器。
- <u>port</u>：羚羊云推流服务器端口,为0时,则使用羚羊云调度最优的服务器端口,否则使用指定端口。目前一般使用1935。 
- <u>protocolType</u>：协议类型，[1]`QSUP`, [2]`QSTP`, [3]云端录像下载
- <u>connectType</u>：连接类型，[1]推流端, [2]拉流端
- <u>mode</u>：推流模式，`protocolType`必须设为`2` [2]公众模式 [3]私有+存储模式 [4]公众+存储模式 [5]私有模式
- <u>cid、begin、end、play</u>：下载录像需要用到，其他功能可不用，cid表示要下载录像的源设备羚羊cid，begin表示要下载录像的开始时间，end表示结束时间，play表示开始播放的时间，需要在begin和end的范围之内。时间单位为秒。
- <u>token</u>：设备token，具体内容格式请见[羚羊云token认证机制](http://doc.topvdn.com/api/#!public-doc/token_format.md)的详细介绍。

下面列举了不同的场景下的url设置。

##3 QSTP方式推拉流

##3.1 QSTP推送直播流示例

###3.1.1 url示例
```
topvdn://0.0.0.0:0?protocolType=2&connectType=1&token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069&mode=2
```
此url为使用`QSTP`的`公众模式推流`。

```
topvdn://183.57.151.161:1935?protocolType=2&connectType=1&token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069&mode=2
```
此url为使用`QSTP`的`公众模式推流`到url中指定服务器IP和端口

###3.1.2 字段解释
- `ip` 羚羊云推流服务器IP,为0.0.0.0则为使用羚羊云选择最优服务器，否则使用指定url中指定IP服务器
- `port` 羚羊云推流服务器端口，为0时，则使用羚羊云调度最优服务器端口，否则使用指定端口。目前一般使用1935 
- `protocolType` 值为2，表示使用QSTP协议推流
- `connectType` 必须为1
- `mode` 
   - 2-使用QSTP协议推流，公众模式；
   - 3-使用QSTP协议推流，私有模式，开启云存储；
   - 4-使用QSTP协议推流，公众模式，开启云存储；
   - 5-使用QSTP协议推流，私有模式。
- `token` 设备token，从应用后台获取
- `begin` 无
- `end` 无
- `play` 无

##3.2 QSTP拉取直播流示例

###3.2.1 url示例
```
topvdn://183.57.151.161:1935?protocolType=2&connectType=2 &token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069
```
此url为使用`QSTP拉流`。

###3.2.2 字段解释
- `ip` 此IP从应用后台获取
- `port` 此端口在获取IP时获取到 
- `protocolType` 值为2，表示使用QSTP协议拉流
- `connectType` 必须为2
- `mode` 无
- `token` 设备token，从应用后台获取
- `begin` 无
- `end` 无
- `play` 无

##3.3 QSTP拉取录像流示例

###3.3.1 url示例
```
topvdn://public.topvdn.cn?cid=1003469&protocolType=3&token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069&begin=1464082941&end=1464086522&play=0
```
此url为使用`羚羊云下载协议`下载录像，录像起始、结束时间时间单位为秒。play为相对于begin的时间差，例如为1的时候，即从1464086522+1秒开始播放。

###3.3.2 字段解释
- `ip` 此时固定为羚羊云域名：public.topvdn.cn
- `port` 无
- `cid` 对方设备的cid
- `protocolType` 必须为3
- `connectType` 无
- `mode` 无
- `token` 对方设备的token，从应用后台获取
- `begin` 录像开始时间
- `end` 录像结束时间
- `play` 开始播放录像的时间，必须在起始和终止时间区间内

##4 QSUP方式推拉流

##4.1 QSUP推拉直播流示例

###4.1.1 url示例
```
topvdn://203.195.157.248:80?protocolType=1&token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069
```
此url为使用`QSUP协议从对方拉流`，或使用`QSUP协议推流到对方`。
此url适合视频通话的应用场景。

###4.1.2 字段解释
- `ip` 对方登录的羚羊云trackerIP
- `port` 对方登录的羚羊云tracker端口
- `protocolType` 必须为1
- `connectType` 无
- `mode` 无
- `token` 对方的token
- `begin` 无
- `end` 无
- `play` 无

####相关链接
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
