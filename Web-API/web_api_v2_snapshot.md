# 羚羊云Web API-设备截图

本部分接口包含设备封面截图及更新设备封面截图等接口

## 1 设备封面截图

- 接口状态: `使用中`
- 接口功能: 获取 client 设备的封面截图
- 接口类型: 设备接口
- 使用对象: 应用客户端
- 请求地址: `/v2/snapshots/<client_id>/cover`
- 请求方式: `GET`
- 权限验证: **需要在请求携带本方设备的token**
- 请求参数:

| 参数名       | 类型   | 描述          | 必须   | 举例       |
| --------- | ---- | ----------- | ---- | -------- |
| client_id | int  | 路径参数，客户端 ID | 是    | 10000415 |

- `curl` 请求示例:

```
curl -X GET -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/snapshots/10000415/cover?client_token=10000415_0_1490680747_a830147b503b587dd524f4b11b8f96c2"
```

- 请求报文:

```json
GET /v2/snapshots/10000415/cover?client_token=10000415_0_1490680747_a830147b503b587dd524f4b11b8f96c2 HTTP/1.1
Host: api.topvdn.com
Cache-Control: no-cache

```

- 返回数据: 二进制图片文件
- 截图返回逻辑:
  - 如果设备正在推流, 则转跳到推流服务获取当前推流保存的最新一张图片
  - 如果设备没有推流, 则查询并转跳到设备最近保存录像截图的区域获取最新的一张录像截图
  - 如果设备没有录像截图, 则在羚羊中央服务器查询本地保存的封面截图并返回, 此截图可以通过 `2 上传设备截图` 接口上传


- 状态码:

| 状态码  | 描述                  |
| ---- | ------------------- |
| 200  | 请求成功, 返回正确的图片文件     |
| 400  | 参数错误, 可能缺少参数或者类型不正确 |
| 401  | token 验证不通过         |
| 403  | 无权请求该设备封面截图         |
| 404  | 该设备无封面截图            |
| 500  | 系统内部错误              |

## 2 上传设备截图

- 接口状态: `开发中`
- 接口功能: 上传设备截图到羚羊中央服务器作为设备封面截图, 并且每次上传将会替换上一次上传的截图, 在设备离线并且无录像截图的时候返回
- 接口类型: 设备接口
- 使用对象: 应用客户端
- 请求地址: `/v2/devices/<client_id>/snapshots`
- 请求方式: `POST`
- 权限验证: **需要在请求携带本方设备的token**
- 请求参数:

| 参数名       | 类型    | 描述          | 必须   | 举例       |
| --------- | ----- | ----------- | ---- | -------- |
| client_id | int   | 路径参数，客户端 ID | 是    | 10000415 |
| file      | 二进制文件 | `form data` | 是    | -        |

- `curl` 请求示例:

```
curl -X POST -H "Cache-Control: no-cache" -H "Content-Type: multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW" -F "file=@10000415.jpg" "http://api.topvdn.com/v2/devices/10000415/snapshots?client_token=10000415_0_1490680747_a830147b503b587dd524f4b11b8f96c2"
```

- 请求报文:

```json
POST /v2/devices/10000415/snapshots?client_token=10000415_0_1490680747_a830147b503b587dd524f4b11b8f96c2 HTTP/1.1
Host: api.topvdn.com
Cache-Control: no-cache
Content-Type: multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW

------WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="file"; filename=""
Content-Type: 


------WebKitFormBoundary7MA4YWxkTrZu0gW--
```

- 返回数据:

```json
{
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```
- 状态码:

| 状态码  | 描述                  |
| ---- | ------------------- |
| 200  | 请求成功, 返回正确的数据       |
| 400  | 参数错误, 可能缺少参数或者类型不正确 |
| 401  | token 验证不通过         |
| 403  | 无权上传该设备截图           |
| 500  | 系统内部错误              |