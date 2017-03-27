# 羚羊云Web API-设备截图

本部分接口包含设备封面截图及更新设备封面截图等接口

## 1 设备封面截图

- 接口状态: `调整中`
- 接口功能: 获取设备的封面截图, 返回该设备所有截图来源中最新的一张
- 接口类型: 设备接口
- 使用对象: 应用客户端
- 请求地址: `/v2/snapshots/<cid>/cover`
- 请求方式: `GET`
- 权限验证: **需要在请求携带本方设备的token**
- 请求参数:

| 参数名  | 类型   | 描述          | 必须   | 举例       |
| ---- | ---- | ----------- | ---- | -------- |
| cid  | int  | 路径参数，客户端 ID | 是    | 10000415 |

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
- 截图来源: 
  - 如果设备正在推流, 推流服务器上会保存一张实时更新的截图
  - 如果设备推录像流, 在录像存储服务器集群每 5 分钟会保存一张
  - 通过 `2 上传设备截图` 接口上传的截图


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
- 接口功能: 上传设备截图到羚羊中央服务器作为设备封面截图, 并且每次上传将会替换上一次上传的截图, 频率限制为每 5 分钟一张
- 接口类型: 设备接口
- 使用对象: 应用客户端
- 请求地址: `/v2/devices/<cid>/snapshots`
- 请求方式: `POST`
- 权限验证: **需要在请求携带本方设备的token**
- 请求参数:

| 参数名  | 类型    | 描述                            | 必须   | 举例       |
| ---- | ----- | ----------------------------- | ---- | -------- |
| cid  | int   | 路径参数，客户端 ID                   | 是    | 10000415 |
| file | 二进制文件 | `form data `, 上传的截图大小不能超过过 2M | 是    | -        |

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

| 状态码  | 描述                   |
| ---- | -------------------- |
| 200  | 请求成功, 返回正确的数据        |
| 400  | 参数错误, 可能缺少参数或者类型不正确  |
| 401  | token 验证不通过          |
| 403  | 无权上传该设备截图            |
| 413  | 截图大小超过限制, 最大 2M      |
| 429  | 上传太频繁, 频率限制为每 5 分钟一张 |
| 500  | 系统内部错误               |