package com.example.dms;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class GeneralAdminMy extends AppCompatActivity {
    private String GAId;
    @Override
    protected void onCreate(@Nullable @org.jetbrains.annotations.Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.general_admin_my);
        Intent intent = getIntent();
        GAId=intent.getStringExtra("GAId");
        TextView  generalAdminId = (TextView)findViewById(R.id.generalAdminId);
        generalAdminId.setText(GAId);

        Button chengePassword = (Button)findViewById(R.id.chengePassword); //更改密码
        chengePassword.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(GeneralAdminMy.this, ChangePassword.class);
                intent.putExtra("id",GAId);
                intent.putExtra("type","generalAdmin");
                startActivity(intent);
            }
        });

        Button quit = (Button)findViewById(R.id.quit);  //退出账户
        quit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(GeneralAdminMy.this,Login.class);
                startActivity(intent);
            }
        });
    }

    public void navigationHome(View view){
        Intent intent = new Intent(GeneralAdminMy.this, GeneralAdminHome.class);
        intent.putExtra("GAId",GAId);
        startActivity(intent);
    }
}

