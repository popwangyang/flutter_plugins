import Flutter
import UIKit
import AliAPMInterface
//import AlicloudTLog

public class SwiftFlutterPluginsPlugin: NSObject, FlutterPlugin {
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "flutter_plugins", binaryMessenger: registrar.messenger())
    let instance = SwiftFlutterPluginsPlugin()
    registrar.addMethodCallDelegate(instance, channel: channel)
  }

  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
//    result("iOS " + UIDevice.current.systemVersion)
      let method = call.method;
      switch method {
      case "sendNotification":
          print("sendNotification")
          
          let appVersion = Bundle.main.infoDictionary?["CFBundleShortVersionString"] as? String
          let appBundleId = Bundle.main.infoDictionary?["CFBundleIdentifier"] as? String
          
          if let tem = appVersion, let tam = appBundleId {
              print(tem, tam)
          }
         
          
          result(Bool(true))
          
      case "initEMASTLog":
          print("lsllsl")
      default:
          print("lsllsll")
      }
  }
}

func goo(params: inout Int){
    params+=1;
}

//func initEMASTLog(appKey: String, secret: String, tlogRsaSecret: String, appVersion: String, channel: String, nick: String) -> Void {
//    
//    let emasLog = AlicloudTLog.AlicloudTlogProvider.init()
//    
//    emasLog.initWithAppKey(appKey, secret: secret, tlogRsaSecret: tlogRsaSecret, appVersion: appVersion, channel: channel, nick: nick)
//    
//    
//    
//    
//    
//    
//}

