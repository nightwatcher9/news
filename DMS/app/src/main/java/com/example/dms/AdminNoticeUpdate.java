package com.example.dms;

import android.annotation.SuppressLint;
import android.content.ContentValues;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;


public class AdminNoticeUpdate extends AppCompatActivity {
    private EditText ET_noticeTitle;
    private EditText ET_noticeContent;
    private TextView ET_noticeTime;
    private TextView ET_ID;
    private int NID;
    MySqlite sqlite;
    SQLiteDatabase myDb;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.admin_notice_update);

        sqlite = new MySqlite(AdminNoticeUpdate.this, "Dormitory.db", null, 1);
        myDb = sqlite.getWritableDatabase();
        Intent intent = getIntent();
        NID = intent.getIntExtra("NID", 0);
        Log.d("Upate_Notice", "NID is" + NID);
        ET_noticeTitle = (EditText) findViewById(R.id.ET_noticeTitle);
        ET_noticeContent = (EditText) findViewById(R.id.ET_noticeContent);
        ET_noticeTime = (TextView) findViewById(R.id.ET_noticeTime);
        ET_ID=(TextView)findViewById(R.id.TV_noticeId);
        Cursor cv = myDb.rawQuery("select * from Notice where NID=?", new String[]{Integer.toString(NID)});
        if (cv.moveToFirst()) {
            ET_ID.setText(String.valueOf(cv.getString(cv.getColumnIndex("NID"))));
            ET_noticeTime.setText(String.valueOf(cv.getString(cv.getColumnIndex("Time"))));
            ET_noticeTitle.setText(String.valueOf(cv.getString(cv.getColumnIndex("Title"))));
            ET_noticeContent.setText(String.valueOf(cv.getString(cv.getColumnIndex("Content"))));
        }

        Button update = (Button) findViewById(R.id.BtnUpdate);
        update.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (ET_noticeTitle.getText().toString().equals("")) {
                    Toast.makeText(AdminNoticeUpdate.this, "公告标题输入不能为空!", Toast.LENGTH_LONG).show();
                    ET_noticeContent.setFocusable(true);
                    ET_noticeContent.requestFocus();
                    return;

                }
                if (ET_noticeContent.getText().toString().equals("")) {
                    Toast.makeText(AdminNoticeUpdate.this, "公告内容输入不能为空!", Toast.LENGTH_LONG).show();
                    ET_noticeContent.setFocusable(true);
                    ET_noticeContent.requestFocus();
                    return;
                }
                if (ET_noticeTime.getText().toString().equals("")) {
                    Toast.makeText(AdminNoticeUpdate.this, "公告时间输入不能为空!", Toast.LENGTH_LONG).show();
                    ET_noticeContent.setFocusable(true);
                    ET_noticeContent.requestFocus();
                    return;
                } else {
                    ContentValues cv = new ContentValues();
                    cv.put("Content", ET_noticeContent.getText().toString());
                    cv.put("Time", ET_noticeTime.getText().toString());
                    cv.put("Title", ET_noticeTitle.getText().toString());
                    myDb.update("Notice", cv, "NID=?", new String[]{String.valueOf(NID)});
                    Toast.makeText(AdminNoticeUpdate.this, "更新成功!", Toast.LENGTH_SHORT).show();
                    finish();
                }
            }
        });
    }
}
