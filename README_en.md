# NodeMediaClient
A simple, fast, free live streaming SDK.

# Cocoapods install
## create Podfile
```ruby
# Uncomment the next line to define a global platform for your project
platform :ios, '9.0'

target 'QLive' do
  # Uncomment the next line if you're using Swift or would like to use dynamic frameworks
  use_modular_headers!

  # Pods for QLive
  pod 'NodeMediaClient', '~> 2.9.4' 
end
```
## install
```shell
pod install
```

# Simple usage

## NodePlayer
```
#import <NodeMediaClient/NodeMediaClient.h>
......

@property (strong,nonatomic) NodePlayer *np;

......
// start play live stram
    _np = [[NodePlayer alloc] init];
    [_np setPlayerView:self.view];
    [_np setInputUrl:@"rtmp://192.168.0.10/live/stream"];
    [_np start];
    
......

// stop play live stream
    [_np stop];
```

## NodePublisher

**Please confirm that the description of the 'Privacy - Microphone Usage Description' and the 'Privacy - Camera Usage Description' is added in info.plist .**

```
#import <NodeMediaClient/NodeMediaClient.h>

......

@property (strong, nonatomic) NodePublisher *np;

......
// start preview and push live stream
    _np = [[NodePublisher alloc] init];
    [_np setCameraPreview:self.view cameraId:CAMERA_FRONT frontMirror:YES];
    [_np setAudioParamBitrate:32000 profile:AUDIO_PROFILE_HEAAC];
    [_np setVideoParamPreset:VIDEO_PPRESET_16X9_360 fps:15 bitrate:500000 profile:VIDEO_PROFILE_MAIN frontMirror:NO];
    [_np setOutputUrl:@"rtmp://192.168.0.10/live/stream"];
    [_np startPreview];
    [_np start];

......


// stop preview and push live stream
    [_np stopPreview];
    [_np stop];
```
# Features
## NodePlayer

## NodePublisher

## NodeStreamer

# Premium version
- Hardware acceleration video Decoder & Encoder
- Microphone denoise
- Smooth beautiful skin
- rtmp/http-flv video and audio crypto

Please contact business service email : service@nodemedia.cn
