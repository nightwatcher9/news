package com.example.dms;

import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.widget.AdapterView;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.RecyclerView;
import androidx.recyclerview.widget.StaggeredGridLayoutManager;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class AdminHome extends AppCompatActivity {
    private MySqlite sqlite;
    private SQLiteDatabase myDb;
    private String adId;
    private List<Room> rooms=new ArrayList<Room>();
    private Room room;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.admin_home);
        sqlite = new MySqlite(this, "Dormitory.db", null, 1);
        myDb = sqlite.getWritableDatabase();//打开数据库myDb
        Intent intent = getIntent();
        adId=intent.getStringExtra("adId");

        TextView buildingNumber= (TextView)findViewById(R.id.buildingNumber);
        buildingNumber.setText(adId+"号宿舍楼");


        Cursor cursor = myDb.rawQuery("select * from Room where BuildID=?",new String[]{adId});
        if (cursor.moveToFirst()){
            do {
                int roomId = cursor.getInt(Integer.parseInt(String.valueOf(cursor.getColumnIndex("RoomID"))));
                int residual =cursor.getInt(Integer.parseInt(String.valueOf(cursor.getColumnIndex("Residual"))));
                if(residual>0){
                    room=new Room(R.drawable.ic_room_green,Integer.toString(roomId));
                }
                else{
                    room=new Room(R.drawable.ic_room_red,Integer.toString(roomId));
                }
                rooms.add(room);
            }while (cursor.moveToNext());
        }

        final RecyclerView recyclerView=(RecyclerView)findViewById(R.id.recyclerView);
        recyclerView.setLayoutManager(new StaggeredGridLayoutManager(4, StaggeredGridLayoutManager.VERTICAL));
        recyclerView.setAdapter(new RoomAdapter(rooms));

        final EditText searchBar= (EditText)findViewById(R.id.searchBar);
        searchBar.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView textView, int actionID, KeyEvent keyEvent) {
                if(actionID==EditorInfo.IME_ACTION_SEND ||((keyEvent!=null&&keyEvent.getKeyCode()== KeyEvent.KEYCODE_ENTER)&&keyEvent.getAction()==KeyEvent.ACTION_DOWN))
                {
                    rooms.clear();
                    String searchMsg = searchBar.getText().toString();
                    Cursor cursor = myDb.rawQuery("select * from  Room where RoomID like ? and BuildID = ?",new String[]{"%"+searchMsg+"%", adId});
                    int i=cursor.getColumnIndex("RoomID");
                    int j=cursor.getColumnIndex("Residual");
                    if (cursor.moveToFirst()){
                        do {
                            String roomNumber = cursor.getString(i);
                            int residual = cursor.getInt(j);
                            if(residual>0)
                                room=new Room(R.drawable.ic_room_green,roomNumber);
                            else
                                room=new Room(R.drawable.ic_room_red,roomNumber);
                            rooms.add(room);
                            Log.d("SS","dwada"+room.getRoomNumber());
                        }while(cursor.moveToNext());
                    }
                    RoomAdapter adapter=new RoomAdapter(rooms);
                    recyclerView.setAdapter(adapter);
                    adapter.notifyDataSetChanged();
                    return true;
                }
                return false;
            }
        });

    }

    public void navigationMy(View view){
        Intent intent = new Intent(this, AdminMy.class);
        intent.putExtra("adId",adId);
        startActivity(intent);
    }

    public void navigationNotice(View view){
        Intent intent = new Intent(this, AdminNotice.class);
        intent.putExtra("adId",adId);
        startActivity(intent);
    }
}
