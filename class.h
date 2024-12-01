#include <iostream>
#include <string>
#include <fstream>
#include "classroom.h"
#include <sstream>

class Class {

    string subject;
    string days;
    string time;
    string sectionName;
    string classroom; // building abbreviation + room num
    string teacherName; // ordered
    string students[30][2]; // first for number, second for name
    int daysPerWeek;
    int studentCount = 0;

public:
    Class () {}

    void setSubject(string subj) {

        if (!isValidInteger(subj)) { 
            cout << "Subject choice not valid. " << endl;
            return;
        }

        subject = subjectNameFromOption(stoi(subj));
    }

    void setDays(string d) {

        if (!isValidInteger(d)) { 
            cout << "Days choice not valid. " << endl;
            return;
        }

        if (stoi(d) <= 2) { 

            daysPerWeek = 2;

        } else{ 

            daysPerWeek = 1;
        }

        days = daysFromDayChoice(stoi(d));
    }

    void setTime(string t) {

        if (!isValidInteger(t)) { 

            cout << "Time choice not valid. " << endl;
            return;
        }

        switch (daysPerWeek)
        {
        case 1:
            time = timesFromOptionSingleDay(stoi(t));
            break;

        case 2:
            time = timesFromOptionDoubleDay(stoi(t));
            break;
        }
    }

    void setSectionName(string section) {
        sectionName = section;
    }

    void setClassroom(string room) {
        classroom = room;
    }

    void setTeacherName(string teacher) {
        teacherName = teacher;
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

    string getClassroom() { 
        return classroom;
    }

    string getTeacherName() {
        return teacherName;
    }

    int getDaysPerWeek() { 
        return daysPerWeek;
    }

    // subject counter

    // check for section duplicates

    // add students to file
    void addStudentsToFile(string filename) { 

        ofstream file (filename, ios::app);
    }

    void addStudent(string studentNum, string studentName) { 
        students[studentCount][0] = studentNum;
        students[studentCount][1] = studentName;
    }

    // sort student list
    void sortStudents()
    {
        // get the student nums

        // remove the "24-"

        // convert to integer

        // sort integers

        // add the "24-"

        // set the student name to the appropriate student num
    }


    void setStudentCount(int count) { 
        studentCount = count;
    }

    int getStudentCountFromFile(string fileName)
    {
        string line;
        int count = 0;
        bool pastStudentHeaderLine = false; 

        ifstream classFile(fileName);

        while (getline(classFile, line)) 
        {
            if (pastStudentHeaderLine == true)
            {
                // The numbers are at the beginning of the line
                stringstream ss(line);
                int number;
                ss >> number; // Extract the number

                if (ss) // Check if extraction was successful
                { 
                    count++; // Increment the count of students
                }
            }
            else
            {
                if (line == "Students: ")
                {
                    pastStudentHeaderLine = true;
                }
            }
        }

        classFile.close();

        return count;
    }   
};

