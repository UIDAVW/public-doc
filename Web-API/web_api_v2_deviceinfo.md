# 羚羊云Web API-查询设备在线信息

## 查询设备在线信息
* 接口状态：`使用中`
* 接口功能：获取接入到羚羊云的某设备的在线状态、内网ip、公网ip、流媒体转发服务器ip、调度服务器ip、封面截图URL等网络节点地址信息。
* 接口类型：管理接口
* 使用对象：应用服务器
* 请求地址：`/v2/devices/state?size=20&page=1`
* 请求方式：`POST`
* 权限验证：**需要在请求首部携带 X-APP-ID 和 X-APP-Key**

* 请求参数：


| 参数名  | 类型            | 描述                             | 必须   | 举例   |
| ---- | ------------- | ------------------------------ | ---- | ---- |
| size | unsigned int  | `query param` 每页大小             | 否    | 10   |
| page | unsigned uint | `query param` 第几页              | 否    | 2    |
| cids | json array    | 设备 ID 字符串列表，如果没有或者为空则分页返回所有的数据 | 否    | []   |


* `curl` 请求示例：

```
curl -X POST -H "X-APP-ID: mock" -H "X-APP-Key: mock-app-key-use-your-own-pls" -H "Content-Type: application/json" -d '{
    "cids": [1003538]
}' "http://api.topvdn.com/v2/devices/state?page=1&size=20"
```

* 请求报文：

```json
POST /v2/devices/state?page=1&size=20 HTTP/1.1
Host: api.topvdn.com
X-APP-ID: mock
X-APP-Key: mock-app-key-use-your-own-pls
Content-Type: application/json
Cache-Control: no-cache

{
    "cids": [1003538]
}
```

* 返回数据：

```json
{
	"init_string": "[Config]\r\nIsDebug=1\r\nLocalBasePort=8200\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nUdpSendInterval=2\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n[LogServer]\r\nCount=1\r\nIP1=223.202.103.147\r\nPort1=80",
    "devices": [
	    {
		    "cid": 1003538,
			"state": 4,
			"tracker_ip": "203.195.157.248",
			"tracker_port": 80,
			"public_ip": "14.215.177.37",
			"public_port": 8747,
			"local_ip": "192.168.2.222",
			"local_port": 8732,
			"config_type": 0,
			"conn_key": 1243,
			"relay_ip": "125.91.251.79",
			"relay_port": 80,
			"cover_url": "http://api.topvdn.com/v2/snapshots/1003775/cover?client_token=1003775_0_1452756453_0d78e95edab47e565010f47a0300de2d",
			"rtmp_url": "rtmp://rtmp0-9.public.topvdn.cn/",
			"hls": "http://hls0-9.public.topvdn.cn/hls/<cid>/index.m3u8"
		}
	],
	"total": 145,
	"size": 20,
	"page": 1,
    "request_id": "2279fa57f4d644c1b333f5ff5ff7a2b7"
}
```

* 返回字段：

| 字段名         | 类型           | 描述         |
| ----------- | ------------ | ---------- |
| init_string | string       | 设备初始化串     |
| devices     | json array   | 设备列表       |
| total       | unsigned int | 查询条件下的设备总数 |
| page        | unsigned int | 页数         |
| size        | unsigned int | 页大小        |
| request_id  | string       | 此次请求的唯一编号  |


* devices 字段：

| 字段名          | 类型     | 描述                                       |
| ------------ | ------ | ---------------------------------------- |
| cid          | int    | 设备 id                                    |
| state        | int    | 设备状态 0：异常或离线； 1：就绪； 2：获取转发中 3：连接转发中 4：推流中 5：断开转发中 |
| config_type  | int    | 设备配置类型，公众或者私有等 0：私有；1：私有广播；2：公众；3：私有录像；4：公众录像; 6: 事件存储 |
| tracker_ip   | string | 设备登录的 tracker 服务器                        |
| tracker_port | int    | 设备登录的 tracker 端口                         |
| public_ip    | string | 设备公网 IP                                  |
| public_port  | int    | 设备公网端口                                   |
| local_ip     | string | 设备本地 IP                                  |
| local_port   | int    | 设备本地端口                                   |
| conn_key     | int    | 连接 key                                   |
| relay_ip     | string | 源转发服务器                                   |
| relay_port   | int    | 源转发 端口                                   |
| cover_url    | string | 设备的封面截图，注意此 URL 会过期，目前默认为获取后 24 小时       |
| rtmp_url     | string | 设备的 rtmp 播放 domain，私有 (config_type 0) 配置设备此字段为空 |
| hls          | string | 设备的 hls 播放地址，私有 (config_type 0) 配置设备此字段为空，详细见下 |


* `hls` 字段

在提供给客户端播放时，第三方应该在本接口返回的 hls 地址后后面添加 token 相关的验证信息作为查询参数，例子如下：

` http://hls0-9.public.topvdn.cn/hls/<cid>/index.m3u8?expire=1566579141&access=3222536192&token=e17e6311c52a23d1d58923fc42f24540`

参考文档: [羚羊云token内容格式](http://doc.topvdn.com/api/#!public-doc/token_format.md#2_羚羊云token内容格式)

| 查询参数   | token 字段 | 意义                |
| ------ | -------- | ----------------- |
| access | control  | token 的权限控制位      |
| expire | expire   | 过期时间              |
| token  | digest   | 根据 token 算法生成的摘要串 |


* 状态码

| 状态码  | 描述                 |
| ---- | ------------------ |
| 200  | 请求成功，返回正确的数据       |
| 400  | 参数错误，可能缺少参数或者类型不正确 |
| 401  | app_key 验证不通过      |
| 406  | size 超过限制，最大为 100  |
| 500  | 系统内部错误             |
