package com.example.dms;

import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.widget.EditText;
import android.widget.ExpandableListAdapter;
import android.widget.ExpandableListView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class StudentNotice extends AppCompatActivity {
    private List<NoticeExpandable> notices = new ArrayList<NoticeExpandable>();
    private NoticeExpandable notice;
    private MySqlite sqlite;
    private SQLiteDatabase myDb;
    private String studentId;
    private String roomNumber;
    private String adId;

    @Override
    protected void onCreate(@Nullable @org.jetbrains.annotations.Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.student_notice);
        sqlite = new MySqlite(this, "Dormitory.db", null, 1);
        myDb = sqlite.getWritableDatabase();

        final ExpandableListView expandableListView = (ExpandableListView)findViewById(R.id.expandableList);
        Intent intent = getIntent();
        studentId=intent.getStringExtra("studentId");
        Cursor cursor = myDb.rawQuery("select * from User where UserID = ? ",new String[]{studentId});
        if(cursor.moveToFirst()){
            roomNumber=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("RoomID"))));
        }
        cursor=myDb.rawQuery("select * from Room Where RoomID = ?", new String[]{roomNumber});
        if (cursor.moveToFirst()){
            adId=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("BuildID"))));
        }
        cursor=myDb.rawQuery("select * from Notice Where AdID = ?", new String[]{adId});
        if(cursor.moveToFirst()){
            String title;
            String time;
            String adId;
            String content;
            do{
                title=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("Title"))));
                time=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("Time"))));
                adId=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("AdID"))));
                content=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("Content"))));
                notice=new NoticeExpandable(title,time,adId,content);
                notices.add(notice);
            }while(cursor.moveToNext());
        }
        Collections.reverse(notices);
        NoticeExpandableAdapter adapter = new NoticeExpandableAdapter(notices,this);
        expandableListView.setAdapter(adapter);

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
                    int i=cursor.getColumnIndex("AdID");
                    int j=cursor.getColumnIndex("Title");
                    int o=cursor.getColumnIndex("Time");
                    int k=cursor.getColumnIndex("Content");
                    if (cursor.moveToFirst()){
                        do {
                            String adId = cursor.getString(i);
                            String time = cursor.getString(o);
                            String title = cursor.getString(j);
                            String content = cursor.getString(k);
                            notice=new NoticeExpandable(title,time,adId,content);
                            notices.add(notice);
                        }while(cursor.moveToNext());
                    }
                    Collections.reverse(notices);
                    NoticeExpandableAdapter adapter=new NoticeExpandableAdapter(notices, StudentNotice.this);
                    expandableListView.setAdapter(adapter);
                    adapter.notifyDataSetChanged();
                    return true;
                }
                return false;

            }
        });
    }
    public void navigationMy(View view){
        Intent intent = new Intent(StudentNotice.this, StudentMy.class);
        intent.putExtra("studentId",studentId);
        startActivity(intent);
    }
}
