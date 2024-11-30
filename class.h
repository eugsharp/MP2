#include <iostream>
#include <string>
#include <fstream>
#include "classroom.h"

#define MAX_STUDENTS 30

using namespace std;

class Class {

    string subject;
    string days;
    string time;
    string sectionName;
    Classroom classroom;
    // Teacher teacherName;
    // Student students[30][2]; // first for number, second for name

    int studentCount;

public:
    Class(string s, string d, string t, string sN) {
        subject = s;
        days = d;
        time = t;
        sectionName = sN;
        studentCount = 0;
    }

    string getSubject() {
        return subject;
    }

    string getDays() {
        return days;
    }

    string getTime() {
        return time;
    }

    string getSectionName() {
        return sectionName;
    }

    Classroom getClassroom() { 
        return classroom;
    }

    void setClassroom(int rn, string bcn, string ba, string ct, string lt) { 
        classroom.setRoomNumber(rn);
        classroom.setBuildingName(bcn);
        classroom.setBuildingAbbreviation(ba);
        classroom.setClassroomType(ct);
        classroom.setLaboratoryType(lt);
    }

    // string getClassroomName() {
    //     return classroomName;
    // }

    // string getClassroomNumber() {
    //     return classroomNumber;
    // }

    // string getTeacherName() {
    //     return teacherName;
    // }

    // string getStudentNames() { 

    //     string studentList = "";

    //     for (int i = 0; i < MAX_STUDENTS; i++) {

    //         if (students[i][0].empty() || students[i][1].empty()) {
    //             return "";
    //         }

    //         studentList += students[i][0] + " " + students[i][1] + '\n';
    //     }
        
    //     return studentList;
    // }

    // void setClassroomName(string classroomNameInput) {
    //     classroomName = classroomNameInput;
    // }

    // void setClassroomNum(string classroomNumInput) {
    //     classroomNumber = classroomNumInput;
    // }

    // void setTeacher(string teacherInput) {
    //     teacherName = teacherInput;
    // }

    // void setStudent(string studentNumber, string studentName) {
    //     students[studentCount][0] = studentNumber;
    //     students[studentCount][1] = studentName;
    //     studentCount++;
    // }
};

