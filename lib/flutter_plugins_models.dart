/// 前台通知结构
/// title：通知的标题
/// content：通知内容
/// payload: 点击通知回掉参数
// ignore_for_file: constant_identifier_names

class FlutterPluginsLocalNotification {
  final String title;
  final String content;
  final String payload;
  FlutterPluginsLocalNotification(
      {required this.title, required this.content, this.payload = ""});

  Map<String, dynamic> toJson() {
    return {"title": title, "content": content, "payload": payload};
  }
}

/// EMASTlog的配置文件
/// appKey用于指定App的AppKey
/// appSecrect用于指定App的AppSecret
/// channel用于设置渠道标识，上报至服务端，进行渠道区分。
/// userNick用于设置用户昵称，上报至服务端，进行用户区分。后续可能依据该参数，进行数据检索。
/// rsaPubilcKey用于指定远程日志公钥
/// type用于全局设置控制台可拉取的日志的级别。

class FlutterPluginsEMASTlogConfig {
  final String appKey;
  final String appSecret;
  final String rsaPublicKey;
  final String channel;
  final bool openDebug;
  final String? userNick;
  final EMASTlogType? type;

  FlutterPluginsEMASTlogConfig(
      {required this.appKey,
      required this.appSecret,
      required this.rsaPublicKey,
      required this.channel,
      required this.openDebug,
      this.userNick,
      this.type});

  Map<String, dynamic> toJson() {
    String? _type;
    switch (type) {
      case EMASTlogType.VERBOSE:
        _type = "v";
        break;
      case EMASTlogType.DEBUG:
        _type = "d";
        break;
      case EMASTlogType.INFO:
        _type = "i";
        break;
      case EMASTlogType.WARN:
        _type = "w";
        break;
      case EMASTlogType.ERROR:
        _type = "e";
        break;
      default:
    }
    return {
      "appKey": appKey,
      "appSecret": appSecret,
      "rsaPublicKey": rsaPublicKey,
      "channel": channel,
      "openDebug": openDebug,
      "userNick": userNick,
      "type": _type
    };
  }
}

/// VERBOSE：可拉取所有级别的日志。
/// DEBUG：可拉取DEBUG/INFO/WARN/ERROR级别的日志。
/// INFO：可拉取INFO/WARN/ERROR级别的日志。
/// WARN：可拉取WARN/ERROR级别的日志。
/// ERROR：可拉取ERROR级别的日志。
enum EMASTlogType { VERBOSE, DEBUG, INFO, WARN, ERROR }

class EMASTlogger {
  final EMASTlogType type;
  final String module;
  final String message;
  final String tag;

  EMASTlogger(
      {required this.type,
      required this.tag,
      required this.message,
      required this.module});

  toJson() {
    return {"message": message, "module": module, "tag": tag};
  }
}
