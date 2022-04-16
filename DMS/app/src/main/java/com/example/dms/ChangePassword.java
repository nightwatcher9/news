package com.example.dms;

import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class ChangePassword extends AppCompatActivity {
    private MySqlite sqlite;
    private SQLiteDatabase myDb;
    private String id;
    private String type;
    private String password=null;
    private String newPassword=null;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.chenge_password);
        sqlite = new MySqlite(this, "Dormitory.db", null, 1);
        myDb = sqlite.getWritableDatabase();//打开数据库myDb

        Intent intent = getIntent();
        id=intent.getStringExtra("id");
        type = intent.getStringExtra("type");

        final EditText originalPassword = (EditText)findViewById(R.id.originalPassword);
        final EditText newPassword_1=(EditText)findViewById(R.id.newPassword1);
        final EditText newPassword_2=(EditText)findViewById(R.id.newPassword2);

        Cursor cursor;
        if(type.equals("admin")){
            cursor = myDb.rawQuery("select * from Admin where AdID=?",new String[]{id});
            if(cursor.moveToFirst()){
                password  = cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("PassWord"))));
            }
        }
        else if(type.equals("student")){
            cursor = myDb.rawQuery("select * from User where UserID=?",new String[]{id});
            if(cursor.moveToFirst()){
                password  = cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("Password"))));
            }
        }
        else{
            cursor = myDb.rawQuery("select * from General_Admin where GAID=?",new String[]{id});
            if(cursor.moveToFirst()){
                password  = cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("password"))));
            }
        }

        Log.d("SSS","dwad"+password);

        Button ok = (Button)findViewById(R.id.ok);
        ok.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(originalPassword.getText().toString().equals(password) && newPassword_1.getText().toString().equals(newPassword_2.getText().toString())){
                    newPassword=newPassword_1.getText().toString();
                    String sqliteUpdate = null;
                    if(type.equals("admin")){
                        sqliteUpdate="UPDATE Admin SET PassWord ="+newPassword+" WHERE AdID="+id;
                        myDb.execSQL(sqliteUpdate);
                    }else if(type.equals("student")){
                        sqliteUpdate="UPDATE User SET Password ="+newPassword+" WHERE UserID="+id;
                        myDb.execSQL(sqliteUpdate);
                    }
                    else{
                        sqliteUpdate="UPDATE General_Admin SET password ="+newPassword+" WHERE GAID="+id;
                        myDb.execSQL(sqliteUpdate);
                    }
                    Toast toast= Toast.makeText(ChangePassword.this,"更改成功！",Toast.LENGTH_SHORT);
                    toast.show();
                    finish();
                }
                else{
                    if(!originalPassword.equals(password))
                        Toast.makeText(ChangePassword.this,"原密码错误！",Toast.LENGTH_SHORT).show();
                    else
                        Toast.makeText(ChangePassword.this,"两次密码不相同！",Toast.LENGTH_SHORT).show();
                }
            }
        });
    }
}
