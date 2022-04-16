package com.example.dms;

import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.util.Log;
import android.widget.ExpandableListView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;
import java.util.List;

public class AdminRoomInformation extends AppCompatActivity {
    private MySqlite sqlite;
    private SQLiteDatabase myDb;
    private String adId;
    private String roomNumber;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.admin_home_room_information);
        sqlite = new MySqlite(this, "Dormitory.db", null, 1);
        myDb = sqlite.getWritableDatabase();//打开数据库myDb

        ExpandableListView expandableListView = (ExpandableListView)findViewById(R.id.expandableList);
        Intent intent = getIntent();
        roomNumber = intent.getStringExtra("roomNumber");

        Cursor cursor = myDb.rawQuery("select * from User where RoomID=?",new String[]{roomNumber});
        Student student;
        List<Student> students = new ArrayList<Student>();
        if (cursor.moveToFirst()){
            String studentId;
            String studentName;
            String sex;
            String netFee;
            do{
                studentId=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("UserID"))));
                studentName=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("UserName"))));
                sex=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("Sex"))));
                netFee=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("NetFees"))));
                student = new Student(studentId,studentName,sex,netFee);
                students.add(student);
            }while(cursor.moveToNext());
        }

        List<Bed> beds=new ArrayList<Bed>();
        Bed bed;
        cursor = myDb.rawQuery("select * from Bed where RoomID=?",new String[]{roomNumber});
        if(cursor.moveToFirst()){
            int i;
            String bedNumber;
            String studentId;
            do{
                bedNumber=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("BedID"))));
                studentId=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("UserID"))));
                bed=new Bed(Integer.parseInt(bedNumber), null);
                bed.setRoomNumber(roomNumber);
                for(i=0; i<students.size();i++){
                    if(students.get(i).getStudentId().equals(studentId))
                        bed=new Bed(Integer.parseInt(bedNumber),students.get(i));
                }
                beds.add(bed);
            }while(cursor.moveToNext());

        }
        Log.d("ssdad","roomNumber is"+Integer.toString(beds.size()));
        BedAdapter bedAdapter=new BedAdapter(beds,this);
        expandableListView.setAdapter(bedAdapter);

    }
}
