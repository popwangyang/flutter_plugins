/// 前台通知结构
/// title：通知的标题
/// content：通知内容
/// payload: 点击通知回掉参数
class LocalNotification {
  final String title;
  final String content;
  final String payload;
  LocalNotification(
      {required this.title, required this.content, this.payload = ""});

  Map<String, dynamic> toJson() {
    return {"title": title, "content": content, "payload": payload};
  }
}
