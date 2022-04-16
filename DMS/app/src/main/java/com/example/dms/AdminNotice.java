package com.example.dms;

import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class AdminNotice extends AppCompatActivity {

    private List<Notice> notices;
    private ListView listView;
    private NoticeAdapter adapter;
    private String adId;
    private Notice notice;
    String time;
    String title;
    private MySqlite sqlite;
    private SQLiteDatabase myDb;



    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.admin_notice);
        Intent intent=getIntent();
        adId=intent.getStringExtra("adId");

        init();
        sqlite = new MySqlite(this, "Dormitory.db", null, 1);
        myDb = sqlite.getWritableDatabase();
        //将数据显示在页面上
        initDate(notices);

        Collections.reverse(notices);
        adapter=new NoticeAdapter(AdminNotice.this,R.layout.notice,notices);
        listView.setAdapter(adapter);

        ImageView add = (ImageView) findViewById(R.id.add);
        add.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(AdminNotice.this,AdminNoticeAdd.class);
                intent.putExtra("adId",adId);
                startActivity(intent);

            }
        });

        final EditText searchBar = (EditText)findViewById(R.id.searchBar);
        searchBar.setImeOptions(EditorInfo.IME_ACTION_SEARCH);
        searchBar.setInputType(EditorInfo.TYPE_CLASS_TEXT);
        searchBar.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView textView, int actionID, KeyEvent keyEvent) {
                if(actionID==EditorInfo.IME_ACTION_SEND ||((keyEvent!=null&&keyEvent.getKeyCode()== KeyEvent.KEYCODE_ENTER)&&keyEvent.getAction()==KeyEvent.ACTION_DOWN))
                {
                    notices.clear();
                    String str = searchBar.getText().toString();
                    Cursor cursor = myDb.rawQuery("select * from  Notice where Title like ?",new String[]{"%"+str+"%"});
                    int i=cursor.getColumnIndex("NID");
                    int j=cursor.getColumnIndex("Title");
                    int o=cursor.getColumnIndex("Time");
                    if (cursor.moveToFirst()){
                        do {
                            int NID = cursor.getInt(i);
                            String time = cursor.getString(o);
                            String title = cursor.getString(j);
                            Log.d("TTT","NID"+NID);
                            notice=new Notice(NID,title,time,adId);
                            notices.add(notice);
                        }while(cursor.moveToNext());
                    }
                    Collections.reverse(notices);
                    adapter=new NoticeAdapter(AdminNotice.this,R.layout.notice,notices);
                    listView.setAdapter(adapter);
                    adapter.notifyDataSetChanged();
                    return true;
                }
                return false;

            }
        });

    }

    public  void init(){
        listView=(ListView) findViewById(R.id.lv_text_view);
        notices=new ArrayList<Notice>();

    }

    public  void initDate(List<Notice> notices){

        Intent intent = getIntent();
        String  adId=intent.getStringExtra("adId");
        //模拟创建数据
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        String ly_time = sdf.format(new java.util.Date());
        Cursor cursor = myDb.rawQuery("select * from Notice  where AdID = ?", new String[]{adId},null);
        if (cursor.moveToFirst()) {
            do {
                int NID = cursor.getInt(Integer.parseInt(String.valueOf(cursor.getColumnIndex("NID"))));
                time=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("Time"))));
                title=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("Title"))));
                notice =new Notice(NID,title,time,adId);
                notices.add(notice);
            }while(cursor.moveToNext());
        }
    }
    public void navigationHome(View view){
        Intent intent = new Intent(this, AdminHome.class);
        intent.putExtra("adId",adId);
        startActivity(intent);
    }

    public void navigationMy(View view){
        Intent intent = new Intent(this, AdminMy.class);
        intent.putExtra("adId",adId);
        startActivity(intent);
    }

}
