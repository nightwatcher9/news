package com.example.dms;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class AdminMy extends AppCompatActivity {
    private String adId;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.admin_my);
        Intent intent = getIntent();
        adId=intent.getStringExtra("adId");

        TextView adminId = (TextView)findViewById(R.id.adminId);
        adminId.setText("管理员ID："+adId);

        Button chengePassword = (Button)findViewById(R.id.chengePassword); //更改密码
        chengePassword.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(AdminMy.this, ChangePassword.class);
                intent.putExtra("id",adId);
                intent.putExtra("type","admin");
                startActivity(intent);
            }
        });

        Button quit = (Button)findViewById(R.id.quit);  //退出账户
        quit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(AdminMy.this,Login.class);
                startActivity(intent);
            }
        });
    }

    public void navigationHome(View view){
        Intent intent = new Intent(this, AdminHome.class);
        intent.putExtra("adId",adId);
        startActivity(intent);
    }

    public void navigationNotice(View view){
        Intent intent = new Intent(this, AdminHome.class);
        intent.putExtra("adId",adId);
        startActivity(intent);
    }

}
