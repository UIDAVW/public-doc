#羚羊云推拉媒体流URL格式
##1 URL格式
  1.QSTP连接URL格式：topvdn://relay_ip:port?protocolType=[]&connectType=[]&token=[]
  2.QSUP连接URl格式：topvdn://traker_ip:port?protocolType=[]&token=[]
  3.云端录像下载URL格式：topvdn://topvdn.public.cn?protocolType=[]&token=[]&begin=[]&end=[]&play=[]

- <u>protocolType</u>：协议类型，[1]QSUP, [2]QSTP, [3]云端录像下载
- <u>connectType</u>：连接类型，[1]推流端, [2]拉流端
- <u>begin、end、play</u>：下载录像需要用到，其他功能可不用，begin表示要下载录像的开始时间，end表示结束时间，play表示开始播放的时间，需要在play和end的范围之内。时间单位为秒。
- <u>token</u>：设备token，具体内容格式请见《羚羊云SDK接入指南》的“羚羊云token认证机制”的详细介绍。

不同的场景下，各个字段所设置的值也不同。

##2 直播推流url示例

###2.1 url示例
topvdn://0.0.0.0:0?protocolType=2&connectType=1&token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069&mode=2。此url为使用QSTP的公众模式推流。
topvdn:// 183.57.151.161:1935?protocolType=2&connectType=1&token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069&mode=2。此url为使用QSTP的公众模式推流到url中指定服务器IP和端口

###2.2 字段解释
- ip 羚羊云推流服务器IP,为0.0.0.0则为使用羚羊云选择最优服务器，否则使用指定url中指定IP服务器
- port 羚羊云推流服务器端口，IP为0.0.0.0，端口为0时，则使用羚羊云调度最优结果的IP，否则使用指定端口。目前一般使用1935 
- protocolType 值为2，表示使用QSTP协议推流
- connectType 必须为1
- mode 2-使用QSTP协议推流，公众模式；3-使用QSTP协议推流，私有模式，开启云存储；4-使用QSTP协议推流，公众模式，开启云存储；5-使用QSTP协议推流，非公众和非存储模式
- token 设备token，从应用后台获取
- begin 无
- end 无
- play 无

##3 拉取直播流示例

###3.1 url示例
topvdn://183.57.151.161:1935?protocolType=2&connectType=2 &token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069。
此url为使用QSTP拉流。

###3.2 字段解释
- ip 此IP从应用后台获取
- port 此端口在获取IP时获取到 
- protocolType 值为2，表示使用QSTP协议拉流
- connectType 必须为2
- mode 无
- token 设备token，从应用后台获取
- begin 无
- end 无
- play 无

##4 拉取录像流

###4.1 url示例
topvdn://public.topvdn.cn?protocolType=3&token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069&begin=1464082941&end=1464086522&play=0。
此url为使用羚羊云下载协议下载录像，录像起始、结束时间时间单位为秒。play为相对于begin的时间差，例如为1的时候，即从1464086522+1秒开始播放。

###4.2 字段解释
- ip 此时固定为羚羊云域名：public.topvdn.cn
- port 无
- protocolType 必须为3
- connectType 无
- mode 无
- token 设备token，从应用后台获取
- begin 录像开始时间
- end 录像结束时间
- play 开始播放录像的时间，必须在起始和终止时间区间内

##5 P2P(QSUP协议)模式推拉流

###5.1 url示例
本方APP与对方互连，或者本方APP连接对端设备。

url示例：
topvdn://203.195.157.248:80?protocolType=1&token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069。
此url为使用QSUP协议连接对方。

###5.2 字段解释
- ip 对方登录的羚羊云trackerIP
- port 对方登录的羚羊云tracker端口
- protocolType 必须为1
- connectType 无
- mode 无
- token 对方的token
- begin 无
- end 无
- play 无

