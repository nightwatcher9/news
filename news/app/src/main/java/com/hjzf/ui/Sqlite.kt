package com.app.ui.activity

import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import androidx.annotation.Nullable

class Sqlite (var context:Context,name :String , version : Int) : SQLiteOpenHelper(context,name,null,version){
     //var user = "create table User(" + "UserID integer primary key,"+"Password varchar(10) "+"Name text,"+"Lived text,"+"Phone integer)"
       var user = "create table User(UserID integer primary key ,Password varchar(10), Name text , Live text , Phone integer)"
    override fun onCreate(db: SQLiteDatabase?) {
         db?.execSQL(user)
    }

    override fun onUpgrade(db: SQLiteDatabase?, oldVersion: Int, newVersion: Int) {

    }
}