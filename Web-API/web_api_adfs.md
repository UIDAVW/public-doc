```
     _    ____  _____ ____
    / \  |  _ \|  ___/ ___|
   / _ \ | | | | |_  \___ \
  / ___ \| |_| |  _|  ___) |
 /_/   \_\____/|_|   |____/   Antelope Distributed File System
```

# 羚羊云Web API-对象存储

## 1. 上传对象到对象存储系统
* 接口状态：`使用中`
* 接口功能：将对象上传到对象存储系统。
* 接口类型：管理接口
* 使用对象：永久对象、循环对象
* 请求地址：`/upload2?size=xx&access_token=xx_xx_xx_xx&expiretype=xx&key=/xx/xx`
* 请求方式：`POST`
* 权限验证：**需要正确的请求access_token**
* 请求参数： 



|              | 类型           | 描述                                  | 位置         | 必须   | 举例                                       |
| ------------ | ------------ | :---------------------------------- | ---------- | ---- | ---------------------------------------- |
| size         | unsigned int | 上传文件大小                              | URL String | 是    | 123456                                   |
| access_token | string       | 用于权限验证的access_token                 | URL String | 是    | xx_xx_xx_xx                              |
| file         | POST form    | 存放对象数据的表单                           | POST       | 是    | --form "file=@/home/test/test.txt"（curl方式） |
| expiretype   | unsigned int | 周期类型，0表示永久，1表示7天，2表示30天，3表示90天，默认为0 | URL String | 否    | 1                                        |
| key          | string       | 用户自定义的对象唯一标识符                       | POST       | 否    | /1/upload.txt                            |
| metadata     | json         | 用户自定义的对象元数据                         | POST       | 否    |                                          |

+ 细节分析

  1. size大于1G或者大小与实际文件大小不一致，返回400 Bad Request

  2. 用户自定义key，但是key的格式必须为绝对路径或者是带绝对路径的文件名

     例如：/1/upload.txt 、/1/、/1/${filename} 

     `/1` 和`/1/upload.txt`：OSS将按用户自定义保存key

     `/1/`和`/1/${filename}` ： OSS将自动填充文件名称，例如文件名称为2.txt，key则将被填充为/1/2.txt

  3. key可以放在URL参数、Request Header或者POST 表单中，OSS优先从URL参数获取key，没有就从Request Header获取，再没有就从POST 表单中获取。如果用户没有自定义key，则OSS自动生成key，key的格式为OID_FILENAME，例如：58230e560000000001005e71_upload.txt

     当自定义key放在post表单中时，该表单名称为"key"，且该表单必须在“file”表单之前

  4. key的长度大于1024或者key不符合命名格式，返回400 Bad Request

  5. 用户可以根据上传后返回的最终的key，进行对象的下载、删除、查询元数据信息操作。

  6. metadata可以放在Request Header或者POST 表单中，OSS优先从Request Header获取，没有就从POST 表单中获取

     当metadata放在post表单中时，该表单名称为"metadata"，且该表单必须在“file”表单之前

  7. metadata的长度大于1024，返回400 Bad Request

  8. 用户上传的metadata内容OSS并不关心，用户可以通过下载对象或者单独获取对象元数据来获取metadata


* `postman` 请求示例：

![我是图片](C:\Users\俞淦\Desktop\upload2.png)

* `postman` 请求报文：

```text
POST /upload2?size=144896&amp;access_token=1003775_3145728_1577429797_abf24269c1b163a04a4090643a82f411&amp;expiretype=0&amp;key=/1/upload.txt HTTP/1.1
Host: 122.226.181.252:8030
Cache-Control: no-cache
Postman-Token: 2164cdb5-b435-f852-ed08-24c74149d149
Content-Type: multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW

------WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="metadata"

{
                "K1": "V1",
                "K2": 2,
                "K3": {
                    "K3_1": "K3_1",
                    "K3_2": 32
                 }
}
------WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="file"; filename=""
Content-Type: 


------WebKitFormBoundary7MA4YWxkTrZu0gW--
```

* `postman` 返回数据：

```json
{
  "obj_id": "59251953000f50ff01001a7a",
  "key": "/1/upload.txt",
  "name": "guimain.exe",
  "c_id": 1003775,
  "app_id": "Test",
  "file_id": "63dd6168efccf34442141bc6a30ca4b5bfb5eeb8",
  "timestamp": 1495603539,
  "file_size": 144896,
  "metadata": {
    "K1": "V1",
    "K2": 2,
    "K3": {
      "K3_1": "K3_1",
      "K3_2": 32
    }
  },
  "expire_type": 0,
  "area_id": 1
}
```

| 字段名         | 类型           | 描述                                       |
| ----------- | ------------ | ---------------------------------------- |
| obj_id      | string       | 每次上传的对象的唯一标识，OSS生成并返回，用户可以使用该字段进行下载、删除、查询等操作 |
| key         | string       | 对象的key，可以使用该字段进行对象下载、删除、查询等操作            |
| name        | string       | 对象名称                                     |
| c_id        | unsigned int | 用户ID                                     |
| app_id      | string       | 厂商ID                                     |
| file_id     | string       | 文件的唯一表示，相同的对象FileID相同                    |
| timestamp   | unsigned int | 创建时间                                     |
| file_size   | unsigned int | 对象大小，单位字节                                |
| metadata    | json         | 用户自定义的对象元数据                              |
| expire_type | unsigned int | 周期类型，0表示永久，1表示7天，2表示30天，3表示90天，默认为0      |
| area_id     | byte         | 区域ID                                     |

* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | app_key 验证不通过      |
| 500  | 系统内部错误             |



## 2. 事件相关接口

### 2.1 上传事件到对象存储系统

- 接口状态：`使用中`
- 接口功能：将事件（含至少1个子对象）上传到对象存储系统。
- 接口类型：管理接口
- 使用对象：永久对象、循环对象
- 请求地址：`upload3?access_token=xx_xx_xx_xx`
- 请求方式：`POST`
- 权限验证：**需要正确的请求access_token**
- 请求参数： 

| 参数名          | 类型        | 位置         | 描述                  | 必须   | 举例                  |
| ------------ | --------- | ---------- | ------------------- | ---- | ------------------- |
| access_token | string    | URL String | 用于权限验证的access_token | 是    | xx_xx_xx_xx         |
| message      | json      | POST       | 事件的描述信息，有固定的格式要求    | 是    | 见下面`message表单的固定格式` |
| 其他子对象表单      | POST form | POST       |                     |      |                     |



* message表单的固定格式：

```json
  {
      "channel_id":  0,
      "subject": "",
      "body": {},
      "attachments": [
       {
              "form_field": "first_object",
              "key": "/1/upload.txt",
              "area_id": 0,
              "metadata": {},
              "url": "",
              "file_name": "",
              "expiretype": 1
       },
       {
              "form_field": "second_object",
              "key": "",
              "area_id": 0,
              "metadata": {},
              "url": "",
              "file_name": "",
               "expiretype": 0
       }...
      ]
  }
```

* message表单字段：

| 参数名         | 类型             | 描述                                       | 必须   | 举例       |
| ----------- | -------------- | ---------------------------------------- | ---- | -------- |
| channel_id  | uint32         | 事件通道，每个appid有16个事件通道，对应16个卡夫卡队列。设置该值，确认事件类型，值范围为0-15。 | 是    | 0        |
| subject     | string         | OSS不关心里面内容，用户自定义                         | 否    | test     |
| body        | json           | OSS不关心里面内容，用户自定义                         | 否    | {}       |
| attachments | attachment格式数组 | 子对象的描述信息数组，一个attachment对应1个子对象           | 否    | [{}, {}] |

* attachment结构字段：

| 参数名        | 类型     | 描述                                  | 必须   | 举例            |
| ---------- | ------ | ----------------------------------- | ---- | ------------- |
| form_field | string | 子对象所在表单名称                           | 否    | first_object  |
| key        | string | 用户自定义子对象标识                          | 否    | /1/upload.txt |
| area_id    | uint32 | 对象存储的区域ID，由OSS返回                    | 不填   |               |
| metadata   | json   | 子对象的自定义元数据，OSS不关心里面内容               | 否    | {}            |
| url        | string | 子对象的下载路径，由OSS返回                     | 不填   |               |
| file_name  | string | 子对象名称                               | 否    |               |
| expiretype | uint32 | 周期类型，0表示永久，1表示7天，2表示30天，3表示90天，默认为0 | 是    | 1             |

* 细节分析：

  1. message表单必须为第一个表单，且表单大小小于等于4K

  2. 事件上传成功后，OSS将修改message内容，并将message内容缓存起来。用户需要通过中央查询接口获取message

  3. channel_id大于15，返回400 Bad Request

  4. key的规则和`upload2`接口的key规则相同

  5. url由OSS修改，用户可以使用该url进行子对象的下载，如果url里的access_token过期，用户需要自行更新access_token

  6. 每个子对象文件的最大大小为50M，如果大于50M，返回400 Bad Request

  7. 事件上传的具体设计请参考《对象存储支持事件上传 .docx》

     ​

* `postman`请求示例：

![我是图片](C:\Users\俞淦\Desktop\upload3.png)

* `postman`请求报文：

```test
  POST /upload3?access_token=1003775_3145728_1577429797_abf24269c1b163a04a4090643a82f411 HTTP/1.1
  Host: 122.226.181.252:8030
  Cache-Control: no-cache
  Postman-Token: f0ddd74c-c1f5-8076-570e-7b58abd7de95
  Content-Type: multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW

  ------WebKitFormBoundary7MA4YWxkTrZu0gW
  Content-Disposition: form-data; name="message"

  {
      "channel_id":  0,
      "subject": "",
      "body": {},
      "attachments": [
       {
              "form_field": "first_object",
              "key": "/1/upload.txt",
              "area_id": 0,
              "metadata": {},
              "url": "",
              "file_name": "",
              "expiretype": 1
       },
       {
              "form_field": "second_object",
              "key": "",
              "area_id": 0,
              "metadata": {},
              "url": "",
              "file_name": "",
               "expiretype": 0
       }
      ]
  }
  ------WebKitFormBoundary7MA4YWxkTrZu0gW
  Content-Disposition: form-data; name="first_object"; filename=""
  Content-Type: 

  ------WebKitFormBoundary7MA4YWxkTrZu0gW
  Content-Disposition: form-data; name="second_object"; filename=""
  Content-Type: 

  ------WebKitFormBoundary7MA4YWxkTrZu0gW--
```

* 返回数据：

  > 无


* 状态码：

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | app_key 验证不通过      |
| 404  | 下载文件不存在            |
| 500  | 系统内部错误             |



### 2.2 从中央下载事件元数据

- 接口状态：`使用中`
- 接口功能：从中央批量获取事件上传后的元数据
- 接口类型：管理接口
- 使用对象：永久对象、循环对象
- 请求地址：`/v2/events?channel_id=xx&size=xx`
- 请求方式：`GET`
- 权限验证：**需要在请求首部携带 X-APP-ID 和 X-APP-Key**
- 请求参数： 

| 参数名        | 类型   | 位置         | 描述                  | 必须                       | 举例   |
| ---------- | ---- | ---------- | :------------------ | ------------------------ | ---- |
| channel_id | int  | Query  str | 事件通道 ID             | 是                        | 12   |
| size       | int  | Query  str | 返回的消息数量, 不大于 100    | 是                        | 10   |
| offset     | int  | Query  str | 消息在 kafka 中的 offset | 否, 默认为 partition下最早可请求到的 | 42   |

* 请求报文：

  ```test
  GET /v2/events?channel_id=1&size=10&offset=42 HTTP/1.1
  Host: 127.0.0.1:8080
  X-APP-ID: Test
  X-APP-Key: mock-app-key-use-your-own-pls
  Cache-Control: no-cache
  ```

* 返回数据：

  ```json
  {
    "events": [
  	{
  	"channelid": 1,
  	"subject": "",
  	"body": {},
  	"attachments": [
  		{
  		  "form_field": "first_object",
  		  "key": "/1/upload.txt",
  		  "area_id": 1,
  		  "metadata": {},
  		  "url": "http://192.168.2.233:8030/files?KeyID=/1/upload.txt&access_token=1003775_3145728_1577429797_abf24269c1b163a04a4090643a82f411",
  		  "file_name": "guistub.exe",
  		  "expiretype": 1
  		},
  		{
  		  "form_field": "second_object",
  		  "key": "59258107000f50ff0100525e_lastrites.exe",
  		  "area_id": 1,
  		  "metadata": {},
  		  "url": "http://192.168.2.233:8030/files?KeyID=59258107000f50ff0100525e_lastrites.exe&access_token=1003775_3145728_1577429797_abf24269c1b163a04a4090643a82f411",
  		  "file_name": "lastrites.exe",
  		  "expiretype": 0
  		}
  	  ]
  	}
    ],
    "offset": 45,
    "request_id": "56e83d08ea1e4c209af9b857c2a9abf8"
  }
  ```

* 返回字段：

  | 参数名        | 类型           | 描述                                       |
  | :--------- | :----------- | :--------------------------------------- |
  | events     | json  object | 元素内容为OSS修改后的message内容 。用户可以使用message进行元数据管理，message中的URL可以直接进行对象下载。如果message中的URL过期，需要用户自行更新 |
  | offset     | int          | 当前消费的消息 offset, 下次请求可以 +1 带上请求下一组消息      |
  | request_id | 字符串          | 本次请求唯一标识                                 |

* 状态码：

  | 状态码  | 描述                 |
  | :--- | :----------------- |
  | 200  | 请求成功，返回正确的数据       |
  | 400  | 参数错误，可能缺少参数或者类型不正确 |
  | 401  | 权限验证不通过            |
  | 406  | 参数 size 大于限制 100   |
  | 500  | 系统内部错误             |


## 3. 从对象存储系统中下载数据

* 接口状态：`使用中`
* 接口功能：从对象系统中下载数据。
* 接口类型：管理接口
* 使用对象：永久对象、循环对象
* 请求地址：`/files?access_token=xx_xx_xx_xx&key=/xx/xx&obj_id=xx`
* 请求方式：`GET`
* 权限验证：**需要正确的请求access_token**

* 请求参数：


| 参数名          | 类型     | 位置         | 描述                  | 必须                            | 举例                       |
| ------------ | ------ | ---------- | ------------------- | ----------------------------- | ------------------------ |
| obj_id       | string | URL String | 对象唯一标识              | obj_id和key填一个即可，如果都填以obj_id为准 | 59243ae1000f50ff01002827 |
| key          | string | URL String | 文件唯一标识              | obj_id和key填一个即可，如果都填以obj_id为准 | /1/upload.txt            |
| access_token | string | URL String | 用于权限验证的access_token | 是                             | xx_xx_xx_xx              |


* `postman` 请求示例：

```
http://122.226.181.252:8030/files?access_token=1003775_3145728_1577429797_abf24269c1b163a04a4090643a82f411&key=/1/upload.txt&obj_id=59251953000f50ff01001a7a
```

* 请求报文：

```text
GET /files?access_token=100377531457281577429797_abf24269c1b163a04a4090643a82f411key=/1/upload.txtobj_id=59251953000f50ff01001a7a HTTP/1.1

Host: 122.226.181.252:8030

Cache-Control: no-cache

Postman-Token: f5f350d7-2cde-5e62-cdb3-501abe722f19

```

* 返回数据：

```test
请求的对象的内容
```

* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | app_key 验证不通过      |
| 404  | 下载文件不存在            |
| 500  | 系统内部错误             |

## 4. 删除对象数据
* 接口状态：`使用中`
* 接口功能：从对象系统中删除对象数据。
* 接口类型：管理接口
* 使用对象：永久对象
* 请求地址：`fileinfo/delete?obj_id=xx&key=/xx/xx&access_token=xx_xx_xx_xx`
* 请求方式：`GET`
* 权限验证：**需要正确的请求access_token**

* 请求参数： 


| 参数名          | 类型     | 位置         | 描述                  | 必须                            | 举例                       |
| ------------ | ------ | ---------- | ------------------- | ----------------------------- | ------------------------ |
| obj_id       | string | URL String | 对象唯一标识              | obj_id和key填一个即可，如果都填以obj_id为准 | 59243ae1000f50ff01002827 |
| key          | string | URL String | 文件唯一标识              | obj_id和key填一个即可，如果都填以obj_id为准 | /1/upload.txt            |
| access_token | string | URL String | 用于权限验证的access_token | 是                             | xx_xx_xx_xx              |


* `postman` 请求示例：

```
http://122.226.181.252:8030/fileinfo/delete?key=/1/upload.txt1&obj_id=59251953000f50ff01001a7a&access_token=1003775_3145728_1577429797_abf24269c1b163a04a4090643a82f411
```

* 请求报文：

```text
GET /fileinfo/delete?key=/1/upload.txt1obj_id=59251953000f50ff01001a7aaccess_token=100377531457281577429797_abf24269c1b163a04a4090643a82f411 HTTP/1.1

Host: 122.226.181.252:8030

Cache-Control: no-cache

Postman-Token: 10b7eb7d-0ac5-5716-2cb2-642383724704
```

* 返回数据：

```
{
  "c_id": 1003775,
  "deleted": true,
  "key": "/1/upload.txt",
  "obj_id": "59251953000f50ff01001a7a"
}
```

* 返回字段：

| 字段名     | 类型           | 描述         |
| ------- | ------------ | ---------- |
| c_id    | unsigned int | 用户ID       |
| deleted | bool         | 是否删除成功     |
| key     | string       | 删除的对象的key  |
| obj_id  | string       | 删除的对象的唯一标识 |

* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | app_key 验证不通过      |
| 404  | 下载文件不存在            |
| 500  | 系统内部错误             |



## 5. 查询用户上传的某个对象的信息
* 接口状态：`使用中`
* 接口功能：查询用户上传的某个对象的信息。
* 接口类型：管理接口
* 使用对象：永久对象、循环对象
* 请求地址：`/fileinfo/infos?obj_id=xx&key=/xx/xx&access_token=xx_xx_xx_xx`
* 请求方式：`GET`
* 权限验证：**需要正确的请求access_token**

* 请求参数：


| 参数名          | 类型     | 位置         | 描述                            | 必须   | 举例                       |
| ------------ | ------ | ---------- | ----------------------------- | ---- | ------------------------ |
| obj_id       | string | URL String | obj_id和key填一个即可，如果都填以obj_id为准 | 是    | 59243ae1000f50ff01002827 |
| key          | string | URL String | obj_id和key填一个即可，如果都填以obj_id为准 | 是    | /1/upload.txt            |
| access_token | string | URL String | 用于权限验证的access_token           | 是    | xx_xx_xx_xx              |


* `curl` 请求示例：

```
http://122.226.181.252:8030/fileinfo/infos?obj_id=592529a8000f50ff0100677d&key=/1/upload.txt&access_token=1003775_3145728_1577429797_abf24269c1b163a04a4090643a82f411
```

* 请求报文：

```text
GET /fileinfo/infos?obj_id=592529a8000f50ff0100677d&amp;key=/1/upload.txt&amp;access_token=1003775_3145728_1577429797_abf24269c1b163a04a4090643a82f411 HTTP/1.1
Host: 122.226.181.252:8030
Cache-Control: no-cache
Postman-Token: 91242f6f-e7f3-206d-ed89-f1e774c7081d
```

* 返回数据：

```json
{
  "obj_id": "592529a8000f50ff0100677d",
  "key": "/1/upload.txt",
  "name": "guimain.exe",
  "c_id": 1003775,
  "app_id": "Test",
  "file_id": "63dd6168efccf34442141bc6a30ca4b5bfb5eeb8",
  "timestamp": 1495607720,
  "file_size": 144896,
  "metadata": {
    "K1": "V1",
    "K2": 2,
    "K3": {
      "K3_1": "K3_1",
      "K3_2": 32
    }
  },
  "expire_type": 1,
  "area_id": 1
}
```

* 返回字段：

| 字段名         | 类型           | 描述                                       |
| ----------- | ------------ | ---------------------------------------- |
| obj_id      | string       | 每次上传的对象的唯一标识，OSS生成并返回，用户可以使用该字段进行下载、删除、查询等操作 |
| key         | string       | 对象的key，可以使用该字段进行对象下载、删除、查询等操作            |
| name        | string       | 对象名称                                     |
| c_id        | unsigned int | 用户ID                                     |
| app_id      | string       | 厂商ID                                     |
| file_id     | string       | 文件的唯一表示，相同的对象FileID相同                    |
| timestamp   | unsigned int | 创建时间                                     |
| file_size   | unsigned int | 对象大小，单位字节                                |
| metadata    | json         | 用户自定义的对象元数据                              |
| expire_type | unsigned int | 周期类型，0表示永久，1表示7天，2表示30天，3表示90天，默认为0      |
| area_id     | byte         | 区域ID                                     |

* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | app_key 验证不通过      |
| 500  | 系统内部错误             |



## 6. 查询用户上传的某个对象之后的所有对象信息（不包含该对象）

- 接口状态：`使用中`
- 接口功能：查询用户上传的某个对象之后的所有对象信息。
- 接口类型：管理接口
- 使用对象：永久对象、循环对象
- 请求地址：`fileinfo/listbysort?obj_id=xx&key=/xx/xx&count=xx&access_token=xx_xx_xx_xx`
- 请求方式：`GET`
- 权限验证：**需要正确的请求access_token**
- 请求参数：

| 参数名          | 类型           | 位置         | 描述                            | 必须   | 举例                       |
| ------------ | ------------ | ---------- | ----------------------------- | ---- | ------------------------ |
|              |              |            |                               |      |                          |
| obj_id       | string       | URL String | obj_id和key填一个即可，如果都填以obj_id为准 | 是    | 59243ae1000f50ff01002827 |
| key          | string       | URL String | obj_id和key填一个即可，如果都填以obj_id为准 | 是    | /1/upload.txt            |
| count        | unsigned int | URL String | 返回的对象个数，最大只能为200              | 是    | 2                        |
| access_token | string       | URL String | 用于权限验证的access_token           | 是    | xx_xx_xx_xx              |

* `postman` 请求示例：

```
http://122.226.181.252:8030/fileinfo/listbysort?obj_id=592529a8000f50ff0100677d&key=/1/upload.txt&count=10&access_token=1003775_3145728_1577429797_abf24269c1b163a04a4090643a82f411
```

* 请求报文：

```text
GET /fileinfo/listbysort?obj_id=592529a8000f50ff0100677d&amp;key=/1/upload.txt&amp;count=10&amp;access_token=1003775_3145728_1577429797_abf24269c1b163a04a4090643a82f411 HTTP/1.1
Host: 122.226.181.252:8030
Cache-Control: no-cache
Postman-Token: 0226b082-a830-6169-e7f0-6caa23967b75
```

* 返回数据：

```json
[
  {
    "obj_id": "592529c6000f50ff0100677e",
    "key": "/1/upload1.txt",
    "name": "guimain.exe",
    "c_id": 1003775,
    "app_id": "Test",
    "file_id": "63dd6168efccf34442141bc6a30ca4b5bfb5eeb8",
    "timestamp": 1495607750,
    "file_size": 144896,
    "metadata": {
      "K1": "V1",
      "K2": 2,
      "K3": {
        "K3_1": "K3_1",
        "K3_2": 32
      }
    },
    "expire_type": 0,
    "area_id": 1
  },
  {
    "obj_id": "592529cf000f50ff0100677f",
    "key": "/1/upload2.txt",
    "name": "guimain.exe",
    "c_id": 1003775,
    "app_id": "Test",
    "file_id": "63dd6168efccf34442141bc6a30ca4b5bfb5eeb8",
    "timestamp": 1495607759,
    "file_size": 144896,
    "metadata": {
      "K1": "V1",
      "K2": 2,
      "K3": {
        "K3_1": "K3_1",
        "K3_2": 32
      }
    },
    "expire_type": 0,
    "area_id": 1
  }
]
```

* 返回字段：

  `参见4.查询用户上传的某个对象的信息的返回字段 `

* 状态码：

| 描述                 | 状态码  |
| ------------------ | ---- |
| 请求成功，返回正确的数据       | 200  |
| 参数错误，可能缺少参数或者类型不正确 | 400  |
| app_key 验证不通过      | 401  |
| 系统内部错误             | 500  |

## 7. 查询AppID对应的所有CID列表信息

* 接口状态：`使用中`
* 接口功能：查询AppID下所有占用存储空间的CID列表
* 接口类型：管理接口
* 使用对象：永久对象、循环对象
* 请求地址：`fileinfo/cidsbyappid?access_token=xx_xx_xx_xx&obj_type=x`
* 请求方式：`GET`
* 权限验证：**需要正确的请求access_token**
* 请求参数：


| 参数名          | 类型           | 位置         | 描述                  | 必须   | 举例          |
| ------------ | ------------ | ---------- | ------------------- | ---- | ----------- |
| obj_type     | unsigned int | URL String | 对象类型                | 是    | 1：永久 2：循环   |
| access_token | string       | URL String | 用于权限验证的access_token | 是    | xx_xx_xx_xx |


* `postman` 请求示例：

```
http://122.226.181.252:8030/fileinfo/cidsbyappid?access_token=1003775_3145728_1577429797_abf24269c1b163a04a4090643a82f411&obj_type=1
```

* 请求报文：

```text
GET /fileinfo/cidsbyappid?access_token=1003775_3145728_1577429797_abf24269c1b163a04a4090643a82f411&amp;obj_type=1 HTTP/1.1
Host: 122.226.181.252:8030
Cache-Control: no-cache
Postman-Token: 2f99e46f-5f87-dc6a-9633-32e85b2ec6f1
```

* 返回数据：

```json
{
  "c_ids": [
    1003775,
    1003776
  ]
}	
```

* 返回字段：

| 字段名   | 类型             | 描述                       |
| ----- | -------------- | ------------------------ |
| c_ids | unsigned int数组 | 该区内AppID中所有占用存储空间的c_id列表 |

* 状态码

| 描述                 | 状态码  |
| ------------------ | ---- |
| 请求成功，返回正确的数据       | 200  |
| 参数错误，可能缺少参数或者类型不正确 | 400  |
| 权限验证不通过            | 401  |
| 系统内部错误，检查数据库等      | 500  |
