//
//  AliCrashReporterServiceInterface.h
//  Pods
//
//  Created by 晨燕 on 2018/1/11.
//

#import <Foundation/Foundation.h>


typedef NSDictionary* (^AliAdditionalCrashInfoHandler)(void);

// crash record object
@interface AliCrashRecord : NSObject

@property (nonatomic, assign) NSTimeInterval timestamp;         //
@property (nonatomic, copy) NSString* page;

@end

@protocol AliCrashReporterInterface <NSObject>

/**
 * append extra information on crash caught
 */
- (void)appendAdditionalInformation:(AliAdditionalCrashInfoHandler)handler;

/**
 * get all available crash records with time information and biz information
 * note: records are sorted by time ascend
 */
- (NSArray<AliCrashRecord*>*)getHistoryCrashRecords;

@end


#define AliCrashReporterService getAliCrashReporterService()

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
    // default get [AliCrashReporterImp sharedInstance]接口来获取，如果没有的话，就返回nil
    id<AliCrashReporterInterface> getAliCrashReporterService(void);
    void setAliCrashReporterService(id<AliCrashReporterInterface> service);
#ifdef __cplusplus
}
#endif // __cplusplus
