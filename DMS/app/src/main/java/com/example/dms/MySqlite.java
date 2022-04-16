package com.example.dms;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import androidx.annotation.Nullable;

public class MySqlite extends SQLiteOpenHelper {
    public static String User="create table User( UserID int(10) primary key,Password varchar(15),RoomID int(10),UserName text,"+
            "Sex int(4),CostComments int(4),NetFees int(10),Comments text)";
    public static String Lost="create table Lost(LostID int(10) primary key,ReceiveComments int(2),Time datetime,Information text,"+
            "AdID int(10), Comments text)";
    public static String Room="create table Room(RoomID int(10) primary key,Total int(4),Residual int(2),"+
            "RoomType int(4),WAE_Fees int(20),Comments text,BuildID int(10))";
    public static String Bed="create table Bed(BedID int(10) ,UserID int(10),Free int(2),RoomID int(10) ,Comments text,primary key(BedID,RoomID))";
    public static String Leave="create table Leave(LeaveID integer PRIMARY KEY AUTOINCREMENT,UserID int(10),Agree int(2), ApplyTime datetime,Comments text)";
    public static String Repair="create table Repair(RepID integer PRIMARY KEY AUTOINCREMENT,UserID int(10), Time datetime,Information text,Comments text)";
    public static String Admin="create table Admin(AdID int(10) primary key,PassWord varchar(20),BuildID int(10),Comments text)";
    public static String Receive_Lost="create table Admin_Lost(User int(10) ,LostID int(10) ,Telphone int(12), Time datetime,"+
            " Process varchar(20),Comments text,primary key(User,LostID))";
    public static String Adimin_Repair="create table Admin_Repari(AdID int(10) ,RepID int(10) , Time datetime,"+
            " Comments text ,primary key(AdID,RepID))";
    public static String Adimin_Leave="create table Admin_Leave(AdID int(10) ,LeaveID int(10) , Time datetime,"+
            " Comments text,primary key(AdID,LeaveID))";
    public static String Building="create table Building(BuildID int(10) primary key,Floor int(4),Rsum int(10),Money int(10),Comments text)";
    public static String Notice="create table Notice(NID integer PRIMARY KEY AUTOINCREMENT,AdID int(10),Title text,Content text,Time datetime,Comments text)";
    public static String General_Admin="create table General_Admin(GAID int(10) primary key,password varchar(15),Comments text)";
    public static String Building_Arrange="create table Building_Arrange(BuildID int(10) ,GAID int(10) ,Arrangement text,Time datetime,Comments text,primary key(BuildID,GAID))";
    public MySqlite(@Nullable Context context, @Nullable String name, @Nullable SQLiteDatabase.CursorFactory factory, int version) {
        super(context, name, factory, version);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL(User);
        db.execSQL(Lost);
        db.execSQL(Room);
        db.execSQL(Bed);
        db.execSQL(Leave);
        db.execSQL(Repair);
        db.execSQL(Admin);
        db.execSQL(Receive_Lost);
        db.execSQL(Adimin_Repair);
        db.execSQL(Adimin_Leave);
        db.execSQL(Building);
        db.execSQL(Notice);
        db.execSQL(General_Admin);
        db.execSQL(Building_Arrange);
        //db.execSQL("insert into User (UserID,RoomID,UserName,Sex,CostComments,NetFees,Comments) values (?,?,?,?,?,?,?)",new String[]{"123", "321","何思源","1" ,"1","200"});
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int i, int i1) {
        //数据库升级
    }
}
