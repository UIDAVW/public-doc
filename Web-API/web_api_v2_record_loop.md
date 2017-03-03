# 羚羊云Web API-查询循环式录像

获取<u>设备以循环方式存储音视频数据在羚羊云</u>的录像时间轴或录像文件列表。

## 1 获取录像时间轴

* 接口状态：`调整中`
* 接口功能：获取指定设备羚羊云端的录像的时间轴列表，列表中的一个条目表示一个完整的时间段，该时间段内存有录像。若列表中仅有一条则表明从开始存储音视频流到现在一直都在录像。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/record/<cid>/timeline`
* 请求方式：`GET`
* 权限验证：**需要在请求携带本方设备token**
* 请求参数：

| 参数名   | 类型   | 描述                    | 必须   | 举例         |
| ----- | ---- | --------------------- | ---- | ---------- |
| cid   | int  | 设备 ID                 | 是    | 1003555    |
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
  	"eventinfo": [
      	{
        	"event_flag": 1,
      		"event_time": 1476948635,
      		"event_type": 14
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
| eventinfo  | son array  | 事件列表          |
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

- eventinfo 字段：

| 字段名        | 类型   | 描述                                |
| ---------- | ---- | --------------------------------- |
| event_time | int  | 发生时间                              |
| event_flag | int  | 兼容字段, 新版一直为 1 , 无具体意义            |
| event_type | int  | 事件存储 event_type ，由用户透传，用以标识事件录像类型 |


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

## 2 获取录像文件列表

* 接口状态：`使用中`
* 接口功能：获取指定设备的HLS录像文件列表，返回的数据为m3u8文件列表，每个文件的录像时长为1小时。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/record/<cid>/storage/hls?start=1439626260&end=1439633460`
* 请求方式：`GET`
* 权限验证：**需要在请求携带本方设备token**
* 请求参数：



| 参数名   | 类型   | 描述                    | 必须   | 举例         |
| ----- | ---- | --------------------- | ---- | ---------- |
| cid   | int  | 设备 ID                 | 是    | 10000415   |
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

## 3 获取录像文件

* 接口状态：`开发中`
* 接口功能：获取指定设备的循环式录像的录像文件，文件的录像时长最多为1小时，超过1小时则返回`begin`后1小时内的数据。另外`begin`和`end`最好对齐30秒。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/record/<cid>/storage/hls/<begin>_<end>.m3u8?client_token=xxxx`
* 请求方式：`GET`
* 权限验证：**需要在请求携带本方设备token**
* 请求参数：

| 参数名   | 类型   | 描述             | 必须   | 举例         |
| ----- | ---- | -------------- | ---- | ---------- |
| cid   | int  | `路径参数` 设备 ID   | 是    | 1003293    |
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
