package com.example.dms;

public class Student {
            private String studentId;
            private String studentName;
            private String sex;
            private String netFee;

            public Student(String studentId, String studentName, String sex, String netFee) {
                this.studentId = studentId;
                this.studentName = studentName;
                this.sex = sex;
                this.netFee = netFee;
            }

            public String getStudentId() {
                return studentId;
            }

            public String getStudentName() {
                return studentName;
            }

            public String getSex() {
                return sex;
    }

    public String getNetFee() {
        return netFee;
    }
}
