package com.example.dms;

import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class StudentMy extends AppCompatActivity {
    private MySqlite sqlite;
    private SQLiteDatabase myDb;
    private String studentId;
    @Override
    protected void onCreate(@Nullable @org.jetbrains.annotations.Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.student_my);
        Intent intent =getIntent();
        studentId=intent.getStringExtra("studentId");
        sqlite = new MySqlite(this, "Dormitory.db", null, 1);
        myDb = sqlite.getWritableDatabase();//打开数据库myDb

        String studentName = null;
        String netFee = null;
        Cursor cursor = myDb.rawQuery("select * from User where UserID = ?", new String[]{studentId});
        if(cursor.moveToFirst()){
            studentName = cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("UserName"))));;
            netFee=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("NetFees"))));;
        }
        TextView Name = (TextView)findViewById(R.id.studentName);
        TextView Id = (TextView)findViewById(R.id.studentId);
        TextView Fee = (TextView)findViewById(R.id.netFee);
        Name.setText("姓名："+studentName);
        Id.setText("学号："+studentId);
        Fee.setText("网费："+netFee+"¥");

        Button changePassword = (Button)findViewById(R.id.changePassword); //更改密码
        changePassword.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(StudentMy.this, ChangePassword.class);
                intent.putExtra("id",studentId);
                intent.putExtra("type","student");
                startActivity(intent);
            }
        });

        Button quit = (Button)findViewById(R.id.quit);  //退出账户
        quit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(StudentMy.this,Login.class);
                startActivity(intent);
            }
        });

    }

    public void navigationNotice(View view){
        Intent intent = new Intent(this, StudentNotice.class);
        intent.putExtra("studentId",studentId);
        startActivity(intent);
    }
}
