//
//  JsenNetworkingManager.h
//  JsenKit
//
//  Created by Wangxuesen on 2016/11/14.
//  Copyright © 2016年 WangXuesen. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JsenNetworkingManagerTransmitDelegate.h"
#import "JsenNetworkingConfig.h"
#import "JsenNetworkingManagerTransmit.h"

NS_ASSUME_NONNULL_BEGIN

/**
 网络请求成功后的回调

 @param response JsenNetworkingSuccessResponse
 */
typedef void(^JsenNetworkingSuccess) (JsenNetworkingSuccessResponse *response);

/**
 网络请求失败后的回调

 @param response JsenNetworkingFailedResponse
 */
typedef void(^JsenNetworkingFailed) (JsenNetworkingFailedResponse *response);

/**
 网络请求完毕后的回调
 */
typedef void(^JsenNetworkingFinished) ();

/**
 网络请求进度的回调，实时回调

 @param uploadProgress NSProgress 请求进度
 */
typedef void(^JsenNetworkingProgress) (NSProgress *uploadProgress);



/******************************************************************************
                        华   丽   的   分   割   线
 ******************************************************************************/
@interface JsenNetworkingManager : NSObject


/**
 网络请求成功回调
 */
@property (nonatomic, strong) JsenNetworkingSuccess success;

/**
 网络请求失败的回调
 */
@property (nonatomic, strong) JsenNetworkingFailed failed;

/**
 网络请求完成的回调
 */
@property (nonatomic, strong) JsenNetworkingFinished finished;

/**
 请求进度回调
 */
@property (nonatomic, strong) JsenNetworkingProgress progress;

/**
 代理
 */
@property (nonatomic, weak) id<JsenNetworkingManagerTransmitDelegate> delegate;

/**
 初始化请求mgr

 @return self的实例
 */
+ (instancetype _Nonnull)manager;


/**
 post请求 block模式
 apiKey 为url的路径，在JsenNetworkingConfig 中进行必要的配置后，请求会拼接config中的请求头部，公共参数等
 如果设置了apikey对应的超时时间也会对应的应用。
 
 @param apiKey apiKey
 @param parameters 请求参数
 @param progress 请求进度回调
 @param success 请求成功回调
 @param failed 请求失败回调
 @param finished 请求完毕回调
 */
- (void)post:(NSString *)apiKey
  parameters:(NSDictionary * __nullable)parameters
    progress:(JsenNetworkingProgress __nullable)progress
     success:(JsenNetworkingSuccess __nullable)success
      failed:(JsenNetworkingFailed __nullable)failed
    finished:(JsenNetworkingFinished __nullable)finished;

/**
 post请求 代理模式
 ⚠️：在使用代理模式时不能在JsenNetworkingManagerTransmit单例中获取到代理回调。因为manager的代理只能有一个

 apiKey 为url的路径，在JsenNetworkingConfig 中进行必要的配置后，请求会拼接config中的请求头部，公共参数等
 如果设置了apikey对应的超时时间也会对应的应用。
 
 @param apiKey apiKey
 @param parameters 请求参数
 */
- (void)post:(NSString *)apiKey
  parameters:(NSDictionary * __nullable)parameters
    delegate:(id<JsenNetworkingManagerTransmitDelegate>)delegate;


/**
 get请求 block模式
 apiKey 为url的路径，在JsenNetworkingConfig 中进行必要的配置后，请求会拼接config中的请求头部，公共参数等
 如果设置了apikey对应的超时时间也会对应的应用。
 
 @param apiKey apiKey
 @param parameters 请求参数
 @param progress 请求进度回调
 @param success 请求成功回调
 @param failed 请求失败回调
 @param finished 请求完毕回调
 */
- (void)get:(NSString *)apiKey
 parameters:(NSDictionary * __nullable)parameters
   progress:(JsenNetworkingProgress __nullable)progress
    success:(JsenNetworkingSuccess __nullable)success
     failed:(JsenNetworkingFailed __nullable)failed
   finished:(JsenNetworkingFinished __nullable)finished;

/**
 get请求 代理模式
 ⚠️：在使用代理模式时不能在JsenNetworkingManagerTransmit单例中获取到代理回调。因为manager的代理只能有一个
 
 apiKey 为url的路径，在JsenNetworkingConfig 中进行必要的配置后，请求会拼接config中的请求头部，公共参数等
 如果设置了apikey对应的超时时间也会对应的应用。
 
 @param apiKey apiKey
 @param parameters 请求参数
 */
- (void)get:(NSString *)apiKey
  parameters:(NSDictionary * __nullable)parameters
    delegate:(id<JsenNetworkingManagerTransmitDelegate>)delegate;

/**
 上传单个data block模式
 比如一张图片，一个文件

 @param apiKey apiKey
 @param name 服务端取数据时的key
 @param data 文件的NSData类型
 @param fileName 文件名字
 @param mimeType 文件类型 eg：image/jpeg
 @param parameters 其他参数
 @param progress 请求进度回调
 @param success 请求成功回调
 @param failed 请求失败回调
 @param finished 请求完毕回调
 */
- (void)uploadTaskWithMultiPartApiKey:(NSString *)apiKey
                                 name:(NSString *)name
                                 data:(NSData *)data
                             fileName:(NSString *)fileName
                             mimeType:(NSString *)mimeType
                           parameters:(NSDictionary * __nullable)parameters
                             progress:(JsenNetworkingProgress __nullable)progress
                              success:(JsenNetworkingSuccess __nullable)success
                               failed:(JsenNetworkingFailed __nullable)failed
                             finished:(JsenNetworkingFinished __nullable)finished;
/**
 上传单个data 代理模式
 ⚠️：在使用代理模式时不能在JsenNetworkingManagerTransmit单例中获取到代理回调。因为manager的代理只能有一个

 比如一张图片，一个文件
 
 @param apiKey apiKey
 @param name 服务端取数据时的key
 @param data 文件的NSData类型
 @param fileName 文件名字
 @param mimeType 文件类型 eg：image/jpeg
 @param parameters 其他参数
 @param delegate JsenNetworkingManagerTransmitDelegate 代理
 */

- (void)uploadTaskWithMultiPartApiKey:(NSString *)apiKey
                                 name:(NSString *)name
                                 data:(NSData *)data
                             fileName:(NSString *)fileName
                             mimeType:(NSString *)mimeType
                           parameters:(NSDictionary * __nullable)parameters
                             delegate:(id<JsenNetworkingManagerTransmitDelegate>)delegate;


/**
 多文件上传 block模式（需要服务端支持一个上传接口同时接收多个文件）
 eg：多张图片
 
 注意：文件data数组中的对象必须和filenameArray中文件名的字符串一一对应，

 @param apiKey apiKey
 @param name 服务端取数据时的key
 @param dataArray 文件的NSData类型 数组
 @param fileNameArray 文件名字 数组
 @param mimeType 文件类型 eg：image/jpeg
 @param parameters 其他参数
 @param progress 请求进度回调
 @param success 请求成功回调
 @param failed 请求失败回调
 @param finished 请求完毕回调
 */
- (void)uploadTaskWithMultiPartApiKey:(NSString *)apiKey
                                 name:(NSString *)name
                            dataArray:(NSArray<NSData*> *)dataArray
                        fileNameArray:(NSArray<NSString*> *)fileNameArray
                             mimeType:(NSString *)mimeType
                           parameters:(NSDictionary * __nullable)parameters
                             progress:(JsenNetworkingProgress __nullable)progress
                              success:(JsenNetworkingSuccess __nullable)success
                               failed:(JsenNetworkingFailed __nullable)failed
                             finished:(JsenNetworkingFinished __nullable)finished;

/**
 多文件上传 代理模式（需要服务端支持一个上传接口同时接收多个文件）
 ⚠️：在使用代理模式时不能在JsenNetworkingManagerTransmit单例中获取到代理回调。因为manager的代理只能有一个

 eg：多张图片
 
 注意：文件data数组中的对象必须和filenameArray中文件名的字符串一一对应，
 
 @param apiKey apiKey
 @param name 服务端取数据时的key
 @param dataArray 文件的NSData类型 数组
 @param fileNameArray 文件名字 数组
 @param mimeType 文件类型 eg：image/jpeg
 @param parameters 其他参数
 @param delegate JsenNetworkingManagerTransmitDelegate 代理
 */
- (void)uploadTaskWithMultiPartApiKey:(NSString *)apiKey
                                 name:(NSString *)name
                            dataArray:(NSArray<NSData*> *)dataArray
                        fileNameArray:(NSArray<NSString*> *)fileNameArray
                             mimeType:(NSString *)mimeType
                           parameters:(NSDictionary * __nullable)parameters
                             delegate:(id<JsenNetworkingManagerTransmitDelegate>)delegate;

@end
NS_ASSUME_NONNULL_END