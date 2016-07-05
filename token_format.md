#羚羊云token认证机制
##1 羚羊云的身份验证方式
羚羊云采用目前web领域普遍的认证方式：基于token的身份验证。

无论是调用羚羊云Web API或者客户端SDK的接口，需要将token作为参数传入，在羚羊云服务端进行身份验证。

##2 羚羊云token内容格式
>格式：{明文段}\_{验证码}

>样式：cid\_control\_expire\_\[vod\_time\]\_\[ip\]\_\[refer\]\_digest

其中：
**cid\_control\_expire\_\[vod\_time\]\_\[ip\]\_\[refer\]**为明文段，**[ ]**标记表示可选字段。
**digest**为验证码

举例：
**537067556_3222536192_1493481600**_**f0399b369aa760362ac4edd224bae23b**

##3 token明文段
token明文段包含以下字段：

|字段| 数据类型 | 含义 |
|----|----|----|
|cid |4字节无符号整型| 详见[《SDK接入指南》](http://doc.topvdn.com/api/#!public-doc/integration.md#3._相关术语和名词)关于`cid`的名词解释。|
|control |4字节无符号整型| 控制字段，设备对视频流的推送、播放、云存储等功能的参数配置，各字节以及位的意义详见下文control字段介绍。|
|expire |4字节无符号整型| 过期时间，token的有效时间，为UTC时间戳（秒级精度，4字节）。|
|vod_time |4字节无符号整型| 点播时间，点播时对应的录制时间，同时也是点播文件的文件名部分。|
|ip |4字节无符号整型| 设备的公网ip地址，该字段一般用来启用防盗链功能。|
|refer |字符串| http请求时的refer地址中的域名部分，该字段一般用来启用防盗链功能。|

**注意：**
除refer字段外，所有的字段都是主机字节序(Little-Endian小端存储)，无符号四字节整数类型；

##4 token明文段的control字段
该字段在内存中以Little-Endian小端方式存储，第一字节为无符号int类型的低位，第四字节为无符号int类型的高位。

| **第一字节**（推送控制及安全控制） | **第二字节**（录制控制） | **第三字节**（播放控制）| **第四字节**（多码流保留）|

- **第一字节（0-7位）**：推送控制及安全控制
0位：  是否开启rtmp直播
1位：  是否开启hls直播
2位：  是否验证ip &nbsp;&nbsp;如果该项开启则token明文段中必须填写ip字段，用以防止非本方的其他设备盗用URL链接。
3位：  是否验证refer &nbsp;&nbsp;如果该项开启则token明文段中必须填写refer字段，用以防止非本方的其他设备盗用URL链接。
4位：  是否接受udp请求 &nbsp;&nbsp;如果不开启则不接受udp的数据请求
5-7位：保留

- **第二字节（0-7位）**：录制控制
0-3位: 录像循环存储开关
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;0000 不存储录像
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;0001 存储7天录像  超过7天则会覆盖最旧的录像数据而继续循环存储
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;0010 存储30天录像 超过30天则会覆盖最旧的录像数据而继续循环存储
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;0011 存储90天录像 超过90天则会覆盖最旧的录像数据而继续循环存储
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;其他 保留
4位 : FLV持久化开关，默认为0表示不打开
5位 : HLS持久化开关，默认为0表示不打开
6-7位: 保留
**`注意`**: 以上三个开关同时只能开启一个。

- **第三字节（0-7位）**：播放控制
0位：能否观看公众 可否观看公众设备的视频
1位：能否观看私有 可否观看私有设备的视频
2位：能否观看时移 该项暂作保留
3位：能否观看录像 可否观看设备的录像
4位：能否语音回传 该项暂作保留
5位：能否视频回传 该项暂作保留
6位：能否查看截图 开启该项则可查看封面截图
7位：能否收听声音 如果已开启上面的观看选项，该项设置则无效；当没有开启上面的观看选项该项才有效。

##5 token验证码
由明文串配上羚羊云提供的密钥，通过HMAC-MD5标准算法，生成token的验证码部分。验证码为16个无符号的字节数组。

- `明文串格式`：各个字段按顺序无缝拼接而成，长度根据字段数目不同而不定。例如：<u>537067556</u>3222536192<u>1493481600</u>
其中：<u>537067556</u>为**cid**字段，<u>3222536192</u>为**control**字段，<u>1493481600</u>为**expire**字段。
- `密钥`：羚羊云提供给用户的appkey。
- `生成的验证码`：16进制32个字符的字符串。
- `验证码生成的示例代码`：

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;C语言示例代码如下：
```
unsigned int cid = 537067556;
unsigned int control = 3222536192;
unsigned int expire = 1493481600;
unsigned char src[12];
char token[100];
memcpy(src, &cid, 4);
memcpy(src+4, &control, 4);
memcpy(src+8, &expire, 4);
char key[50] = "abcdefghijklmnopqrstuvwxyz123456";
unsigned char digest[16];

int ret = hmac_md5((unsigned char*)key,strlen(key),src,12,digest);
if(ret != 0)
{
    return -1;
}

snprintf(token, sizeof(token), “%u_%u_%u_%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x, cid, control, expire, digest[0] , digest[1] , digest[2] , digest[3] , digest[4] , digest[5] , digest[6] , digest[7] , digest[8] , digest[9] , digest[10] , digest[11] , digest[12] , digest[13] , digest[14] , digest[15]”);

return 0;
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PHP示例代码如下：
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```
<?php 
    function generate_ly_token($app_key, $cid, $control, $expire) {
    	$data = pack("I", $cid).pack("I", $control).pack("I", $expire);
    	$hash_val = hash_hmac("md5", $data, $app_key);
    	return $cid."_".$control."_".$expire."_".$hash_val;
    }
    
    /*Sample data.*/
    $app_key = "d57559a82027b7d846318a0c1596d645";
    $cid = 10000;
    $control = 3222274048;
    $expire = 1475031947;
    
    /*Should be 10000_3222274048_1475031947_f124654ced4d5b30dad739caac64f424 */
    echo generate_ly_token($app_key, $cid, $control, $expire);
?>
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Java示例代码如下：
```
import java.nio.ByteOrder;
import java.nio.ByteBuffer;
import java.io.UnsupportedEncodingException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;

class Main {

  public static String generateLYToken(String appKey, Integer cid, Integer control, Integer expire) {
      byte[] data = getTokenPartsBytes(cid, control, expire);
      String hash_val = hmac_md5(appKey, data);
      return String.format(
        "%d_%d_%d_%s", Integer.toUnsignedLong(cid.intValue()),
        Integer.toUnsignedLong(control.intValue()),
        Integer.toUnsignedLong(expire.intValue()), hash_val);
  }

  public static byte[] getTokenPartsBytes(Integer cid, Integer control, Integer expire) {
      ByteBuffer buf = ByteBuffer.allocate(12);
      buf.order(ByteOrder.LITTLE_ENDIAN);
      buf.putInt(cid.intValue());
      buf.putInt(control.intValue());
      buf.putInt(expire.intValue());
      return buf.array();
  }
  
  public static String hmac_md5(String appKey, byte[] data) {
    String algorithm = "HmacMD5";
    Mac mac = null;
    
    try {
        SecretKeySpec key = new SecretKeySpec((appKey).getBytes("UTF-8"), algorithm);
        mac = Mac.getInstance(algorithm);
        mac.init(key);
    } catch (UnsupportedEncodingException e) {
      System.out.println(e);
    } catch (InvalidKeyException e) {
      System.out.println(e);
    } catch (NoSuchAlgorithmException e) {
      System.out.println(e);
    }

    byte[] bytes = mac.doFinal(data);
    StringBuffer hash = new StringBuffer();
    for (int i = 0; i < bytes.length; i++) {
        String hex = Integer.toHexString(0xFF & bytes[i]);
        if (hex.length() == 1) {
           hash.append('0');
        }
        hash.append(hex);
    }
    return hash.toString();
  }

  public static void main(String[] args) {
    String appKey = "d57559a82027b7d846318a0c1596d645";
    Integer cid = Integer.parseUnsignedInt("10000");
    Integer control = Integer.parseUnsignedInt("3222274048");
    Integer expire = Integer.parseUnsignedInt("1475031947");

    // Should be 10000_3222274048_1475031947_f124654ced4d5b30dad739caac64f424
    System.out.println(generateLYToken(appKey, cid, control, expire));
  }
}
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Python示例代码如下：
```
import hmac
import struct
import functools
from hashlib import md5

pack_unsigned_int = functools.partial(struct.pack, 'I')

def generate_ly_token(app_key, cid, control, expire):
    parts = [cid, control, expire]
    data = ''.join(map(pack_unsigned_int, parts))
    hash_val = hmac.new(app_key, data, md5).hexdigest()
    return '_'.join(map(str, parts)+[hash_val])

if __name__ == '__main__':
    app_key = 'd57559a82027b7d846318a0c1596d645'
    cid = 10000
    control = 3222274048
    expire = 1475031947
    # Should be `10000_3222274048_1475031947_f124654ced4d5b30dad739caac64f424`
    print(generate_ly_token(app_key, cid, control, expire))
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Go语言示例代码如下：
```
package main

import (
    "bytes"
    "crypto/hmac"
    "crypto/md5"
    "encoding/binary"
    "fmt"
    "log"
)

func GenerateLYToken(app_key []byte, cid, control, expire uint32) string {
    buf := bytes.Buffer{}
    err := binary.Write(&buf, binary.LittleEndian, cid)
    if err != nil {
        log.Fatal(err)
    }
    err = binary.Write(&buf, binary.LittleEndian, control)
    if err != nil {
        log.Fatal(err)
    }
    err = binary.Write(&buf, binary.LittleEndian, expire)
    if err != nil {
        log.Fatal(err)
    }

    mac := hmac.New(md5.New, app_key)
    mac.Write(buf.Bytes())
    hash_val := mac.Sum([]byte{})
    return fmt.Sprintf("%d_%d_%d_%x", cid, control, expire, hash_val)
}

func main() {
    app_key := []byte("d57559a82027b7d846318a0c1596d645")

    var cid, control, expire uint32
    cid = 10000
    control = 3222274048
    expire = 1475031947
    //Should be 10000_3222274048_1475031947_f124654ced4d5b30dad739caac64f424
    fmt.Println(GenerateLYToken(app_key, cid, control, expire))
}
```

##6 羚羊云token类型
根据设备(包括手机、摄像头等)所处于羚羊云端点的不同，token分为设备token和访问token。本方所携带的token称为设备token，对端设备的token称为访问token。

- `设备token`

明文组成部分为cid + control + expire + \[ip]；
\[ip]:可选项，如果control字段里面设置验证ip的标志位，则ip字段必须填写。

- `访问token`

明文组成部分为cid + control + expire + \[vod_time] + \[ip] + \[refer]；
按照访问方式不同，[]中的可选项又分为以下几种情况：
\[vod_time]:只有在看http点播时必须使用，其他情况不得添加；
\[ip]:可选项，如果control字段里面设置验证ip的标志位，则ip字段必须填写；
\[refer]：可选项，并只有在http访问方式下使用，如果control里设置了验证refer标志位，则refer字段必须填写。

##相关链接
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/integration.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)
