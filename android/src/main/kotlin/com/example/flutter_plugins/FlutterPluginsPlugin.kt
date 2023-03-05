package com.example.flutter_plugins

import android.app.Activity
import android.app.Application
import android.app.Application.ActivityLifecycleCallbacks
import android.app.Notification
import android.content.*
import android.os.Bundle
import android.os.IBinder
import android.util.Log
import io.flutter.embedding.engine.plugins.FlutterPlugin
import io.flutter.embedding.engine.plugins.FlutterPlugin.FlutterPluginBinding
import io.flutter.embedding.engine.plugins.activity.ActivityAware
import io.flutter.embedding.engine.plugins.activity.ActivityPluginBinding
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugin.common.MethodChannel.MethodCallHandler
import io.flutter.plugin.common.MethodChannel.Result
import io.flutter.plugin.common.PluginRegistry


const val TGA = "flutterPluginsLog1"

/** FlutterPluginsPlugin */
class FlutterPluginsPlugin: FlutterPlugin, MethodCallHandler, PluginRegistry.NewIntentListener,
  PluginRegistry.RequestPermissionsResultListener,
  ActivityAware {

  private lateinit var channel : MethodChannel
  private lateinit var context: Context
  private lateinit var localNotification: LocalNotification
  private var mainActivity: Activity? = null
  private var notificationBinder: ForegroundService.NotificationBinder? = null
  private var notificationId: Int? = 0
  private var notification: Notification? = null
  private var emasTlog: EmasTlog? = null
  private val connection = object : ServiceConnection {

    override fun onServiceConnected(p0: ComponentName, p1: IBinder) {
      notificationBinder = p1 as ForegroundService.NotificationBinder
      notificationBinder!!.createForegroundService(notificationId!!, notification!!)
    }

    override fun onServiceDisconnected(p0: ComponentName) {
    }

  }


  override fun onAttachedToEngine(flutterPluginBinding: FlutterPluginBinding) {
    channel = MethodChannel(flutterPluginBinding.binaryMessenger, "flutter_plugins")
    channel.setMethodCallHandler(this)
    context = flutterPluginBinding.applicationContext
    localNotification = LocalNotification(context)
  }

  override fun onDetachedFromEngine(binding: FlutterPluginBinding) {
  }

  override fun onMethodCall(call: MethodCall, result: Result) {
    Log.d(TGA, call.method)
    when(call.method) {
      "sendNotification" -> localNotification.sendNotification(call, result, "important") {
        id , notification, manager -> manager.notify(id, notification)
      }
      "sendForwardNotification" -> localNotification.sendNotification(call, result, "important") {
          id , n, _ ->
        notificationId = id
        notification = n
        bindService()
      }
      "updateForwardNotification" -> localNotification.sendNotification(call, result, "important") {
          id , n, _ ->
        if(notification == null) {
          notificationId = id
          notification = n
          bindService()
        }else{
          notification = n
          notificationBinder?.updateForegroundService(notification!!)
        }
      }
      "stopForwardNotification" ->
        if(notificationBinder != null) {
          notificationBinder?.stopForegroundService()
          context.unbindService(connection)
          notificationBinder = null
          notificationId = null
          notification = null
        }
      "initEMASTLog" -> {
        val appKey = call.argument<String>("appKey")
        val appSecret = call.argument<String>("appSecret")
        val rsaPublicKey = call.argument<String>("rsaPublicKey")
        val channel = call.argument<String>("channel")
        val userNick = call.argument<String?>("userNick")
        val type = call.argument<String?>("type")
        val debug = call.argument<Boolean>("debug")
        val emasTlogParams = EmasTlogParams(appKey!!, appSecret!!, userNick, rsaPublicKey!!, channel!!, debug!!, type)
        emasTlog = EmasTlog(context, emasTlogParams)
        result.success("初始化成功")
      }
      "printInEMASLog" -> {
        emasTlog?.log(call, result)
      }
      "updateNickNameEMASLog" -> {
        val name = call.argument<String?>("name")
        emasTlog?.updateNickName(name)
      }
      "commentEMASLog" -> {
        emasTlog?.comment()
      }
      else ->  result.notImplemented()
    }
  }

  private fun bindService() {
    context.apply {
      val intent = Intent(this, ForegroundService::class.java)
      bindService(intent, connection, Context.BIND_AUTO_CREATE)
      Log.d(TGA, "createForegroundService")
    }
  }

  override fun onNewIntent(intent: Intent): Boolean {
    val res = sendNotificationPayloadMessage(intent)
    if(res && mainActivity != null) {
      mainActivity!!.intent = intent
    }
    return res
  }

  private fun sendNotificationPayloadMessage(intent: Intent): Boolean {
    if (intent.action == LocalNotification.SELECT_NOTIFICATION) {
      val payload: String? = intent.getStringExtra("payload")
      if(payload != null) {
        channel.invokeMethod("selectNotification", payload)
        return  true
      }
      return false
    }
    return  false
  }

  override fun onRequestPermissionsResult(
    requestCode: Int,
    permissions: Array<out String>?,
    grantResults: IntArray?
  ): Boolean {
    return false
  }

  override fun onAttachedToActivity(binding: ActivityPluginBinding) {
    binding.addOnNewIntentListener(this);
    binding.addRequestPermissionsResultListener(this);
    mainActivity = binding.activity;
  }

  override fun onDetachedFromActivityForConfigChanges() {
    mainActivity = null;
  }

  override fun onReattachedToActivityForConfigChanges(binding: ActivityPluginBinding) {
    binding.addOnNewIntentListener(this);
    binding.addRequestPermissionsResultListener(this);
    mainActivity = binding.activity;
  }

  override fun onDetachedFromActivity() {
    mainActivity = null;
  }


}
