package com.example.dms;

import android.content.ContentValues;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Color;
import android.os.Bundle;
import android.text.InputType;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class Login extends AppCompatActivity {
    public MySqlite sqlite;
    public SQLiteDatabase myDb;
    String type;
    int i=1;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.login);
        sqlite = new MySqlite(this, "Dormitory.db", null, 1);
        myDb = sqlite.getWritableDatabase();//打开数据库myDb
/*
        ContentValues contentValues = new ContentValues();
        contentValues.put("UserID",220180002);
        contentValues.put("password",180002);
        contentValues.put("RoomID",1202);
        contentValues.put("UserName","大雄");
        contentValues.put("Sex",1);
        contentValues.put("NetFees",0);
        myDb.insert("User",null,contentValues);
*/

        TextView tv1=findViewById(R.id.t4);
        tv1.setTextColor(Color.BLUE);
        type="User";
    }
    public void ClickTVs(View view){

        TextView tv1=findViewById(R.id.t4);
        TextView tv2=findViewById(R.id.t6);
        TextView tv3=findViewById(R.id.t8);
        if(view==tv1) {
            tv1.setTextColor(Color.BLUE);
            type="User";
        }
        else tv1.setTextColor(Color.GRAY);
        if(view==tv2) {
            tv2.setTextColor(Color.BLUE);;
            type="Admin";
        }
        else tv2.setTextColor(Color.GRAY);
        if(view==tv3) {
            tv3.setTextColor(Color.BLUE);
            type="General_Admin";
        }
        else tv3.setTextColor(Color.GRAY);

    }
    public void ClickView1(View view){
        ImageView im1=findViewById(R.id.hidePassword);
        TextView tv1=findViewById(R.id.t1);
        if(i%2!=0) {
            im1.setColorFilter(Color.BLUE);
            tv1.setInputType(InputType.TYPE_TEXT_VARIATION_VISIBLE_PASSWORD);
        }
        else {
            im1.setColorFilter(Color.GRAY);
            tv1.setInputType(InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_PASSWORD);
        }
        i++;
    }
    public void enter(View view){
        int j=0;
        EditText e1=findViewById(R.id.t);
        EditText e2=findViewById(R.id.t1);
        //   TextView t4=findViewById(R.id.t4);//用户
        //  TextView t6=findViewById(R.id.t6);//管理员
        //  TextView t8=findViewById(R.id.t8);//超级管理员
        String id=e1.getText().toString();
        // i= Integer.valueOf(id).intValue();
        String pwd=e2.getText().toString();
        if(id!=null&&pwd!=null)
            j=dbQueryuserid(id,type,pwd);
        if(j==1) {
            if(type.equals("User")) {
                Intent intent= new Intent(this, StudentNotice.class);
                intent.putExtra("studentId",id);
                startActivity(intent);
            }
            else if(type.equals("Admin")) {
                Intent intent= new Intent(this, AdminHome.class);
                intent.putExtra("adId",id);
                startActivity(intent);
            }
            else if(type.equals("General_Admin")) {
                Intent intent= new Intent(this, GeneralAdminHome.class);
                intent.putExtra("GAId",id);
                startActivity(intent);
            }
        }
        if(j==0)
            Toast.makeText(this,"账户或密码错误",Toast.LENGTH_LONG).show();
    }
    public int dbQueryuserid(String id,String types,String pwd){
        String sql=null;
        if(types.equals("User")){
            sql="select password from '"+types+"'where userId='"+id+"'";
            Cursor cursor = myDb.rawQuery( sql,null);
            if (cursor.moveToNext()){
                String pwd1=cursor.getString(cursor.getColumnIndex("Password"));
                if(pwd.equals(pwd1))
                    return 1;
            }
        }
        else if(types.equals("Admin")){
            sql="select password from '"+types+"'where AdId='"+id+"'";
            Cursor cursor = myDb.rawQuery( sql,null);
            if (cursor.moveToNext()){
                String pwd1=cursor.getString(cursor.getColumnIndex("PassWord"));
                if(pwd.equals(pwd1))
                    return 1;
            }
        }

        else if(types.equals("General_Admin")){
            sql="select password from '"+types+"'where GAid='"+id+"'";
            Cursor cursor = myDb.rawQuery( sql,null);
            if (cursor.moveToNext()){
                String pwd1=cursor.getString(cursor.getColumnIndex("password"));
                if(pwd.equals(pwd1))
                    return 1;
            }
        }

        return 0;
    }
}
