//
//  NodePlayer.h
//  NodeMediaClient
//
//  Created by Mingliang Chen on 2025/11/16.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define NMC_EXPORT __attribute__((visibility("default")))

NS_ASSUME_NONNULL_BEGIN

@protocol NodePlayerDelegate

- (void)onEventCallback:(id)sender event:(int)event msg:(NSString *)msg;

@end

NMC_EXPORT
@interface NodePlayer : NSObject

///事件委托
@property (nullable, nonatomic, weak) id<NodePlayerDelegate> nodePlayerDelegate;

///直播视频缓冲时长，单位毫秒，默认1000，当设为0时不进行缓冲与音视频同步
@property (nonatomic) NSInteger bufferTime;

///视频缩放模式，0-填充，1-等比缩放，2-等比填充三种
@property (nonatomic) NSInteger scaleMode;

///日志等级 0-error，1-info，2-debug
@property (nonatomic) NSInteger logLevel;

///开启硬件极速
@property (nonatomic) Boolean HWAccelEnable;

///播放音量  0.0 ~ 1.0
@property (nonatomic) float volume;

///解密密钥，16位字符串
@property (nonatomic, copy) NSString *cryptoKey;

/// RTSP 传输协议
@property (nonatomic, copy) NSString *RTSPTransport;

/// HTTP Referer
@property (nonatomic, copy) NSString *HTTPReferer;

/// HTTP User Agent
@property (nonatomic, copy) NSString *HTTPUserAgent;

/// 当前视频是否是点播流
@property (nonatomic, readonly) Boolean isVod;

/// 当前视频是否暂停
@property (nonatomic, readonly) Boolean isPause;

/// 当前视频是否正在播放
@property (nonatomic, readonly) Boolean isPlaying;

/// 点播视频总时长，单位毫秒
@property (nonatomic, readonly) NSInteger duration;

/// 当前视频播放点，单位毫秒
@property (nonatomic, readonly) NSInteger currentPosition;

/// 当前视频缓冲点，单位毫秒
@property (nonatomic, readonly) NSInteger bufferPosition;

/**
 * 使用许可证初始化 NodePlayer
 * @param license NodePlayer 的许可证字符串
 * @return 已初始化的 NodePlayer 实例
 */
- (instancetype)initWithLicense:(NSString *)license;

/**
 * 附加 UIView 用于渲染媒体内容
 * UIView 应具有 CAEAGLLayer 层用于 OpenGL ES 渲染
 * @param view 用于渲染的 UIView
 */
- (void)attachView:(UIView *)view;

/**
 * 分离当前附加的 UIView
 */
- (void)detachView;

/**
 * 开始播放
 * @param url 要播放的媒体 URL
 * @return int 状态码
 */
- (NSInteger)start:(NSString *)url;

/**
 * 停止播放
 * @return int 状态码
 */
- (NSInteger)stop;

/**
 * 暂停播放
 * @return int 状态码
 */
- (NSInteger)pause:(Boolean)isPause;

/**
 * 跳转到指定位置
 * @param pts 要跳转到的显示时间戳
 * @return int 状态码
 */
- (NSInteger)seek:(NSUInteger)pts;

/**
 * 截图并保存到指定文件名
 * @param filename 保存截图的文件名
 * @return int 状态码
 */
- (NSInteger)screenshot:(NSString *)filename;

/**
 * 开始录制到指定文件名
 * @param filename 保存录制的文件名
 * @return int 状态码
 */
- (NSInteger)startRecord:(NSString *)filename;

/**
 * 停止录制
 * @return int 状态码
 */
- (NSInteger)stopRecord;

@end

NS_ASSUME_NONNULL_END
