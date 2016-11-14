# 羚羊云Web API-事件传输

接口包括：

1 上传新的事件消息;

2 查询已上传的事件;

本节提供的接口请求 HOST 不一定是 `api.topvdn.com` ，请根据具体的接口获取上传事件的服务器 HOST。

## 1 事件上传

- 接口状态：`开发中`
- 接口功能：上传事件信息
- 接口类型：设备接口
- 使用对象：应用客户端
- 请求地址：`/v2/events`
- 请求方式：`POST`
- 权限验证：**需要在请求携带本方设备的token**
- 请求参数：

```json
{
    "cid": 10000415,
    "mode": 1,
    "event_type": 12,
    "expire_time": 3600,
    "subject": "门禁事件通知",
    "body": {
        "user": "张三",
        "event": "启动门禁"
    },
    "attachments": ["5821975e31603ec1bb821d4e", "5680a94a07d2786a03239c37"],
    "client_version": "2.87",
    "client_type": "1"
}
```

- `curl` 请求示例：

```
curl -X POST -H "Content-Type: application/json" -H "Cache-Control: no-cache" -d '{
  	"cid": 10000415,
	"mode": 1,
	"event_type": 12,
	"expire_time": 3600,
    "subject": "门禁事件通知",
    "body": {
      "user": "张三",
      "event": "启动门禁"
    },
    "attachments": ["5821975e31603ec1bb821d4e", "5680a94a07d2786a03239c37"],
    "client_version": "2.87",
    "client_type": "1"
}' "http://127.0.0.1/v2/events"
```

- 请求报文：

```
POST /v2/events HTTP/1.1
Host: 127.0.0.1
Content-Type: application/json
Cache-Control: no-cache

{
  	"cid": 10000415,
	"mode": 1,
	"event_type": 12,
	"expire_time": 3600,
    "subject": "门禁事件通知",
    "body": {
      "user": "张三",
      "event": "启动门禁"
    },
    "attachments": ["5821975e31603ec1bb821d4e","5680a94a07d2786a03239c37"],
    "client_version": "2.87",
    "client_type": "1"
}
```



| 参数名            | 类型           | 描述                          | 必须    | 举例                                       |
| -------------- | ------------ | --------------------------- | ----- | ---------------------------------------- |
| cid            | int          | 设备 ID                       | 是     | 100303                                   |
| mode           | int          | 1:需要存储，２:不存储，直接转发给第三方服务器    | 否，默认１ | 1                                        |
| event_type     | int          | 第三方自定义的事件类型，如：移动侦测，门磁，红外探测等 | 是     | 42                                       |
| expire_time    | int          | 事件的有效时间，单位是秒，0 代表永不过期           | 否，默认0 | 3600                                     |
| subject        | string       | 事件主题，事件的简单描述                | 是     | "门禁事件通知"                                 |
| body           | json object  | 通过 Key-> Value 的方式描述具体的事件内容，这个内容由第三方自主定义      | 是     | {"user":"张三", "event":"上班打卡"}         |
| attachments    | string array | 事件附件在羚羊云对象存储的ObjectId字符串列表  | 否     | ["5821975e31603ec1bb821d4e", "5680a94a07d2786a03239c37"] |
| client_version | string       | 客户端版本                       | 是     | ”2.87“                                   |
| client_type    | string       | 客户端类型                       | 是     | "1"                                      |

- 返回数据：

```json
{
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

- 返回字段：

| 字段名        | 类型     | 描述       |
| ---------- | ------ | -------- |
| request_id | string | 此次请求唯一标识 |


## 2 事件查询

- 接口状态：`开发中`
- 接口功能：查询事件信息
- 接口类型：管理接口
- 使用对象：应用服务器
- 请求地址：`/v2/events?cid=100303&event_type=1&begin=1479116818&end=1479116829&page=1&size=10`
- 请求方式：`GET`
- 权限验证：**需要在请求首部携带 X-APP-ID 和 X-APP-Key**
- 请求参数：

| 参数名        | 类型   | 描述        | 必须      | 举例         |
| ---------- | ---- | --------- | ------- | ---------- |
| cid        | int  | 要查询的设备ＩＤ  | 否       | 100303     |
| event_type | int  | 要查询的事件类型  | 否       | 23         |
| begin      | int  | 要查询的开始时间戳 | 否       | 1479116818 |
| end        | int  | 要查询的结束时间戳 | 否       | 1479116829 |
| page       | int  | 页数        | 否，默认为1  | 1          |
| size       | int  | 每页数据大小    | 否，默认为10 | 10         |

- `curl` 请求示例：

```
curl -X GET -H "Cache-Control: no-cache" "http://127.0.0.1/v2/events?cid=100303&event_type=1&begin=1479116818&end=1479116829&page=1&size=10"
```

- 请求报文：

```
GET /v2/events?cid=100303&amp;event_type=1&amp;begin=1479116818&amp;end=1479116829&amp;page=1&amp;size=10 HTTP/1.1
Host: 127.0.0.1
Cache-Control: no-cache

```

- 返回数据：

```json
{
    "events": [
    {
      "id": "58297d437fd4fc2ca396422e"
      "mode": 1,
	  "event_type": 12,
      "timestamp": 1479116818,
	  "expire": 1479116829,
      "subject": "门禁事件通知",
      "body": {
        "user": "张三",
        "event": "启动门禁",
      },
      "attachments": [
         "http://api.topvdn.com/event/123123",
         "http://api.topvdn.com/event/123123"
      ]
	},
    ...
    ],
    "total": 43,
    "current": 1,
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```


- 返回字段：

| 字段名        | 类型         | 描述       |
| ---------- | ---------- | -------- |
| events     | json array | 事件列表     |
| total      | int        | 总数       |
| current    | int        | 当前页      |
| request_id | string     | 此次请求唯一标识 |

- events数组字段

| 字段名         | 类型           | 描述                          |
| ----------- | ------------ | --------------------------- |
| id          | string       | 事件ID                        |
| cid         | int          | 路径参数，设备ID                   |
| mode        | int          | 1:需要存储，２:不存储，直接转发给第三方服务器    |
| event_type  | int          | 第三方自定义的事件类型，如：移动侦测，门磁，红外探测等 |
| timestamp   | int          | 事件创建的 unix 时间戳，单位为秒           |
| expire      | int          | 事件过期时间戳，0 代表永不过期             |
| subject     | string       | 事件主题，事件的简单描述                |
| body        | json object  | 通过 Key -> Value 的方式描述具体的事件内容，这个内容由第三方自主定义      |
| attachments | string array | 事件附件在羚羊云对象存储的 url 列表          |
