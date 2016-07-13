#羚羊云iOS API手册-云服务接口

>接口名称：LYCloudService
    
获取单例对象
```
+ (LYCloudService *) sharedLYCloudService;
```
| - | - |
|-------|----|
| 接口名 | sharedLYCloudService |
| 功能 | 单例方法，整个SDK运行期间云服务类只会生成一次。|
| 返回值 | LYCloudService实例对象 |
    
##1 启动云服务
```
- (void) startCloudService: (NSString *)token
                    config: (NSString *)config
                startBlock: (startCloudServiceBlock)startBlock
           popMessageBlock: (cloudServicePopMessageBlock)popMessageBlock;

```
| - | - |
|-------|----|
| 接口名 | startCloudService: config: startBlock: popMessageBlock:|
| 功能 | 调用了此api之后,平台相关凭证及资源开始准备，并且在回调接口通知云服务是否启动成功！ 建议在客户端登录验证逻辑通过之后即刻调用。服务启动之后，相关的平台接口才能正常使用； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|token|NSString *|in|必须|设备token，由[应用服务器](http://doc.topvdn.com/api/index.html#!public-doc/start_archit.md#3._%E7%9B%B8%E5%85%B3%E6%9C%AF%E8%AF%AD%E5%92%8C%E5%90%8D%E8%AF%8D)生成。|
|config|NSString *|in|必须|配置串，从[应用服务器](http://doc.topvdn.com/api/index.html#!public-doc/start_archit.md#3._%E7%9B%B8%E5%85%B3%E6%9C%AF%E8%AF%AD%E5%92%8C%E5%90%8D%E8%AF%8D)获取。|
|startBlock|startCloudServiceBlock|in|--|启动服务状态回调 详见平台接口block|
|popMessageBlock|cloudServicePopMessageBlock|in|--|消息监听回调，设备状态变更、建立连接消息、自定义消息均通过改block回调，详见平台接口block|
**注意**：
**token**：设备token，由应用后台生成，格式：2147549953\_1458979882\_1469999882\_bad3686a62a7aba595df3fb4c9c400e9。
token的内容格式及意义请见[羚羊云token认证机制](http://doc.topvdn.com/api/#!public-doc/token_format.md)
**config**：配置串，从后台获取(无需解析)，格式如下：
[Config]\r\nIsDebug=0\r\nLocalBasePort=8200\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nUdpSendInterval=2\r\nConnectTimeout=10000\r\nTransferTimeout=10000\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n[LogServer]\r\nCount=1\r\nIP1=120.26.74.53\r\nPort1=80\r\n
调用者不必知道该字符串内容所表示的意义。
应用后台调用Web API的[查询设备状态](http://doc.topvdn.com/api/#!web_api_v2.md#2.1.1_%E6%9F%A5%E8%AF%A2%E8%AE%BE%E5%A4%87%E7%8A%B6%E6%80%81)接口获取，接口返回的`init_string`字段即配置串。

##2 停止云服务
```
-(void) stopCloudService;
```
| - | - |
|-------|----|
| 接口名 | stopCloudService |
| 功能 | 调用了此api之后，相应的底层资源完全释放，建议在应用退出的时候调用，节省系统资源； |
| 返回值 | 无 |
| 参数列表 | 无 |

##3 消息监听
从上面的"启动云服务"接口方法介绍中可知，消息监听是通过用户的回调函数实现，设备状态变更、建立连接消息、自定义消息均通过改block回调，详见本文"数据类型-平台接口block"。
```
typedef void(^cloudServicePopMessageBlock)(NSDictionary *dictionary);
```

##4 获取SDK版本号
```
- (NSString *) getSDKVersion;
```
| - | - |
|-------|----|
| 接口名 | getSDKVersion |
| 功能 | 获取SDK版本号； |
| 返回值 | 返回SDK版本号 |
| 参数列表 | 无 |

##5 用户是否在线
```
- (BOOL) isOnline;
```
| - | - |
|-------|----|
| 接口名 | isOnline |
| 功能 | 获取用户在线状态； |
| 返回值 | 返回用户在线状态 YES: 在线  NO: 为离线|
| 参数列表 | 无 |

#### 相关链接
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)