# 羚羊云Web API-剪辑云端录像
接口包括：
新建对云端的录像进行剪辑的任务；
查询已剪辑的任务列表；
查询指定剪辑任务的状态；
获取指定剪辑任务的录像文件地址；
删除指定剪辑任务；

## 1 新建剪辑任务

* 接口状态：`使用中`
* 接口功能：为指定应用客户端创建一个新的剪辑任务，本接口只是开启一个异步的剪辑任务，任务状态可以通过查看状态接口得到，剪辑任务完成也会回调用户提供的回调接口通知。
* 接口类型：设备接口
* 使用对象：应用该客户端
* 请求地址：`/v2/record/<client_id>/clips`
* 请求方式：`POST`
* 权限验证：**需要在请求携带本方设备token和要剪辑的录像设备访问token**
* 请求参数：

| 参数名       | 类型   | 描述                        | 必须   | 举例         |
| --------- | ---- | ------------------------- | ---- | ---------- |
| client_id | int  | 剪辑所属 client id ，一般即是用户 id | 是    | 3000000226    |
| cid       | int  | 要剪辑的录像设备 ID               | 是    | 1003136    |
| start     | int  | 剪辑起始时间戳                   | 否    | 1456142250 |
| end       | int  | 剪辑结束时间戳                   | 否    | 1456142850 |

**注意：消息回调的数据请查看异步回调事件**

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

## 2 获取剪辑列表

* 接口状态：`使用中`
* 接口功能：获取一个本方设备下所有的录像剪辑列表，只会返回成功的剪辑。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/record/<client_id>/clips?page=1&size=10`
* 请求方式：`GET`
* 权限验证：**需要在请求携带本方设备的token**
* 请求参数：

| 参数名       | 类型   | 描述                        | 必须   | 举例      |
| --------- | ---- | ------------------------- | ---- | ------- |
| client_id | int  | 剪辑所属 client id ，一般即是用户 id | 是    | 3000000226 |
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

## 3 查询剪辑状态

* 接口状态：`使用中`
* 接口功能：查询指定剪辑任务的剪辑状态。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/record/clips/<clip_id>/status`
* 请求方式：`GET`
* 权限验证：**需要在请求携带本方设备的token**
* 请求参数：

| 参数名     | 类型   | 描述                  | 必须   | 举例   |
| ------- | ---- | ------------------- | ---- | ---- |
| clip_id | int  | `query param` 剪辑 ID | 是    | 42   |


* `curl` 请求示例：

```
curl -X GET -H "X-Client-Token: 3000000226_0_1456222962_478f89ea0bcbb6678cef561adc6efe52" -H "Content-Type: application/json" -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/record/clips/42/status"
```

* 请求报文：

```json
GET /v2/record/clips/42/status HTTP/1.1
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

## 4 获取剪辑文件

* 接口状态：`使用中`
* 接口功能：获取指定剪辑任务的视频下载地址列表，一个剪辑可能会由多个分段视频组成。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/record/clips/<clip_id>`
* 请求方式：`GET`
* 权限验证：**需要在请求携带本方设备的token**
* 请求参数：
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

## 5 删除一个剪辑

* 接口状态：`使用中`
* 接口功能：删除一个指定剪辑任务的数据。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/record/clips/remove`
* 请求方式：`POST`
* 权限验证：**需要在请求携带本方设备的token**
* 请求参数：

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
