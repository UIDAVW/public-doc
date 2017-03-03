# 羚羊云Web API-查询事件式录像

获取<u>设备以事件方式存储音视频数据在羚羊云</u>的事件列表、录像文件列表和录像文件。

## 1 获取事件列表

* 接口状态：`使用中`
* 接口功能：获取指定设备的事件列表，列表中的条目并非一个完整事件的开始和结束，仅仅记录了某个事件的发生时间，例如：1458205472时间点开始了某个事件，是一个条目；1458206072时间点结束了某个事件，是另一个条目。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/record/<cid>/eventinfo?begin=1441676854&end=1441680454`
* 请求方式：`GET`
* 权限验证：**需要在请求携带本方设备token**
* 请求参数：

| 参数名   | 类型   | 描述                    | 必须   | 举例         |
| ----- | ---- | --------------------- | ---- | ---------- |
| cid   | int  | 设备 ID                 | 是    | 1003555    |
| begin | int  | `query param` 录像起始时间戳 | 否    | 1441676854 |
| end   | int  | `query param` 录像结束时间戳 | 否    | 1441680454 |


* `curl` 请求示例：

```
curl -X GET -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/record/1003555/eventinfo?begin=1441676854&end=1441680454&client_token=1003555_3356753920_1463469894_c88181fb30d35401cd4612cfde96a4d2"
```

* 请求报文：

```json
GET /v2/record/1003555/eventinfo?begin=1441676854&end=1441680454&client_token=1003555_3356753920_1463469894_c88181fb30d35401cd4612cfde96a4d2 HTTP/1.1
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

## 2 获取录像文件列表

* 接口状态：`使用中`
* 接口功能：获取指定设备某时间段内所有事件式录像的文件列表。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：
  `/v2/record/<cid>/events?begin=1441676854&end=1441680454`
* 请求方式：`GET`
* 权限验证：**需要在请求携带本方设备token**
* 请求参数：

| 参数名   | 类型   | 描述                    | 必须   | 举例         |
| ----- | ---- | --------------------- | ---- | ---------- |
| cid   | int  | 设备 ID                 | 是    | 1003555    |
| begin | int  | `query param` 录像起始时间戳 | 否    | 1441676854 |
| end   | int  | `query param` 录像结束时间戳 | 否    | 1441680454 |


* `curl` 请求示例：

```
curl -X GET -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/record/1003555/events?begin=1441676854&end=1441680454&client_token=1003555_3356753920_1463469894_c88181fb30d35401cd4612cfde96a4d2"
```

* 请求报文：

```json
GET /v2/record/1003555/events?begin=1441676854&end=1441680454&client_token=1003555_3356753920_1463469894_c88181fb30d35401cd4612cfde96a4d2 HTTP/1.1
Host: api.topvdn.com
Cache-Control: no-cache

```


* 返回数据：

```json
{
	"events": [
		{
			"begin": 1441676854,
			"end": 1441680454,
			"url": "http://www.domain.com/v2/record/<client_id>/hls/1441676854_1441680454.m3u8?client_token=yyyy"
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

## 3 获取事件录像文件

* 接口状态：`使用中`
* 接口功能：获取某个事件存储指定时间范围内的录像播放文件。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/record/<cid>/events/hls/<begin>_<end>.m3u8?client_token=xxx`
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
curl -X GET -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/record/1003293/events/hls/1452247470_1452249510.m3u8?client_token=1003293_3356753920_1461219077_fa60f10623d9349899bd6785473a8f93"
```

* 请求报文：

```json
GET /v2/record/1003293/events/hls/1452247470_1452249510.m3u8?client_token=1003293_3356753920_1461219077_fa60f10623d9349899bd6785473a8f93 HTTP/1.1
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
