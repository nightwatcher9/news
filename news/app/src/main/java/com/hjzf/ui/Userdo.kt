package com.app.ui.activity


import android.content.Intent
import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import com.hjzf.NewsApplication
import com.hjzf.R
import com.hjzf.ui.MainActivity

class Userdo : AppCompatActivity(){
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.fragment_user)
        /*
        val quit = findViewById<Button>(R.id.quit)
        val changepassword = findViewById<Button>(R.id.changePassword)
        val changeinformation = findViewById<Button>(R.id.changeinformation)
        quit.setOnClickListener{
            val intent = Intent(this, MainActivity::class.java)
            startActivity(intent)
        }
        changepassword.setOnClickListener {
            val intent = Intent(NewsApplication.context,ChangePassword::class.java)
            startActivity(intent)
        }
        changeinformation.setOnClickListener {
            val intent = Intent(this,ChangeInformation::class.java)
            startActivity(intent)
        }
*/
    }
}