//
//  AlicloudTlogProvider.h
//  AliHATLog
//
//  Created by sky on 2019/9/17.
//

#import <Foundation/Foundation.h>
#import <TRemoteDebugger/TRDConstDefine.h>

#define ALICLOUDTLOG_VERSION @"1.0.1.1"

NS_ASSUME_NONNULL_BEGIN

@interface AlicloudTlogProvider : NSObject

/*!
 * @brief 远程日志初始化接口（自动读取appKey、appSecret）
 * @details 远程日志初始化接口，appKey、appSecret会从AliyunEmasServices-Info.plist自动读取
 * @param appVersion app版本，会上报
 * @param channel 渠道标记，自定义，会上报
 * @param nick 昵称，自定义，会上报
 */
- (void)autoInitWithAppVersion:(NSString *)appVersion
                       channel:(NSString *)channel
                          nick:(NSString *)nick;

/*!
 * @brief 远程日志初始化接口
 * @details 远程日志初始化接口
 * @param appKey appKey,可从控制台或AliyunEmasServices-Info.plist获取
 * @param secret appSecret,可从控制台或AliyunEmasServices-Info.plist获取
 * @param tlogRsaSecret tlogRsaSecret,用于日志加密。可从AliyunEmasServices-Info.plist获取
 * @param appVersion app版本
 * @param channel 渠道标记，自定义
 * @param nick 昵称，自定义，会上报
 */
- (void)initWithAppKey:(NSString *)appKey
                secret:(NSString *)secret
         tlogRsaSecret:(NSString *)tlogRsaSecret
            appVersion:(NSString *)appVersion
               channel:(NSString *)channel
                  nick:(NSString *)nick;

/*!
 * @brief 主动上报缓存的日志信息接口
 * @details 主动上报缓存的日志信息接口
 * @param comment  主动上报备注
 */
+ (void)uploadTLog:(NSString *)comment;


@end

NS_ASSUME_NONNULL_END
