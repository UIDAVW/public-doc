#羚羊云Android API手册-云服务接口

接口名称：LYService
    
##1 启动云服务
```
void startCloudService(String userToken, String configString, CallBackListener<Long> listener);
```
| - | - |
|-------|----|
| 接口名 | startCloudService |
| 功能 | 调用了此api之后,平台相关凭证及资源开始准备，并且在回调接口通知云服务是否启动成功！ 建议在客户端登录验证逻辑通过之后即刻调用。服务启动之后，相关的平台接口才能正常使用。 |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|userToken|String|in|必须|设备token，由应用服务器生成。|
|configString|String|in|必须|配置串，从应用服务器获取。|
|listener|CallBackListener<Long>|in|必须|启动结果监听回调，返回成功或失败|

**注意**：

**userToken**：设备token，由应用后台生成，格式如下：<br>
2147549953\_1458979882\_1469999882\_bad3686a62a7aba595df3fb4c9c400e9。<br>
token的内容格式及意义请见[羚羊云token认证机制](http://doc.topvdn.com/api/#!public-doc/token_format.md)

**configString**：配置串，从后台获取(无需解析)，格式如下：
[Config]\r\nIsDebug=0\r\nLocalBasePort=8200\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nUdpSendInterval=2\r\nConnectTimeout=10000\r\nTransferTimeout=10000\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n[LogServer]\r\nCount=1\r\nIP1=120.26.74.53\r\nPort1=80\r\n<br>
调用者不必知道该字符串内容所表示的意义。
应用后台调用[Web API的'查询设备状态'接口](http://doc.topvdn.com/api/#!web_api_v2.md#2.1.1_%E6%9F%A5%E8%AF%A2%E8%AE%BE%E5%A4%87%E7%8A%B6%E6%80%81)获取，接口返回的"init_string"字段即配置串。

##2 停止云服务
```
void stopCloudService();
```
| - | - |
|-------|----|
| 接口名 | stopCloudService |
| 功能 | 调用了此api之后，相应的底层资源完全释放，建议在应用退出的时候调用，节省系统资源； |
| 返回值 | 无 |
| 参数列表 | 无 |

##3 消息监听

###3.1 消息结构定义
```
    /**
     * 平台消息回调
     */
    class CloudMessage {
        public String Name;
        public String Message;
        public String SrcID;

        public CloudMessage(String name,
                            String message,
                            String srcID) {

            this.Name = name;
            this.Message = message;
            this.SrcID = srcID;
        }
    }
```

###3.2 设置消息接收回调
```
void setCloudMessageListener(AcceptMessageListener acceptCloudMessageListener);
```
| - | - |
|-------|----|
| 接口名 | setCloudMessageListener |
| 功能 | 设置云消息接收回调，建议开启云服务后即刻调用，设置了该监听才能收到关闭、设备绑定确认、设备配置状态等云消息； |
| 返回值 | 无|
| 参数列表 | 请参见下面的消息接收回调函数 |

###3.3 消息接收回调函数
```
    interface AcceptMessageListener {
        void accept(CloudMessage message);
    }
```
| - | - |
|-------|----|
| 接口名 | AcceptMessageListener |
| 功能 | 视频通话、关闭、设备绑定确认、设备配置状态等云消息接收回调监听； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|message|CloudMessage|out|--|请参见本文数据类型章节的消息结构定义|

##4 用户是否在线
```
boolean isOnline();
```
| - | - |
|-------|----|
| 接口名 | isOnline |
| 功能 | 获取用户在线状态； |
| 返回值 | 返回用户在线状态 true: 在线  false: 为离线|
| 参数列表 | 无 |

##5 获取SDK和平台版本号
```
String getSDKVersion();
```
| - | - |
|-------|----|
| 接口名 | getSDKVersion |
| 功能 | 获取Android SDK和平台版本号； |
| 返回值 | 返回Android SDK和平台版本号 |
| 参数列表 | 无 |

##6 日志打印开关
```
void setNativeLoggingEnabled(boolean enabled);
```
| - | - |
|-------|----|
| 接口名 | setNativeLoggingEnabled |
| 功能 | 是否开启底层日志打印，设置开启的时候，开发者可在log中看到底层日志，tag:[JPlayer] |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|enabled|boolean|in|必须|true为开启,false为不开启(默认)|

#### 相关链接
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)