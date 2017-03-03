# 羚羊云  Web API V2 文档

## 1 文档概述

本文档描述羚羊云平台的 v2 版本的 Web 接口，内容主要包括设备状态查询，设备录像查询及剪辑和消息推送等内容。本文档的使用场景分为羚羊云用户的应用服务器及应用客户端，注明需求携带  `X-APP-ID` 及 `X-APP-Key`  的接口应当从应用服务器发起请求，否则只需要携带指定的验证token。

### 1.1 应用服务器
* 用户开发的服务端应用程序，为客户端程序提供后台数据、后台业务处理等服务。

### 1.2 应用客户端
* 用户开发的客户端应用程序，如手机app、PC桌面应用、嵌入在智能硬件设备中的应用程序等等。

### 1.3 羚羊云http服务器

* 正式：http://api.topvdn.com

### 1.4 请求相关

请求数据：

* GET：请求使用标准的 HTTP 请求。
* POST：
    *  请求体：json 数据
    *  请求首部：`Content-Type: application/json; charset=utf-8` 。

请求返回：

* 返回数据： 如果返回的 HTTP 状态码为 `200` 则返回 `json` 数据，非 `200` 的状态码则为请求错误，请根据接口错误码判断。

### 1.5 状态码

接口的请求状态可以通过 HTTP 的状态码判断，下面列出一些通用的状态码：

| 错误码  | 描述                     |
| ---- | ---------------------- |
| 200  | 请求成功，返回正确的数据           |
| 400  | 参数错误，可能缺少参数或者类型不正确     |
| 401  | token 或者 app_key 验证不通过 |
| 500  | 系统内部错误                 |

### 1.6 权限验证

应用服务器发送的请求必须设置以下验证相关的请求首部：

* `X-APP-ID` : 请求的 APP ID ，4 个字符，羚羊云分配
* `X-APP-Key`：请求的 APP 标识 key， 32 个字符，羚羊云分配，请不要把 key 存放在不可控的设备段上，如果泄露，可以申请重新分配

请求的验证 token：

* `X-Client-Token`: client 设备 token
* `X-Access-Token`: 设备访问 token

**注意：验证 token 的提交方式，支持在请求首部及作为 query param 的方式**

| 类型         | 请求首部             | query param  |
| ---------- | ---------------- | ------------ |
| 设备 token   | `X-Client-Token` | client_token |
| 设备访问 token | `X-Access-Token` | access_token |

### 1.7 调试信息

为了方便调试，接口的每次请求都会返回这个请求的唯一标识，这个请求标识可以在响应头 header 的 `X-Request-ID` 得到。

另外考虑到一些情况下不太方便查看响应头，这个请求标识同样也加入到了返回的 json 数据中，字段名为 `request_id`。

如果请求出问题，可以提交这个请求标识给羚羊云去查看相关的情况。

### 1.8 接口类型

* 管理接口：提供给应用服务器的接口，只验证 app id 及 app key；
* 设备接口：提供给设备的接口，需要验证设备 token；

### 1.9 文档更新

* 2016-07-07:
    - 添加查询设备事件存储数据接口；
* 2016-07-06：
    - 调整查询 ID 段接口；
* 2016-05-17：
    - 文件上传接口实现；
    - 接口添加 `curl` 示例及请求报文；
* 2016-03-17：
    - 调整接口 `2.2.1` 添加返回 HLS 存储的数据；
    - 新增短视频和图片分享接口;
* 2016-01-26：
    - 添加新的录像剪辑相关接口。
* 2016-01-06：

羚羊云 Web 接口从 v1 迭代到 v2。

在 v2 版本中，我们不再区分用户和摄像头的概念，将所有连接到我们平台的用户都视为统一的设备，采取预分配设备 ID 段的方式分配设备 ID。

羚羊云平台也不保存设备的配置和绑定关系等内容，这些都交由应用自己管理，这样就不会有绑定关系不一致的情况。

设备 token 和设备访问 token 的生成改到用户的应用，只要使用遵循我们给出的算法生成的 token 来进行请求都可以通过验证。羚羊云平台只控制生成token的key。

## 2 接口列表
接口功能

![Alt text](./usercase-web.png "羚羊云Web API功能")
## 2.1 设备

本节包含设备相关的接口，支持查询设备在线信息和 APP 的设备 ID 段信息。

### 2.1.1 查询设备在线信息

* 接口状态：`使用中`
* 接口功能：提供给应用服务器查询指定设备的状态。
* 接口类型：管理接口
* 请求地址：`/v2/devices/state?size=20&page=1`
* 请求方式：`POST`
* 请求参数：

**注意：需要在请求首部携带 X-APP-ID 和 X-APP-Key**

* POST 请求参数

```json
{
	"cids": [1003538]
}
```

| 参数名  | 类型            | 描述                             | 必须   | 举例   |
| ---- | ------------- | ------------------------------ | ---- | ---- |
| size | unsigned int  | `query param` 每页大小             | 否    | 10   |
| page | unsigned uint | `query param` 第几页              | 否    | 2    |
| cids | json array    | 设备 ID 字符串列表，如果没有或者为空则分页返回所有的数据 | 否    | []   |


* `curl` 请求示例：

```
curl -X POST -H "X-APP-ID: mock" -H "X-APP-Key: mock-app-key-use-your-own-pls" -H "Content-Type: application/json" -d '{
    "cids": [1003538]
}' "http://api.topvdn.com/v2/devices/state?page=1&size=20"
```

* 请求报文：

```json
POST /v2/devices/state?page=1&size=20 HTTP/1.1
Host: api.topvdn.com
X-APP-ID: mock
X-APP-Key: mock-app-key-use-your-own-pls
Content-Type: application/json
Cache-Control: no-cache

{
    "cids": [1003538]
}
```

* 返回数据：

```json
{
	"init_string": "[Config]\r\nIsDebug=1\r\nLocalBasePort=8200\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nUdpSendInterval=2\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n[LogServer]\r\nCount=1\r\nIP1=223.202.103.147\r\nPort1=80",
    "devices": [
	    {
		    "cid": 1003538,
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
			"relay_port": 80,
			"cover_url": "http://api.topvdn.com/v2/snapshots/1003775/cover?client_token=1003775_0_1452756453_0d78e95edab47e565010f47a0300de2d",
			"rtmp_url": "rtmp://rtmp0-9.public.topvdn.cn/",
			"hls": "http://hls0-9.public.topvdn.cn/hls/<cid>/index.m3u8"
		}
	],
	"total": 145,
	"size": 20,
	"page": 1,
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名         | 类型           | 描述         |
| ----------- | ------------ | ---------- |
| init_string | string       | 设备初始化串     |
| devices     | json array   | 设备列表       |
| total       | unsigned int | 查询条件下的设备总数 |
| page        | unsigned int | 页数         |
| size        | unsigned int | 页大小        |
| request_id  | string       | 此次请求的唯一编号  |


* devices 字段：

| 字段名          | 类型     | 描述                                       |
| ------------ | ------ | ---------------------------------------- |
| cid          | int    | 设备 id                                    |
| state        | int    | 设备状态 0：异常或离线； 1：就绪； 2：获取转发中 3：连接转发中 4：推流中 5：断开转发中 |
| config_type  | int    | 设备配置类型，公众或者私有等 0：私有；1：私有广播；2：公众；3：私有录像；4：公众录像 |
| tracker_ip   | string | 设备登录的 tracker 服务器                        |
| tracker_port | int    | 设备登录的 tracker 端口                         |
| public_ip    | string | 设备公网 IP                                  |
| public_port  | int    | 设备公网端口                                   |
| local_ip     | string | 设备本地 IP                                  |
| local_port   | int    | 设备本地端口                                   |
| conn_key     | int    | 连接 key                                   |
| relay_ip     | string | 源转发服务器                                   |
| relay_port   | int    | 源转发 端口                                   |
| cover_url    | string | 设备的封面截图，注意此 URL 会过期，目前默认为获取后 24 小时       |
| rtmp_url     | string | 设备的 rtmp 播放 domain，私有配置设备此字段为空           |
| hls          | string | 设备的 hls 播放地址，私有配置设备此字段为空                 |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | app_key 验证不通过      |
| 406  | size 超过限制，最大为 100  |
| 500  | 系统内部错误             |

### 2.1.2 查询设备 ID 段

* 接口状态：`使用中`
* 接口功能：提供给应用服务器查询分配给该 app 的设备 id 分段数据。任何需要连接到羚羊云的 client 分配的 id 必须在返回的分段内。
* 接口类型：管理接口
* 请求地址：`/v2/devices/ids`
* 请求方式：`GET`

**注意：需要在请求首部携带 X-APP-ID 和 X-APP-Key**


* `curl` 请求示例：

```
curl -X GET -H "X-APP-ID: Test" -H "X-APP-Key: mock-app-key-use-your-own-pls" -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/devices/ids"
```

* 请求报文：

```json
GET /v2/devices/ids HTTP/1.1
Host: api.topvdn.com
X-APP-ID: Test
X-APP-Key: mock-app-key-use-your-own-pls
Cache-Control: no-cache

```

* 返回数据：

```json
{
	"app_id": "Test",
	"cids": [
		{
			"begin": 1234,
			"end": 5678,
			"usage": 1
		}
	],
	"request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型                | 描述                 |
| ---------- | ----------------- | ------------------ |
| app_id     | string            | 羚羊云给用户提供的 APP ID   |
| cids       | json object array | 各个 cid 分段其实和结束，闭区间 |
| begin      | int               | 分段起始               |
| end        | int               | 分段结束               |
| usage      | int               | 使用类型，1 推流设备，2 观看用户 |
| request_id | string            | 此次请求的唯一编号          |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | app_key 验证不通过      |
| 500  | 系统内部错误             |

### 2.1.3 清除设备存储数据

* 接口状态：`使用中`
* 接口功能：清除指定设备的所有存储数据，内容包括循环存储、时事件存储及所有截图。本接口调用是启动一个异步的任务，**数据一旦删除无法恢复!!!**
* 接口类型：管理接口
* 请求地址：`/v2/devices/<cid>/storage`
* 请求方式：`DELETE`
* 请求参数：

**注意：需要在请求首部携带 X-APP-ID 和 X-APP-Key**

| 参数名  | 类型   | 描述         | 必须   | 举例      |
| ---- | ---- | ---------- | ---- | ------- |
| cid  | int  | 路径参数，设备 ID | 是    | 1003775 |


* `curl` 请求示例：

```
curl -X DELETE -H "X-APP-ID: Test" -H "X-APP-Key: mock-app-key-use-your-own-pls" -H "Content-Type: application/json" -H "Cache-Control: no-cache" -d '' "http://api.topvdn.com/v2/devices/1003200/storage"
```

* 请求报文：

```json
DELETE /v2/devices/1003200/storage HTTP/1.1
Host: api.topvdn.com
X-APP-ID: Test
X-APP-Key: mock-app-key-use-your-own-pls
Content-Type: application/json
Cache-Control: no-cache

```


* 返回数据：

```json
{
	"request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型     | 描述        |
| ---------- | ------ | --------- |
| request_id | string | 此次请求的唯一编号 |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | app_key 验证不通过      |
| 500  | 系统内部错误             |

### 2.1.4 删除设备录像

* 接口状态：`开发中`
* 接口功能：删除设备指定时间内的录像数据，包括循环存储及事件存储，必须要提供指定的 `start` 和 `end` 时间。本接口调用是启动一个异步的任务，**数据一旦删除无法恢复!!!**
* 接口类型：管理接口
* 请求地址：`/v2/devices/<cid>/storage/partial?start=1439626260&end=1439633460`
* 请求方式：`DELETE`
* 请求参数：

**注意：需要在请求首部携带 X-APP-ID 和 X-APP-Key**

| 参数名   | 类型   | 描述                  | 必须   | 举例         |
| ----- | ---- | ------------------- | ---- | ---------- |
| cid   | int  | 路径参数，设备 ID          | 是    | 1003775    |
| start | int  | `query param` 起始时间戳 | 是    | 1439626260 |
| end   | int  | `query param` 结束时间戳 | 是    | 1439633460 |


* `curl` 请求示例：

```
curl -X DELETE -H "Content-Type: application/json" -H "X-APP-ID: Test" -H "X-APP-Key: mock-app-key-use-your-own-pls" -H "Cache-Control: no-cache" -d '{
    "start": 1460689347,
    "end": 1460689499
}' "http://api.topvdn.com/v2/devices/1003200/storage/partial"
```

* 请求报文：

```json
DELETE /v2/devices/1003200/storage/partial HTTP/1.1
Host: api.topvdn.com
Content-Type: application/json
X-APP-ID: Test
X-APP-Key: mock-app-key-use-your-own-pls
Cache-Control: no-cache

{
    "start": 1460689347,
    "end": 1460689499
}
```


* 返回数据：

```json
{
	"request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型     | 描述        |
| ---------- | ------ | --------- |
| request_id | string | 此次请求的唯一编号 |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | app_key 验证不通过      |
| 500  | 系统内部错误             |

## 2.2 录像

本节接口主要和设备录像相关，包含了录像时间轴查询和录像剪辑等。

### 2.2.1 设备录像时间轴

* 接口状态：`调整`
* 接口功能：查询指定设备的录像时间轴列表。
* 接口类型：设备接口
* 请求地址：`/v2/record/<cid>/timeline`
* 请求方式：`GET`
* 请求参数：

**注意：需要在请求携带设备 token**

| 参数名   | 类型   | 描述                    | 必须   | 举例         |
| ----- | ---- | --------------------- | ---- | ---------- |
| cid   | int  | 设备 ID                 | 是    | 1003775    |
| start | int  | `query param` 录像起始时间戳 | 否    | 1441676854 |
| end   | int  | `query param` 录像结束时间戳 | 否    | 1441680454 |


* `curl` 请求示例：

```
curl -X GET -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/record/1003555/timeline?client_token=1003555_3356753920_1463469894_c88181fb30d35401cd4612cfde96a4d2"
```

* 请求报文：

```json
GET /v2/record/1003555/timeline?client_token=1003555_3356753920_1463469894_c88181fb30d35401cd4612cfde96a4d2 HTTP/1.1
Host: api.topvdn.com
Cache-Control: no-cache

```


* 返回数据：

```json
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
			"begin": 1458205472,
			"end": 1458205562,
			"url": "http://www.domain.com/v2/record/<client_id>/hls/1458205472_1458205562.m3u8?client_token=yyyy"
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

* 返回字段：

| 字段名        | 类型         | 描述            |
| ---------- | ---------- | ------------- |
| videos     | json array | 循环存储列表        |
| events     | json array | 事件存储列表        |
| servers    | json array | 录像所存储的服务器信息列表 |
| request_id | string     | 此次请求的唯一编号     |


* videos 字段：

| 字段名          | 类型   | 描述                           |
| ------------ | ---- | ---------------------------- |
| from         | int  | 录像段起始时间                      |
| to           | int  | 录像段结束时间                      |
| server_index | int  | 录像段所存服务器信息在返回的 `servers` 中索引 |


* events 字段：

| 字段名   | 类型     | 描述                                  |
| ----- | ------ | ----------------------------------- |
| begin | int    | 事件存储起始时间，这个值与 cid 一起可以得到一个唯一的事件存储录像 |
| end   | int    | 事件存储段结束时间                           |
| url   | string | 事件存储的 m3u8 播放列表地址                   |


* servers 字段

| 字段名  | 类型     | 描述    |
| ---- | ------ | ----- |
| ip   | string | 服务器地址 |
| port | int    | 服务器端口 |


**注意：得到录像列表之后，一个录像段的磁盘播放信息需要向该录像段的服务器请求**

* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 500  | 系统内部错误             |

### 2.2.2 设备录像剪辑

* 接口状态：`使用中`
* 接口功能：创建一个新的剪辑任务，本接口只是开启一个异步的剪辑任务，任务状态可以通过查看状态接口得到，剪辑任务完成也会回调用户提供的回调接口通知。
* 接口类型：设备接口
* 请求地址：`/v2/record/<client_id>/clips`
* 请求方式：`POST`
* 请求参数：

**注意：需要在请求携带设备 token 和要剪辑的录像设备访问 token**

```json
{
    "cid": 1003775,
    "start": 1444697601,
	"end": 1444701201
}
```

| 参数名       | 类型   | 描述                        | 必须   | 举例         |
| --------- | ---- | ------------------------- | ---- | ---------- |
| client_id | int  | 剪辑所属 client id ，一般即是用户 id | 是    | 5003060    |
| cid       | int  | 要剪辑的录像设备 ID               | 是    | 1003775    |
| start     | int  | 剪辑起始时间戳                   | 否    | 1441676854 |
| end       | int  | 剪辑结束时间戳                   | 否    | 1441680454 |

**注意：消息回调的数据请查看 附录 1.2**

* `curl` 请求示例：

```
curl -X POST -H "X-Client-Token: 3000000226_0_1456222962_478f89ea0bcbb6678cef561adc6efe52" -H "X-Access-Token: 1003136_0_1456284297_e6ab9b6fb0b52926a75bd647caee6e57" -H "Content-Type: application/json" -H "Cache-Control: no-cache" -d '{
    "cid": 1003136,
    "start": 1456142250,
    "end": 1456142850
}' "http://api.topvdn.com/v2/record/3000000226/clips"
```

* 请求报文：

```json
POST /v2/record/3000000226/clips HTTP/1.1
Host: api.topvdn.com
X-Client-Token: 3000000226_0_1456222962_478f89ea0bcbb6678cef561adc6efe52
X-Access-Token: 1003136_0_1456284297_e6ab9b6fb0b52926a75bd647caee6e57
Content-Type: application/json
Cache-Control: no-cache

{
    "cid": 1003136,
    "start": 1456142250,
    "end": 1456142850
}
```


* 返回数据：

```json
{
	"clip_id": 42,
	"request_id": "70507923d1c97dcc990ef9a456ce10140d473ace"
}
```

* 返回字段：

| 字段名        | 类型     | 描述                      |
| ---------- | ------ | ----------------------- |
| clip_id    | int    | 剪辑任务的 id ，可以根据这个来查询任务状态 |
| request_id | string | 此次请求的唯一编号               |


* 状态码

| 状态码  | 描述                    |
| ---- | --------------------- |
| 200  | 请求成功，返回正确的数据          |
| 400  | 参数错误，可能缺少参数或者类型不正确    |
| 401  | app_key 或 token 验证不通过 |
| 403  | cid 与访问 token 不一致     |
| 404  | 指定的时间段无数据             |
| 406  | 指定的时间超过限制，不被接受        |
| 409  | 指定的 start 和 end 已经剪辑过 |
| 500  | 系统内部错误                |

### 2.2.3 查询剪辑列表

* 接口状态：`使用中`
* 接口功能：查询一个 client 下的所有录像剪辑列表，只会返回成功的剪辑。
* 接口类型：设备接口
* 请求地址：`/v2/record/<client_id>/clips?page=1&size=10`
* 请求方式：`GET`
* 请求参数：

**注意：需要在请求携带 client token**

| 参数名       | 类型   | 描述                        | 必须   | 举例      |
| --------- | ---- | ------------------------- | ---- | ------- |
| client_id | int  | 剪辑所属 client id ，一般即是用户 id | 是    | 5003060 |
| page      | int  | `query param` 页数，默认为 1    | 否    | 1       |
| size      | int  | `query param` 每页大小，默认为 10 | 否    | 10      |


* `curl` 请求示例：

```
curl -X GET -H "X-Client-Token: 3000000226_0_1456222962_478f89ea0bcbb6678cef561adc6efe52" -H "Content-Type: application/json" -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/record/3000000226/clips"
```

* 请求报文：

```json
GET /v2/record/3000000226/clips HTTP/1.1
Host: api.topvdn.com
X-Client-Token: 3000000226_0_1456222962_478f89ea0bcbb6678cef561adc6efe52
Content-Type: application/json
Cache-Control: no-cache

```


* 返回数据：

```json
{
	"total": 2,
    "clips": [
		{
			"id": 42,
			"start": 1444697601,
			"end": 1444701201,
			"segments": [
				{
					"start": 1444697621,
					"end": 1444697821,
					"download": "http://xxx.domain.com/xxx/xx.mp4",
					"cover": "http://xxx.domain.com/xxx/xxx"
				},
				{
					"start": 1444697921,
					"end": 1444701201,
					"download": "http://yyy.domain.com/yyy/yy.mp4",
					"cover": "http://xxx.domain.com/xxx/xxx"
				},
				...
		    ],
		    "created": "2015-10-13T15:34:28Z"
		},
		...
	],
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型        | 描述        |
| ---------- | --------- | --------- |
| total      | int       | 剪辑总数      |
| clips      | json list | 剪辑列表      |
| request_id | string    | 此次请求的唯一编号 |


* clips 字段

| 字段名      | 类型        | 描述            |
| -------- | --------- | ------------- |
| id       | int       | 剪辑 ID         |
| start    | int       | 剪辑的开始时间       |
| end      | int       | 剪辑的结束时间       |
| cover    | string    | 剪辑视频的封面截图     |
| segments | json list | 指定 ID 剪辑的视频列表 |
| download | string    | 分段视频下载地址      |
| created  | string    | 剪辑创建时间        |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 500  | 系统内部错误             |

### 2.2.4 查询剪辑状态

* 接口状态：`使用中`
* 接口功能：查询指定剪辑 ID 的剪辑任务状态。
* 接口类型：设备接口
* 请求地址：`/v2/record/clips/<clip_id>/status`
* 请求方式：`GET`
* 请求参数：

**注意：需要在请求携带 client token**

| 参数名     | 类型   | 描述                  | 必须   | 举例   |
| ------- | ---- | ------------------- | ---- | ---- |
| clip_id | int  | `query param` 剪辑 ID | 是    | 42   |


* `curl` 请求示例：

```
curl -X GET -H "X-Client-Token: 3000000226_0_1456222962_478f89ea0bcbb6678cef561adc6efe52" -H "Content-Type: application/json" -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/record/3000000226/clips"
```

* 请求报文：

```json
GET /v2/record/3000000226/clips HTTP/1.1
Host: api.topvdn.com
X-Client-Token: 3000000226_0_1456222962_478f89ea0bcbb6678cef561adc6efe52
Content-Type: application/json
Cache-Control: no-cache

```


* 返回数据：

```json
{
    "status": "WAIT",
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型     | 描述                                       |
| ---------- | ------ | ---------------------------------------- |
| status     | string | 剪辑任务状态：`WAIT` 等待，尚未开始；`START` 任务已经开始；`FINISH` 任务已经完成，`FAIL` 失败 |
| request_id | string | 此次请求的唯一编号                                |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 403  | 没有权限访问该剪辑          |
| 404  | 指定的 clip_id 不存在    |
| 500  | 系统内部错误             |

### 2.2.5 查询剪辑数据

* 接口状态：`使用中`
* 接口功能：获取指定剪辑的视频下载地址列表，一个剪辑可能会有多个视频。
* 接口类型：设备接口
* 请求地址：`/v2/record/clips/<clip_id>`
* 请求方式：`GET`
* 请求参数：

**注意：需要在请求携带 client token**
**注意：视频下载地址有效期暂定为一天**

| 参数名     | 类型   | 描述                  | 必须   | 举例   |
| ------- | ---- | ------------------- | ---- | ---- |
| clip_id | int  | `query param` 剪辑 ID | 是    | 42   |


* `curl` 请求示例：

```
curl -X GET -H "X-Client-Token: 5003062_0_1453967008_7c52d0249e96317c20433b151e6105b0" -H "Content-Type: application/json" -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/record/clips/568"
```

* 请求报文：

```json
GET /v2/record/clips/568 HTTP/1.1
Host: api.topvdn.com
X-Client-Token: 5003062_0_1453967008_7c52d0249e96317c20433b151e6105b0
Content-Type: application/json
Cache-Control: no-cache

```


* 返回数据：

```json
{
    "segments": [
		{
			"start": 1444697621,
			"end": 1444697821,
			"download": "http://xxx.domain.com/xxx/xx.mp4",
			"cover": "http://xxx.domain.com/xxx/xxx"
		},
		{
			"start": 1444697921,
			"end": 1444701201,
			"download": "http://yyy.domain.com/yyy/yy.mp4",
			"cover": "http://xxx.domain.com/xxx/xxx"
		},
		...
	],
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型        | 描述            |
| ---------- | --------- | ------------- |
| segments   | json list | 指定 ID 剪辑的视频列表 |
| start      | int       | 分段起始时间        |
| end        | int       | 分段结束时间        |
| cover      | string    | 剪辑视频的封面截图     |
| download   | string    | 分段视频下载地址      |
| request_id | string    | 此次请求的唯一编号     |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 403  | 没有权限访问该剪辑          |
| 404  | 指定的 clip_id 不存在    |
| 500  | 系统内部错误             |

### 2.2.6 删除剪辑

* 接口状态：`使用中`
* 接口功能：删除指定的剪辑数据。
* 接口类型：设备接口
* 请求地址：`/v2/record/clips/remove`
* 请求方式：`POST`
* 请求参数：

**注意：需要在请求携带 client token**

```json
{
	"clip_id": 42
}
```

| 参数名     | 类型   | 描述    | 必须   | 举例   |
| ------- | ---- | ----- | ---- | ---- |
| clip_id | int  | 剪辑 ID | 是    | 42   |


* `curl` 请求示例：

```
curl -X POST -H "Content-Type: application/json" -H "X-Client-Token: 5003062_0_1453967008_7c52d0249e96317c20433b151e6105b0" -H "Cache-Control: no-cache" -d '{
    "clip_id": 568
}' "http://api.topvdn.com/v2/record/clips/remove"
```

* 请求报文：

```json
POST /v2/record/clips/remove HTTP/1.1
Host: api.topvdn.com
Content-Type: application/json
X-Client-Token: 5003062_0_1453967008_7c52d0249e96317c20433b151e6105b0
Cache-Control: no-cache

{
    "clip_id": 568
}
```


* 返回数据：

```json
{
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型     | 描述        |
| ---------- | ------ | --------- |
| request_id | string | 此次请求的唯一编号 |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 403  | 没有权限访问该剪辑          |
| 404  | 指定的 clip_id 不存在    |
| 500  | 系统内部错误             |

### 2.2.7 设备 HLS 录像

* 接口状态：`使用中`
* 接口功能：查询设备的 HLS 录像播放列表，返回的数据为一个小时一个 m3u8 播放文件列表。
* 接口类型：设备接口
* 请求地址：`/v2/record/<cid>/storage/hls?start=1439626260&end=1439633460`
* 请求方式：`GET`
* 请求参数：

**注意：需要在请求携带设备 token**

| 参数名   | 类型   | 描述                    | 必须   | 举例         |
| ----- | ---- | --------------------- | ---- | ---------- |
| cid   | int  | 设备 ID                 | 是    | 1003775    |
| start | int  | `query param` 录像起始时间戳 | 否    | 1439626260 |
| end   | int  | `query param` 录像结束时间戳 | 否    | 1439633460 |


* `curl` 请求示例：

```
curl -X GET -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/record/10000415/storage/hls?client_token=10000415_3356753920_1462692103_558635b97a09da92fd43cb65a0e61789"
```

* 请求报文：

```json
GET /v2/record/10000415/storage/hls?client_token=10000415_3356753920_1462692103_558635b97a09da92fd43cb65a0e61789 HTTP/1.1
Host: api.topvdn.com
Cache-Control: no-cache

```


* 返回数据：

```json
{
	"playlist":[
		{
			"from": 1439626260,
			"to": 1439629860,
			"link": "http://api.topvdn.com/v2/record/1003775/storage/hls/1439626260_1439629860.m3u8?storage_server=1&client_token=xxxx"
		},
		{
			"from": 1439629860,
			"to": 1439633460,
			"link": "http://api.topvdn.com/v2/record/1003775/storage/hls/1439629860_1439633460.m3u8?storage_server=1&client_token=xxxx"
		}
	],
	"request_id": "70507923d1c97dcc990ef9a456ce10140d473ace"
}
```

* 返回字段：

| 字段名        | 类型         | 描述        |
| ---------- | ---------- | --------- |
| playlist   | json array | 播放文件列表    |
| request_id | string     | 此次请求的唯一编号 |


* playlist 字段：

| 字段名  | 类型   | 描述        |
| ---- | ---- | --------- |
| from | int  | 录像段起始时间   |
| to   | int  | 录像段结束时间   |
| link | int  | m3u8 播放文件 |


* events 字段：

| 字段名      | 类型     | 描述                |
| -------- | ------ | ----------------- |
| from     | int    | 录像段起始时间           |
| to       | int    | 录像段结束时间           |
| playlist | string | 事件存储的 m3u8 播放列表地址 |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 500  | 系统内部错误             |

### 2.2.8 设备录像 m3u8 播放

* 接口状态：`开发中`
* 接口功能：获取设备循环存储录像的 m3u8 播放文件，最多为一个小时，超过一个小时返回 `begin` 后一个小时内的数据。另外 `begin` 和 `end` 最好对齐 30 秒。
* 接口类型：设备接口
* 请求地址：`/v2/record/<cid>/storage/hls/<begin>_<end>.m3u8?client_token=xxxx`
* 请求方式：`GET`
* 请求参数：

**注意：需要在请求携带设备 token**

| 参数名   | 类型   | 描述             | 必须   | 举例         |
| ----- | ---- | -------------- | ---- | ---------- |
| cid   | int  | `路径参数` 设备 ID   | 是    | 1003775    |
| begin | int  | `路径参数` 录像起始时间戳 | 是    | 1439626260 |
| end   | int  | `路径参数` 录像结束时间戳 | 是    | 1439633460 |


* `curl` 请求示例：

```
curl -X GET -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/record/1003293/storage/hls/1452247470_1452249510.m3u8?client_token=1003293_3356753920_1461219077_fa60f10623d9349899bd6785473a8f93"
```

* 请求报文：

```json
GET /v2/record/1003293/storage/hls/1452247470_1452249510.m3u8?client_token=1003293_3356753920_1461219077_fa60f10623d9349899bd6785473a8f93 HTTP/1.1
Host: api.topvdn.com
Cache-Control: no-cache

```


* 返回数据：`m3u8` 文件
    * `Content-Type`:  `application/vnd.apple.mpegurl`

* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 500  | 系统内部错误             |

### 2.2.9 设备事件存储数据

* 接口状态：`开发中`
* 接口功能：查询指定设备的事件存储录像数据。
* 接口类型：设备接口
* 请求地址：
  `/v2/record/<cid>/events?begin=1441676854&end=1441680454`
* 请求方式：`GET`
* 请求参数：

**注意：需要在请求携带设备 token**

| 参数名   | 类型   | 描述                    | 必须   | 举例         |
| ----- | ---- | --------------------- | ---- | ---------- |
| cid   | int  | 设备 ID                 | 是    | 1003775    |
| begin | int  | `query param` 录像起始时间戳 | 否    | 1441676854 |
| end   | int  | `query param` 录像结束时间戳 | 否    | 1441680454 |


* `curl` 请求示例：

```
curl -X GET -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/record/1003775/events?begin=1441676854&end=1441680454&client_token=1003555_3356753920_1463469894_c88181fb30d35401cd4612cfde96a4d2"
```

* 请求报文：

```json
GET /v2/record/1003775/events?begin=1441676854&end=1441680454&client_token=1003555_3356753920_1463469894_c88181fb30d35401cd4612cfde96a4d2 HTTP/1.1
Host: api.topvdn.com
Cache-Control: no-cache

```


* 返回数据：

```json
{
	"events": [
		{
			"begin": 1458205472,
			"end": 1458205562,
			"url": "http://www.domain.com/v2/record/<client_id>/hls/1458205472_1458205562.m3u8?client_token=yyyy"
		},
		...
	],
	"request_id": "70507923d1c97dcc990ef9a456ce10140d473ace"
}
```

* 返回字段：

| 字段名        | 类型         | 描述        |
| ---------- | ---------- | --------- |
| events     | json array | 事件存储列表    |
| request_id | string     | 此次请求的唯一编号 |


* events 字段：

| 字段名   | 类型     | 描述                                  |
| ----- | ------ | ----------------------------------- |
| begin | int    | 事件存储起始时间，这个值与 cid 一起可以得到一个唯一的事件存储录像 |
| end   | int    | 事件存储段结束时间                           |
| url   | string | 事件存储的 m3u8 播放列表地址                   |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 500  | 系统内部错误             |

### 2.2.10 设备事件列表

* 接口状态：`开发中`
* 接口功能：查询指定设备的事件列表
* 接口类型：设备接口
* 请求地址：`/v2/record/<cid>/eventinfo?begin=1441676854&end=1441680454`
* 请求方式：`GET`
* 请求参数：

**注意：需要在请求携带设备 token**

| 参数名   | 类型   | 描述                    | 必须   | 举例         |
| ----- | ---- | --------------------- | ---- | ---------- |
| cid   | int  | 设备 ID                 | 是    | 1003775    |
| begin | int  | `query param` 录像起始时间戳 | 否    | 1441676854 |
| end   | int  | `query param` 录像结束时间戳 | 否    | 1441680454 |


* `curl` 请求示例：

```
curl -X GET -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/record/1003775/eventinfo?begin=1441676854&end=1441680454&client_token=1003555_3356753920_1463469894_c88181fb30d35401cd4612cfde96a4d2"
```

* 请求报文：

```json
GET /v2/record/1003775/eventinfo?begin=1441676854&end=1441680454&client_token=1003555_3356753920_1463469894_c88181fb30d35401cd4612cfde96a4d2 HTTP/1.1
Host: api.topvdn.com
Cache-Control: no-cache

```


* 返回数据：

```json
{
	"eventinfo": [
		{
			"event_time": 1458205472,
			"event_flag": 1,
			"event_type": 42
		},
		...
	],
	"request_id": "70507923d1c97dcc990ef9a456ce10140d473ace"
}
```

* 返回字段：

| 字段名        | 类型         | 描述        |
| ---------- | ---------- | --------- |
| eventinfo  | json array | 事件列表      |
| request_id | string     | 此次请求的唯一编号 |


* eventinfo 字段：

| 字段名        | 类型   | 描述                                |
| ---------- | ---- | --------------------------------- |
| event_time | int  | 发生时间                              |
| event_flag | int  | 兼容字段, 新版一直为 1 , 无具体意义            |
| event_type | int  | 事件存储 event_type ，由用户透传，用以标识事件录像类型 |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 500  | 系统内部错误             |

### 2.2.11 删除单个事件存储录像

* 接口状态：`开发中`
* 接口功能：删除某个设备指定 event_time 值的某个事件的所有存储数据。
* 接口类型：管理接口
* 请求地址：`/v2/record/<cid>/events/<event_time>` 
* 请求方式：`DELETE`
* 请求参数：

**注意：需要在请求首部携带 X-APP-ID 和 X-APP-Key**

| 参数名        | 类型   | 描述                                     | 必须   | 举例         |
| ---------- | ---- | -------------------------------------- | ---- | ---------- |
| cid        | int  | 路径参数，设备 ID                             | 是    | 1003775    |
| event_time | int  | 路径参数，设备事件存储的 begin 时间，可以从 `2.2.9` 接口获取 | 是    | 1458205472 |


* `curl` 请求示例：

```
curl -X DELETE -H "X-APP-ID: Test" -H "X-APP-Key: mock-app-key-use-your-own-pls"  "http://api.topvdn.com/v2/record/1003775/events/1458205472"
```

* 请求报文：

```json
DELETE /v2/record/1003775/events/1458205472 HTTP/1.1
Host: api.topvdn.com
X-APP-ID: Test
X-APP-Key: mock-app-key-use-your-own-pls

```


* 返回数据：

```json
{
	"request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型     | 描述        |
| ---------- | ------ | --------- |
| request_id | string | 此次请求的唯一编号 |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | app_key 验证不通过      |
| 500  | 系统内部错误             |

### 2.2.12 删除时间范围内事件存储录像

* 接口状态：`开发中`
* 接口功能：删除某个设备指定时间范围内的事件存储数据，begin 和 end 时间需要按小时对齐。
* 接口类型：管理接口
* 请求地址：`/v2/record/<cid>/events?begin=1458201600&end=1458205200` 
* 请求方式：`DELETE`
* 请求参数：

**注意：需要在请求首部携带 X-APP-ID 和 X-APP-Key**

| 参数名   | 类型   | 描述               | 必须        | 举例         |
| ----- | ---- | ---------------- | --------- | ---------- |
| cid   | int  | 路径参数，设备 ID       | 是         | 1003775    |
| begin | int  | query param，起始时间 | 否，默认为 0   | 1458201600 |
| end   | int  | query param，结束时间 | 否，默认为当前时间 | 1458205200 |


* `curl` 请求示例：

```
curl -X DELETE -H "X-APP-ID: Test" -H "X-APP-Key: mock-app-key-use-your-own-pls"  "http://api.topvdn.com/v2/record/1003775/events?begin=1458201600&end=1458205200"
```

* 请求报文：

```json
DELETE /v2/record/1003775/events?begin=1458201600&end=1458205200 HTTP/1.1
Host: api.topvdn.com
X-APP-ID: Test
X-APP-Key: mock-app-key-use-your-own-pls

```


* 返回数据：

```json
{
	"request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型     | 描述        |
| ---------- | ------ | --------- |
| request_id | string | 此次请求的唯一编号 |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | app_key 验证不通过      |
| 500  | 系统内部错误             |

## 2.3 消息

本节主要是提供了消息推送相关的接口，允许从 APP 的服务端调用及直接从设备客户端调用。

### 2.3.1 设备推送消息

* 接口状态：`使用中`
* 接口功能：提供给设备客户端推送消息，支持推送消息给一个或多个设备、或回调消息给用户。
* 接口类型：设备接口
* 请求地址：`/v2/message/client/push`
* 请求方式：`POST`
* 请求参数：

**注意：需要在请求携带 X-Client-Token**

* POST 请求参数

```json
{
    "msg": "aGVsbG8=",
    "flag": 3,
    "callback": 1,
    "access_tokens": ["5001234_0_1452755824_a91f4dbe1a3fb949d7f570cfb39f079a"]
}
```

| 参数名           | 类型         | 描述                                       | 必须   | 举例             |
| ------------- | ---------- | ---------------------------------------- | ---- | -------------- |
| msg           | string     | 要推送的消息 base64 编码后值，原消息长度不超过 256          | 是    | "aGVsbG8="     |
| flag          | int        | 消息的送达标记，2：消息尽可能送达,在没收到回应之前,会尝试按照1,2,3,5秒的间隔发送5次,若仍然没收到回应,会将消息丢弃, 3：消息转发一次后,丢弃 | 否    | 2 默认行为为 2      |
| callback      | int        | 是否回调给设备，1：是，0：否                          | 是    | １              |
| access_tokens | json array | 消息要推到的设备 token 列表                        | 是    | ［］空则表示不推送给任何设备 |


* `curl` 请求示例：

```
curl -X POST -H "X-Client-Token: 1003200_3356753920_1460640064_f95c09b6837c5fa95096f424ebb17015" -H "Content-Type: application/json" -H "Cache-Control: no-cache" -d '{
    "msg": "aGVsbG8=",
    "flag": 2,
    "callback": 1,
    "access_tokens": ["5003062_3356753920_1460640029_3c10950d5c5768b3c5b09728fd77516d"]
}' "http://api.topvdn.com/v2/message/client/push"
```

* 请求报文：

```json
POST /v2/message/client/push HTTP/1.1
Host: api.topvdn.com
X-Client-Token: 1003200_3356753920_1460640064_f95c09b6837c5fa95096f424ebb17015
Content-Type: application/json
Cache-Control: no-cache

{
    "msg": "aGVsbG8=",
    "flag": 2,
    "callback": 1,
    "access_tokens": ["5003062_3356753920_1460640029_3c10950d5c5768b3c5b09728fd77516d"]
}
```


* 返回数据：

```json
{
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型     | 描述        |
| ---------- | ------ | --------- |
| request_id | string | 此次请求的唯一编号 |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 500  | 系统内部错误             |

### 2.3.2 服务器推送消息

* 接口状态：`使用中`
* 接口功能：提供给应用服务器推送消息给多个设备，或者代理设备推送消息。
* 接口类型：管理接口
* 请求地址：`/v2/message/server/push`
* 请求方式：`POST`
* 请求参数：


**注意：需要在请求首部携带 X-APP-ID 和 X-APP-Key**

* POST 请求参数

批量推送消息:

```json
{
    "proxy": 0,
    "payload": {
        "msg": "aGVsbG8=",
        "flag": 3,
        "clients": [5003062, 1003775]
    }
}
```

| 参数名     | 类型          | 描述       | 必须   | 举例         |
| ------- | ----------- | -------- | ---- | ---------- |
| proxy   | int         | 是否为代理发送  | 是    | 批量推送消息值为 0 |
| payload | json object | 消息推送负载数据 | 是    | {}         |


* payload 字段:

| 参数名     | 类型         | 描述                                       | 必须   | 举例                 |
| ------- | ---------- | ---------------------------------------- | ---- | ------------------ |
| msg     | string     | 要推送的消息 base64 编码后值，原消息长度不超过 256          | 是    | "aGVsbG8="         |
| flag    | int        | 消息的送达标记，2：消息尽可能送达,在没收到回应之前,会尝试按照1,2,3,5秒的间隔发送5次,若仍然没收到回应,会将消息丢弃, 3：消息转发一次后,丢弃 | 否    | 2 默认行为为 2          |
| clients | json array | 接收消息的设备列表                                | 是    | [5003062, 1003775] |


代理推送消息:

```json
{
    "proxy": 1,
    "payload": [
        {
            "from": 1003200,
            "to": 5003062,
            "flag": 3,
            "msg": "aGVsbG8="
        }    
    ]
}
```

| 参数名     | 类型                | 描述       | 必须   | 举例         |
| ------- | ----------------- | -------- | ---- | ---------- |
| proxy   | int               | 是否为代理发送  | 是    | 代理推送消息值为 1 |
| payload | json object array | 消息推送负载数据 | 是    | []         |


* payload 字段：

| 参数名  | 类型     | 描述                                       | 必须   | 举例         |
| ---- | ------ | ---------------------------------------- | ---- | ---------- |
| msg  | string | 要推送的消息 base64 编码后值，原消息长度不超过 256          | 是    | "aGVsbG8=" |
| flag | int    | 消息的送达标记，2：消息尽可能送达,在没收到回应之前,会尝试按照1,2,3,5秒的间隔发送5次,若仍然没收到回应,会将消息丢弃, 3：消息转发一次后,丢弃 | 否    | 2 默认行为为 2  |
| from | int    | 消息来源设备 id                                | 是    | 1003200    |
| to   | int    | 接收消息的设备 id                               | 是    | 5002654    |


* `curl` 请求示例：

```
curl -X POST -H "Content-Type: application/json" -H "X-APP-ID: Test" -H "X-APP-Key: mock-app-key-use-your-own-pls" -H "Cache-Control: no-cache" -d '{
    "proxy": 0,
    "payload": {
        "msg": "aGVsbG8=",
        "flag": 3,
        "clients": [1003181]
    }
}' "http://api.topvdn.com/v2/message/server/push"
```

* 请求报文：

```json
POST /v2/message/server/push HTTP/1.1
Host: api.topvdn.com
Content-Type: application/json
X-APP-ID: Test
X-APP-Key: mock-app-key-use-your-own-pls
Cache-Control: no-cache

{
    "proxy": 0,
    "payload": {
        "msg": "aGVsbG8=",
        "flag": 3,
        "clients": [1003181]
    }
}
```


* 返回数据：

```json
{
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型     | 描述        |
| ---------- | ------ | --------- |
| request_id | string | 此次请求的唯一编号 |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 500  | 系统内部错误             |

## 2.4 回调

本节接口用户查看和更新 APP 的回调地址，APP 如果提供了通用回调地址，则录像剪辑完成的时候会推送数据到通用回调地址，如果提供了状态回调地址，则设备状态变化数据会推到这个地址。


| 回调类型   | 接收数据             |
| ------ | ---------------- |
| 通用回调地址 | 录像剪辑完成及消息推送回调等数据 |
| 状态回调地址 | 设备状态变化数据         |

### 2.4.1 查询回调地址

* 接口状态：`使用中`
* 接口功能：查询应用服务器当前配置的回调地址。
* 请求地址：`/v2/apps/webhook`
* 请求方式： `GET`
* 请求参数：

**注意：需要在请求首部携带 X-APP-ID 和 X-APP-Key**


* `curl` 请求示例：

```
curl -X GET -H "X-APP-ID: Test" -H "X-APP-Key: mock-app-key-use-your-own-pls" -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/apps/webhook"
```

* 请求报文：

```json
GET /v2/apps/webhook HTTP/1.1
Host: api.topvdn.com
X-APP-ID: Test
X-APP-Key: mock-app-key-use-your-own-pls
Cache-Control: no-cache

```

* 返回数据：

```json
{
	"webhook": "http://www.domain.com/api/url",
	"state_webhook": "http://www.domain.com/api/callback",
	"request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名           | 类型     | 描述         |
| ------------- | ------ | ---------- |
| webhook       | string | 通用回调接口地址   |
| state_webhook | string | 设备状态变更回调地址 |
| request_id    | string | 此次请求的唯一编号  |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | app key 验证不通过      |
| 500  | 系统内部错误             |

### 2.4.2 更新回调地址

* 接口状态：`使用中`
* 接口功能：更新应用服务器的回调地址
* 请求地址：`/v2/apps/webhook`
* 请求方式： `POST`
* 请求参数：

**注意：需要在请求首部携带 X-APP-ID 和 X-APP-Key**

```json
{
	"webhook": "http://www.domain.com/api/newurl",
	"state_webhook": ""
}
```

| 参数名           | 类型     | 描述                           | 必须   | 举例                                  |
| ------------- | ------ | ---------------------------- | ---- | ----------------------------------- |
| webhook       | string | 通用回调接口地址，录像剪辑完成及消息回调等会推到这个地址 | 否    | "" 空字符串表示删除                         |
| state_webhook | string | 状态回调地址，设备状态变更会推向这个地址         | 否    | "https://www.domain.com/api/newurl" |


* `curl` 请求示例：

```
curl -X POST -H "X-APP-ID: Test" -H "X-APP-Key: mock-app-key-use-your-own-pls" -H "Content-Type: application/json" -H "Cache-Control: no-cache" -d '{
    "webhook": "http://www.baidu.com/"
}' "http://api.topvdn.com/v2/apps/webhook"
```

* 请求报文：

```json
POST /v2/apps/webhook HTTP/1.1
Host: api.topvdn.com
X-APP-ID: Test
X-APP-Key: mock-app-key-use-your-own-pls
Content-Type: application/json
Cache-Control: no-cache

{
    "webhook": "http://www.baidu.com/"
}
```


* 返回数据：

```json
{
	"request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型     | 描述        |
| ---------- | ------ | --------- |
| request_id | string | 此次请求的唯一编号 |


* 状态码

| 状态码  | 描述                  |
| ---- | ------------------- |
| 200  | 请求成功，返回正确的数据        |
| 400  | 参数错误，可能缺少参数或者类型不正确  |
| 401  | app key 验证不通过       |
| 406  | 提供的分空字符串 URL 地址不可访问 |
| 500  | 系统内部错误              |

## 2.5 短视频及图片上传分享

短视频及图片上传分享流程：

 请求上传 (2.5.1) -> 上传文件 (2.5.2) -> 获取分享链接 (2.5.3) -> 分享

### 2.5.1 请求上传

* 接口状态：`开发中`
* 接口功能：用户申请上传短视频或图片，将会返回一个上传 url ，上传 url 包含了相关上传的信息和校验 token ，存在有效时间，暂定为 30 分钟。
* 接口类型：设备接口
* 请求地址：`/v2/cloud/<client_id>/uploads`
* 请求方式：`POST`
* 请求参数：

**注意：需要在请求携带设备 client_token**

| 参数名       | 类型   | 描述          | 必须   | 举例   |
| --------- | ---- | ----------- | ---- | ---- |
| client_id | int  | 路径参数，客户端 ID | 是    | 42   |


* `curl` 请求示例：

```
curl -X POST -H "Content-Type: application/json" -H "X-Client-Token: 5003062_3356753920_1460640064_0037c26c9018f9984c866db08bed2d95" -H "Cache-Control: no-cache" -d '' "http://api.topvdn.com/v2/cloud/5003062/uploads"
```

* 请求报文：

```json
POST /v2/cloud/5003062/uploads HTTP/1.1
Host: api.topvdn.com
Content-Type: application/json
X-Client-Token: 5003062_3356753920_1460640064_0037c26c9018f9984c866db08bed2d95
Cache-Control: no-cache

```


* 返回数据：

```json
{
	"upload_id": 42,
	"upload_url": "http://www.domain.com/v2/cloud/<client_id>/uploads/<upload_id>?client_token=xxx&upload_token=xxxxxxx",
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型     | 描述                       |
| ---------- | ------ | ------------------------ |
| upload_id  | int    | 本次上传的标识，可以通过这个来下载或分享本次上传 |
| upload_url | string | 上传地址，通过表单的形式 POST 上传文件   |
| request_id | string | 此次请求的唯一编号                |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 500  | 系统内部错误             |

### 2.5.2 上传文件

* 接口状态：`开发中`
* 接口功能：即是 `2.5.1` 接口返回的 upload_url ，可以通过本接口上传文件，本接口不一定在 `api.topvdn.com` 上。
* 接口类型：设备接口
* 请求地址：`/v2/cloud/<client_id>/uploads/<upload_id>?upload_token=xxxxxxx`
* 请求方式：`POST`
* 请求参数：

**注意：需要在请求携带设备 client_token**
**注意：上传以 multipart/form-data 的方式提交**

| 参数名          | 类型     | 描述                              | 必须   | 举例      |
| ------------ | ------ | ------------------------------- | ---- | ------- |
| client_id    | int    | 路径参数，客户端 ID                     | 是    | 1003775 |
| upload_id    | int    | 路径参数，上传 ID                      | 是    | 42      |
| upload_token | string | `query param` 上传的 Token         | 是    | "xxxx"  |
| upload_file  | 文件     | `form data` 要上传的文件，注意文件的名称需要有后缀 | 是    | 二进制文件   |



* `curl` 请求示例：

```
curl -X POST -H "Cache-Control: no-cache" -H "Content-Type: multipart/form-data" -F "upload_file=@whatabeauty.png" "http://122.226.181.107/v2/cloud/5003062/uploads/80?upload_token=NTAwMzA2Ml84MF8xNDYzNDY1NDIyXzNfZW1wdHlfNTM3N2JjZTJkOGEwZmViMjg1NzdiZGRjNmUyZGI2OTU4OGMxODUzNg%3D%3D&client_token=5003062_3356753920_1460640064_cfebd8c9c262d3be3e4cc06cd6f007cc"
```

* 请求报文：

```json
POST /v2/cloud/5003062/uploads/80?upload_token=NTAwMzA2Ml84MF8xNDYzNDY1NDIyXzNfZW1wdHlfNTM3N2JjZTJkOGEwZmViMjg1NzdiZGRjNmUyZGI2OTU4OGMxODUzNg%3D%3D&client_token=5003062_3356753920_1460640064_0037c26c9018f9984c866db08bed2d95 HTTP/1.1
Host: 122.226.181.107
Cache-Control: no-cache
Content-Type: multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW

----WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="upload_file"; filename="whatabeauty.png"
Content-Type: 


----WebKitFormBoundary7MA4YWxkTrZu0gW
```


* 返回数据：

```json
{
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型     | 描述        |
| ---------- | ------ | --------- |
| request_id | string | 此次请求的唯一编号 |


* 状态码

| 状态码  | 描述                                 |
| ---- | ---------------------------------- |
| 200  | 请求成功，返回正确的数据                       |
| 400  | 参数错误，可能缺少参数或者类型不正确                 |
| 401  | token 验证不通过                        |
| 403  | 上传 token 不正确或者过期                   |
| 406  | 不允许的文件类型，图片支持 jpeg / png ，视频支持 mp4 |
| 413  | 文件大小超出限制，图片 2M，视频 16M              |
| 500  | 系统内部错误                             |

### 2.5.3 获取分享链接

* 接口状态：`开发中`
* 接口功能：获取 client 某个上传的分享链接，可以将得到的上传资源链接分享到公开的地方提供给别人查看。
* 接口类型：设备接口
* 请求地址：`/v2/cloud/<client_id>/uploads/<upload_id>/share?expire=3600`
* 请求方式：`GET`
* 请求参数：

**注意：需要在请求携带设备 client_token**

| 参数名       | 类型   | 描述                                       | 必须   | 举例        |
| --------- | ---- | ---------------------------------------- | ---- | --------- |
| client_id | int  | 路径参数，客户端 ID                              | 是    | 1003775   |
| upload_id | int  | 路径参数，上传 ID                               | 是    | 42        |
| expire    | int  | `query param` 分享过期时间，单位为秒，不提供或者为 0 则分享链接不过期 | 否    | 3600 一个小时 |


* `curl` 请求示例：

```
curl -X GET -H "Content-Type: application/json" -H "X-Client-Token: 5003062_3356753920_1460640064_99960324d02ba8be765db83066b833db" -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/cloud/5003062/uploads/1/share?expire=30"
```

* 请求报文：

```json
GET /v2/cloud/5003062/uploads/1/share?expire=30 HTTP/1.1
Host: api.topvdn.com
Content-Type: application/json
X-Client-Token: 5003062_3356753920_1460640064_99960324d02ba8be765db83066b833db
Cache-Control: no-cache

```


* 返回数据：

```json
{
	"link": "http://www.domain.com/v2/cloud/<cid>/uploads/<upload_id>/share/<file_name>?share_token=xxxx",
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型     | 描述        |
| ---------- | ------ | --------- |
| request_id | string | 此次请求的唯一编号 |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 403  | 无权分享该上传            |
| 404  | 指定的上传不存在           |
| 500  | 系统内部错误             |

### 2.5.4 查看上传列表

* 接口状态：`开发中`
* 接口功能：查看 client 的上传列表，这里只返回上传成功的文件列表。
* 接口类型：设备接口
* 请求地址：`/v2/cloud/<client_id>/uploads?page=1&size=10`
* 请求方式：`GET`
* 请求参数：

**注意：需要在请求携带设备 client_token**

| 参数名       | 类型   | 描述                        | 必须   | 举例      |
| --------- | ---- | ------------------------- | ---- | ------- |
| client_id | int  | 路径参数，客户端 ID               | 是    | 1003775 |
| page      | int  | `query param` 页数，默认为 1    | 否    | 1       |
| size      | int  | `query param` 每页数量，默认为 10 | 否    | 10      |


* `curl` 请求示例：

```
curl -X GET -H "X-Client-Token: 5003062_3356753920_1460640064_cfebd8c9c262d3be3e4cc06cd6f007cc" -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/cloud/5003062/uploads?page=1&size=10"
```

* 请求报文：

```json
GET /v2/cloud/5003062/uploads?page=1&size=10 HTTP/1.1
Host: api.topvdn.com
X-Client-Token: 5003062_3356753920_1460640064_cfebd8c9c262d3be3e4cc06cd6f007cc
Cache-Control: no-cache

```


* 返回数据：

```json
{
	"total_space": 1074790400,
	"used_space": 254399,
	"uploads": [
		{
			"id": 42,
			"size": 4096,
			"filename": "myfavoriate.jpg",
			"mimetype": "image/jpeg",
			"updated": "2012-01-01T12:00:00Z",
			"url": "http://api.topvdn.com/v2/cloud/<client_id>/uploads/<upload_id>/<file_name>?client_token=xxxx"
		},
		...
	],
	"page": 1,
	"size": 10,
	"total": 25,
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名         | 类型         | 描述                     |
| ----------- | ---------- | ---------------------- |
| total_space | int        | 该 client 上传空间大小，单位字节   |
| used_space  | int        | 该 client 已经使用的空间，单位字节  |
| uploads     | json array | 上传列表                   |
| page        | int        | 列表页数                   |
| size        | int        | 每页内容数量，最大为 100 ，默认为 10 |
| total       | int        | 该 client 上传的文件数量       |
| request_id  | string     | 此次请求的唯一编号              |


* uploads 字段：

| 字段名      | 类型     | 描述                           |
| -------- | ------ | ---------------------------- |
| id       | int    | 上传 ID                        |
| size     | int    | 上传文件大小                       |
| filename | string | 上传的文件名，带后缀                   |
| mimetype | string | 上传的文件资源类型                    |
| updated  | string | 上传的更新时间，一般即是上传完成时间           |
| url      | string | 上传的文件下载地址，需要 client token 下载 |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 500  | 系统内部错误             |

### 2.5.5 下载上传内容

* 接口状态：`开发中`
* 接口功能：下载上传的文件，可以通过 `2.5.4` 接口得到，本接口不一定在 `api.topvdn.com` 上。
* 接口类型：设备接口
* 请求地址：`/v2/cloud/<client_id>/uploads/<upload_id>/<file_name>`
* 请求方式：`GET`
* 请求参数：

**注意：需要在请求携带设备 client_token**

| 参数名       | 类型     | 描述           | 必须   | 举例              |
| --------- | ------ | ------------ | ---- | --------------- |
| client_id | int    | 路径参数，客户端 ID  | 是    | 1003775         |
| upload_id | int    | 路径参数，上传 ID   | 是    | 42              |
| file_name | string | 路径参数，带后缀的文件名 | 是    | "favoriate.mp4" |


* `curl` 请求示例：

```
curl -X GET -H "Cache-Control: no-cache" "http://122.226.181.107/v2/cloud/5003062/uploads/80/whatabeauty.png?client_token=5003062_3356753920_1460640064_cfebd8c9c262d3be3e4cc06cd6f007cc"
```

* 请求报文：

```json
GET /v2/cloud/5003062/uploads/80/whatabeauty.png?client_token=5003062_3356753920_1460640064_cfebd8c9c262d3be3e4cc06cd6f007cc HTTP/1.1
Host: 122.226.181.107
Cache-Control: no-cache

```


* 返回数据：上传的文件内容

* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 403  | 无权访问该上传            |
| 404  | 该上传文件不存在，可能已经被删除   |
| 500  | 系统内部错误             |

### 2.5.6 删除上传的文件

* 接口状态：`开发中`
* 接口功能： 删除上传的指定文件。
* 接口类型：设备接口
* 请求地址：`/v2/cloud/<client_id>/uploads/<upload_id>`
* 请求方式：`DELETE`
* 请求参数：

**注意：需要在请求携带设备 client_token**

| 参数名       | 类型   | 描述          | 必须   | 举例      |
| --------- | ---- | ----------- | ---- | ------- |
| client_id | int  | 路径参数，客户端 ID | 是    | 1003775 |
| upload_id | int  | 路径参数，上传 ID  | 是    | 42      |


* 返回数据：

```json
{
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型     | 描述        |
| ---------- | ------ | --------- |
| request_id | string | 此次请求的唯一编号 |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 403  | 无权访问该上传            |
| 404  | 该上传文件不存在，可能已经被删除   |
| 500  | 系统内部错误             |

## 附录 1 回调请求

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
| X-Topvdn-Event | 请求的事件，`device-message` :设备消息回调事件，`device-record-clip`：录像剪辑回调 |
| X-Event-Sign   | 请求签名，需要对签名进行验证                           |

**签名的算法:** 

伪码：

md5(X-APP-ID+request.body+X-APP-Key)

具体：

羚羊云分配的 `X-APP-ID` ，整个请求体和羚羊云分配的 `X-APP-Key` 连接成一个字符串，然后用 md5 算法哈希。

对请求进行签名是为了让应用服务器验证这个请求的合法性，检查请求在中途是否被篡改，所以应用服务器应该对每个回调的消息请求都进行签名校验。

##  附录 1.1 设备消息回调

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

##  附录 1.2 录像剪辑回调

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

##  附录 1.3 设备状态变化

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
