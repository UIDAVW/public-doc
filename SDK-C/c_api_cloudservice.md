#羚羊云C API手册-云服务接口

##1 启动云服务
```
int	LY_startCloudService(const char* const apToken, const char* const apConfig, const PlatformMessageCallBack apMessageCallBack, void *apUserData);
```
| - | - |
|-------|----|
| 接口名 | LY_startCloudService |
| 功能 | 启动云服务。调用了此api之后,平台相关凭证及资源开始准备，平台的回调消息通过回调函数apMessageCallBack通知调用者，其他接口必须在云服务启动成功之后才能正常使用。 |
| 返回值 | 0表示成功，非0表示失败。 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|apToken|char*|in|必须|设备token，由[应用服务器](http://doc.topvdn.com/api/index.html#!public-doc/start_archit.md#3._%E7%9B%B8%E5%85%B3%E6%9C%AF%E8%AF%AD%E5%92%8C%E5%90%8D%E8%AF%8D)生成。|
|apConfig|char*|in|必须|配置串，从[应用服务器](http://doc.topvdn.com/api/index.html#!public-doc/start_archit.md#3._%E7%9B%B8%E5%85%B3%E6%9C%AF%E8%AF%AD%E5%92%8C%E5%90%8D%E8%AF%8D)获取。|
|apMessageCallBack|PlatformMessageCallBack|in|必须|平台消息回调函数，该函数用来处理云平台返回的消息|
|apUserData|void*|in|可选|由SDK保存，平台每次调用aPMessageCallBack这个回调函数作为第一个参数传递进去，可传递一些用户自定义信息|
**注意**：

**apToken**：设备token，由应用后台生成，格式：2147549953\_3222536192\_1469999882\_bad3686a62a7aba595df3fb4c9c400e9。

token的内容格式及意义请见[羚羊云token认证机制](http://doc.topvdn.com/api/#!public-doc/token_format.md)

**apConfig**：配置串，从后台获取(无需解析)，格式如下：
[Config]\r\nIsDebug=0\r\nLocalBasePort=8200\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nUdpSendInterval=2\r\nConnectTimeout=10000\r\nTransferTimeout=10000\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n[LogServer]\r\nCount=1\r\nIP1=120.26.74.53\r\nPort1=80\r\n

调用者不必知道该字符串内容所表示的意义。
应用后台调用[Web API的'查询设备在线信息'接口](http://doc.topvdn.com/api/index.html#!public-doc/Web-API/web_api_v2_deviceinfo.md)获取，接口返回的"init_string"字段即配置串。

平台消息回调函数:
```
typedef void (*PlatformMessageCallBack)(void* apUserData, const char* constaMessage);
```
|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|apUserData|void*|in|必须|用户自定义数据，对于羚羊云透明，羚羊云只做保存和传递。|
|aMessage|char*|in|必须|羚羊云的回调数据，cJSON格式，需要解析，解析示例请参照羚羊云C接口DEMO。|

##2 停止云服务
```
void LY_stopCloudService();
```
| - | - |
|-------|----|
| 接口名 | LY_stopCloudService |
| 功能 | 调用了此api之后，相应的底层资源完全释放，建议在应用退出的时候调用，节省系统资源； |
| 返回值 | 无 |
| 参数列表 | 无 |

#### 相关链接
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)
