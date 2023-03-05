import 'dart:async';
import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_plugins/flutter_plugins_models.dart';
export './flutter_plugins_models.dart';

class FlutterPlugins {
  final MethodChannel _channel = const MethodChannel('flutter_plugins');

  ValueChanged<String>? _onSelectNotification;

  Future<String?> sendForwardNotification(
      FlutterPluginsLocalNotification notification) async {
    if (Platform.isAndroid) {
      return await _channel.invokeMethod(
          "sendForwardNotification", notification.toJson());
    }
    return null;
  }

  Future<String?> updateForwardNotification(
      FlutterPluginsLocalNotification notification) async {
    if (Platform.isAndroid) {
      return await _channel.invokeMethod(
          "updateForwardNotification", notification.toJson());
    }
    return null;
  }

  Future<String?> stopForwardNotification() async {
    if (Platform.isAndroid) {
      return await _channel.invokeMethod("stopForwardNotification");
    }
    return null;
  }

  Future<bool?> sendNotification(
      FlutterPluginsLocalNotification notification) async {
    if (Platform.isAndroid) {
      return await _channel.invokeMethod(
          "sendNotification", notification.toJson());
    }
    return null;
  }

  Future<bool?> initialize({ValueChanged<String>? onSelectNotification}) async {
    _onSelectNotification = onSelectNotification;
    _channel.setMethodCallHandler(_handleMethod);
    return null;
  }

  Future<bool?> initEMASTlog(FlutterPluginsEMASTlogConfig config) async {
    if (Platform.isAndroid) {
      return await _channel.invokeMethod("initEMASTLog", config.toJson());
    }
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
