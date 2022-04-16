package com.example.dms;

public class Room {
    private int picId;
    private String roomNumber;

    public Room(int picId, String roomNumber) {
        this.picId = picId;
        this.roomNumber = roomNumber;
    }

    public int getPicId() {
        return picId;
    }

    public String getRoomNumber() {
        return roomNumber;
    }
}
