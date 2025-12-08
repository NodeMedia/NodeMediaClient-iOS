//
//  NodePublisher.h
//  NodeMediaClient
//
//  Created by Mingliang Chen on 2025/11/16.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

#define NMC_CODEC_ID_H264                   27
#define NMC_CODEC_ID_H265                   173
#define NMC_CODEC_ID_AAC                    86018
#define NMC_CODEC_ID_OPUS                   86076
#define NMC_CODEC_ID_PCMA                   65543
#define NMC_CODEC_ID_PCMU                   65542

#define NMC_PROFILE_AUTO                    0
#define NMC_PROFILE_H264_BASELINE           66
#define NMC_PROFILE_H264_MAIN               77
#define NMC_PROFILE_H264_HIGH               100
#define NMC_PROFILE_H265_MAIN               1
#define NMC_PROFILE_AAC_LC                  1
#define NMC_PROFILE_AAC_HE                  4
#define NMC_PROFILE_AAC_HE_V2               28

#define VIDEO_ORIENTATION_PORTRAIT          1
#define VIDEO_ORIENTATION_LANDSCAPE_RIGHT   3
#define VIDEO_ORIENTATION_LANDSCAPE_LEFT    4

#define FLAG_AF                             1
#define FLAG_AE                             2
#define FLAG_AWB                            4

#define NMC_DEVICE_TYPE_WideAngleCamera     0 // 广角
#define NMC_DEVICE_TYPE_TelephotoCamera     1 // 长焦
#define NMC_DEVICE_TYPE_UltraWideCamera     2 // 超广角
#define NMC_DEVICE_TYPE_DualCamera          3 // 双摄
#define NMC_DEVICE_TYPE_TripleCamera        4 // 三摄

#define EFFECTOR_BRIGHTNESS                 @"brightness"   // 该参数 0.0f -- 2.0f, 默认是 1.0f
#define EFFECTOR_CONTRAST                   @"contrast"     // 该参数 0.0f -- 2.0f, 默认是 1.0f
#define EFFECTOR_SATURATION                 @"saturation"   // 该参数 0.0f -- 2.0f, 默认是 1.0f
#define EFFECTOR_SHARPEN                    @"sharpen"      // 该参数 0.0f -- 1.0f
#define EFFECTOR_SMOOTHSKIN                 @"smoothskin"   // 该参数 0.0f -- 1.0f
#define EFFECTOR_STYLE                      @"style"        // 该参数 0.0f -- 1.0f

#define EFFECTOR_STYLE_ID_ORIGINAL          0
#define EFFECTOR_STYLE_ID_ENHANCED          1
#define EFFECTOR_STYLE_ID_FAIRSKIN          2
#define EFFECTOR_STYLE_ID_COOL              3
#define EFFECTOR_STYLE_ID_FILM              4
#define EFFECTOR_STYLE_ID_BOOST             5

#define NMC_EXPORT __attribute__((visibility("default")))

@protocol NodePublisherDelegate

- (void)onEventCallback:(id)sender event:(int)event msg:(NSString *)msg;

@end

NMC_EXPORT
@interface NodePublisher : NSObject

///事件委托
@property (nonatomic, weak) id <NodePublisherDelegate> nodePublisherDelegate;

/// 日志等级 0-error，1-info，2-debug
@property (nonatomic) NSInteger logLevel;

/// 是否开启硬件加速编码
@property (nonatomic) Boolean HWAccelEnable;

/// 是否开启背景音降噪
@property (nonatomic) Boolean denoiseEnable;

/// 是否使用扩展FLV ID方式进行编码推流
@property (nonatomic) Boolean extendedFlvId;

/// 音视频内容加密密码，16字节字符串
@property (nonatomic, copy) NSString *cryptoKey;

/// 预览前置摄像头画面是否镜像
@property (nonatomic) Boolean cameraFrontMirror;

/// 视频关键帧间隔，单位秒
@property (nonatomic) NSInteger keyFrameInterval;

/// 视频方向
@property (nonatomic) NSInteger videoOrientation;

- (instancetype)initWithLicense:(NSString *)license;

///打开摄像头，是否是前置打开
- (NSInteger)openCamera:(Boolean)frontCamera;

///打开指定类型摄像头，是否是前置打开
- (NSInteger)openCameraDevice:(NSInteger)deviceType withFront:(Boolean)frontCamera;

///关闭摄像头
- (NSInteger)closeCamera;

///切换摄像头
- (NSInteger)switchCamera;

/// 开启闪光灯补光
- (void)enableTorch:(Boolean)enable;

/// 设置缩放, 0.0-1.0
- (void)setRoomRatio:(float)ratio;

/// 设置中心点自动对焦曝光白平衡
- (void)startFocusAndMeteringCenter;

/// 设置自动对焦曝光白平衡
- (void)startFocusAndMetering:(nullable CGPoint*)point withFlags:(NSInteger)flags;

///设置音频编码参数
- (void)setAudioParamWithCodec:(NSInteger)c profile:(NSInteger)p samplerate:(NSInteger)s channels:(NSInteger)ch bitrate:(NSInteger)b;

///设置视频编码参数
- (void)setVideoParamWithCodec:(NSInteger)c profile:(NSInteger)p width:(NSInteger)w height:(NSInteger)h fps:(NSInteger)f bitrate:(NSInteger)b;

/// 设置特效参数的强度
- (void)setEffectParameter:(NSString *)parameter withIntensity:(float)intensity;

/// 设置特性风格id
- (void)setEffectStyleWithId:(NSInteger)sid;

///开始推送视频流
- (NSInteger)start:(NSString *)url;

///停止推送视频流
- (NSInteger)stop;

///添加额外输出，可以是直播流地址，也可以是全路径的文件，支持flv,mp4,ts,mkv格式
- (NSInteger)addOutput:(NSString *)url;

///移除全部额外输出
- (NSInteger)removeOutputs;

///附加到视图
- (void)attachView:(UIView *)view;

///从视图移除
- (void)detachView;



@end

NS_ASSUME_NONNULL_END
