#羚羊云Android API手册-数据类型

##1 媒体参数类型
```
public interface IMediaParamProtocol {
    //1.当前视频下载速度
    int STREAM_MEDIA_PARAM_VIDEO_DOWNLOADSPEED = 1;
    //2.当前音频下载速度
    int STREAM_MEDIA_PARAM_AUDIO_DOWNLOADSPEED = 2;
    //3.当前视频帧率
    int STREAM_MEDIA_PARAM_VIDEO_RATE = 3;
    //4.当前音频帧率
    int STREAM_MEDIA_PARAM_AUDIO_RATE = 4;
    //5.平均视频下载速度
    int STREAM_MEDIA_PARAM_VIDEO_AVERAGEDOWNLOADSPEED = 5;
    //6.平均音频下载速度
    int STREAM_MEDIA_PARAM_AUDIO_AVERAGEDOWNLOADSPEED = 6;
    //7.获取QSTP转发ip地址
    int STREAM_MEDIA_PARAM_QSTP = 7;
    //8.上行帧率
    int STREAM_MEDIA_PARAM_DEVICE_UPLOADFRAME = 8;
    //9.上行速度
    int STREAM_MEDIA_PARAM_DEVICE_UPLOADSPEED = 9;
    //10. 缓冲时长（毫秒）
    int STREAM_MEDIA_PARAM_BUFFER_TIME = 10;
    //11.缓冲区帧数
    int STREAM_MEDIA_PARAM_BUFFER_FRAME = 11;
    // 12.当前帧延时（毫秒）
    int STREAM_MEDIA_PARAM_FRAME_DELAY = 12;
    //13. 缓冲区延时（毫秒）
    int STREAM_MEDIA_PARAM_BUFFER_DELAY = 13;
    //14.分辨率宽
    int STREAM_MEDIA_PARAM_RATIO_WIDTH = 14;
    //15.分辨率高
    int STREAM_MEDIA_PARAM_RATIO_HEIGHT = 15;
    //16.发送时间比
    int STREAM_MEDIA_QSTP_SEND_PERCENT = 16;
    //17.在线人数
    int STREAM_MEDIA_ONLINE_NUMBER = 17;
}
```

##2 画面缩放比例
```
public interface IScreenRatioChanger {
    //视频等比最佳
    int TYPE_PLAYER_RATIO_PROP_BEST = 0;
    //视频等比全屏
    int TYPE_PLAYER_RATIO_PROP_FULL = 1;
    //16x9
    int TYPE_PLAYER_RATIO_PROP_16X9 = 2;
    //5x4
    int TYPE_PLAYER_RATIO_PROP_5X4 = 3;
    //4x3
    int TYPE_PLAYER_RATIO_PROP_4X3 = 4;
    //3x4
    int TYPE_PLAYER_RATIO_PROP_3X4 = 5;
    //9x16
    int TYPE_PLAYER_RATIO_PROP_9X16 = 6;
}
```

##3 SessionConfig配置直播推流参数
```
    // 设置图像的旋转角度 只能是 0,90,180,270       
    public Builder withCameraDisplayOrientation(int displayOrientation) ;
    // 是否需要使用音频
    public Builder useAudio(boolean use) ;
    //是否需要使用视频
    public Builder useVideo(boolean use) ;
    // 期望摄像机
    public Builder withDesireadCamera(int camera);
    //设置视频宽高
    public Builder withVideoResolution(int width, int height) ;
    // 使用视频硬编码
    public Builder useHardVideoEncode(boolean encode);
    //使用音频硬编码
    public Builder useHardAudioEncode(boolean encode);
    //使用视频硬编码
    public Builder useAudioEffect(boolean use) ;
    // 设置视频码率
    public Builder withVideoBitrate(int bitrate) ;
    //设置音频采样频率
    public Builder withAudioSampleRateInHz(int samplerate) ;
    //设置音频采样码率
    public Builder withAudioBitrate(int bitrate);
    //设置省道数 1代表单声道，2代表立体声
    public Builder withAudioChannels(int numChannels);
```

##4 预览View形状参数
```
public enum SurfaceFrameShape {
    RECTANGLE, //四边形
    TRIANGLE, //三角形
    CIRCLE   //圆形
}
```

##5 播放缓冲时长参数
```
    //atlp播放最小缓冲时长 
    public Builder withMinAtlpBufferTime(int time) ;
    //atlp播放最大缓冲时长 
    public Builder withMaxAtlpBufferTime(int time);
    //aulp播放最小缓冲时长 
    public Builder withMinAulpBufferTime(int time) ;
    //aulp播放最大缓冲时长 
    public Builder withMaxAulpBufferTime(int time) ;
    //是否静音
    public Builder withMute(boolean isMute) ;
```

##6 错误信息
```
public class LYException extends Exception {
    //错误信息
    private String mMessage; 
    //错误码
    private int mCode; 
    //获取错误信息
    public String getMessage() {
        return mMessage;
    }
    //获取错误码
    public int getCode() {
        return mCode;
    }
}
```

