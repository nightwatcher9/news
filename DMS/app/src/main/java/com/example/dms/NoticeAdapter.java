package com.example.dms;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import java.util.HashMap;
import java.util.List;


public class NoticeAdapter extends ArrayAdapter<Notice> {

    private int resId;
    private Context context;
    Notice notice;
    MySqlite sqlite;
    SQLiteDatabase myDb;
    private String AdID;

    public NoticeAdapter(Context context, int resource, List<Notice> notices){
        super(context,resource,notices);
        resId=resource;
        this.context = context;
    }

    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        View view;
        view= LayoutInflater.from(getContext()).inflate(resId,parent,false);


        notice=getItem(position);
        TextView title=(TextView)view.findViewById(R.id.title);
        title.setText(notice.getTitle());
        TextView time=(TextView)view.findViewById(R.id.time);
        time.setText(notice.getTime());
        AdID=notice.getAdID();

        Button button1 = (Button)view.findViewById(R.id.button1) ;
        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(context,AdminNoticeUpdate.class);
                intent.putExtra("NID",notice.getNid());
                context.startActivity(intent);
            }
        });

        Button button2 = (Button)view.findViewById(R.id.button2);
        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                AlertDialog.Builder dialog=new AlertDialog.Builder(context);
                dialog.setTitle("是否要删除这条数据？");
                dialog.setCancelable(true);
                dialog.setNegativeButton("确认", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        sqlite = new MySqlite(context, "Dormitory.db", null, 1);
                        myDb = sqlite.getWritableDatabase();
                        myDb.delete("Notice","NID=?",new String[]{Integer.toString(notice.getNid())});
                        Toast.makeText(context, "删除成功!", Toast.LENGTH_LONG).show();
                        Intent intent = new Intent(context,AdminNotice.class);
                        intent.putExtra("adId",AdID);
                        context.startActivity(intent);
                    }
                });
                dialog.setPositiveButton("取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {

                    }
                });
                dialog.show();

            }
        });
        return view;

    }
}
