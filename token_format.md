#羚羊云token认证机制
##1 羚羊云的身份验证方式
羚羊云采用目前web领域普遍的认证方式：基于token的身份验证。

无论是调用羚羊云Web API或者客户端SDK的接口，需要将token作为参数传入，在羚羊云服务端进行身份验证。

##2 羚羊云token内容格式
>格式：{明文段}\_{验证码}

>样式：cid\_control\_expire\_\[vod\_time\]\_\[ip\]\_\[refer\]\_digest

其中：
**cid\_control\_expire\_\[vod\_time\]\_\[ip\]\_\[refer\]**为明文段，**[ ]**标记表示可选字段。
**digest**为验证码

举例：
**537067556_3222536192_1493481600**_**f0399b369aa760362ac4edd224bae23b**

##3 token明文段
token明文段包含以下字段：

|字段 | 含义|
|----|----|
|cid	| 设备id，为访问云平台的设备id，如摄像机或需要p2p通讯或直播的手机id，在参与计算token时采用4字节整数方式；|
|control	| 控制字段，表示此设备将使用的平台功能权限，在参与计算token时采用4字节整数方式；该字段各个字节和位所表达的意思请见下文的control字段介绍。|
|expire | 过期时间，指token的有效时间，为Unix时间戳（秒级精度，4字节）在参与计算token时采用4字节整数方式；|
|vod_time | 点播时间，指点播时对应的录制时间，同时也是点播文件的文件名部分，在参与计算token时采用4字节整数方式；|
|ip | 指设备的公网ip地址，在计算token时采用4字节整数方式；|
|refer | http请求时的refer地址中的域名部分，这个字段一般用来启用防盗链功能，在参与计算token时采用字符串方式；|

**注意：**
除refer字段外，所有的字段都是主机字节序(Little-Endian小端存储)，无符号四字节整数类型；

##4 token明文段的control字段
第一字节为int类型的低位，第四字节为int类型的高位

第一字节（推送播放验证） |	第二字节（录制控制） | 第三字节（播放控制）| 第四字节（多码流保留）
-- | -- 

第一字节（0-7位）：验证及推送控制字段
0位：  是否开启rtmp直播
1位：  是否开启hls直播
2位：  是否验证推送IP
3位：  是否验证refer
4位：  UDP standby，是否可以接受UDP连接
5-7位：保留

第二字节（0-7位）：录制控制
0-3位: 存储时间权限, 0000=>没有存储权限, 0001=>存储7天, 0010=>存储30天,0011=>90天其他保留
4位 : FLV 持久化开关，默认为 0 不打开
5位 : HLS 持久化开关，默认为 0 不打开
6-7位: 保留

第三字节（0-7位）：播放控制
0位：能否观看公众
1位：能否观看私有
2位：能否观看时移
3位：能否观看录像
4位：能否语音回传
5位：能否视频回传
6位：能否查看截图
7位：能否收听声音

##5 token验证码
由明文串配上羚羊云提供的密钥，通过HMAC-MD5标准算法，生成token的验证码部分。验证码为16个无符号的字节数组。
- 明文串格式：各个字段按顺序无缝拼接而成，长度根据字段数目不同而不定。如：
53706755632225361921493481600
其中：<u>537067556</u>为**cid**字段，<u>3222536192</u>为**control**字段，<u>1493481600</u>为**expire**字段。
- 密钥：羚羊云提供给用户的appkey。
- 生成的验证码：16进制32个字符的字符串。
- 验证码生成的示例代码：

```
    //C语言代码，并不完整，仅作为示例以供参考

    unsigned int cid = 537067556;
	unsigned int control = 3222536192;
	unsigned int expire = 1493481600;
	unsigned char src[12];
	char token[100];
	memcpy(src, &cid, 4);
	memcpy(src+4, &control, 4);
	memcpy(src+8, &expire, 4);
    char key[50] = "abcdefghijklmnopqrstuvwxyz123456";
	unsigned char digest[16];

	int ret = hmac_md5((unsigned char*)key,strlen(key),src,12,digest);
	if(ret != 0)
	{
		return -1;
	}

	snprintf(token, sizeof(token), “%u_%u_%u_%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x, cid, control, expire, digest[0] , digest[1] , digest[2] , digest[3] , digest[4] , digest[5] , digest[6] , digest[7] , digest[8] , digest[9] , digest[10] , digest[11] , digest[12] , digest[13] , digest[14] , digest[15]”);

	return 0;
```

##6 羚羊云token类型
根据设备(包括手机、摄像头等)所处于羚羊云端点的不同，token分为设备token和访问token。本方所携带的token称为设备token，对端设备的token称为访问token。
- 设备token
明文组成部分为cid + control + expire + \[ip]；
\[ip]:可选项，如果control字段里面设置验证IP的标志位，则IP字段需要加入到用于token验证码计算的明文中。

- 访问token
明文组成部分为cid + control + expire + \[vod_time] + \[ip] + \[refer]；
按照访问方式不同，[]中的可选项又分为以下几种情况：
\[vod_time]:只有在看http点播时必须使用，其他情况不得添加；
\[ip]:可选项，如果control字段里面设置验证IP的标志位，则IP字段需要加入到用于token验证码计算的明文中；
\[refer]：可选项，并只有在http访问方式下使用，如果control里设置了验证refer标志位，则refer字段需要加入到用于token验证码计算的明文中。
