package com.example.dms;

import android.content.ContentValues;
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

public class GeneralAdminBuildingBuild extends AppCompatActivity {
    private MySqlite sqlite;
    private SQLiteDatabase myDb;
    private String buildingNumber;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.general_admin_building_build);
        sqlite = new MySqlite(this, "Dormitory.db", null, 1);
        myDb = sqlite.getWritableDatabase();//打开数据库myDb

        final TextView building = (TextView) findViewById(R.id.buildingNumber);
        final EditText floor=(EditText)findViewById(R.id.floorSum);
        final EditText room = (EditText)findViewById(R.id.roomSum);
        final EditText bed=(EditText)findViewById(R.id.bedSum);

        Cursor cursor=myDb.rawQuery("select * from Building",null);
        cursor.moveToLast();
        buildingNumber= Integer.toString(cursor.getInt(Integer.parseInt(String.valueOf(cursor.getColumnIndex("BuildID"))))+1);
        building.setText("宿舍编号："+buildingNumber);


        Button ok =(Button)findViewById(R.id.ok);
        ok.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String floorSum =floor.getText().toString();
                String roomSum=room.getText().toString();
                String bedSum=bed.getText().toString();
                if(Integer.parseInt(roomSum)%Integer.parseInt(floorSum)!=0){
                    Toast.makeText(GeneralAdminBuildingBuild.this,"楼层数应整除宿舍数！",Toast.LENGTH_SHORT).show();
                    return ;
                }
                Log.d("SSS","sdawd  "+buildingNumber);
                ContentValues contentValues = new ContentValues(); //building
                contentValues.put("BuildID",Integer.parseInt(buildingNumber));
                contentValues.put("Floor",Integer.parseInt(floorSum));
                contentValues.put("Rsum",Integer.parseInt(roomSum));
                myDb.insert("Building",null,contentValues);

                int roomPerFloor = Integer.parseInt(roomSum)/Integer.parseInt(floorSum); //room
                String roomNumber=null;
                for(int i=1;i<=Integer.parseInt(floorSum);i++)
                {
                    for(int j=1;j<=roomPerFloor;j++){
                        roomNumber=buildingNumber+Integer.toString(i*100+j);
                        ContentValues contentValues1 = new ContentValues();
                        contentValues1.put("RoomID",roomNumber);
                        contentValues1.put("Total",bedSum);
                        contentValues1.put("Residual",bedSum);
                        contentValues1.put("WAE_Fees",0);
                        contentValues1.put("BuildID",buildingNumber);
                        myDb.insert("Room",null,contentValues1);
                        for(int k=1;k<Integer.parseInt(bedSum);k++){                //bed
                            ContentValues contentValues2 = new ContentValues();
                            contentValues2.put("BedID",k);
                            contentValues2.put("RoomID",roomNumber);
                            myDb.insert("Bed",null,contentValues2);

                        }
                    }
                }

                ContentValues contentValues3 = new ContentValues();
                contentValues3.put("AdID",Integer.parseInt(buildingNumber));
                contentValues3.put("PassWord",buildingNumber+buildingNumber+buildingNumber);
                contentValues3.put("BuildID",Integer.parseInt(buildingNumber));
                myDb.insert("Admin",null,contentValues3);
                Toast.makeText(GeneralAdminBuildingBuild.this,"修建成功",Toast.LENGTH_SHORT).show();
                finish();
            }

        });
    }
}
