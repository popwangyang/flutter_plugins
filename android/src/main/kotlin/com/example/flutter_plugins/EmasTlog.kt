package com.example.flutter_plugins

import android.app.Application
import android.content.Context
import android.content.pm.PackageManager
import androidx.annotation.NonNull
import com.alibaba.ha.adapter.AliHaAdapter
import com.alibaba.ha.adapter.AliHaConfig
import com.alibaba.ha.adapter.Plugin
import com.alibaba.ha.adapter.service.tlog.TLogLevel
import com.alibaba.ha.adapter.service.tlog.TLogService
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel.Result

class EmasTlog(@NonNull val context: Context, @NonNull val emasTlogParams: EmasTlogParams) {
    init {
        val config = AliHaConfig()
        config.appKey = emasTlogParams.appKey; //配置项：appkey
        config.appVersion = getVersionName(); //配置项：应用的版本号
        config.appSecret = emasTlogParams.appSecret; //配置项：appsecret
        config.channel = emasTlogParams.channel; //配置项：应用的渠道号标记，自定义
        config.userNick = emasTlogParams.userNick; //配置项：用户的昵称
        config.application = context.applicationContext as Application; //配置项：应用指针
        config.context = context.applicationContext; //配置项：应用上下文
        config.isAliyunos = false; //配置项：是否为yunos
        config.rsaPublicKey = emasTlogParams.rsaPublicKey; //配置项：tlog公钥
        AliHaAdapter.getInstance().addPlugin(Plugin.tlog);
        AliHaAdapter.getInstance().openDebug(emasTlogParams.openDebug);
        AliHaAdapter.getInstance().start(config);
        if(emasTlogParams.type!=null){
            when (emasTlogParams.type) {
                "v"->{
                    TLogService.updateLogLevel(TLogLevel.VERBOSE) //配置项：控制台可拉取的日志级别
                }
                "d"->{
                    TLogService.updateLogLevel(TLogLevel.VERBOSE) //配置项：控制台可拉取的日志级别
                }
                "i"->{
                    TLogService.updateLogLevel(TLogLevel.INFO) //配置项：控制台可拉取的日志级别
                }
                "w"->{
                    TLogService.updateLogLevel(TLogLevel.WARN) //配置项：控制台可拉取的日志级别
                }
                "e"->{
                    TLogService.updateLogLevel(TLogLevel.ERROR) //配置项：控制台可拉取的日志级别
                }
            }
        }else{
            TLogService.updateLogLevel(TLogLevel.WARN); //配置项：控制台可拉取的日志级别
        }
    }

    // 输出日志
    fun log(@NonNull call: MethodCall, @NonNull result: Result){
        val message = call.argument<String>("message")
        val module = call.argument<String>("module")
        val tag = call.argument<String>("tag")
        when (call.method) {
            "logv"->{
                TLogService.logv(module,tag,message);
            }
            "logd"->{
                TLogService.logd(module,tag,message);
            }
            "logi"->{
                TLogService.logi(module,tag,message);
            }
            "logw"->{
                TLogService.logw(module,tag,message);
            }
            "loge"->{
                TLogService.loge(module,tag,message);
            }
        }
        result.success(true)
    }

    // 主动上报日志
    fun comment() {
        TLogService.positiveUploadTlog("COMMENT");
    }

    //替换昵称
    fun updateNickName(nickName: String?) {
        AliHaAdapter.getInstance().updateUserNick(nickName)
    }

    private fun getVersionName():String {
        context.apply {
            val info = packageManager.getPackageInfo(packageName, PackageManager.GET_CONFIGURATIONS)
            val versionName = info.versionName
            val versionCode = info.versionCode
            return versionName + "+${versionCode.toString()}"
        }
    }
}


data class EmasTlogParams(
    val appKey: String,
    val appSecret: String,
    val userNick: String?,
    val rsaPublicKey: String,
    val channel: String,
    val openDebug: Boolean,
    val type: String?
)