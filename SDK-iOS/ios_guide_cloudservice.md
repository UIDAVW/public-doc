#羚羊云iOS SDK示例-基础云服务

## 接口调用流程

#### **(1)**将应用接入到羚羊云
在使用基础云服务的接口之前，用户必须先将自己的应用体系(含应用客户端和应用服务器)[接入到羚羊云](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)。

#### **(2)**接口调用顺序
![Alt text](./../images/callflow_ios.png)


##1. 启动云服务
启动羚羊云服务，该接口函数分配并初始化本地系统资源，登录到羚羊云平台，在平台端进行安全认证。

```
[[LYCloudService sharedLYCloudService] startCloudService: m_token
                                                  config: m_config
                                              startBlock: ^(LYstatusCode statusCode, NSString *errorString)
                                                        {
                                                            //启动云服务的成功与否状态回调
                                                        }
                                         popMessageBlock: ^(NSDictionary *dictionary)
                                                        {
                                                            //平台透传的所有消息都从这回调出来
                                                        }
];
```
**注意**：其他接口必须在此接口被调用成功之后才能调用。

##2. 停止云服务
 
```
[[LYCloudService sharedLYCloudService] stopCloudService];
```
在应用退出的时候调用，释放系统资源。

##3. 消息透传
当应用客户端使用SDK接入到羚羊云后，可以向同样接入到羚羊云的另外一端的应用客户端，互相传递他们之间协定的网络消息。这些消息对于羚羊云来说是透明的，羚羊云只提供消息传递的通道。

该功能可以有如下应用场景：
(1)在移动终端的应用中读取或更改接入到羚羊云中的私人摄像设备的参数。
(2)在移动终端的应用中监听各个摄像设备的在线状态变化。

在启动云服务时设置popMessageBlock回调，可以监听从云平台传送过来的消息，在popMessageBlock回调函数中您可以处理消息并选择是否回应消息给对方。
```
popMessageBlock:^(NSDictionary *dictionary) {
    //处理平台消息
    //…
}
```
**注意**：
(1)消息最大长度为256个字节;
(2)本SDK只提供了监听消息的功能，当对方有消息到来的时候，本方会通过回调函数通知到应用层的SDK调用者，应用层可以对该消息进行处理以及回应该消息至对端的客户端。
推送消息或者回应消息并不属于本SDK的功能范畴，需要调用羚羊云提供的[Web API接口](http://doc.topvdn.com/api/#!web_api_v2.md)“设备推送消息”。

#### 相关链接
[羚羊云SDK服务架构](http://doc.topvdn.com/api/index.html#!public-doc/start_archit.md)
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
