//
//  AlicloudAPMProvider.h
//  AlicloudAPM
//
//  Created by sky on 2019/9/19.
//

#import <Foundation/Foundation.h>

#define ALICLOUDAPM_VERSION @"1.1.1"

NS_ASSUME_NONNULL_BEGIN

@interface AlicloudAPMProvider : NSObject

/*!
 * @brief 性能监控初始化接口（自动读取appKey、appSecret）
 * @details 性能监控初始化接口，appKey、appSecret会从AliyunEmasServices-Info.plist自动读取
 * @param appVersion app版本，会上报
 * @param channel 渠道标记，自定义，会上报
 * @param nick 昵称，自定义，会上报
 */
- (void)autoInitWithAppVersion:(NSString *)appVersion
                       channel:(NSString *)channel
                          nick:(NSString *)nick;

/*!
 * @brief 性能监控初始化接口
 * @details 性能监控初始化接口
 * @param appKey appKey,可从控制台或AliyunEmasServices-Info.plist获取
 * @param secret appSecret,可从控制台或AliyunEmasServices-Info.plist获取
 * @param appVersion app版本
 * @param channel 渠道标记，自定义
 * @param nick 昵称，自定义，会上报
 */
- (void)initWithAppKey:(NSString *)appKey
                secret:(NSString *)secret
            appVersion:(NSString *)appVersion
               channel:(NSString *)channel
                  nick:(NSString *)nick;

/*!
 * @brief 性能监控初始化接口
 * @details 性能监控初始化接口
 * @param appKey appKey,可从控制台或AliyunEmasServices-Info.plist获取
 * @param secret appSecret,可从控制台或AliyunEmasServices-Info.plist获取
 * @param rsaSecret rsaSecret。可从AliyunEmasServices-Info.plist获取
 * @param appVersion app版本
 * @param channel 渠道标记，自定义
 * @param nick 昵称，自定义，会上报
 */
- (void)initWithAppKey:(NSString *)appKey
                secret:(NSString *)secret
         rsaSecret:(NSString *)rsaSecret
            appVersion:(NSString *)appVersion
               channel:(NSString *)channel
                  nick:(NSString *)nick;
@end

NS_ASSUME_NONNULL_END
