#羚羊云C API手册-其他接口

##1. 获取在线状态
```
int	LY_getOnlineStatus(void);
```
| - | - |
|-------|----|
| 接口名 | LY_getOnlineStatus |
| 功能 | 获取本方在云平台的在线状态（网络正常情况下，获取到的状态的是准确无误的；如果网络状况不好，延时比较大(触发超时更改状态)，可能出现实际状态和获取到的状态不一致，可通过平台回调函数的"Online"和"Offline"消息同步状态。） |
| 返回值 | 0表示离线，1表示在线 |

##2. 更新token信息
```
int LY_updateToken(const char *aDeviceToken, int maxLen);
```
| - | - |
|-------|----|
| 接口名 | LY_updateToken |
| 功能 | token过期后可调用此接口更新token信息。|
| 返回值 | 0表示成功，非0表示失败 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aDeviceToken|char*|Out|必须|接收token信息的内存空间的指针。|
|maxLen|int|In|必须|接受token信息内存空间的最大长度。|
**注意**：

**aDeviceToken**：设备token，由应用后台生成，格式如下：2147549953_3222536192_1469999882_bad3686a62a7aba595df3fb4c9c400e9。

token的内容格式及意义请见[羚羊云token认证机制](http://doc.topvdn.com/api/public-doc/#!token_format.md)

##3.定位录像到指定时间点
```
int LY_seek(const int aFd, const unsigned int aCurrentTime);
```
| - | - |
|-------|----|
| 接口名 | LY_seek |
| 功能 | 定位录像到指定的时间点，定位的时间点范围在打开该录像通道的开始时间和结束时间内。时间单位为秒。 |
| 返回值 | 0表示成功，非0表示失败 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aFd|int|in|必须|建立录像传输通道时的通道句柄fd|
|aCurrentTime|unsigned int|in|必须|要定位的时间点，该时间点为相对于建立录像传输通道时传入的begin的差值，必须大于等于0 |

##4. 设置指定网卡IP
```
int LY_setLocalIP(const char *aFirstIP, const int aFirstIpLength, const char *aSecondIP, const int aSecondIpLength);
```
| - | - |
|-------|----|
| 接口名 | LY_setLocalIP |
| 功能 | 在双网卡情况下，可调用此接口设置两个网卡的IP，数据从两个网卡同时发送，避免某个网卡网络差的时候出现延时或者丢包，由另外一个网卡发送确保数据的及时送达。由调用者保证IP不冲突。不调用时随机选择一个网卡发送数据。IP的格式是点分十进制的字符串格式。在使用QSTP协议下调用有效。 |
| 返回值 | 0表示成功，非0表示失败 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aFirstIP|const char *|in|必须|第一个IP|
|aFirstIpLength|int|in|必须|第一个IP的长度 |
|aSecondIP|const char *|in|必须|第二个IP |
|aSecondIpLength|int|in|必须|第二个IP的长度 |

##5. 设置媒体编解码信息
```
int LY_setMediaInfo(const int aFd, const MediaInfo_t aMediaInfo); 
```
| - | - |
|-------|----|
| 接口名 | setMediaInfo |
| 功能 | 设置媒体流编解码信息 |
| 返回值 | 0表示成功，非0表示失败 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aFd|const int|in|必须|传输通道fd|
|aMediaInfo|const MediaInfo_t|in|必须|多媒体编解码信息 |

##6. 设置加密密钥
```
int	LY_setQSUPEncryptKey(const unsigned int aEncryptType,const char * const apEncryptKey, const int aEncryptKeyLength);
```
| - | - |
|-------|----|
| 接口名 | LY_setQSUPEncryptKey |
| 功能 | 设置加密密钥，密钥最长不能超过128个字节。加密、解密在SDK内部算法实现，外部无需关心。如果没有设置加密秘钥，使用加密功能时会使用羚羊云默认的加密秘钥。QSUP协议默认是使用羚羊云默认加密秘钥加密的，如果需要取消加密，则可调用此接口，第一个参数设置为0即可。QSTP协议如果使用云存储功能，则使用羚羊云默认加密秘钥加密；否则不加密。公众模式下，设置与否都不加密。 |
| 返回值 | 0表示成功，非0表示失败 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|aEncryptType|int|in|必须|加密类型（0：无加密；1：AES加密）|
|apEncryptKey|const char*|in|必须|加密秘钥内容指针,自定义秘钥|
|aEncryptKeyLength|int|in|必须|加密秘钥内容长度, 密钥最长不能超过128个字节|


#### 相关链接
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)
