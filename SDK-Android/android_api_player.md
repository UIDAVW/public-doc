#羚羊云Android API手册-播放器接口

接口名称：LYPlayer

播放器模块可单独实现直播播放，摄像头直播播放，云存储播放，本地录像等功能。

##1 播放器布局
该布局是基于SurfaceView的自定义播放器控件，在使用过程中，只需要引入播放器控件的相应的layout界面即可。

    <com.lingyang.sdk.player.widget.LYPlayer
        android:id="@+id/ly_player"
        android:layout_width="match_parent"
        android:layout_height="match_parent" />
 
##2 设置播放源
```
public void setDataSource(String url)
```
| - | - |
|-------|----|
| 接口名 | setDataSource |
| 功能 | 根据传入的url判断播放类型，实例化IPlayer播放控制器，设置播放模式； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|url|String|In|--|地址，从应用服务器获取。内容格式和意义请参见[羚羊云播放源url格式解析](http://doc.topvdn.com/api/#!public-doc/url_format.md)|

##3 设置播放缓冲时长
```
void setPlayOptions(PlayOptions playOptions);
```
| - | - |
|-------|----|
| 接口名 | setPlayOptions |
| 功能 | 配置播放缓冲时长，可选择性调用。必须在开始播放前调用； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|playOptions|PlayOptions|In|必须|缓冲数据，缓冲时长等相关配置，详见：数据类型_播放缓冲时长参数。|

##4 开始播放
```
void start();
```
| - | - |
|-------|----|
| 接口名 | start |
| 功能 |开始播放； |
| 返回值 | 无 |

##6 停止播放
```
void stop();
```
| - | - |
|-------|----|
| 接口名 | stop |
| 功能 | 停止播放，必须在开始播放后调用； |
| 返回值 | 无 |

##7 播放信息

###7.1 是否正在播放
```
boolean isPlaying();
```
| - | - |
|-------|----|
| 接口名 | isPlaying |
| 功能 | 测试当前对象是否处于started状态； |
| 返回值 | 返回当前播放状态，true：正在播放   false：其他状态，比如Prepared，Paused和PlaybackCompleted等状态 |

###7.2 获取窗口宽
```
int getMinWidth();
```
| - | - |
|-------|----|
| 接口名 | getMinWidth |
| 功能 | 获取非全屏的宽 |
| 返回值 | 无 |

###7.3 获取窗口高
```
int getMinHeight();
```
| - | - |
|-------|----|
| 接口名 | getMinHeight |
| 功能 | 获取非全屏的高 |
| 返回值 | 无 |

###7.4 获取流媒体信息
```
String getMediaParam(int paramType);
```
| - | - |
|-------|----|
| 接口名 | getMediaParam |
| 功能 | 根据传入的参数获取相应的流媒体信息； |
| 返回值 |返回相应的流媒体信息 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|paramType|int|In|必须|流媒体信息对应的协议参数，详见：数据类型IMediaParamProtocol的媒体参数协议|

###7.5 获取时长
```
int getDuration();
```
| - | - |
|-------|----|
| 接口名 | getDuration |
| 功能 | 获取播放的时长 ，仅在点播状态下有效； |
| 返回值 |返回录像时长，单位秒 |

###7.6 获取当前播放位置
```
int getCurrentPosition();
```
| - | - |
|-------|----|
| 接口名 | getCurrentPosition |
| 功能 | 获取当前播放位置，仅在点播状态下有效； |
| 返回值 |无 |

###7.7 获取当前缓冲进度
```
int getBufferPercentage();
```
| - | - |
|-------|----|
| 接口名 | getBufferPercentage |
| 功能 | 获取当前缓冲进度的百分比，仅在点播状态下有效； |
| 返回值 |返回当前缓冲进度的百分比 |

###7.8 是否能暂停
```
boolean canPause();
```
| - | - |
|-------|----|
| 接口名 | canPause |
| 功能 | 测试当前对象是否能暂停，仅在点播状态下有效； |
| 返回值 |返回boolean类型结果，true：能  false：不能 |

###7.9 是否能后退
```
boolean canSeekBackward();
```
| - | - |
|-------|----|
| 接口名 | canSeekBackward |
| 功能 | 测试当前对象是否能后退，仅在点播状态下有效； |
| 返回值 |返回boolean类型结果，true：能  false：不能 |

###7.10 是否能快进
```
boolean canSeekForward();
```
| - | - |
|-------|----|
| 接口名 | canSeekForward |
| 功能 | 测试当前对象是否能快进，仅在点播状态下有效； |
| 返回值 |返回boolean类型结果，true：能  false：不能 |

##8 播放控制

###8.1 设置画面显示比例
```
void setScreenRatio(int screenType);
```
| - | - |
|-------|----|
| 接口名 | setScreenRatio |
| 功能 | 设置画面显示比例； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|screenType|int|In|必须|详见：数据类型IScreenRatioChanger画面缩放比例；|

###8.2 设置全屏
```
void setFullScreen(boolean isFullScreen);
```
| - | - |
|-------|----|
| 接口名 | setFullScreen |
| 功能 | 设置画面显示比例,默认为false； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|isFullScreen|boolean|In|必须|True：全屏 False：非全屏|

###8.3 暂停播放
```
void pause();
```
| - | - |
|-------|----|
| 接口名 | pause |
| 功能 | 暂停播放，仅在点播状态下有效； |
| 返回值 | 无 |

###8.4 暂停以切入后台
```
void pauseToBackground();
```
| - | - |
|-------|----|
| 接口名 | pauseToBackground |
| 功能 | 切入后台时，在宿主Activity的onPause方法中调用此方法暂停播放，节省资源； |
| 返回值 | 无 |

###8.5 从后台恢复播放
```
void resumeFromBackground();
```
| - | - |
|-------|----|
| 接口名 | resumeFromBackground |
| 功能 |后台进入前台时,在宿主Activity的onResume方法中调用此方法恢复播放； |
| 返回值 | 无 |

###8.6 设置播放位置
```
void seekTo(int pos);
```
| - | - |
|-------|----|
| 接口名 | seekTo |
| 功能 | 调整到特定的时间位置(相对时间)，必须在开始播放后调用，仅在点播状态下有效； |
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|pos|int|In|必须|播放时间点，单位秒，从开始播放到指定时间点的秒数。|

###8.7 动态设置视频是否自适应
```
public void setFitScreen(boolean isFit);
```
| - | - |
|-------|----|
| 接口名 | setFitScreen |
| 功能 | 设置视频是否自适应，如果播放器view和获取的视频流宽高比不一致时，设置为true，则将将画面进行裁剪以适应View，设置为false，则不裁剪画面，可能导致画面变形。|
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|isFit|boolean|In|--|true 为自适应，false 为不自适应 |

###8.8 视频截图
```
void snapshot(String path, String name, OnSnapshotListener listener);
```
| - | - |
|-------|----|
| 接口名 | snapshot |
| 功能 | 创建视频截图； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|path|String|In|必须|保存路径(必须是已创建的文件夹的绝对路径)；|
|name|String|In|必须|截图名称，不需要填写格式名称，保存为jpg格式|
|listener|OnSnapshotListener|In|必须|详见：视频截图结果通知回调|

###8.9 视频截图结果通知回调
```
//截图返回的参数错误
int ERROR_RETURN_PARAM = -101;
//存储空间不足
int ERROR_NOT_ENOUGH_SPACE = -102;
//不能解码成jpeg
int ERROR_NOT_DECODE_TO_JPEG = -103;

//截图成功时回调函数；
//输出参数:saveFullPath 保存的完整路径
void onSnapshotSuccess(String saveFullPath)；

//截图失败时回调函数；
//输出参数:errorCode 错误码，详见创建视频截图结束时回调接口_结构定义
void onSnapshotFail(int errorCode);
```

###8.10 开始本地录像
```
void startLocalRecord(String filePath);
```
| - | - |
|-------|----|
| 接口名 | startLocalRecord |
| 功能 | 开始本地录像，在开始播放后调用； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|filePath|String|In|必须|保存路径；|

###8.11 结束本地录像   
```
void stopLocalRecord();
```
| - | - |
|-------|----|
| 接口名 | stopLocalRecord |
| 功能 | 结束本地录像； |
| 返回值 |无 |

###8.12 重置播放器配置
```
void reset();
```
| - | - |
|-------|----|
| 接口名 | reset |
| 功能 | 将播放器的所有配置清空，回到初始化状态，但保留播放器实例，用户可重新设置播放器配置，重新设置播放源进行播放； |
| 返回值 |无 |

##9 注册播放事件的回调

###9.1 注册本地录像状态回调
```
void setLocalRecordListener(OnLocalRecordListener onLocalRecordListener);
```
| - | - |
|-------|----|
| 接口名 | setLocalRecordListener |
| 功能 | 录像时回调函数； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|onLocalRecordListener|OnLocalRecordListener|In|必须|详见：本地录像状态回调函数|

###9.2 本地录像状态回调接口
```
void onRecordSizeChange(long size, long time);
```
| - | - |
|-------|----|
| 接口名 | onRecordSizeChange |
| 功能 | 录制每一KB都会回调此函数； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|size|long|out|--|录制大小，单位：KB|
|time|long|out|--|制时长，单位：S|

###9.3 录像时发生错误时调用的回调函数
```
void onRecordError(LYException e);
```
| - | - |
|-------|----|
| 接口名 | onRecordError |
| 功能 | 录像时发生错误时调用的回调函数； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|e|LYException|out|--|错误信息|

###9.4 注册播放进度回调
```
void setOnPlayProgressListener(OnPlayProgressListener playProgressListener);
```
| - | - |
|-------|----|
| 接口名 | setOnPlayProgressListener |
| 功能 | 注册播放进度回调监听，仅在云存储播放时调用； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|playProgressListener|OnPlayProgressListener|In|必须|详见：播放进度回调监听|

###9.5 播放进度回调接口
```
public interface OnPlayProgressListener {
        void onPlayProgress(int playProgress);
    }
```
| - | - |
|-------|----|
| 接口名 | OnPlayProgressListener |
| 功能 | 媒体文件播放结束后调用的回调接口； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|playProgress|int|out|--|播放进度时间，单位秒|

###9.6 注册连接状态的回调
```
void setOnPreparedListener(OnPreparedListener preparedListener);
```
| - | - |
|-------|----|
| 接口名 | setOnPreparedListener |
| 功能 | 媒体文件即将播放时调用的回调函数； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|preparedListener|OnPreparedListener|In|必须|详见：媒体文件即将播放时调用的回调函数|

###9.7 连接状态的回调接口
```
interface OnPreparedListener {
        void onPrepared( int time);
    }
```
| - | - |
|-------|----|
| 接口名 | OnPreparedListener |
| 功能 | 媒体文件装载时或即将播放时调用的回调接口； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|time|int|out|--|准备时长|

###9.8 注册播放结束后事件的回调
```
void setOnCompletionListener(OnCompletionListener completionListener);
```
| - | - |
|-------|----|
| 接口名 | setOnCompletionListener |
| 功能 | 媒体文件播放结束后调用的回调函数，仅在点播状态下有效； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|completionListener|OnCompletionListener|In|必须|详见：媒体文件播放结束后调用的回调函数|

###9.9 播放结束后事件的回调接口
```
interface OnCompletionListener {
        void onCompletion();
    }
```
| - | - |
|-------|----|
| 接口名 | OnCompletionListener |
| 功能 | 媒体文件播放结束后调用的回调接口，仅在点播状态下有效； |
| 返回值 |无 |

###9.10 注册关闭播放器回调
```
void setOnClosedListener(OnClosedListener closedListener)
```
| - | - |
|-------|----|
| 接口名 | setOnClosedListener |
| 功能 | 对当调用stop停止播放的接口后的结果回调； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|closedListener|OnClosedListener|In|必须|详见：闭播放器事件回调|

###9.11 关闭播放器事件回调
```
interface OnClosedListener {
        void onClosed();;
    }
```
| - | - |
|-------|----|
| 接口名 | OnClosedListener |
| 功能 | 对当调用stop停止播放的接口后的结果回调；|
| 返回值 |无 |

###9.12 注册播放错误事件的回调
```
void setOnErrorListener(OnErrorListener errorListener);
```
| - | - |
|-------|----|
| 接口名 | setOnErrorListener |
| 功能 | 在播放和建立播放期间发生错误被调用的回调函数 如果回调函数没有注册，或者回调函数返回错误, 将不返回用户任何错误； |
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|errorListener|OnErrorListener|In|必须|详见：播放和建立播放期间发生错误的回调函数|

###9.13 播放错误事件的回调接口
```
interface OnErrorListener {
        boolean onError(int code, String msg);
    }
```
| - | - |
|-------|----|
| 接口名 | OnErrorListener |
| 功能 | 播放和建立播放期间发生错误时的回调接口；|
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|code|int|out|--|错误码|
|msg|String|out|--|错误信息|

###9.14 注册播放缓冲的回调       
```
void setOnPlayingBufferCacheListener(OnPlayingBufferCacheListener bufferListener);
```
| - | - |
|-------|----|
| 接口名 | setOnPlayingBufferCacheListener |
| 功能 | 播放时缓存的回调函数，仅在点播状态下有效；|
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|bufferListener|OnPlayingBufferCacheListener|In|必须|详见：播放时缓存的回调函数|

###9.15 播放缓冲的回调接口
```
interface OnPlayingBufferCacheListener {
	void onPlayingBufferCache(int percent);
	void onBufferStart();
	void onBufferEnd();
}
```

#### 当前缓冲的百分比
```
void onPlayingBufferCache(int percent)；
```
| - | - |
|-------|----|
| 接口名 | onPlayingBufferCache |
| 功能 | 正在缓冲时每个百分比都会对调此函数返回当前百分比；|
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|percent|int|out|--|当前缓冲的百分比|

#### 开始缓冲
```
void onBufferStart();
```
| - | - |
|-------|----|
| 接口名 | onBufferStart |
| 功能 | 开始缓冲时回调函数；|
| 返回值 |无 |

#### 缓冲结束
```
void onBufferEnd();
```
| - | - |
|-------|----|
| 接口名 | onBufferEnd |
| 功能 | 缓冲结束时回调函数；|
| 返回值 |无 |

###9.16 注册seek结束事件的回调       
```
void setOnSeekCompleteListener(OnSeekCompleteListener seekCompleteListener);
```
| - | - |
|-------|----|
| 接口名 | setOnSeekCompleteListener |
| 功能 | Seek完成时调用的回调函数，仅在点播状态下有效；|
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|seekCompleteListener|OnSeekCompleteListener|In|必须|详见：播放定位查找结束时调用的回调接口|

###9.17 seek结束事件的回调接口
```
interface OnSeekCompleteListener {
        void onSeekSuccess( int time);
        void onSeekError(LYException exception);
    }
```
#### seek成功回调
```
void onSeekSuccess( int time);
```
| - | - |
|-------|----|
| 接口名 | onSeekSuccess |
| 功能 | Seek完成时调用的回调函数，仅在点播状态下有效；|
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|time|int|out|必须|seek耗时|

#### seek失败回调
```
void onSeekError(LYException exception);
```
| - | - |
|-------|----|
| 接口名 | onSeekError |
| 功能 | Seek失败时调用的回调函数，仅在点播状态下有效；|
| 返回值 |无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|exception|LYException|out|必须|错误对象，包括错误码和错误信息，详见：数据类型_错误信息|

#### 相关链接
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)