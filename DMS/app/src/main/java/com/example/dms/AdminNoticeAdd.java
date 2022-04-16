package com.example.dms;

import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;

import android.content.ContentValues;
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.text.SimpleDateFormat;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class AdminNoticeAdd extends AppCompatActivity {

    private EditText ET_noticeTitle;
    private EditText ET_noticeContent;
    private TextView ET_noticeTime;
    private String adId;
    MySqlite sqlite;
    SQLiteDatabase myDb;
    SimpleDateFormat sdf = new SimpleDateFormat("YYYY-MM-DD HH:MM:SS");
    String ly_time = sdf.format(new java.util.Date());

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.admin_notice_add);
        Intent intent = getIntent();
        adId=intent.getStringExtra("adId");

        Button add=(Button)findViewById(R.id.add);
        ET_noticeTitle = (EditText) findViewById(R.id.ET_noticeTitle);
        ET_noticeContent = (EditText) findViewById(R.id.ET_noticeContent);
        ET_noticeTime = (TextView) findViewById(R.id.ET_noticeTime);
        ET_noticeTime.setText(ly_time);

        add.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (ET_noticeTitle.getText().toString().equals(""))
                {
                    Toast.makeText(AdminNoticeAdd.this, "公告标题输入不能为空!", Toast.LENGTH_LONG).show();
                    ET_noticeContent.setFocusable(true);
                    ET_noticeContent.requestFocus();
                    return;
                }
                if(ET_noticeContent.getText().toString().equals("")) {
                    Toast.makeText(AdminNoticeAdd.this, "公告内容输入不能为空!", Toast.LENGTH_LONG).show();
                    ET_noticeContent.setFocusable(true);
                    ET_noticeContent.requestFocus();
                    return;
                }
                if(ET_noticeTime.getText().toString().equals("")) {
                    Toast.makeText(AdminNoticeAdd.this, "公告时间输入不能为空!", Toast.LENGTH_LONG).show();
                    ET_noticeContent.setFocusable(true);
                    ET_noticeContent.requestFocus();
                    return;
                }
                else{
                    ContentValues contentValues = new ContentValues();
                    contentValues.put("Title",ET_noticeTitle.getText().toString());
                    contentValues.put("Content",ET_noticeContent.getText().toString());
                    contentValues.put("Time",ly_time);
                    contentValues.put("AdID",adId);
                    sqlite = new MySqlite(AdminNoticeAdd.this, "Dormitory.db", null, 1);
                    myDb = sqlite.getWritableDatabase();
                    myDb.insert("Notice",null,contentValues);
                    Toast.makeText(AdminNoticeAdd.this, "发布成功!", Toast.LENGTH_LONG).show();
                    Intent intent = new Intent(AdminNoticeAdd.this,AdminNotice.class);
                    intent.putExtra("adId",adId);
                    startActivity(intent);
                }
            }
        });
    }
}
