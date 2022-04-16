package com.example.dms;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;
import java.util.List;

public class GeneralAdminBuildingAbandon extends AppCompatActivity {
    private MySqlite sqlite;
    private SQLiteDatabase myDb;
    private List<String> buildingNumbers = new ArrayList<String>();
    private String buildingNumber = null;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.general_admin_building_abandon);
        sqlite = new MySqlite(this, "Dormitory.db", null, 1);
        myDb = sqlite.getWritableDatabase();//打开数据库myDb

        Spinner spinner = (Spinner)findViewById(R.id.buildingAbandonSpinner);

        Cursor cursor =myDb.rawQuery("select * from Building",null);
        if (cursor.moveToFirst()){
            do {
                buildingNumber=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("BuildID"))));
                buildingNumbers.add(buildingNumber+"号宿舍楼");
            }while(cursor.moveToNext());
        }

        ArrayAdapter<String> spinnerAdapter = new ArrayAdapter<String>(this,android.R.layout.simple_spinner_dropdown_item,buildingNumbers);
        spinnerAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(spinnerAdapter);
        spinner.setSelection(-1,true);
        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                int length=parent.getSelectedItem().toString().length();
                buildingNumber=parent.getSelectedItem().toString().substring(0,length-4);
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

        Button ok = (Button)findViewById(R.id.ok);
        ok.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
              String sqlDelete = "delete from Building where BuildID = "+buildingNumber; //building
              myDb.execSQL(sqlDelete);
              sqlDelete="delete from Admin where BuildID = "+buildingNumber; //admin
              myDb.execSQL(sqlDelete);
              Cursor cursor1 =myDb.rawQuery("select * from Room where BuildID = ?",new String[]{buildingNumber});
              if (cursor1.moveToFirst()){
                  int roomNumber;
                  String sqliteUpdate;
                  do {
                      roomNumber=cursor1.getInt(Integer.parseInt(String.valueOf(cursor1.getColumnIndex("RoomID"))));
                      myDb.delete("Room","RoomID=?",new String[]{Integer.toString(roomNumber)}); //room
                      myDb.delete("Bed","RoomID=?",new String[]{Integer.toString(roomNumber)});  //bed
                      sqliteUpdate = "UPDATE User SET RoomID = NULL WHERE RoomID = "+roomNumber;                    //user
                      myDb.execSQL(sqliteUpdate);
                  }while(cursor1.moveToNext());
              }
              Toast.makeText(GeneralAdminBuildingAbandon.this,"删除成功！",Toast.LENGTH_SHORT).show();
              finish();
            }
        });
    }
}
