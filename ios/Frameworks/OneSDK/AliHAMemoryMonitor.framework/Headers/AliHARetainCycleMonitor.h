//
//  AliHARetainCycleMonitor.h
//  AliHAMemoryMonitorCore
//
//  Created by junzhan on 2017/7/31.
//  Copyright © 2017年 taobao. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AliHAProtocol/AliHAProtocol.h>

@protocol AliHARetainCycleMonitorPlugin <NSObject>

@required

- (void)onMemoryLeakRetainCycleSummary:(NSString *)summary detail:(NSString *)detail;
- (void)onMemoryLeakObjectSummary:(NSString *)summary detail:(NSString *)detail;

@end

@interface AliHARetainCycleMonitor : NSObject<AliHAPluginProtocol>

+ (instancetype)sharedInstance;

- (void)addMonitorPlugin:(id<AliHARetainCycleMonitorPlugin>)plugin;

@end


@interface TestCycleRootObject : NSObject

@end


#ifdef DEBUG

#define  TestObjectClass(x) \
@interface TestObject##x : TestCycleRootObject \
@property (nonatomic, strong) id object;\
@property (nonatomic, strong) id secondObject;\
@end\
@implementation TestObject##x\
@end\

#endif
