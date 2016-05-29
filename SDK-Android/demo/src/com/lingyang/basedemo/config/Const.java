package com.lingyang.basedemo.config;


public class Const {
	public static final String USERTOKEN_LL = "3000000185_3356753920_1492163431_cc3acc347784f3e30cd4713acec615b1";//token有效期 2016-4-6至2017-4-6
    public static final String mUserToken188 = "3000000227_3356753920_1491475615_f77ae8d40cd145134df2752586924dd9";//有效期 2016-4-6至2017-4-6
    public static final String CONFIG  =  "[Config]\r\nIsDebug=1\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nIsSendBroadcast=0\r\nUdpSendInterval=2" +
	 		"\r\nSendPacketBufferLength=1408\r\nRecvPacketBufferLength=1408\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80" +
	 		"\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n[RealtimeModeConfig]\r\nLongConncettionServerIP=223.202.103.146" +
	 		"\r\nLongConncettionServerPort=8088\r\nDebugServerIP=120.24.56.51\r\nDebugServerPort=41234\r\nRealtimeModeConfigString=00000000000000\r\nPlayerDataBufferDelayLength=6" +
	 		"[LogServer]\r\nCount=1\r\nIP1=120.26.74.53\r\nPort1=80\r\n";


    public static final String KEY_OF_PLAYER_TYPE="PLAYER_TYPE";
    
//   protocolType：   1:私有； 2:rtmp； 3:录像
//   connectType（1：是推流端，上传媒体流； 2：是拉流端，取媒体流播放）
//   MODE: 1．使用QSUP协议推流，私有模式。
//         2.使用QSTP协议推流，公众模式
//         3.使用QSTP协议推流，私有模式，开启云存储
//         4.使用QSTP协议推流，公众模式，开启云存储
  
    //互联地址
    public static final String FACETIME_CALLING_USERTOKEN="3000000227_3356753920_1491475615_f77ae8d40cd145134df2752586924dd9";//188  token有效期 2016-4-6至2017-4-6
    public static final String FACETIME_LISTENER_USERTOKEN="3000000185_3356753920_1492163431_cc3acc347784f3e30cd4713acec615b1";//159  token有效期 2016-4-6至2017-4-6
    public static final String FACETIME_URL159="topvdn://203.195.157.248:80?token=3000000185_3356753920_1492163431_cc3acc347784f3e30cd4713acec615b1&" +
    		"protocolType=1";
    
    //直播推流地址
    public static final String BROADCAST_URL_LL = "topvdn://0.0.0.0:0?protocolType=2&connectType=1&mode=2&" +
    		"token=3000000185_3356753920_1492163431_cc3acc347784f3e30cd4713acec615b1&cid=3000000185";//token有效期 2016-4-6至2017-4-6
    
    /**
     * 播放器
     */
    //公众摄像机直播观看地址（私有带云存储也是该格式） 格式暂定  rtmp6.public.topvdn.cn:1935是转发服务器地址
    public static final String CAMERA_PLAYER_URL = "topvdn://rtmp6.public.topvdn.cn:1935?token=1003136&protocolType=2&connectType=2";//办公室1
    
    //私有不带云存储摄像机直播观看地址 token是摄像头token  203.195.157.248:80调度服务器地址
    public static final String PRIVATE_CAMERA_PLAYER_URL_LL = "topvdn://203.195.157.248:80?token=1003182_3222536192_1467302400_b862e6a09c7c12022794a18aa61e71bb&"+
    		"protocolType=1" ;//token有效期 2016-4-6至2017-4-6
    
    //手机直播观看地址
    public static final String BROADCAST_LIVE_URL159 = "topvdn://rtmp5.public.topvdn.cn:1935?token=3000000185_3356753920_1492163431_cc3acc347784f3e30cd4713acec615b1&" +
    		"protocolType=2&connectType=2";//token有效期 2016-4-6至2017-4-6
    
    //云存储观看地址 ，，client_token就是设备token，所有时间单位都是秒
    public static final String RECORD_PLAYER_URL_LL = "topvdn://public.topvdn.cn?protocolType=3&" +
    		"token=1003639_3356753920_1466920474_d0063cb1050b05adb0fe69767ba95138&cid=1003639&" +
    		"begin=1464317700&end=1464319828&play=1464317700";  
    
    
    
    
    
    
    
    
    


}
