//
//  TBCrashReportMonitor.h
//  CrashReporterDemo
//
//  Created by 贾复 on 15/3/16.
//  Copyright (c) 2015年 Taobao lnc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <mach/mach_types.h>

@protocol CrashReporterMonitorDelegate <NSObject>

@optional
- (void)crashReporterLog:(id)loger;

/**
 *  数据上报额外信息提供
 *
 *  @return 额外信息
 */
- (NSDictionary *)crashReporterAdditionalInformation;

// thread_t
- (NSDictionary *)crashReporterAdditionalInformationWithUContext:(void *)ucontext;

- (NSDictionary *)crashReporterAdditionalInformationWithThread:(thread_t)thread ucontext:(void *)ucontext;

/**
 * crash callback with thread, error ptr and ucontext
 * @param errorPtr usually fault address
 */
- (NSDictionary *)crashReporterAdditionalInformationWithThread:(thread_t)thread ucontext:(void *)ucontext errorPtr:(uintptr_t)errorPtr ;

@end


@interface TBCrashReporterMonitor : NSObject

+ (instancetype)sharedMonitor;

/**
 *  额外信息拉取，业务方不要调用
 *
 *  @return 额外信息
 */
- (NSDictionary *)crashReportCallBackInfo:(NSString*)viewControllerInfo Count:(int)count UploadFlag:(int)flag ucontext:(void *)ucontext thread:(thread_t)thread errorPtr:(uintptr_t)errorPtr;

/**
 *  注册monitor，monitor实现CrashReporterMonitorDelegate里的方法提供额外信息
 *
 *  @param monitor 监视器
 */
- (void)registerCrashLogMonitor:(id<CrashReporterMonitorDelegate>)monitor;

@end
