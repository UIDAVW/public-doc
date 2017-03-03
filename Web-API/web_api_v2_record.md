# 羚羊云Web API-查询设备录像

获取<u>设备在羚羊云存储的音视频数据及事件信息</u>的统一接口。

## 1 获取设备录像及事件

* 接口状态：`开发中`
* 接口功能：获取指定设备羚羊云端的录像 HLS 播放地址及事件信息。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/record/<cid>`
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
curl -X GET -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/record/1003555?client_token=1003555_3356753920_1463469894_c88181fb30d35401cd4612cfde96a4d2"
```

* 请求报文：

```json
GET /v2/record/1003555?client_token=1003555_3356753920_1463469894_c88181fb30d35401cd4612cfde96a4d2 HTTP/1.1
Host: api.topvdn.com
Cache-Control: no-cache

```


* 返回数据：

```json
{
	"videos": [
		{
			"begin": 1458205472,
			"end": 1458205562,
			"url": "http://www.domain.com/v2/record/<cid>/<type>/1458205472_1458205562.m3u8?client_token=yyyy"
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
	"request_id": "70507923d1c97dcc990ef9a456ce10140d473ace"
}
```

* 返回字段：

| 字段名        | 类型         | 描述        |
| ---------- | ---------- | --------- |
| videos     | json array | 录像片段列表    |
| eventinfo  | son array  | 事件列表      |
| request_id | string     | 此次请求的唯一编号 |


* videos 字段：

| 字段名   | 类型     | 描述            |
| ----- | ------ | ------------- |
| begin | int    | 录像片段起始时间      |
| end   | int    | 录像片段结束时间      |
| url   | string | 录像片段的 m3u8 地址 |

- eventinfo 字段：

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
