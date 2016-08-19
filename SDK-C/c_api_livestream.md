#羚羊云C API手册-推拉流接口

##1 建立传输通道
```
int LY_connect (const char *aUrl, const char *aDataSourceInfo)
```
| - | - |
|-------|----|
| 接口名 | LY_connect |
| 功能 | 建立音视频流的传输通道。该函数与 LY_disconnect配套使用。 |
| 返回值 | 大于等于0表示成功，且返回传输通道句柄fd；否则失败 |
| 参数列表 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aUrl|char*|in|必须|目标服务器的url地址，连接类型（推流或拉流），使用的协议等。|
|aDataSourceInfo|char*|in|可选|如果是观看录像时调用，则此参数为必须；否则参数填NULL。此参数内容从[应用服务器](http://doc.topvdn.com/api/index.html#!public-doc/start_archit.md#3._%E7%9B%B8%E5%85%B3%E6%9C%AF%E8%AF%AD%E5%92%8C%E5%90%8D%E8%AF%8D)获取，对调用者透明。|
**注意**：

**aUrl**：连接地址，从后台获取到IP、端口和token，按照如下格式组合：

topvdn://183.57.151.161:1935?protocolType=2&connectType=1&mode=2&token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069

topvdn://ip=%s:port=%d?protocolType=%d&connectType=%d&mode=%u&token=%s&begin=%lu&end=%lu&play=%lu

Url各字段意义及详解请见[羚羊云Url格式解析](http://doc.topvdn.com/api/public-doc/#!url_format.md)

##2 支持直播录制
该功能需要在调用`LY_connect`接口方法时传入特定格式的URL，按照[羚羊云推拉流URL格式](http://doc.topvdn.com/api/public-doc/#!url_format.md)设置`protocolType`、`connectType`和`mode`字段。例如：
```
topvdn://183.57.151.161:1935?protocolType=2&connectType=1&token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069&mode=4
```
其中：
- `protocolType` 必须为2，表示使用QSTP协议推流。
- `connectType` 必须为1，表示推流端。
- `mode` 值可为3，表示使用QSTP协议推流，私有模式，并开启云存储；也可为4，表示使用QSTP协议推流，公众模式，并开启云存储。

##3 断开通道连接
```
int	LY_disconnect(const int aFd);
```
| - | - |
|-------|----|
| 接口名 | LY_disconnect |
| 功能 | 根据传入的fd参数，断开对应传输通道的连接，与 LY_connect配套使用。 |
| 返回值 | 0表示成功，非0表示失败 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aFd|int|in|必须|传输通道句柄|

##4 发送媒体帧
```
int	LY_sendMediaFrame(const int aFd, MediaFrame_t * apMediaFrame);
```
| - | - |
|-------|----|
| 接口名 | LY_sendMediaFrame |
| 功能 | 以数据帧为单位向已连接成功的传输通道发送音视频数据。 |
| 返回值 | 0表示成功，非0表示失败|
| 参数列表 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aFd|int|in|必须|传输通道句柄|
|apMediaFrame|MediaFrame_t|in|必须|多媒体数据帧结构体指针，详细参考数据类型中的媒体帧信息|

##5 接收媒体帧
```
int	LY_recvMediaFrame(const int aFd, MediaFrame_t * apMediaFrame);
```
| - | - |
|-------|----|
| 接口名 | LY_recvMediaFrame |
| 功能 | 从传输通道接收媒体数据。该接口在没有数据到来时会阻塞，且需要外面管理接收数据的内存空间。 |
| 返回值 | 0表示成功，非0表示失败|

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aFd|int|in|必须|传输通道句柄|
|apMediaFrame|MediaFrame_t|in|必须|多媒体数据帧结构体指针，详细参考数据类型中的媒体帧信息|

#### 相关链接
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)
