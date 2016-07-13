#羚羊云Android API手册-预览器接口

接口名称：LYGLCameraView

预览控件可用于直播推流、视频通话等的本地预览，可设置成四边形，圆形，三角形等形状。

##1 预览View布局
该布局是基于GLSurfaceView的自定义预览控件，在使用过程中，只需要引入预览控件的相应的layout界面即可。

    <com.lingyang.sdk.view.LYGLCameraEncoderView
        android:id="@+id/ly_preview"
        android:layout_width="match_parent"
        android:layout_height="match_parent" />

##2 设置预览形状
```
void setShape(SurfaceFrameShape shape);
```
| - | - |
|-------|----|
| 接口名 | setShape |
| 功能 | 设置本地预览控件形状，在设置预览之前调用|
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|shape|SurfaceFrameShape|in|必须|预览形状参数，目前有四边形，三角形和圆形三种，详见:数据类型_预览View形状参数|

##3 将预览View设置为视图最外层
```
void setZOrderOnTop(boolean onTop);
```
| - | - |
|-------|----|
| 接口名 | setShape |
| 功能 | 将预览View设置为视图最外层，在圆形预览和三角形预览时必须调用此方法才能看到预览下层的View|
| 返回值 | 无 |

|参数列表|类型|In/Out|可选/必须|描述|
|-------|----|----|----|----|
|onTop|boolean|in|必须|是否将预览View设置为视图最外层，true：设置为最外层；false：不设置为最外层|

#### 相关链接
[羚羊云SDK接入指南](http://doc.topvdn.com/api/index.html#!public-doc/start_joinup.md)
[羚羊云token认证机制](http://doc.topvdn.com/api/index.html#!public-doc/token_format.md)
[羚羊云推拉流URL格式解析](http://doc.topvdn.com/api/index.html#!public-doc/url_format.md)