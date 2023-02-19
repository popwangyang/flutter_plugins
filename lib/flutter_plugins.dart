import 'dart:async';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_plugins/flutter_plugins_models.dart';
export './flutter_plugins_models.dart';

class FlutterPlugins {
  final MethodChannel _channel = const MethodChannel('flutter_plugins');

  ValueChanged<String>? _onSelectNotification;

  Future<String?> sendForwardNotification(
      LocalNotification notification) async {
    return await _channel.invokeMethod(
        "sendForwardNotification", notification.toJson());
  }

  Future<String?> updateForwardNotification(
      LocalNotification notification) async {
    return await _channel.invokeMethod(
        "updateForwardNotification", notification.toJson());
  }

  Future<String?> stopForwardNotification() async {
    return await _channel.invokeMethod("stopForwardNotification");
  }

  Future<bool?> sendNotification(LocalNotification notification) async {
    return await _channel.invokeMethod(
        "sendNotification", notification.toJson());
  }

  Future<bool?> initialize({ValueChanged<String>? onSelectNotification}) async {
    _onSelectNotification = onSelectNotification;
    _channel.setMethodCallHandler(_handleMethod);
    return null;
  }

  Future<void> _handleMethod(MethodCall call) async {
    switch (call.method) {
      case 'selectNotification':
        _onSelectNotification?.call(call.arguments);
        break;
      default:
        return await Future<void>.error('Method not defined');
    }
  }
}
