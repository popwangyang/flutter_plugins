package com.example.flutter_plugins

import android.app.Activity
import android.content.Intent
import android.content.pm.PackageManager
import android.provider.ContactsContract
import android.util.Log
import android.widget.Toast
import androidx.annotation.NonNull
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugin.common.PluginRegistry

class ContactsPicker(@NonNull val activity: Activity): PluginRegistry.ActivityResultListener, PluginRegistry.RequestPermissionsResultListener {

    private val REQUEST_ADDRESSBOOK:Int = 10
    private val REQUEST_PERMISSION_ADDRESSBOOK :Int = 11


    private var _result: MethodChannel.Result? = null


    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?): Boolean {
        when(requestCode){
            REQUEST_ADDRESSBOOK -> {
                val contactId = data?.data?.lastPathSegment
                contactId?.let {
                    activity.contentResolver.query(
                        ContactsContract.CommonDataKinds.Phone.CONTENT_URI,
                        null,
                        "${ContactsContract.Contacts._ID} =?",
                        arrayOf(contactId),
                        null
                    )?.apply {
                        while (moveToNext()) {
                            var nameIndex: Int = getColumnIndex(
                                ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME)
                            var phoneIndex: Int = getColumnIndex(
                                ContactsContract.CommonDataKinds.Phone.NUMBER)
                            // 获取联系人姓名
                            val name = getString(nameIndex)
                            // 获取联系人手机号
                            val phone = getString(phoneIndex).replace(" ", "")
                            var contacts = mapOf("name" to name, "phone" to  phone)
                            Log.d(TGA, contacts.toString())
                            success(contacts)
                        }
                    }
                }
            }
        }
        return true
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>?,
        grantResults: IntArray?
    ): Boolean {
        when(requestCode) {
            REQUEST_PERMISSION_ADDRESSBOOK -> {
                if (grantResults != null) {
                    if (grantResults.isNotEmpty()
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                        goContactsPage()
                    } else {
                        success(null)
                        Toast.makeText(activity, "你禁止了访问通讯录权限",
                            Toast.LENGTH_SHORT).show()
                    }
                }
            }
        }

        return true
    }

    fun getContacts(result: MethodChannel.Result): Map<String, String>? {
        _result = result
       val permission = checkPermission()
        if(permission){
            goContactsPage()
        }
        return null
    }

    private fun checkPermission(): Boolean {
        if (ContextCompat.checkSelfPermission(activity
                , android.Manifest.permission.READ_CONTACTS) != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(activity
                , arrayOf(android.Manifest.permission.READ_CONTACTS), REQUEST_PERMISSION_ADDRESSBOOK)
            return  false
        }
        return  true
    }

    private fun goContactsPage() {
        activity.apply {
             var intent = Intent();
            intent.action = "android.intent.action.PICK";
            intent.addCategory("android.intent.category.DEFAULT");
            intent.type = "vnd.android.cursor.dir/phone_v2";
            startActivityForResult(intent, REQUEST_ADDRESSBOOK)
        }
    }

    private fun success(contacts: Map<String, String>?) {
        _result?.success(contacts)
    }
}