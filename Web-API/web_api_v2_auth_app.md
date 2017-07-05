# 羚羊云Web API-设备授权接口
接口包括：
设备授权/取消授权给某个 APP；
获取设备 token；

##1 设备授权给 APP

* 接口状态：`使用中`
* 接口功能：将设备授权给指定的 APP, 只有特定的 APP 才有这个权限, 并且被授权的 APP 也有限制
* 接口类型：管理接口
* 使用对象：应用服务器
* 请求地址：`/v2/devices/auth`
* 请求方式：`POST`
* 权限验证：**需要在请求携带 X-APP-ID 和 X-APP-Key**
* 请求参数：

* POST 请求参数

```json
{
    "cids": [
      {
        "cid": 1003555,
        "token": "1003555_0_1492492623_c98ee18c889f200634b0db53d407aba2"
      },
      ...
    ],
  	"app_ids": ["Test"]
}
```

| 参数名     | 类型         | 描述            | 必须   | 举例      |
| ------- | ---------- | ------------- | ---- | ------- |
| cids    | json array | 设备 ID 列表      | 是    | -       |
| app_ids | json array | 被授权的 APPID 列表 | 是    | -       |
| cid     | int        | 设备 ID         | 是    | 1003555 |
| token   | string     | 设备 token      | 是    | -       |


* `curl` 请求示例：

```
curl -X POST \
  http://122.226.182.221/v2/devices/auth \
  -H 'cache-control: no-cache' \
  -H 'content-type: application/json' \
  -H 'x-app-id: upwe' \
  -H 'x-app-key: mock-app-key-use-your-own-pls' \
  -H 'x-client-token: 1003555_0_1492492623_c98ee18c889f200634b0db53d407aba2' \
  -d '{
    "cids": [
      {
        "cid": 1003555,
        "token": "1003555_0_1492492623_c98ee18c889f200634b0db53d407aba2"
      }
    ],
  	"app_ids": ["Test", "upwe"]
}'
```

* 请求报文：

```json
curl -X POST \
  http://122.226.182.221/v2/devices/auth \
  -H 'cache-control: no-cache' \
  -H 'content-type: application/json' \
  -H 'x-app-id: upwe' \
  -H 'x-app-key: mock-app-key-use-your-own-pls' \
  -H 'x-client-token: 1003555_0_1492492623_c98ee18c889f200634b0db53d407aba2' \
  -d '{
    "cids": [
      {
        "cid": 1003555,
        "token": "1003555_0_1492492623_c98ee18c889f200634b0db53d407aba2"
      }
    ],
  	"app_ids": ["Test", "upwe"]
}'
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
| 403  | 无权进行此操作            |
| 500  | 系统内部错误             |

##2 取消给 APP 的授权

* 接口状态：`使用中`
* 接口功能：设备取消设备对 APP 的授权
* 接口类型：管理接口
* 使用对象：应用服务器
* 请求地址：`/v2/devices/auth/cancellation` 
* 请求方式：`POST`
* 权限验证：**需要在请求携带 X-APP-ID 和 X-APP-Key**
* 请求参数：
* POST 请求参数

```json
{
    "cids": [1003555, 10000415],
  	"app_ids": ["Test"]
}
```



| 参数名     | 类型         | 描述       | 必须   | 举例      |
| ------- | ---------- | -------- | ---- | ------- |
| cids    | int        | 设备 ID    | 是    | 1003555 |
| app_ids | json array | APPID 列表 | 否    | -       |


* `curl` 请求示例：

```
curl -X POST \
  http://api.topvdn.com/v2/devices/auth/cancellation \
  -H 'cache-control: no-cache' \
  -H 'content-type: application/json' \
  -H 'x-app-id: Test' \
  -H 'x-app-key: mock-app-key-use-your-own-pls' \
  -d '{
    "cids": [1003555, 10000415],
  	"app_ids": ["Test"]
}'
```

* 请求报文：

```json
POST /v2/devices/auth/cancellation HTTP/1.1
Host: api.topvdn.com
X-APP-ID: Test
X-APP-Key: mock-app-key-use-your-own-pls
Content-Type: application/json
Cache-Control: no-cache

{
    "cids": [1003555, 10000415],
  	"app_ids": ["Test"]
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
| 403  | 无权进行此操作            |
| 500  | 系统内部错误             |

## 3 获取设备 token

- 接口状态：`使用中`
- 接口功能：获取指定设备的 token, 本接口返回的 token 有效期比较短, 目前为 5 分钟
- 接口类型：管理接口
- 使用对象：应用服务器
- 请求地址：`/v2/devices/tokens`
- 请求方式：`POST`
- 权限验证：**需要在请求携带 X-APP-ID 和 X-APP-Key**
- 请求参数：
- POST 请求参数

```json
{
  "cids": [1003555, 10000415]
}
```

| 参数名  | 类型         | 描述       | 必须   | 举例      |
| ---- | ---------- | -------- | ---- | ------- |
| cids | json array | 设备 ID 列表 | 是    | 1003555 |

- `curl` 请求示例：

```
curl -X POST \
  http://api.topvdn.com/v2/devices/tokens \
  -H 'cache-control: no-cache' \
  -H 'content-type: application/json' \
  -H 'x-app-id: Test' \
  -H 'x-app-key: mock-app-key-use-your-own-pls' \
  -d '{
  "cids": [1003555, 10000415]
}'
```

- 请求报文：

```json
POST /v2/devices/tokens HTTP/1.1
Host: api.topvdn.com
Content-Type: application/json
X-APP-ID: Test
X-APP-Key: mock-app-key-use-your-own-pls
Cache-Control: no-cache

{
  "cids": [1003555, 10000415]
}
```

- 返回数据：

```json
{
  	"tokens": [
      {
        "cid": 1003555,
        "token": "1003555_0_1492313854_2adb4e7c5d44ac9f130df89deb022b71"
      },
      {
        "cid": 10000415,
        "token": "10000415_0_1492313854_2adb4e7c5d44ac9f130df89deb022b71"
      }
     ],
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

- 返回字段：

| 字段名        | 类型         | 描述          |
| ---------- | ---------- | ----------- |
| tokens     | json array | 设备 token 列表 |
| request_id | string     | 此次请求的唯一编号   |

- `tokens` 字段：

| 字段名   | 类型     | 描述       |
| ----- | ------ | -------- |
| cid   | int    | 设备 ID    |
| token | string | 设备 token |

- 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 403  | 无权获取该设备 token      |
| 500  | 系统内部错误             |