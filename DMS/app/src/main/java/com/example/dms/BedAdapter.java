package com.example.dms;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.provider.ContactsContract;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseExpandableListAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class BedAdapter extends BaseExpandableListAdapter {
    private MySqlite sqlite;
    private SQLiteDatabase myDb;
    private String adId;
    private List<Bed> beds;
    private Context context;

    public BedAdapter(List<Bed> beds, Context context){
        this.beds=beds;
        this.context=context;
    }

    @Override
    public int getGroupCount() {
        return beds.size();
    }

    @Override
    public int getChildrenCount(int groupPosition) {
        return 1;
    }

    @Override
    public Object getGroup(int groupPosition) {
        return beds.get(groupPosition);
    }

    @Override
    public Object getChild(int groupPosition, int childPosition) {
        return beds.get(groupPosition).getStudent();
    }

    @Override
    public long getGroupId(int groupPosition) {
        return 0;
    }

    @Override
    public long getChildId(int groupPosition, int childPosition) {
        return 0;
    }

    @Override
    public boolean hasStableIds() {
        return false;
    }

    @Override
    public View getGroupView(int groupPosition, boolean isExpanded, View convertView, ViewGroup parent) {
        View view = LayoutInflater.from(context).inflate(R.layout.bed_group,parent,false);
        Bed bed = beds.get(groupPosition);
        ImageView bedIc=(ImageView)view.findViewById(R.id.bedIc);
        TextView bedNumber=(TextView)view.findViewById(R.id.bedNumber);
        if(bed.getStudent()!=null)
            bedIc.setImageResource(R.drawable.ic_bed_red);
        else
            bedIc.setImageResource(R.drawable.ic_bed_green);
        bedNumber.setText(Integer.toString(bed.getBedNumber())+"号床");
        return view;
    }

    @Override
    public View getChildView(int groupPosition, int childPosition, boolean isLastChild, View convertView, ViewGroup parent) {
        final Bed bed = beds.get(groupPosition);
        final Student student = bed.getStudent();
        final View view;
        if(student!=null){
            view = LayoutInflater.from(context).inflate(R.layout.bed_child,parent,false);
            TextView studentId=(TextView)view.findViewById(R.id.studentId);
            TextView studentName=(TextView)view.findViewById(R.id.studentName);
            TextView studentSex=(TextView)view.findViewById(R.id.studentSex);
            TextView studentNetFee=(TextView)view.findViewById(R.id.studentNetFee);
            studentId.setText(studentId.getText()+student.getStudentId());
            studentName.setText(studentName.getText()+student.getStudentName());
            studentSex.setText(studentSex.getText()+student.getSex());
            studentNetFee.setText(studentNetFee.getText()+student.getNetFee());

            Button quit = (Button)view.findViewById(R.id.quit);
            quit.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    sqlite = new MySqlite(context, "Dormitory.db", null, 1);
                    myDb = sqlite.getWritableDatabase();//打开数据库myDb
                    ContentValues contentValues = new ContentValues();
                    int bedNumber = bed.getBedNumber();
                    int residual;
                    String studentId = student.getStudentId();
                    String roomNumber = null;
                    Cursor cursor=myDb.rawQuery("select RoomID from User where UserID=?",new String[]{studentId});
                    if (cursor.moveToFirst()) {
                        roomNumber=cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("RoomID"))));
                        String sqliteUpdate = "UPDATE User SET RoomID = NULL WHERE UserID = "+studentId;
                        myDb.execSQL(sqliteUpdate);
                    }
                    cursor=myDb.rawQuery("select * from Room where RoomID=?",new String[]{roomNumber});
                    if (cursor.moveToFirst()) {
                        residual=Integer.parseInt(cursor.getString(Integer.parseInt(String.valueOf(cursor.getColumnIndex("Residual")))));
                        residual++;
                        String sqliteUpdate = "UPDATE Room SET Residual ="+Integer.toString(residual)+" WHERE RoomID = "+roomNumber;
                        myDb.execSQL(sqliteUpdate);
                    }
                        String sqliteUpdate = "UPDATE Bed SET UserID = NULL WHERE RoomID = "+roomNumber+" and BedID = "+ Integer.toString(bedNumber);
                        myDb.execSQL(sqliteUpdate);
                        Toast.makeText(context,"退出成功！",Toast.LENGTH_SHORT).show();

                }
            });

        }
        else {
            view = LayoutInflater.from(context).inflate(R.layout.bed_null_child,parent,false);
            Button roomIn = (Button)view.findViewById(R.id.roomIn);
            roomIn.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    sqlite = new MySqlite(context, "Dormitory.db", null, 1);
                    myDb = sqlite.getWritableDatabase();//打开数据库myDb
                    EditText editTextStudentId = (EditText)view.findViewById(R.id.studentId);
                    String studentId = editTextStudentId.getText().toString();
                    String roomNumber = bed.getRoomNumber();
                    int bedNumber=bed.getBedNumber();
                    String sqliteCount = "SELECT * FROM User WHERE UserID="+studentId;
                    Cursor cursor = myDb.rawQuery(sqliteCount,null);
                    cursor.moveToFirst();
                    long count = cursor.getLong(0);
                    if (count>0){
                        String sqliteUpdate="UPDATE User SET RoomID = "+roomNumber+" WHERE UserID ="+studentId;
                        myDb.execSQL(sqliteUpdate);
                        sqliteUpdate="UPDATE Bed SET UserID = "+studentId+" WHERE BedID ="+Integer.toString(bedNumber)+" and RoomID ="+roomNumber;
                        myDb.execSQL(sqliteUpdate);
                        cursor = myDb.rawQuery("select * from Room where RoomID=?",new String[]{roomNumber});
                        if(cursor.moveToFirst()){
                            int residual =cursor.getInt(Integer.parseInt(String.valueOf(cursor.getColumnIndex("Residual"))));
                            residual--;
                            sqliteUpdate="UPDATE Room SET Residual = "+Integer.toString(residual)+" WHERE RoomID = "+roomNumber;
                            myDb.execSQL(sqliteUpdate);
                            Toast.makeText(context,"入住成功！",Toast.LENGTH_SHORT).show();
                        }
                    }
                    else{
                        Toast.makeText(context,"学号错误！",Toast.LENGTH_SHORT).show();
                    }

                }
            });
        }
        return view;

    }

    @Override
    public boolean isChildSelectable(int groupPosition, int childPosition) {
        return false;
    }
}
