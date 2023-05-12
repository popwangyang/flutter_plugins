import Flutter
import UIKit
import AlicloudUtils

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
          print("ppppppp")
          AlicloudReport()
          result(Bool(true))
      case "koo":
          print("lsllsl")
      default:
          print("lsllsll")
      }
  }
}
