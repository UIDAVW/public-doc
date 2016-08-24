#羚羊云视频点播功能开发

## 视频点播功能开发

##1. 应用接入
开发视频点播的应用之前，需将应用先接入羚羊云。(点击[这里](http://doc.topvdn.com/api/index.html#!public-doc/appfunc_joinup.md))
完成应用的接入后，应用服务器端会保存应用的`config`字符串、所有设备的羚羊`cid`、`token`。

##2. 录像时间轴
视频点播的内容来源于推流端设备在直播过程中存储于羚羊云的录像文件。应用层首先需要知道指定的推流端设备在什么时间段内有录像存储在羚羊云，然后播放有效时间段内任何时间点的录像视频。

推流端设备的录像时间轴可通过调用羚羊云[Web API特定接口](http://doc.topvdn.com/api/index.html#!public-doc/Web-API/web_api_v2_record_loop.md)发送HTTP请求来获取，然后接收HTTP的返回数据并解析得到该设备的时间轴信息。
以下仅展示`curl`方式的Web http请求示例，用户需根据自己应用客户端所采用的开发语言去完成http请求并解析返回的json数据。
```
curl -X GET -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/record/1003555/timeline?client_token=1003555_3356753920_1463469894_c88181fb30d35401cd4612cfde96a4d2"
```

请求报文：
```
GET /v2/record/1003555/timeline?client_token=1003555_3356753920_1463469894_c88181fb30d35401cd4612cfde96a4d2 HTTP/1.1
Host: api.topvdn.com
Cache-Control: no-cache
```
其中`1003555`推流设备在羚羊云的`cid`。

请求发送后将返回如下数据：
```
{
	"videos":[
		{
			"from": 1439626260,
			"to": 1439655720,
			"server_index": 0
		},
		...
	],
	"events": [
		{
			"from": 1458205472,
			"to": 1458205562,
			"link": "http://www.domain.com/v2/record/<client_id>/hls/1458205472_1458205562.m3u8?client_token=yyyy"
		},
		...
	],
	"servers": [
		{
			"ip": "192.168.2.11",
			"port": 8005
		},
		...
    ],
	"request_id": "70507923d1c97dcc990ef9a456ce10140d473ace"
}
```
其中的`videos`json数组字段中的`from`和`to`分别表示一段录像的开始时间和结束时间。


##3. 播放录像
只需调用SDK的播放器接口。

详细接口方法调用示例请参考：
[SDK播放器接口调用示例-Android](http://doc.topvdn.com/api/index.html#!public-doc/SDK-Android/android_guide_player.md)
[SDK播放器接口调用示例-iOS](http://doc.topvdn.com/api/index.html#!public-doc/SDK-iOS/ios_guide_player.md)

详细接口方法介绍请参考：
[播放器API-Android](http://doc.topvdn.com/api/index.html#!public-doc/SDK-Android/android_api_player.md)
[播放器API-iOS](http://doc.topvdn.com/api/index.html#!public-doc/SDK-iOS/ios_api_player.md)

在相应的API中(iOS为**打开播放器**API，Android为**设置播放源**API)传入`播放地址`时按照[羚羊云推拉流URL格式](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md#3.3_QSTP%E6%8B%89%E5%8F%96%E5%BD%95%E5%83%8F%E6%B5%81%E7%A4%BA%E4%BE%8B)设置`protocolType`字段为`3`，格式如下：
```
topvdn://public.topvdn.cn?cid=1003469&protocolType=3&token=1003469_3222536192_1493481600_5574318032e39b62063d98e6bff50069&begin=1464082941&end=1464086522&play=0
```

其中：
- `cid ` 推流端设备的羚羊cid。
- `protocolType` 必须为3。
- `connectType` 无。
- `mode` 无。
- `token` 推流端设备的token。
- `begin ` 录像开始时间。
- `end ` 录像结束时间。
- `mode`  开始播放录像的时间，必须在起始和终止时间区间内。
