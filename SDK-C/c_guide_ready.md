#羚羊云C SDK集成准备

##1 SDK的获取
[点击这里获取](http://doc.topvdn.com/api/public-doc/SDK-C/zipdown/ly_sdk_c.zip "获取SDK")

##2 SDK库结构
SDK目录
|--lib      包含羚羊云的静态库libTopvdn.a和动态库libPusher.so
|--include  包含了使用羚羊云C接口SDK需要的头文件
|--demo   包含当前版本SDK的demo程序，编译生成程序后可运行查看SDK功能演示及其效果

**SDK包内库文件如下**：
libPusher.s:平台基础库，包括登录平台，获取转发，p2p连接等；
libTopvdn.a:羚羊云功能实现库，包括功能概要中提供到所有功能，并可根据用户需求进行裁剪；
libstdc++.so.6:标准c++库，若使用gcc编译器，则需要连接此库，否则会编译不通过；
libcrypto.a和libssl.a:羚羊云使用到的加密库，如果需要加密相关功能，则需要链接。

**SDK包内头文件如下**：

common_define.h：此头文件中包含羚羊云一些公共数据类型的定义

LYPlatformAPI.h：此头文件包含羚羊云C接口的声明

##3 SDK的集成
###3.1 linux环境下在Makefile中配置示例：
INCLUDE_DIR	:= ./include /*配置头文件路径*/
LIB_DIR		:= ./lib     /*配置库文件路径*/
CFLAGS		:= -I$(INCLUDE_DIR)
LDFLAGS		:= -Wl,-rpath=. -lPusher–lTopvdnSDK-lpthread -lssl -lcrypto

###3.2 windows环境工程配置（VS2012为例）
1. 新建一个工程。
2. 右键工程，选择“属性”。
3. 选择“C/C++”，点击“常规”，在“附加包含目录”中配置头文件目录。
4. 选择“库管理器”，点击“常规”，在“附件库目录”中配置库路径，然后在附加依赖项中添加libTopvdn.lib
