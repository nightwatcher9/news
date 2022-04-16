package com.example.dms;

public class Bed {
    String roomNumber;
    int bedNumber;
    Student student;

    public Bed(int bedNumber, Student student) {
        this.bedNumber = bedNumber;
        this.student=student;
    }

    public String getRoomNumber() {
        return roomNumber;
    }

    public void setRoomNumber(String roomNumber) {
        this.roomNumber = roomNumber;
    }

    public int getBedNumber() {
        return bedNumber;
    }

    public Student getStudent() {
        return student;
    }
}
