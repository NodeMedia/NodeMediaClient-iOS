## 简介
NodePlayer类用于视频播放

## 方法
### - (id)initWithLicense:(NSString *)license;
以注册码初始化播放器
``` objc
#import <NodeMediaClient/NodeMediaClient.h>

@interface PlayViewController () <NodePlayerDelegate>
@property (nonatomic, strong) NodePlayer *np;
@end

@implementation PlayViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    _np = [[NodePlayer alloc] initWithLicense:@"your license string"];
}
```

### - (void)attachView:(UIView *)view;
附加到视图
``` objc
- (void)viewDidLoad {
    …………
    [_np attachView:self.view];
}
```

### - (void)detachView;
从视图移除

``` objc
-(void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];

    [_np detachView];
}
```

### - (int)start:(NSString *)url;
开始播放视频流，传入rtmp http rtsp hls流地址
``` objc
- (IBAction)startAction:(id)sender {
    [_np start:@"rtmp://192.168.0.2/live/sony_4k_264"];
}
```

### - (int)stop;
停止播放视频流
``` objc
- (IBAction)stopAction:(id)sender {
    [_np stop];
}
```

### - (int)pause:(Boolean)isPause;
暂停播放点播视频流
``` objc
- (IBAction)pauseAction:(id)sender {
    [_np pause:YES];
}
```

### - (int)seek:(NSUInteger)pts;
点播视频时移到时间点
``` objc
- (IBAction)seekAction:(id)sender {
    [_np pause:YES];
}
```

### - (int)screenshot:(NSString *)filename;
视频截图
``` objc
- (IBAction)screenshotAction:(id)sender {
    [_np screenshot:filename];
}
```

### - (int)startRecord:(NSString *)filename;
开始录制
``` objc
- (IBAction)startRecordAction:(id)sender {
    [_np startRecord:filename];
}
```

### - (int)stopRecord;
停止录制
``` objc
- (IBAction)stopRecordAction:(id)sender {
    [_np stopRecord];
}
```

## 属性

### @property (nullable, nonatomic, weak) id<NodePlayerDelegate> nodePlayerDelegate;
事件委托
``` obj-c
#import <NodeMediaClient/NodeMediaClient.h>

@interface PlayViewController () <NodePlayerDelegate>
@property (nonatomic, strong) NodePlayer *np;
@end
- (void)viewDidLoad {
	……
    [_np setNodePlayerDelegate:self];
}
```

``` objc
- (void)onEventCallback:(id _Nonnull)sender event:(int)event msg:(NSString * _Nonnull)msg {
//    NSLog(@"NodePlayerView on Event:%d Message:%@\n",event,msg);
}
```

### @property (nonatomic) NSUInteger bufferTime;
直播视频缓冲时长，单位毫秒，默认1000，当设为0时不进行缓冲与音视频同步
``` objc
    [_np setBufferTime:1000];
```

### @property (nonatomic) NSUInteger scaleMode;
视频缩放模式，0-填充，1-等比缩放，2-等比填充三种
``` objc
[_np setScaleMode:1];
```

### @property (nonatomic) NSUInteger logLevel;
日志等级 0-error，1-info，2-debug
``` objc
[_np setLogLevel:2];
```

### @property (nonatomic) Boolean HWAccelEnable;
开启硬件极速
``` objc
[_np setHWAccelEnable:YES];
```

### @property (nonatomic) float volume;
播放音量  0.0 ~ 1.0
``` objc
[_np setVolume:0.5];
```

### @property (nonatomic, copy) NSString *cryptoKey;
解密密钥，16位字符串
```objc
[_np setCryptoKey:@"qwerty234567890"];
```

### @property (nonatomic, copy) NSString *RTSPTransport;
 RTSP 传输协议
```objc
[_np setRTSPTransport:@"tcp"];
```

### @property (nonatomic, copy) NSString *RTMPSwfUrl;
 RTMP Swf Url
```objc
[_np setRTMPSwfUrl:@"http://rtmpswfurl.com"];
```

### @property (nonatomic, copy) NSString *RTMPPageUrl;
 RTMP Page Url
```objc
[_np setRTMPPageUrl:@"rtmppageurl.com"];
```

### @property (nonatomic, copy) NSString *HTTPReferer;
 HTTP Referer
```objc
[_np setHTTPReferer:@"http://http_referer.com"];
```

### @property (nonatomic, copy) NSString *HTTPUserAgent;
 HTTP User Agent
```objc
    [_np setHTTPUserAgent:@"Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:47.0) Gecko/20100101 Firefox/47.0"];
```

### @property (nonatomic, readonly) Boolean isVod;
 当前视频是否是点播流
```objc
[_np isVod];
```

### @property (nonatomic, readonly) Boolean isPause;
 当前视频是否暂停
```objc
[_np isPause];
```

### @property (nonatomic, readonly) Boolean isPlaying;
 当前视频是否正在播放
```objc
[_np isPlaying];
```

### @property (nonatomic, readonly) NSUInteger duration;
 点播视频总时长，单位毫秒
```objc
[_np duration];
```


### @property (nonatomic, readonly) NSUInteger currentPosition;
 当前视频播放点，单位毫秒
```objc
[_np currentPosition];
```

### @property (nonatomic, readonly) NSUInteger bufferPosition;
 当前视频缓冲点，单位毫秒
```objc
[_np bufferPosition];
```

## 事件
### 1000
正在连接视频

### 1001
视频连接成功

### 1002
视频连接失败, 会进行自动重连.

### 1003
视频开始重连

### 1004
视频播放结束

### 1005
视频播放中网络异常, 会进行自动重连.

### 1006
网络连接超时, 会进行自动重连.

### 1100
播放缓冲区为空

### 1101
播放缓冲区正在缓冲数据

### 1102
播放缓冲区达到bufferTime设定值,开始播放

### 1103
json 字符串的流统计，开始播放后每秒回调一次
{"abps":%d, "afps":%d, "abuf":%d, "vbps":%d, "vfps":%d, "vbuf":%d}

### 1104
解码后得到视频高宽, 格式为 width x height
