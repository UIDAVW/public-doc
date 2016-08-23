# 羚羊云Web API-推送自定义消息
接口包括：
支持应用服务器推送消息至多个应用客户端；
支持一个设备和多个设备之间的自定义消息推送；

### 1 应用客户端推送消息

* 接口状态：`使用中`
* 接口功能：设备(应用客户端)推送自定义消息，支持推送消息给一个或多个设备，或回调消息给应用服务器。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/message/client/push`
* 请求方式：`POST`
* 权限验证：**需要在请求携带本方设备的token**
* 请求参数：

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
| access_tokens | json array | 对端多个设备的token列表                        | 是    | ［］空则表示不推送给任何设备 |


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

## 2 应用服务器推送消息

* 接口状态：`使用中`
* 接口功能：应用服务器推送自定义消息给多个设备。
* 接口类型：管理接口
* 使用对象：应用服务器
* 请求地址：`/v2/message/server/push`
* 请求方式：`POST`
* 权限验证：**需要在请求首部携带 X-APP-ID 和 X-APP-Key**
* 请求参数：

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
