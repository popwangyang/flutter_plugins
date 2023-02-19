package com.example.flutter_plugins

import android.annotation.SuppressLint
import android.app.Notification
import android.app.NotificationChannel
import android.app.NotificationManager
import android.app.PendingIntent
import android.content.ComponentName
import android.content.Context
import android.content.Intent
import android.os.Build
import androidx.core.app.NotificationCompat
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel


class LocalNotification(private val context: Context) {

    companion object {
        const val SELECT_NOTIFICATION: String = "SELECT_NOTIFICATION"
    }

    private var notificationId: Int = 1

    @SuppressLint("LaunchActivityFromNotification", "UnspecifiedImmutableFlag")
    fun sendNotification(call: MethodCall, result: MethodChannel.Result, channelId:String = "important", callback: (Int, Notification, NotificationManager) -> Unit) {
        context.apply {
            val arg: HashMap<String, String> = call.arguments()
            val title = arg["title"]
            val content = arg["content"]
            val payload = arg["payload"]
            val manager = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
            if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                val channel = NotificationChannel(channelId, channelId, NotificationManager.IMPORTANCE_HIGH)
                manager.createNotificationChannel(channel)
            }
            val intent = getLaunchIntent(context)
            intent!!.action = SELECT_NOTIFICATION
            intent.putExtra("payload", payload)
            var flags = PendingIntent.FLAG_UPDATE_CURRENT
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                flags = flags or PendingIntent.FLAG_IMMUTABLE
            }
            val pi = PendingIntent.getActivity(context, notificationId, intent, flags)
            val notification = NotificationCompat.Builder(this, channelId)
                .setContentTitle(title)
                .setContentText(content)
                .setSmallIcon(applicationInfo.icon)
                .setStyle(NotificationCompat.BigTextStyle().bigText(content))
                .setContentIntent(pi)
                .setAutoCancel(true)
                .build()
            callback(notificationId, notification, manager)
            notificationId++
        }
    }

    private fun getLaunchIntent(context: Context): Intent? {
        val packageName = context.packageName
        val packageManager = context.packageManager
        return packageManager.getLaunchIntentForPackage(packageName)
    }

}

