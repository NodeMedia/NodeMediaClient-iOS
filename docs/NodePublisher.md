# iOS NodePublisher API 文档

NodePublisher 是 NodeMediaClient 框架的核心推流器类，提供摄像头采集、音视频编码、直播推流及多路输出等功能。

## 快速开始

```objc
// 初始化推流器
NodePublisher *pub = [[NodePublisher alloc] initWithLicense:@"your-license"];

// 设置音视频编码参数
[pub setVideoParamWithCodec:NMC_CODEC_ID_H264
                    profile:NMC_PROFILE_H264_MAIN
                      width:720 height:1280
                        fps:24 bitrate:1200 * 1000];

[pub setAudioParamWithCodec:NMC_CODEC_ID_AAC
                    profile:NMC_PROFILE_AAC_LC
                 samplerate:44100 channels:1 bitrate:64 * 1000];

// 打开前置摄像头
[pub openCamera:YES];

// 附加预览视图
[pub attachView:self.previewView];

// 开始推流
[pub start:@"rtmp://live.example.com/publish/streamKey"];
```

## 常量定义

### 编码器 ID

可用于 `setVideoParamWithCodec:` 和 `setAudioParamWithCodec:` 的 `codec` 参数。

| 常量               | 值     | 说明     |
| ------------------ | ------ | -------- |
| `NMC_CODEC_ID_H264`  | 27     | H.264/AVC 视频编码 |
| `NMC_CODEC_ID_H265`  | 173    | H.265/HEVC 视频编码 |
| `NMC_CODEC_ID_AAC`   | 86018  | AAC 音频编码   |
| `NMC_CODEC_ID_OPUS`  | 86076  | Opus 音频编码  |
| `NMC_CODEC_ID_PCMA`  | 65543  | PCM A-law 音频编码 |
| `NMC_CODEC_ID_PCMU`  | 65542  | PCM μ-law 音频编码 |

### 编码规格 (Profile)

#### H.264 Profiles

| 常量                          | 值   | 说明       |
| ----------------------------- | ---- | ---------- |
| `NMC_PROFILE_AUTO`              | 0    | 自动选择   |
| `NMC_PROFILE_H264_BASELINE`     | 66   | Baseline   |
| `NMC_PROFILE_H264_MAIN`         | 77   | Main       |
| `NMC_PROFILE_H264_HIGH`         | 100  | High       |

#### H.265 Profiles

| 常量                    | 值 | 说明 |
| ----------------------- | - | ---- |
| `NMC_PROFILE_H265_MAIN` | 1 | Main |

#### AAC Profiles

| 常量                   | 值  | 说明 |
| ---------------------- | --- | ---- |
| `NMC_PROFILE_AAC_LC`   | 1   | LC (Low Complexity) |
| `NMC_PROFILE_AAC_HE`   | 4   | HE (High Efficiency, AAC+) |
| `NMC_PROFILE_AAC_HE_V2`| 28  | HE v2 |

### 视频方向

用于 `videoOrientation` 属性。

| 常量                            | 值 | 说明 |
| ------------------------------- | - | ---- |
| `VIDEO_ORIENTATION_PORTRAIT`      | 1 | 竖屏 |
| `VIDEO_ORIENTATION_LANDSCAPE_RIGHT` | 3 | 横屏（Home 键在右） |
| `VIDEO_ORIENTATION_LANDSCAPE_LEFT`  | 4 | 横屏（Home 键在左） |

### 对焦测光标志

用于 `startFocusAndMetering:withFlags:` 的 `flags` 参数，支持按位组合。

| 常量       | 值 | 说明             |
| ---------- | - | ---------------- |
| `FLAG_AF`  | 1 | 自动对焦 (Auto Focus) |
| `FLAG_AE`  | 2 | 自动曝光 (Auto Exposure) |
| `FLAG_AWB` | 4 | 自动白平衡 (Auto White Balance) |

### 摄像头设备类型

用于 `openCameraDevice:withFront:` 的 `deviceType` 参数。

| 常量                             | 值 | 说明   |
| -------------------------------- | - | ------ |
| `NMC_DEVICE_TYPE_WideAngleCamera`  | 0 | 广角摄像头 |
| `NMC_DEVICE_TYPE_TelephotoCamera`  | 1 | 长焦摄像头 |
| `NMC_DEVICE_TYPE_UltraWideCamera`  | 2 | 超广角摄像头 |
| `NMC_DEVICE_TYPE_DualCamera`       | 3 | 双摄像头 |
| `NMC_DEVICE_TYPE_TripleCamera`     | 4 | 三摄像头 |

### 特效参数键名

用于 `setEffectParameter:withIntensity:` 的 `parameter` 参数。

| 常量                    | 值（字符串）    | 取值范围     | 默认值 | 说明       |
| ----------------------- | --------------- | ------------ | ------ | ---------- |
| `EFFECTOR_BRIGHTNESS`   | `"brightness"`  | `0.0` ~ `2.0` | `1.0`  | 亮度   |
| `EFFECTOR_CONTRAST`     | `"contrast"`    | `0.0` ~ `2.0` | `1.0`  | 对比度 |
| `EFFECTOR_SATURATION`   | `"saturation"`  | `0.0` ~ `2.0` | `1.0`  | 饱和度 |
| `EFFECTOR_SHARPEN`      | `"sharpen"`     | `0.0` ~ `1.0` | —      | 锐化   |
| `EFFECTOR_SMOOTHSKIN`   | `"smoothskin"`  | `0.0` ~ `1.0` | —      | 美颜(磨皮) |
| `EFFECTOR_STYLE`        | `"style"`       | `0.0` ~ `1.0` | —      | 滤镜强度 |

### 滤镜风格 ID

用于 `setEffectStyleWithId:` 的 `sid` 参数。

| 常量                         | 值 | 说明       |
| ---------------------------- | - | ---------- |
| `EFFECTOR_STYLE_ID_ORIGINAL`   | 0 | 原始       |
| `EFFECTOR_STYLE_ID_ENHANCED`   | 1 | 增强       |
| `EFFECTOR_STYLE_ID_FAIRSKIN`   | 2 | 白皙       |
| `EFFECTOR_STYLE_ID_COOL`       | 3 | 冷色调     |
| `EFFECTOR_STYLE_ID_FILM`       | 4 | 胶片       |
| `EFFECTOR_STYLE_ID_BOOST`      | 5 | 鲜艳       |

## 事件回调

通过 `NodePublisherDelegate` 协议接收推流器状态事件：

```objc
// 设置事件代理
pub.nodePublisherDelegate = self;

// 实现代理方法
- (void)onEventCallback:(id)sender event:(int)event msg:(NSString *)msg {
    NSLog(@"推流事件: %d, 消息: %@", event, msg);
}
```

`event` 取值说明：

| Code | 名称       | 说明                       |
| ---- | ---------- | -------------------------- |
| 2000 | 开始连接   | 开始连接推流服务器         |
| 2001 | 连接成功   | 推流连接成功               |
| 2002 | 连接失败   | 连接失败（自动重连中）     |
| 2003 | 重连中     | 正在重新连接               |
| 2004 | 推流结束   | 推流正常结束               |
| 2005 | 网络异常   | 网络异常（自动重连中）     |
| 2006 | 连接超时   | 网络连接超时（自动重连中） |

---

## 属性参考

### nodePublisherDelegate

事件委托对象，用于接收推流器状态回调。

```objc
@property (nonatomic, weak) id<NodePublisherDelegate> nodePublisherDelegate;
```

### logLevel

日志输出等级：

| 值   | 等级  | 说明                   |
| ---- | ----- | ---------------------- |
| 0    | error | 仅输出错误日志         |
| 1    | info  | 输出信息与错误日志     |
| 2    | debug | 输出全部调试日志       |

```objc
@property (nonatomic) NSInteger logLevel;

pub.logLevel = 0; // 仅错误日志
```

### HWAccelEnable

是否开启硬件加速编码。

```objc
@property (nonatomic) Boolean HWAccelEnable;

pub.HWAccelEnable = YES;
```

### denoiseEnable

是否开启背景音降噪。

```objc
@property (nonatomic) Boolean denoiseEnable;

pub.denoiseEnable = YES;
```

### torchEnable

是否开启补光灯（闪光灯常亮）。

```objc
@property (nonatomic) Boolean torchEnable;

pub.torchEnable = YES;
```

### zoomRatio

缩放等级，取值范围 `0.0` ~ `1.0`，对应 `1x` ~ `10x` 光学/数码变焦。

```objc
@property (nonatomic) float zoomRatio;

pub.zoomRatio = 0.5; // 约 5x 变焦
```

### volume

音量，取值范围 `0.0` ~ `1.0`，用于推流时控制是否静音（如播放背景音乐时静音推流）。

```objc
@property (nonatomic) float volume;

pub.volume = 0.0; // 静音推流
```

### extendedFlvId

是否使用扩展 FLV ID 方式进行编码推流。

```objc
@property (nonatomic) Boolean extendedFlvId;

pub.extendedFlvId = YES;
```

### cryptoKey

音视频内容加密密码，**16 字节字符串**。

```objc
@property (nonatomic, copy) NSString *cryptoKey;

pub.cryptoKey = @"abcdef1234567890";
```

### cameraFrontMirror

预览前置摄像头画面是否镜像。

```objc
@property (nonatomic) Boolean cameraFrontMirror;

pub.cameraFrontMirror = YES; // 前置预览镜像（镜像自拍效果）
```

### keyFrameInterval

视频关键帧间隔，单位秒。较小的值有助于快速拖放定位，但会增加码率。

```objc
@property (nonatomic) NSInteger keyFrameInterval;

pub.keyFrameInterval = 2; // 每 2 秒一个关键帧
```

### videoOrientation

视频方向，使用 `VIDEO_ORIENTATION_*` 常量。

```objc
@property (nonatomic) NSInteger videoOrientation;

pub.videoOrientation = VIDEO_ORIENTATION_PORTRAIT; // 竖屏推流
```

---

## 方法参考

### initWithLicense:

使用许可证初始化推流器。

```objc
- (instancetype)initWithLicense:(NSString *)license;
```

**参数：**

| 参数      | 类型       | 说明               |
| --------- | ---------- | ------------------ |
| license   | NSString * | NodePublisher 许可证字符串 |

**返回值：** 已初始化的 `NodePublisher` 实例。

**示例：**

```objc
NodePublisher *pub = [[NodePublisher alloc] initWithLicense:@"your-license-key"];
```

---

### openCamera:

打开摄像头，指定是否为前置摄像头。

```objc
- (NSInteger)openCamera:(Boolean)frontCamera;
```

**参数：**

| 参数        | 类型    | 说明                       |
| ----------- | ------- | -------------------------- |
| frontCamera | Boolean | `YES` 前置摄像头，`NO` 后置 |

**返回值：** `NSInteger` 状态码（`0` 表示成功）。

**示例：**

```objc
[pub openCamera:YES];  // 打开前置摄像头
```

---

### openCameraDevice:withFront:

打开指定类型的摄像头。

```objc
- (NSInteger)openCameraDevice:(NSInteger)deviceType withFront:(Boolean)frontCamera;
```

**参数：**

| 参数       | 类型       | 说明                        |
| ---------- | ---------- | --------------------------- |
| deviceType | NSInteger  | 设备类型（`NMC_DEVICE_TYPE_*` 常量） |
| frontCamera| Boolean    | `YES` 前置，`NO` 后置          |

**返回值：** `NSInteger` 状态码。

**示例：**

```objc
// 打开后置超广角摄像头
[pub openCameraDevice:NMC_DEVICE_TYPE_UltraWideCamera withFront:NO];
```

---

### closeCamera

关闭摄像头。

```objc
- (NSInteger)closeCamera;
```

**返回值：** `NSInteger` 状态码。

**示例：**

```objc
[pub closeCamera];
```

---

### switchCamera

切换前后摄像头。

```objc
- (NSInteger)switchCamera;
```

**返回值：** `NSInteger` 状态码。

**示例：**

```objc
[pub switchCamera];
```

---

### startFocusAndMeteringCenter

设置中心点自动对焦、自动曝光和自动白平衡。

```objc
- (void)startFocusAndMeteringCenter;
```

**示例：**

```objc
[pub startFocusAndMeteringCenter];
```

---

### startFocusAndMetering:withFlags:

在指定点执行自动对焦、自动曝光和/或自动白平衡。

```objc
- (void)startFocusAndMetering:(nullable CGPoint*)point withFlags:(NSInteger)flags;
```

**参数：**

| 参数   | 类型           | 说明                                 |
| ------ | -------------- | ------------------------------------ |
| point  | CGPoint *      | 对焦/测光点坐标（`nil` 表示中心点）      |
| flags  | NSInteger      | 功能标志（`FLAG_AF`、`FLAG_AE`、`FLAG_AWB`，支持按位组合） |

**示例：**

```objc
// 在指定点同时执行自动对焦和自动曝光
CGPoint point = CGPointMake(0.5, 0.5);
[pub startFocusAndMetering:&point withFlags:FLAG_AF | FLAG_AE];
```

---

### setAudioParamWithCodec:profile:samplerate:channels:bitrate:

设置音频编码参数。**必须在推流前调用。**

```objc
- (void)setAudioParamWithCodec:(NSInteger)c profile:(NSInteger)p samplerate:(NSInteger)s channels:(NSInteger)ch bitrate:(NSInteger)b;
```

**参数：**

| 参数       | 类型       | 说明                       |
| ---------- | ---------- | -------------------------- |
| c (codec)    | NSInteger  | 编码器 ID（`NMC_CODEC_ID_*`）  |
| p (profile)  | NSInteger  | 编码规格（`NMC_PROFILE_*`）    |
| s (samplerate) | NSInteger  | 采样率，单位 Hz（如 44100） |
| ch (channels) | NSInteger  | 声道数（1=单声道，2=立体声）    |
| b (bitrate)  | NSInteger  | 比特率，单位 bps            |

**示例：**

```objc
// AAC-LC, 44100Hz, 单声道, 64kbps
[pub setAudioParamWithCodec:NMC_CODEC_ID_AAC
                    profile:NMC_PROFILE_AAC_LC
                 samplerate:44100 channels:1 bitrate:64000];
```

---

### setVideoParamWithCodec:profile:width:height:fps:bitrate:

设置视频编码参数。**必须在推流前调用。**

```objc
- (void)setVideoParamWithCodec:(NSInteger)c profile:(NSInteger)p width:(NSInteger)w height:(NSInteger)h fps:(NSInteger)f bitrate:(NSInteger)b;
```

**参数：**

| 参数         | 类型       | 说明                     |
| ------------ | ---------- | ------------------------ |
| c (codec)      | NSInteger  | 编码器 ID（`NMC_CODEC_ID_*`） |
| p (profile)    | NSInteger  | 编码规格（`NMC_PROFILE_*`）   |
| w (width)      | NSInteger  | 视频宽度，单位像素        |
| h (height)     | NSInteger  | 视频高度，单位像素        |
| f (fps)        | NSInteger  | 帧率                     |
| b (bitrate)    | NSInteger  | 比特率，单位 bps          |

**示例：**

```objc
// 720p, H.264 Main, 24fps, 1.2Mbps
[pub setVideoParamWithCodec:NMC_CODEC_ID_H264
                    profile:NMC_PROFILE_H264_MAIN
                      width:720 height:1280
                        fps:24 bitrate:1200000];
```

---

### setEffectParameter:withIntensity:

设置特效参数强度。使用 `EFFECTOR_*` 常量作为参数键名。

```objc
- (void)setEffectParameter:(NSString *)parameter withIntensity:(float)intensity;
```

**参数：**

| 参数      | 类型       | 说明                     |
| --------- | ---------- | ------------------------ |
| parameter | NSString * | 特效参数键名（`EFFECTOR_*`） |
| intensity | float      | 强度值（取值范围见常量定义） |

**示例：**

```objc
// 美颜（磨皮）开至 60%
[pub setEffectParameter:EFFECTOR_SMOOTHSKIN withIntensity:0.6];

// 亮度调至 1.2
[pub setEffectParameter:EFFECTOR_BRIGHTNESS withIntensity:1.2];
```

---

### setEffectStyleWithId:

设置滤镜风格。

```objc
- (void)setEffectStyleWithId:(NSInteger)sid;
```

**参数：**

| 参数 | 类型       | 说明              |
| ---- | ---------- | ----------------- |
| sid  | NSInteger  | 风格 ID（`EFFECTOR_STYLE_ID_*` 常量） |

**示例：**

```objc
[pub setEffectStyleWithId:EFFECTOR_STYLE_ID_ENHANCED]; // 增强滤镜
```

---

### start:

开始推流到指定 URL。

```objc
- (NSInteger)start:(NSString *)url;
```

**参数：**

| 参数 | 类型       | 说明             |
| ---- | ---------- | ---------------- |
| url  | NSString * | 推流目标 URL 地址 |

**返回值：** `NSInteger` 状态码（`0` 表示成功）。

**支持的协议：** `rtmp://`

**示例：**

```objc
NSInteger ret = [pub start:@"rtmp://live.example.com/publish/streamKey"];
if (ret != 0) {
    NSLog(@"推流启动失败: %ld", (long)ret);
}
```

---

### stop

停止推流。

```objc
- (NSInteger)stop;
```

**返回值：** `NSInteger` 状态码。

**示例：**

```objc
[pub stop];
```

---

### addOutput:

添加额外输出。可以是直播流地址或文件路径。

```objc
- (NSInteger)addOutput:(NSString *)url;
```

**参数：**

| 参数 | 类型       | 说明                                |
| ---- | ---------- | ----------------------------------- |
| url  | NSString * | 推流地址或文件路径（支持 `flv`、`mp4`、`ts`、`mkv`） |

**返回值：** `NSInteger` 状态码。

**示例：**

```objc
// 同时录制到本地文件
[pub addOutput:[NSTemporaryDirectory() stringByAppendingPathComponent:@"record.mp4"]];
```

---

### removeOutputs

移除全部额外输出。

```objc
- (NSInteger)removeOutputs;
```

**返回值：** `NSInteger` 状态码。

**示例：**

```objc
[pub removeOutputs];
```

---

### attachView:

附加 UIView 用于显示摄像头预览画面。视图应具有 `CAEAGLLayer` 层以支持 OpenGL ES 渲染。

```objc
- (void)attachView:(UIView *)view;
```

**参数：**

| 参数 | 类型     | 说明           |
| ---- | -------- | -------------- |
| view | UIView * | 用于预览的视图 |

**示例：**

```objc
[pub attachView:self.previewView];
```

---

### detachView

分离当前附加的预览视图。

```objc
- (void)detachView;
```

**示例：**

```objc
[pub detachView];
```

---

## 完整示例

```objc
#import <NodeMediaClient/NodePublisher.h>

@interface LivePushViewController () <NodePublisherDelegate>
@property (nonatomic, strong) NodePublisher *publisher;
@property (nonatomic, strong) UIView *previewView;
@end

@implementation LivePushViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // 初始化
    self.publisher = [[NodePublisher alloc] initWithLicense:@"your-license"];
    self.publisher.nodePublisherDelegate = self;
    self.publisher.logLevel = 1;
    
    // 配置编码参数
    [self.publisher setVideoParamWithCodec:NMC_CODEC_ID_H264
                                  profile:NMC_PROFILE_H264_MAIN
                                    width:720 height:1280
                                      fps:24 bitrate:1200000];
    
    [self.publisher setAudioParamWithCodec:NMC_CODEC_ID_AAC
                                   profile:NMC_PROFILE_AAC_LC
                                samplerate:44100 channels:1 bitrate:64000];
    
    // 开启硬件编码 & 降噪
    self.publisher.HWAccelEnable = YES;
    self.publisher.denoiseEnable = YES;
    self.publisher.keyFrameInterval = 2;
    
    // 美颜效果
    [self.publisher setEffectStyleWithId:EFFECTOR_STYLE_ID_ENHANCED];
    [self.publisher setEffectParameter:EFFECTOR_SMOOTHSKIN withIntensity:0.5];
    
    // 打开摄像头并预览
    [self.publisher openCamera:YES];
    [self.publisher attachView:self.previewView];
}

- (IBAction)didTapStart:(id)sender {
    [self.publisher start:@"rtmp://live.example.com/publish/streamKey"];
}

- (IBAction)didTapStop:(id)sender {
    [self.publisher stop];
}

- (IBAction)didTapSwitchCamera:(id)sender {
    [self.publisher switchCamera];
}

- (IBAction)didTapTorch:(id)sender {
    self.publisher.torchEnable = !self.publisher.torchEnable;
}

- (void)onEventCallback:(id)sender event:(int)event msg:(NSString *)msg {
    switch (event) {
        case 2000:
            NSLog(@"开始连接推流服务器");
            break;
        case 2001:
            NSLog(@"推流连接成功");
            break;
        case 2002:
            NSLog(@"连接失败: %@", msg);
            break;
        case 2003:
            NSLog(@"正在重连");
            break;
        case 2004:
            NSLog(@"推流结束");
            break;
        case 2005:
            NSLog(@"网络异常: %@", msg);
            break;
        case 2006:
            NSLog(@"连接超时: %@", msg);
            break;
        default:
            break;
    }
}

- (void)dealloc {
    [self.publisher stop];
    [self.publisher closeCamera];
    [self.publisher detachView];
}

@end
```
