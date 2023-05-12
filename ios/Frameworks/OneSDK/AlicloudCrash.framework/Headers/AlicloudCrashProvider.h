//
//  AlicloudCrashProvider.h
//  AlicloudCrash
//
//  Created by sky on 2019/10/7.
//  Copyright © 2019 aliyun. All rights reserved.
//

#import <Foundation/Foundation.h>

#define ALICLOUDCRASH_VERSION @"1.2.0"

NS_ASSUME_NONNULL_BEGIN

@interface AlicloudCrashProvider : NSObject

/*!
 * @brief 崩溃分析始化接口（自动读取appKey、appSecret）
 * @details 崩溃分析初始化接口，appKey、appSecret会从AliyunEmasServices-Info.plist自动读取
 * @param appVersion app版本，会上报
 * @param channel 渠道标记，自定义，会上报
 * @param nick 昵称，自定义，会上报
 */
- (void)autoInitWithAppVersion:(NSString *)appVersion
                       channel:(NSString *)channel
                          nick:(NSString *)nick;

/*!
 * @brief 崩溃分析初始化接口
 * @details 崩溃分析初始化接口
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
* @brief 设置用户信息
* @details 设置用户信息,崩溃时带上。总数据量要求小于10Kb
* @param key key
* @param value value
*/
+ (void)configCustomInfoWithKey:(NSString *)key value:(NSString *)value;

/*!
* @brief 设置崩溃回调信息
* @details 设置崩溃回调信息
* @param crashReporterAdditionalInformationCallBack 返回字典不超过10kb，不要有耗时操作，只支持字符串
*/
+ (void)setCrashCallBack:(NSDictionary * (^)(NSString * type))crashReporterAdditionalInformationCallBack;

/*!
* @brief 用户自定义错误上报
* @details 用户自定义错误上报
* @param error 用户把错误封装为标准NSError
*/
+ (void)reportCustomError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
