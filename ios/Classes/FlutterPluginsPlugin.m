#import "FlutterPluginsPlugin.h"
#if __has_include(<flutter_plugins/flutter_plugins-Swift.h>)
#import <flutter_plugins/flutter_plugins-Swift.h>
#else
// Support project import fallback if the generated compatibility header
// is not copied when this plugin is created as a library.
// https://forums.swift.org/t/swift-static-libraries-dont-copy-generated-objective-c-header/19816
#import "flutter_plugins-Swift.h"
#endif

@implementation FlutterPluginsPlugin
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  [SwiftFlutterPluginsPlugin registerWithRegistrar:registrar];
}
@end
