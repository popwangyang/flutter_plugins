#import "FlutterPluginsPlugin.h"
#import <AlicloudTLog/AlicloudTlogProvider.h>
#import <AlicloudHAUtil/AlicloudHAProvider.h>
#import <TRemoteDebugger/TRDManagerService.h>

#import <TRemoteDebugger/TLogBiz.h>
#import <TRemoteDebugger/TLogFactory.h>
#import <UTDID/UTDevice.h>

@implementation FlutterPluginsPlugin
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  FlutterMethodChannel* channel = [FlutterMethodChannel
      methodChannelWithName:@"flutter_plugins"
            binaryMessenger:[registrar messenger]];
  FlutterPluginsPlugin* instance = [[FlutterPluginsPlugin alloc] init];
  NSLog(@"\n ==== %@",[UTDevice utdid]); // YZ2gRyP4t0EDAK4z2x7IRG+C
  NSLog(@"这是插件oc代码");
  [registrar addMethodCallDelegate:instance channel:channel];
}

- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result {
      NSString *message = call.arguments[@"message"];
      NSString *module = call.arguments[@"module"];
      TLogBiz *log = [TLogFactory createTLogForModuleName:module];
    
      NSLog(@"message: %@",message);
      NSLog(@"module: %@",module);
      NSLog(@"message: %@",message);

      if ([@"getPlatformVersion" isEqualToString:call.method]) {
        result([@"iOS " stringByAppendingString:[[UIDevice currentDevice] systemVersion]]);

      }else if([@"logv" isEqualToString:call.method]){
        [log debug:message];

      }else if([@"logd" isEqualToString:call.method]){
        [log debug:message];

      }else if([@"loge" isEqualToString:call.method]){
        [log error:message];

      }else if([@"logw" isEqualToString:call.method]){
        [log warn:message];

      }else if([@"logi" isEqualToString:call.method]){
        [log info:message];

      }else if([@"commentEMASLog" isEqualToString:call.method]){ // 主动上传日志
        [AlicloudTlogProvider uploadTLog:@"COMMENT"];

      }else if([@"initEMASTLog" isEqualToString:call.method]){ // alicloud

         /*
             appKey
             appSecret
             tlogRsaSecret
             appVersion // App版本
             channel // 渠道标记 固定外界可不传
             nick  // 用户昵称  都不能为空
         */
         
         NSString *appKey = call.arguments[@"appKeyIos"];
         NSString *appSecret = call.arguments[@"appSecretIos"];
         NSString *tlogRsaSecret = call.arguments[@"rsaPublicKeyIos"];
         NSString *type = call.arguments[@"type"];
        
         
         NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
         NSString *appVersion = [infoDictionary objectForKey:@"CFBundleShortVersionString"];; //配置项：App版本号
         NSString *channel = call.arguments[@"channel"]; //配置项：渠道标记
         NSString *nick = call.arguments[@"userNick"]; //配置项：用户昵称
          
          NSLog(@"appKey: %@",appKey);
          NSLog(@"appSecret: %@",appSecret);
          NSLog(@"tlogRsaSecret: %@",tlogRsaSecret);
          NSLog(@"type: %@",type);
          NSLog(@"appVersion: %@",appVersion);
          NSLog(@"channel: %@",channel);
          NSLog(@"nick: %@",nick);
          
          
         
         //配置项：控制台可拉取的日志级别
         [[AlicloudTlogProvider alloc] initWithAppKey:appKey secret:appSecret tlogRsaSecret:tlogRsaSecret appVersion:appVersion channel:channel nick:nick];
         [AlicloudHAProvider start];
         // 拉取日志级别
         NSInteger logLevel;
         if([type isEqualToString:@"i"]){
             logLevel = TLogLevelInfo;
         }else if([type isEqualToString:@"w"]){
             logLevel = TLogFlagWarn;
         }else if([type isEqualToString:@"e"]){
             logLevel = TLogFlagError;
         }else{
             logLevel = TLogFlagDebug; // i
         }
         [TRDManagerService updateLogLevel:logLevel];

  }else {
    result(FlutterMethodNotImplemented);
  }
}

@end
