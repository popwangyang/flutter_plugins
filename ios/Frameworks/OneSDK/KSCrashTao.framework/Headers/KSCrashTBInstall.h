//
//  KSCrashTBInstall.h
//  KSCrashTao
//
//  Created by 刘坤 on 2019/6/10.
//

#ifndef KSCrashTBInstall_h
#define KSCrashTBInstall_h

#include <stdio.h>
#include <mach/mach_types.h>

#import <KSCrashTao/KSCrashMonitorType.h>

/**
 配置项解构
 */
typedef struct KSCrashTBConfig
{
    // 发生crash还没落盘时候的回调，
    // 重要！！！，这里面不要有OC调用，不要申请内存
    void (*justOnCrash)(void);
    
    // 日志落盘之后的回调，可以在里面尝试上报, 发生二次crash不会影响日志丢失
    post_crash_callback_t postCrashCallback;
    
    // 手淘特有逻辑，会把页面vc名字放到日志Identifier里面，这个回调会在主要日志落盘后回调，避免发生crash导致日志不完整
    const char *(*getCurrentViewName)(void);
    
} KSCrashTBConfig;


/**
 初始化KSCrash

 @param config 配置
 @return 是否初始化成功
 */
bool kscrash_tb_install(KSCrashTBConfig config);

/**
 获取CrashReport ID

 @return reportID
 */
int64_t kscrash_tb_getPendingCrashReportId(void);

/**
 移除所有的CrashReport
 */
void kscrash_tb_deleteAllPendingCrashReport(void);

/**
 移除指定ID的report
 */
void kscrash_tb_deletePendingCrashReport(int64_t reportId);

/**
 读取CrashReporter的Data
 
 @return crash日志的data
 */
NSData *kscrash_readDataOfReport(int64_t reportId, NSError **outError);


/**
 可以通过注册一个 C 方法来Append Log 到日志中
 */
typedef const char *(*KSCrashTBAdditionInfoWriter)(thread_t crashThread, void *crashUContext);
bool  kscrash_tb_add_additionInfoWriter(KSCrashTBAdditionInfoWriter writer);

#endif /* KSCrashTBInstall_h */
