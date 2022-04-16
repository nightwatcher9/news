package com.example.dms;

public class Notice {
    private int Nid;
    private String title;
    private String time;
    private String AdID;
    public Notice(int Nid,String title, String time,String adID){
        this.title=title;
        this.time=time;
        this.Nid=Nid;
        this.AdID=adID;

    }

    public int getNid() {
        return Nid;
    }

    public String getTitle() {
        return title;
    }

    public String getTime() {
        return time;
    }
    public String getAdID(){
        return AdID;
    }
}