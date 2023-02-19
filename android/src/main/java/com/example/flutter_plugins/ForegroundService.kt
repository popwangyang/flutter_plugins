package com.example.flutter_plugins

import android.app.Notification
import android.app.Service
import android.content.Intent
import android.os.Binder
import android.os.IBinder
import android.util.Log

class ForegroundService : Service() {

    private lateinit var notificationBinder: NotificationBinder

    class NotificationBinder(private val service: Service): Binder() {

        private var _notificationId: Int = 0

        fun createForegroundService(notificationId: Int, notification: Notification) {
            _notificationId = notificationId
            service.startForeground(_notificationId, notification)
        }

        fun stopForegroundService() {
            Log.d(TGA, "stopForegroundService")
            service.stopSelf()
        }

        fun updateForegroundService(notification: Notification) {
            service.startForeground(_notificationId, notification)
        }

    }

    override fun onBind(intent: Intent): IBinder {
        return notificationBinder
    }

    override fun onCreate() {
        super.onCreate()
        notificationBinder = NotificationBinder(this)
        Log.d(TGA, "onCreate")
    }

    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        return super.onStartCommand(intent, flags, startId)
    }
}