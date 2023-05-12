//
//  AliPerformanceCPU.h
//  AliPerformanceMonitor
//
//  Created by yingfang on 17/2/6.
//  Copyright © 2017年 Taobao lnc. All rights reserved.
//

#import <AliHAProtocol/AliHAProtocol.h>
#import <Foundation/Foundation.h>

@interface AliHAPerformanceCPUMonitor : NSObject

+ (instancetype)sharedInstance;

- (void)startMonitor:(NSTimeInterval)interval withContext:(id<AliHAContextProtocol>)context;

- (void)stopMonitor;

- (void)latestCPUStatus:(float *)cpuUsageOfApp cpuUsageOfDevice:(float *)cpuUsageOfDevice;

@end
