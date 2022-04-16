package com.app.ui.activity

import android.graphics.Color
import android.os.Bundle
import android.text.InputType
import android.view.View
import android.widget.Button
import android.widget.ImageView
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.hjzf.R

class ChangePassword : AppCompatActivity(){

    override fun onCreate(savedInstanceState: Bundle?) {


        super.onCreate(savedInstanceState)
        /*
        setContentView(R.layout.change_password)
        val originpassword = findViewById<TextView>(R.id.originalPassword)
        val newpassword_1 = findViewById<TextView>(R.id.newPassword1)
        val newpassword_2 = findViewById<TextView>(R.id.newPassword2)
        val button = findViewById<Button>(R.id.ok)
        var  imageview = findViewById<ImageView>(R.id.hidePassword)
        var  tv = findViewById<TextView>(R.id.originalPassword)


        val sqlite = Sqlite(this,"news_db",1)
        val id = intent.getStringExtra("id")
        var newpassword = "test"
        var password = "test"
        var i = 1
        var mydb = sqlite.writableDatabase

        val cursor  =  mydb.rawQuery("select * from User where UserID =?", arrayOf(id))
        if(cursor.moveToFirst()){
            password = cursor.getString(cursor.getColumnIndex("Password"))
        }
        button.setOnClickListener {
                 if (originpassword.text.toString().equals(password)&&newpassword_1.text.toString().equals(newpassword_2.text.toString())){
                     newpassword=newpassword_1.text.toString()
                    var sqliteUpdate ="UPDATE User SET Password =" +newpassword+"WHERE UserID=" +id
                    mydb.execSQL(sqliteUpdate)
                     Toast.makeText(this@ChangePassword, "更改成功！", Toast.LENGTH_SHORT).show()
                     finish()

                 }
                 else{
                    if (!originpassword.equals(password))
                        Toast.makeText(this@ChangePassword, "原密码错误！", Toast.LENGTH_SHORT).show()
                    else
                        Toast.makeText(this@ChangePassword, "两次密码不相同！", Toast.LENGTH_SHORT).show()
                 }
        }
        imageview.setOnClickListener {
            if (i%2!=0){
                imageview.setColorFilter(Color.BLUE)
                tv.setInputType(InputType.TYPE_TEXT_VARIATION_VISIBLE_PASSWORD)
            }
            else{
                imageview.setColorFilter(Color.GRAY)
                tv.setInputType(InputType.TYPE_CLASS_TEXT or InputType.TYPE_TEXT_VARIATION_PASSWORD)
            }
            i++

        }





*/
    }


}