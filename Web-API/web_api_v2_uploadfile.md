# 羚羊云Web API-文件上传管理

该部分接口支持将文件上传至羚羊云，这些文件可以包含图片、短视频文件等。

## 1 申请云端的上传路径

* 接口状态：`使用中`
* 接口功能：用户申请上传短视频或图片，将会返回一个上传 url ，上传 url 包含了相关上传的信息和校验 token ，存在有效时间，暂定为 30 分钟。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/cloud/<client_id>/uploads`
* 请求方式：`POST`
* 权限验证：**需要在请求携带本方设备的token**
* 请求参数：

| 参数名       | 类型   | 描述          | 必须   | 举例   |
| --------- | ---- | ----------- | ---- | ---- |
| client_id | int  | 路径参数，客户端 ID | 是    | 5003062   |


* `curl` 请求示例：

```
curl -X POST -H "Content-Type: application/json" -H "X-Client-Token: 5003062_3356753920_1460640064_0037c26c9018f9984c866db08bed2d95" -H "Cache-Control: no-cache" -d '' "http://api.topvdn.com/v2/cloud/5003062/uploads"
```

* 请求报文：

```json
POST /v2/cloud/5003062/uploads HTTP/1.1
Host: api.topvdn.com
Content-Type: application/json
X-Client-Token: 5003062_3356753920_1460640064_0037c26c9018f9984c866db08bed2d95
Cache-Control: no-cache

```


* 返回数据：

```json
{
	"upload_id": 42,
	"upload_url": "http://www.domain.com/v2/cloud/<client_id>/uploads/<upload_id>?client_token=xxx&upload_token=xxxxxxx",
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名        | 类型     | 描述                       |
| ---------- | ------ | ------------------------ |
| upload_id  | int    | 本次上传的标识，可以通过这个来下载或分享本次上传 |
| upload_url | string | 上传地址，通过表单的形式 POST 上传文件   |
| request_id | string | 此次请求的唯一编号                |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 500  | 系统内部错误             |

## 2 向云端路径上传文件

* 接口状态：`使用中`
* 接口功能：即是上一个接口返回的 upload_url ，可以通过本接口上传文件，本接口不一定在 `api.topvdn.com` 上。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/cloud/<client_id>/uploads/<upload_id>?upload_token=xxxxxxx`
* 请求方式：`POST`
* 权限验证：**需要在请求携带本方设备的token**
* 请求参数：

**注意：上传以 multipart/form-data 的方式提交**

| 参数名          | 类型     | 描述                              | 必须   | 举例      |
| ------------ | ------ | ------------------------------- | ---- | ------- |
| client_id    | int    | 路径参数，客户端 ID                     | 是    | 5003062 |
| upload_id    | int    | 路径参数，上传 ID                      | 是    | 42      |
| upload_token | string | `query param` 上传的 Token         | 是    | "xxxx"  |
| upload_file  | 文件     | `form data` 要上传的文件，注意文件的名称需要有后缀 | 是    | 二进制文件   |



* `curl` 请求示例：

```
curl -X POST -H "Cache-Control: no-cache" -H "Content-Type: multipart/form-data" -F "upload_file=@whatabeauty.png" "http://122.226.181.107/v2/cloud/5003062/uploads/80?upload_token=NTAwMzA2Ml84MF8xNDYzNDY1NDIyXzNfZW1wdHlfNTM3N2JjZTJkOGEwZmViMjg1NzdiZGRjNmUyZGI2OTU4OGMxODUzNg%3D%3D&client_token=5003062_3356753920_1460640064_cfebd8c9c262d3be3e4cc06cd6f007cc"
```

* 请求报文：

```json
POST /v2/cloud/5003062/uploads/80?upload_token=NTAwMzA2Ml84MF8xNDYzNDY1NDIyXzNfZW1wdHlfNTM3N2JjZTJkOGEwZmViMjg1NzdiZGRjNmUyZGI2OTU4OGMxODUzNg%3D%3D&client_token=5003062_3356753920_1460640064_0037c26c9018f9984c866db08bed2d95 HTTP/1.1
Host: 122.226.181.107
Cache-Control: no-cache
Content-Type: multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW

----WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="upload_file"; filename="whatabeauty.png"
Content-Type: 


----WebKitFormBoundary7MA4YWxkTrZu0gW
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

| 状态码  | 描述                                 |
| ---- | ---------------------------------- |
| 200  | 请求成功，返回正确的数据                       |
| 400  | 参数错误，可能缺少参数或者类型不正确                 |
| 401  | token 验证不通过                        |
| 403  | 上传 token 不正确或者过期                   |
| 406  | 不允许的文件类型，图片支持 jpeg / png ，视频支持 mp4 |
| 413  | 文件大小超出限制，图片 2M，视频 16M              |
| 500  | 系统内部错误                             |

## 3 获取云端的文件列表

* 接口状态：`使用中`
* 接口功能：查看 client 的上传列表，这里只返回上传成功的文件列表。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/cloud/<client_id>/uploads?page=1&size=10`
* 请求方式：`GET`
* 权限验证：**需要在请求携带本方设备的token**
* 请求参数：

| 参数名       | 类型   | 描述                        | 必须   | 举例      |
| --------- | ---- | ------------------------- | ---- | ------- |
| client_id | int  | 路径参数，客户端 ID               | 是    | 5003062 |
| page      | int  | `query param` 页数，默认为 1    | 否    | 1       |
| size      | int  | `query param` 每页数量，默认为 10 | 否    | 10      |


* `curl` 请求示例：

```
curl -X GET -H "X-Client-Token: 5003062_3356753920_1460640064_cfebd8c9c262d3be3e4cc06cd6f007cc" -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/cloud/5003062/uploads?page=1&size=10"
```

* 请求报文：

```json
GET /v2/cloud/5003062/uploads?page=1&size=10 HTTP/1.1
Host: api.topvdn.com
X-Client-Token: 5003062_3356753920_1460640064_cfebd8c9c262d3be3e4cc06cd6f007cc
Cache-Control: no-cache

```


* 返回数据：

```json
{
	"total_space": 1074790400,
	"used_space": 254399,
	"uploads": [
		{
			"id": 42,
			"size": 4096,
			"filename": "myfavoriate.jpg",
			"mimetype": "image/jpeg",
			"updated": "2012-01-01T12:00:00Z",
			"url": "http://api.topvdn.com/v2/cloud/<client_id>/uploads/<upload_id>/<file_name>?client_token=xxxx"
		},
		...
	],
	"page": 1,
	"size": 10,
	"total": 25,
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名         | 类型         | 描述                     |
| ----------- | ---------- | ---------------------- |
| total_space | int        | 该 client 上传空间大小，单位字节   |
| used_space  | int        | 该 client 已经使用的空间，单位字节  |
| uploads     | json array | 上传列表                   |
| page        | int        | 列表页数                   |
| size        | int        | 每页内容数量，最大为 100 ，默认为 10 |
| total       | int        | 该 client 上传的文件数量       |
| request_id  | string     | 此次请求的唯一编号              |


* uploads 字段：

| 字段名      | 类型     | 描述                           |
| -------- | ------ | ---------------------------- |
| id       | int    | 上传 ID                        |
| size     | int    | 上传文件大小                       |
| filename | string | 上传的文件名，带后缀                   |
| mimetype | string | 上传的文件资源类型                    |
| updated  | string | 上传的更新时间，一般即是上传完成时间           |
| url      | string | 上传的文件下载地址，需要 client token 下载 |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 500  | 系统内部错误             |

## 4 获取云端文件链接

* 接口状态：`使用中`
* 接口功能：获取 client 某个已上传文件的链接地址，可以将得到的上传资源链接分享到公开的地方提供给别人查看。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/cloud/<client_id>/uploads/<upload_id>/share?expire=3600`
* 请求方式：`GET`
* 权限验证：**需要在请求携带本方设备的token**
* 请求参数：

| 参数名       | 类型   | 描述                                       | 必须   | 举例        |
| --------- | ---- | ---------------------------------------- | ---- | --------- |
| client_id | int  | 路径参数，客户端 ID                              | 是    | 5003062   |
| upload_id | int  | 路径参数，上传 ID                               | 是    | 42        |
| expire    | int  | `query param` 分享过期时间，单位为秒，不提供或者为 0 则分享链接不过期 | 否    | 3600 一个小时 |


* `curl` 请求示例：

```
curl -X GET -H "Content-Type: application/json" -H "X-Client-Token: 5003062_3356753920_1460640064_99960324d02ba8be765db83066b833db" -H "Cache-Control: no-cache" "http://api.topvdn.com/v2/cloud/5003062/uploads/1/share?expire=30"
```

* 请求报文：

```json
GET /v2/cloud/5003062/uploads/1/share?expire=30 HTTP/1.1
Host: api.topvdn.com
Content-Type: application/json
X-Client-Token: 5003062_3356753920_1460640064_99960324d02ba8be765db83066b833db
Cache-Control: no-cache

```


* 返回数据：

```json
{
	"link": "http://www.domain.com/v2/cloud/<cid>/uploads/<upload_id>/share/<file_name>?share_token=xxxx",
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
| 403  | 无权分享该上传            |
| 404  | 指定的上传不存在           |
| 500  | 系统内部错误             |

## 5 下载已上传的文件

* 接口状态：`使用中`
* 接口功能：下载上传的文件，可以通过 `获取云端的文件列表` 接口得到，本接口不一定在 `api.topvdn.com` 上。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/cloud/<client_id>/uploads/<upload_id>/<file_name>`
* 请求方式：`GET`
* 权限验证：**需要在请求携带本方设备的token**
* 请求参数：

| 参数名       | 类型     | 描述           | 必须   | 举例              |
| --------- | ------ | ------------ | ---- | --------------- |
| client_id | int    | 路径参数，客户端 ID  | 是    | 5003062         |
| upload_id | int    | 路径参数，上传 ID   | 是    | 42              |
| file_name | string | 路径参数，带后缀的文件名 | 是    | "favoriate.mp4" |


* `curl` 请求示例：

```
curl -X GET -H "Cache-Control: no-cache" "http://122.226.181.107/v2/cloud/5003062/uploads/80/whatabeauty.png?client_token=5003062_3356753920_1460640064_cfebd8c9c262d3be3e4cc06cd6f007cc"
```

* 请求报文：

```json
GET /v2/cloud/5003062/uploads/80/whatabeauty.png?client_token=5003062_3356753920_1460640064_cfebd8c9c262d3be3e4cc06cd6f007cc HTTP/1.1
Host: 122.226.181.107
Cache-Control: no-cache

```


* 返回数据：上传的文件内容

* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | token 验证不通过        |
| 403  | 无权访问该上传            |
| 404  | 该上传文件不存在，可能已经被删除   |
| 500  | 系统内部错误             |

## 6 删除已上传的文件

* 接口状态：`使用中`
* 接口功能：删除已上传的某个文件。
* 接口类型：设备接口
* 使用对象：应用客户端
* 请求地址：`/v2/cloud/<client_id>/uploads/<upload_id>`
* 请求方式：`DELETE`
* 权限验证：**需要在请求携带本方设备的token**
* 请求参数：

| 参数名       | 类型   | 描述          | 必须   | 举例      |
| --------- | ---- | ----------- | ---- | ------- |
| client_id | int  | 路径参数，客户端 ID | 是    | 5003062 |
| upload_id | int  | 路径参数，上传 ID  | 是    | 42      |

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
| 403  | 无权访问该上传            |
| 404  | 该上传文件不存在，可能已经被删除   |
| 500  | 系统内部错误             |
