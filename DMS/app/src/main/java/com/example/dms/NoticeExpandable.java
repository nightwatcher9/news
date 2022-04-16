package com.example.dms;

public class NoticeExpandable {
    private String title;
    private String time;
    private String AdID;
    private String content;

    public NoticeExpandable(String title, String time, String adID, String content) {
        this.title = title;
        this.time = time;
        AdID = adID;
        this.content = content;
    }

    public String getTitle() {
        return title;
    }

    public String getTime() {
        return time;
    }

    public String getAdID() {
        return AdID;
    }

    public String getContent() {
        return content;
    }
}
