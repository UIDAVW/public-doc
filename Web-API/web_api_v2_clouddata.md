# 羚羊云Web API-云端数据管理

该部分接口用于清理或删除指定设备存储在羚羊云的数据，这些数据包括录像文件、图片文件、短视频文件等。

## 1 清除设备的云数据

* 接口状态：`使用中`
* 接口功能：清除指定设备的所有存储数据，内容包括循环存储、时事件存储及所有截图。本接口调用是启动一个异步的任务，**数据一旦删除无法恢复!!!**
* 接口类型：管理接口
* 使用对象：应用服务器
* 请求地址：`/v2/devices/<cid>/storage`
* 请求方式：`DELETE`
* 权限验证：**需要在请求首部携带 X-APP-ID 和 X-APP-Key**
* 请求参数：

| 参数名  | 类型   | 描述         | 必须   | 举例      |
| ---- | ---- | ---------- | ---- | ------- |
| cid  | int  | 路径参数，设备 ID | 是    | 1003200 |


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

## 2 删除设备的云录像

* 接口状态：`开发中`
* 接口功能：删除设备指定时间内的循环式录像数据，必须要提供指定的 `start` 和 `end` 时间。本接口调用是启动一个异步的任务，**数据一旦删除无法恢复!!!**
* 接口类型：管理接口
* 使用对象：应用服务器
* 请求地址：`/v2/devices/<cid>/storage/partial?start=1439626260&end=1439633460`
* 请求方式：`DELETE`
* 权限验证：**需要在请求首部携带 X-APP-ID 和 X-APP-Key**
* 请求参数：

| 参数名   | 类型   | 描述                  | 必须   | 举例         |
| ----- | ---- | ------------------- | ---- | ---------- |
| cid   | int  | 路径参数，设备 ID          | 是    | 1003200    |
| start | int  | `query param` 起始时间戳 | 是    | 1460689347 |
| end   | int  | `query param` 结束时间戳 | 是    | 1460689499 |


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

## 3 删除指定时间的事件录像

* 接口状态：`开发中`
* 接口功能：删除设备指定时间的整个事件录像存储数据, 时间值应该为事件存储的 `begin` 。
* 接口类型：管理接口
* 使用对象：应用服务器
* 请求地址：`/v2/record/<cid>/events/<event_time>` 
* 请求方式：`DELETE`
* 权限验证：**需要在请求首部携带 X-APP-ID 和 X-APP-Key**
* 请求参数：

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

## 4 删除某时间段的事件式录像

* 接口状态：`开发中`
* 接口功能：删除某个设备指定时间范围内的事件式录像，begin 和 end 时间需要按小时对齐。
* 接口类型：管理接口
* 使用对象：应用服务器
* 请求地址：`/v2/record/<cid>/events?begin=1458201600&end=1458205200` 
* 请求方式：`DELETE`
* 权限验证：**需要在请求首部携带 X-APP-ID 和 X-APP-Key**
* 请求参数：

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
