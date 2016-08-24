# 羚羊云Web API-异步事件回调

羚羊云内部产生某些事件后会发送HTTP请求到Web API调用者事先指定的Http回调服务地址。
这些事件包括：设备状态变化、录像剪辑完毕、设备推送消息成功三个事件类型。

## 1 HTTP回调服务地址
在[羚羊云USC平台(用户服务中心)](http://console.topvdn.com)-设置管理栏目下，可查询或更新HTTP回调服务地址，包括状态回调地址和通用回调地址。状态回调地址是用来监听设备状态变化的事件，通用回调地址主要用来监听录像剪辑完毕和设备推送消息的事件。

## 2 HTTP回调请求格式

* 请求首部：

```json
User-Agent: Topvdn
X-APP-ID: Test
X-Topvdn-Event: xxx
X-Event-Sign: bf215181b5140522137b3d4f6b73544a
```

| 请求首部           | 意义                                       |
| -------------- | ---------------------------------------- |
| User-Agent     | 请求源标识                                    |
| X-APP-ID       | 用户应用在羚羊云的标识                              |
| X-Topvdn-Event | 请求的事件，`device-state` :设备状态变化回调事件，`device-message` :设备推送消息回调事件，`device-record-clip`：录像剪辑完毕回调事件 |
| X-Event-Sign   | 请求签名，需要对签名进行验证                           |

**签名的算法:** 

伪码：

md5(X-APP-ID+request.body+X-APP-Key)

具体：

羚羊云分配的 `X-APP-ID` ，整个请求体和羚羊云分配的 `X-APP-Key` 连接成一个字符串，然后用 md5 算法哈希。

对请求进行签名是为了让应用服务器验证这个请求的合法性，检查请求在中途是否被篡改，所以应用服务器应该对每个回调的消息请求都进行签名校验。

## 3 设备状态变化的回调

设备上/下线或者切换调度等状态变化的时候，如果用户提供了状态回调地址，相关设备状态变化会被 POST 到这个地址：

```json
{
    "event": "device-state",
    "data": {
		"device": 1003190,
		"state": 4,
		"tracker_ip": "203.195.157.248",
		"tracker_port": 80,
		"public_ip": "14.215.177.37",
		"public_port": 8747,
		"local_ip": "192.168.2.222",
		"local_port": 8732,
		"config_type": 0,
		"conn_key": 1243,
		"relay_ip": "125.91.251.79",
		"relay_port": 80
	}
}
```

* data 字段

| 字段名          | 类型     | 描述                                       |
| ------------ | ------ | ---------------------------------------- |
| device       | int    | 设备 id                                    |
| state        | int    | 设备状态 0：异常或离线； 1：准备就绪； 2：正在获取获取转发服务器地址信息 3：正在连接转发服务器 4：正在推流 5：正在断开与转发服务器的连接 |
| config_type  | int    | 设备配置类型，公众或者私有等 0：私有设备(仅该设备所属的用户才能观看)；1：私有设备广播推流；2：公众设备(所有用户都可观看)；3：私有+录像云存储；4：公众+录像云存储 |
| tracker_ip   | string | 设备登录的 tracker 服务器                        |
| tracker_port | int    | 设备登录的 tracker 端口                         |
| public_ip    | string | 设备公网 IP                                  |
| public_port  | int    | 设备公网端口                                   |
| local_ip     | string | 设备本地 IP                                  |
| local_port   | int    | 设备本地端口                                   |
| conn_key     | int    | 连接 key                                   |
| relay_ip     | string | 源转发服务器                                   |
| relay_port   | int    | 源转发 端口                                   |


* 请求首部及请求体例子：

```json
X-Topvdn-Event: device-state
Content-Length: 293
User-Agent: Topvdn
Connection: keep-alive
X-Event-Sign: 93e57fc003e7e5da63bebdcbec376fca
Host: 127.0.0.1:5000
X-App-Id: Test
Accept: */*
Content-Type: application/json
Accept-Encoding: gzip, deflate


{"data": {"tracker_port": 80, "local_port": 8200, "local_ip": "10.154.13.169", "public_port": 56569, "state": 1, "public_ip": "98.234.113.73", "config_type": 0, "relay_port": 0, "conn_key": 0, "device": 1003190, "relay_ip": "0.0.0.0", "tracker_ip": "203.195.157.248"}, "event": "device-state"}
```

## 4 录像剪辑完毕的回调

创建录像剪辑任务之后，当剪辑完成的时候会向用户提供的回调接口发送本回调请求，请求体为 `json` 数据：

```json
{
    "event": "device-record-clip",
    "data": {
		"device": 1003775,
		"clip_id": 1024
	}
}
```

* 请求首部及请求体例子：

```json
X-Topvdn-Event: device-record-clip
Content-Length: 74
User-Agent: Topvdn
Connection: keep-alive
X-Event-Sign: fbe34fd801bea34a16ad4c4e99d486be
Host: 127.0.0.1:5000
X-App-Id: Test
Accept: */*
Content-Type: application/json
Accept-Encoding: gzip, deflate


{"data": {"clip_id": 1024, "device": 1003775}, "event": "device-record-clip"}
```

## 5 设备推送消息的回调

对于设备推送消息给设备的接口，用户可以要求将这个消息回调传给应用服务器。

消息回调需要用户提供一个回调接口，接收到需要回调的消息推送后羚羊云会向提供的接口 POST 一个 `json` 数据。

* 请求体：

```json
{
    "event": "device-message",
    "data": {
		"msg": "aGVsbG8=",
		"from": 1003200,
    	"to": [5003062],
    	"created": 1452338154
	}
}
```

请求体是 `json` 数据，如果用户需要标识某个回调的消息对应某个用户推送到设备的消息，应当自己在消息体内进行标识，羚羊云不会对消息进行解析，只是传递。

* 请求首部及请求体例子：

```json
X-Topvdn-Event: device-message
Content-Length: 106
User-Agent: Topvdn
Connection: keep-alive
X-Event-Sign: 4265f685434e887663bba7d954cbc78f
Host: 127.0.0.1:5000
X-App-Id: Test
Accept: */*
Content-Type: application/json
Accept-Encoding: gzip, deflate


{"data": {"msg": "aGVsbG8=", "to": [5003062], "from": 1003200, "created": 1452666295}, "event": "device-message"}
```
