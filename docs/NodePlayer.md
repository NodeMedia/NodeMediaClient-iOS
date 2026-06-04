# NodePlayer API 文档

NodePlayer 是 NodeMediaClient 框架的核心播放器类，支持 RTMP、RTSP、HTTP 等多种协议的直播与点播播放。

## 快速开始

```objc
// 初始化播放器
NodePlayer *player = [[NodePlayer alloc] initWithLicense:@"your-license"];

// 附加渲染视图
[player attachView:self.renderView];

// 开始播放
[player start:@"rtmp://example.com/live/stream"];
```

## 事件回调

通过 `NodePlayerDelegate` 协议接收播放器状态事件：

```objc
// 设置事件代理
player.nodePlayerDelegate = self;

// 实现代理方法
- (void)onEventCallback:(id)sender event:(int)event msg:(NSString *)msg {
    NSLog(@"Event: %d, Message: %@", event, msg);
    // 根据 event 值处理不同状态
}
```

`event` 取值说明：

### 播放相关事件

| Code | 名称     | 说明                       |
| ---- | -------- | -------------------------- |
| 1000 | 连接中   | 正在连接视频源             |
| 1001 | 连接成功 | 视频连接成功，开始播放     |
| 1002 | 连接失败 | 视频连接失败（自动重连中） |
| 1003 | 重连中   | 视频开始重新连接           |
| 1004 | 播放结束 | 视频播放正常结束           |
| 1005 | 网络异常 | 网络异常（自动重连中）     |
| 1006 | 连接超时 | 网络连接超时（自动重连中） |

### 缓冲相关事件

| Code | 名称       | 说明                                    |
| ---- | ---------- | --------------------------------------- |
| 1100 | 缓冲区空   | 播放缓冲区为空                          |
| 1101 | 缓冲中     | 播放缓冲区正在缓冲数据                  |
| 1102 | 缓冲完成   | 缓冲完成，开始播放                      |
| 1103 | 流统计信息 | 流统计信息（每秒回调一次）              |
| 1104 | 视频分辨率 | 解码后得到视频宽高（`msg` 格式为 `width x height`） |

---

## 属性参考

### nodePlayerDelegate

事件委托对象，用于接收播放器状态回调。

```objc
@property (nullable, nonatomic, weak) id<NodePlayerDelegate> nodePlayerDelegate;
```

### bufferTime

直播视频缓冲时长，单位毫秒。默认值 `1000`。设为 `0` 时不进行缓冲与音视频同步。

> **适用于直播场景**，点播场景通常不需要调整。

```objc
@property (nonatomic) NSInteger bufferTime;

player.bufferTime = 2000; // 缓冲 2 秒
```

### scaleMode

视频缩放模式：

| 值   | 模式     | 说明                           |
| ---- | -------- | ------------------------------ |
| 0    | 填充     | 拉伸填满视图，可能变形         |
| 1    | 等比缩放 | 保持比例，可能出现黑边         |
| 2    | 等比填充 | 保持比例，填满视图，可能裁剪   |

```objc
@property (nonatomic) NSInteger scaleMode;

player.scaleMode = 1; // 等比缩放
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

player.logLevel = 0; // 仅错误日志
```

### HWAccelEnable

开启硬件解码加速。部分设备或流格式可能不支持硬件解码。

```objc
@property (nonatomic) Boolean HWAccelEnable;

player.HWAccelEnable = YES;
```

### volume

播放音量，取值范围 `0.0` ~ `1.0`。

```objc
@property (nonatomic) float volume;

player.volume = 0.5; // 50% 音量
```

### cryptoKey

解密密钥，**16 位字符串**。用于播放加密流。

```objc
@property (nonatomic, copy) NSString *cryptoKey;

player.cryptoKey = @"abcdef1234567890";
```

### RTSPTransport

RTSP 传输协议设置，可选值如 `tcp`、`udp`。

```objc
@property (nonatomic, copy) NSString *RTSPTransport;

player.RTSPTransport = @"tcp"; // 强制 TCP 传输
```

### HTTPReferer

HTTP 播放请求的 Referer 头。

```objc
@property (nonatomic, copy) NSString *HTTPReferer;

player.HTTPReferer = @"https://example.com";
```

### HTTPUserAgent

HTTP 播放请求的 User-Agent 头。

```objc
@property (nonatomic, copy) NSString *HTTPUserAgent;

player.HTTPUserAgent = @"MyApp/1.0";
```

### isVod *(只读)*

当前视频是否为点播流。

```objc
@property (nonatomic, readonly) Boolean isVod;

if (player.isVod) {
    // 支持 seek 等点播操作
}
```

### isPause *(只读)*

当前视频是否处于暂停状态。

```objc
@property (nonatomic, readonly) Boolean isPause;
```

### isPlaying *(只读)*

当前视频是否正在播放。

```objc
@property (nonatomic, readonly) Boolean isPlaying;
```

### duration *(只读)*

点播视频总时长，单位毫秒。直播流返回 `0`。

```objc
@property (nonatomic, readonly) NSInteger duration;

NSInteger totalSeconds = player.duration / 1000;
```

### currentPosition *(只读)*

当前视频播放进度，单位毫秒。

```objc
@property (nonatomic, readonly) NSInteger currentPosition;
```

### bufferPosition *(只读)*

当前视频缓冲进度，单位毫秒。

```objc
@property (nonatomic, readonly) NSInteger bufferPosition;
```

---

## 方法参考

### initWithLicense:

使用许可证初始化播放器。

```objc
- (instancetype)initWithLicense:(NSString *)license;
```

**参数：**

| 参数      | 类型       | 说明               |
| --------- | ---------- | ------------------ |
| license   | NSString * | NodePlayer 许可证字符串 |

**返回值：** 已初始化的 `NodePlayer` 实例。

**示例：**

```objc
NodePlayer *player = [[NodePlayer alloc] initWithLicense:@"your-license-key"];
```

---

### attachView:

附加 UIView 用于渲染媒体内容。视图应具有 `CAEAGLLayer` 层以支持 OpenGL ES 渲染。

```objc
- (void)attachView:(UIView *)view;
```

**参数：**

| 参数 | 类型     | 说明           |
| ---- | -------- | -------------- |
| view | UIView * | 用于渲染的视图 |

**示例：**

```objc
[player attachView:self.videoContainerView];
```

---

### detachView

分离当前附加的渲染视图。

```objc
- (void)detachView;
```

**示例：**

```objc
[player detachView];
```

---

### start:

开始播放指定 URL 的媒体流。

```objc
- (NSInteger)start:(NSString *)url;
```

**参数：**

| 参数 | 类型       | 说明           |
| ---- | ---------- | -------------- |
| url  | NSString * | 媒体流 URL 地址 |

**返回值：** `NSInteger` 状态码（`0` 表示成功，非 `0` 表示失败）。

**支持的协议：** `rtmp://`、`rtsp://`、`http://`、`https://`

**示例：**

```objc
NSInteger ret = [player start:@"rtmp://live.example.com/stream"];
if (ret != 0) {
    NSLog(@"启动播放失败: %ld", (long)ret);
}
```

---

### stop

停止播放。

```objc
- (NSInteger)stop;
```

**返回值：** `NSInteger` 状态码。

**示例：**

```objc
[player stop];
```

---

### pause:

暂停或恢复播放。

```objc
- (NSInteger)pause:(Boolean)isPause;
```

**参数：**

| 参数     | 类型    | 说明                       |
| -------- | ------- | -------------------------- |
| isPause  | Boolean | `YES` 暂停，`NO` 恢复播放  |

**返回值：** `NSInteger` 状态码。

**示例：**

```objc
// 暂停
[player pause:YES];

// 恢复
[player pause:NO];
```

---

### seek:

跳转到指定播放位置（仅点播有效）。

```objc
- (NSInteger)seek:(NSUInteger)pts;
```

**参数：**

| 参数 | 类型       | 说明               |
| ---- | ---------- | ------------------ |
| pts  | NSUInteger | 目标时间戳，单位毫秒 |

**返回值：** `NSInteger` 状态码。

**示例：**

```objc
if (player.isVod) {
    [player seek:60000]; // 跳转到 60 秒处
}
```

---

### screenshot:

截图并保存为 PNG 文件。

```objc
- (NSInteger)screenshot:(NSString *)filename;
```

**参数：**

| 参数     | 类型       | 说明             |
| -------- | ---------- | ---------------- |
| filename | NSString * | 截图保存的文件路径 |

**返回值：** `NSInteger` 状态码。

**示例：**

```objc
NSString *path = [NSTemporaryDirectory() stringByAppendingPathComponent:@"snapshot.png"];
[player screenshot:path];
```

---

### startRecord:

开始录制当前播放的媒体流到文件。

```objc
- (NSInteger)startRecord:(NSString *)filename;
```

**参数：**

| 参数     | 类型       | 说明             |
| -------- | ---------- | ---------------- |
| filename | NSString * | 录制输出的文件路径 |

**返回值：** `NSInteger` 状态码。

**示例：**

```objc
NSString *path = [NSTemporaryDirectory() stringByAppendingPathComponent:@"recorded.mp4"];
[player startRecord:path];
```

---

### stopRecord

停止录制。

```objc
- (NSInteger)stopRecord;
```

**返回值：** `NSInteger` 状态码。

**示例：**

```objc
[player stopRecord];
```

---

## 完整示例

```objc
#import <NodeMediaClient/NodePlayer.h>

@interface MyViewController () <NodePlayerDelegate>
@property (nonatomic, strong) NodePlayer *player;
@property (nonatomic, strong) UIView *videoView;
@end

@implementation MyViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // 初始化播放器
    self.player = [[NodePlayer alloc] initWithLicense:@"your-license"];
    self.player.nodePlayerDelegate = self;
    
    // 配置
    self.player.bufferTime = 1500;          // 1.5 秒缓冲
    self.player.scaleMode = 1;              // 等比缩放
    self.player.HWAccelEnable = YES;        // 硬件解码
    self.player.logLevel = 1;               // info 级别日志
    
    // 附加渲染视图
    [self.player attachView:self.videoView];
    
    // 开始播放
    [self.player start:@"rtmp://live.example.com/stream"];
}

- (void)onEventCallback:(id)sender event:(int)event msg:(NSString *)msg {
    switch (event) {
        case 1001:
            NSLog(@"连接成功");
            break;
        case 1102:
            NSLog(@"缓冲完成，开始播放");
            break;
        case 1002:
            NSLog(@"连接失败: %@", msg);
            break;
        case 1005:
            NSLog(@"网络异常: %@", msg);
            break;
        default:
            break;
    }
}

- (IBAction)didTapPause:(id)sender {
    [self.player pause:YES];
}

- (IBAction)didTapResume:(id)sender {
    [self.player pause:NO];
}

- (IBAction)didTapStop:(id)sender {
    [self.player stop];
}

- (void)dealloc {
    [self.player detachView];
    [self.player stop];
}

@end
```
