package com.app.ui.activity

import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.hjzf.R

class ChangeInformation : AppCompatActivity(){
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(R.layout.change_information)
        val changename = findViewById<TextView>(R.id.name)
        val changeemail = findViewById<TextView>(R.id.email)
        val changelived = findViewById<TextView>(R.id.lived)
        val button = findViewById<Button>(R.id.yes)
        button.setOnClickListener {

        }


    }
}