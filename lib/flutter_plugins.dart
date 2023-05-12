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
    return await _channel.invokeMethod(
        "sendNotification", notification.toJson());
  }

  Future<bool?> initialize({ValueChanged<String>? onSelectNotification}) async {
    _onSelectNotification = onSelectNotification;
    _channel.setMethodCallHandler(_handleMethod);
    return null;
  }

  printInEMASLog(EMASTlogger logger) {
    String method = "log";
    switch (logger.type) {
      case EMASTlogType.DEBUG:
        method += "d";
        break;
      case EMASTlogType.ERROR:
        method += "e";
        break;
      case EMASTlogType.INFO:
        method += "i";
        break;
      case EMASTlogType.VERBOSE:
        method += "v";
        break;
      case EMASTlogType.WARN:
        method += "w";
        break;
    }
    _channel.invokeMethod(method, logger.toJson());
  }

  void commentEMASlog() {
    _channel.invokeMethod("commentEMASLog");
  }

  void updateNickName(String name) {
    _channel.invokeMethod("updateNickNameEMASLog", {"name": name});
  }

  Future<bool?> initEMASTlog(FlutterPluginsEMASTlogConfig config) async {
    if (Platform.isAndroid) {
      return await _channel.invokeMethod("initEMASTLog", config.toJson());
    }
    return null;
  }

  void pointerException() {
    _channel.invokeMethod("pointerException");
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
