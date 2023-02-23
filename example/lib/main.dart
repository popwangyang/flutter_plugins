import 'package:flutter/material.dart';
import 'package:flutter_plugins/flutter_plugins.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  late final FlutterPlugins _flutterPlugins;

  void _onSelectNotification(String value) {
    print(value);
  }

  @override
  void initState() {
    super.initState();
    _flutterPlugins = FlutterPlugins();
    _flutterPlugins.initialize(onSelectNotification: _onSelectNotification);
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: Center(
          child: Column(
            children: [
              ElevatedButton(
                child: const Text("发送本地通知"),
                onPressed: () {
                  _flutterPlugins.sendNotification(
                      FlutterPluginsLocalNotification(
                          title: "郭支书了-业务员",
                          content: "你有一条订单2023473680910审核不通过请查看原因 >>",
                          payload: "928929992992"));
                },
              ),
              ElevatedButton(
                child: const Text("创建service通知"),
                onPressed: () {
                  _flutterPlugins.sendForwardNotification(
                      FlutterPluginsLocalNotification(
                          title: "郭支书了-业务员",
                          content: "你现在正在拜访“小林超市”，请不要忘记里店打卡！！",
                          payload: "928929992992"));
                },
              ),
              ElevatedButton(
                child: const Text("更新service通知"),
                onPressed: () {
                  _flutterPlugins.updateForwardNotification(
                      FlutterPluginsLocalNotification(
                          title: "郭支书了-业务员",
                          content: "你现在正在拜访“洪河超市”，请不要忘记里店打卡！！",
                          payload: "928929992992"));
                },
              ),
              ElevatedButton(
                child: const Text("关闭service通知"),
                onPressed: () {
                  _flutterPlugins.stopForwardNotification();
                },
              ),
            ],
          ),
        ),
      ),
    );
  }
}
