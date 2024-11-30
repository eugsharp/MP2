#include <iostream>
#include <string>
#include "general_input_validation.h"
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

string subjectInputHandler() {
    string subject;
    bool valid;

    cout << "\nWhat is the name of the subject?" << endl;
    cout << "[1] Programming" << endl;
    cout << "[2] Drafting" << endl;
    cout << "[3] Data Analysis" << endl;
    cout << "[4] Circuits 1" << endl;
    cout << "[5] Circuits 2" << endl;
    cout << "[6] OOP" << endl;
    cout << "[7] Electronics 1" << endl;
    cout << "[8] Electronics 2" << endl;
    cout << "[9] Logic Circuits" << endl;
    cout << "[10] Microprocessors" << endl;

    do {
        cout << "Enter your input: ";
        getline(cin, subject);

        valid = isValidInteger(subject) && withinBounds(subject, 1, 10);

        if (!valid) { 
            cout << "\nInvalid input. Please input a number from 1 to 10. " << endl;
        }
    }
    while(!valid);

    return subject;
}

string sectionInputHandler() { 
    string section;

    cout << "\nWhat is the name of the section?" << endl;
    cout << "Enter your input: ";
    getline(cin, section);

    // section input validation

    return section;
}

string dayInputHandler() {

    string daysChoice;
    bool valid; 

    cout << "\nOn what days does this class take place?" << endl;
    cout << "[1] Monday and Thursday" << endl;
    cout << "[2] Tuesday and Friday" << endl;
    cout << "[3] Monday only" << endl;
    cout << "[4] Tuesday only" << endl;
    cout << "[5] Wednesday only" << endl;
    cout << "[6] Thursday only" << endl;
    cout << "[7] Friday only" << endl;
    cout << "[8] Saturday only" << endl;

    do { 
        cout << "Enter your input: " << endl;
        cin >> daysChoice;

        valid = isValidInteger(daysChoice) && withinBounds(daysChoice, 1, 8);

        if (!valid) { 
            cout << "\nInvalid input. Please input a number from 1 to 8. " << endl;
        }

    } while (valid);


    // days choice input

    return daysChoice;
}

string timeInputHandler(string daysChoice) { 
    string time;

    if (!isValidInteger(daysChoice)) { 
        cout << "Choice of day not a valid integer. " << endl;
        return "";
    }

    int intDaysChoice = stoi(daysChoice);

    cout << "\nAt what time does this class take place?" << endl;

    if (intDaysChoice <= 2) { // 2 days a week
        cout << "[1] 08:00-09:30" << endl;
        cout << "[2] 09:30-11:00" << endl;
        cout << "[3] 11:00-12:30" << endl;
        cout << "[4] 12:30-14:00" << endl;
        cout << "[5] 14:00-15:30" << endl;
        cout << "[6] 15:30-17:00" << endl;

        cout << "Enter your input: ";
        getline(cin, time);

        // 2 day input validation
    }
    else { // 1 day a week
        cout << "[1] 08:00-11:00" << endl;
        cout << "[2] 11:00-14:00" << endl;
        cout << "[3] 14:00-15:00" << endl;

        cout << "Enter your input: ";
        getline(cin, time);

        // 1 day input validation
    }

    return time;
}

/*
    Takes the user choice of the subject and returns the subject name of appropriate choice
    @param option numerical option of user for subject
*/
string subjectNameFromOption(int option)
{
    switch (option)
    {
    case 1:
        return "Programming";
        break;

    case 2:
        return "Drafting";
        break;

    case 3:
        return "Data Analysis";
        break;

    case 4: 
        return "Circuits 1";
        break;

    case 5:
        return "Circuits 2";
        break;

    case 6:
        return "OOP";
        break;

    case 7:
        return "Electronics 1";
        break;

    case 8:
        return "Electronics 2";
        break;

    case 9: 
        return "Logic Circuits";
        break;

    case 10:
        return "Microprocessors";
        break;
    
    default:
        return "Invalid option.";
        break;
    }
}

/*
    Takes the user choice of the day and returns the days of appropriate choice
    @param option numerical option of user for days
*/
string daysFromDayChoice(string option)
{
    if (!isValidInteger(option)) { 
        cout << option << " is not a valid integer for days choice. ";
        return "";
    }

    switch (stoi(option))
    {
    case 1:
        return "MTh";
        break;

    case 2:
        return "TF";
        break;

    case 3:
        return "M";
        break;

    case 4: 
        return "T";
        break;

    case 5: 
        return "W";
        break;

    case 6:
        return "Th";
        break;

    case 7:
        return "F";
        break;

    case 8: 
        return "S";
        break;
    
    default:
        return "Invalid option.";
        break;
    }
}

/*
    Takes the user choice of the day and returns the time of appropriate choice, for classes that take place once per week
    @param option numerical option of user for time
*/
string timesFromOptionSingleDay(int option)
{
    switch (option)
    {
    case 1:
        return "08:00-11:00";
        break;

    case 2:
        return "11:00-14:00";
        break;

    case 3:
        return "14:00-17:00";
        break;
    
    default:
        return "Invalid option.";
        break;
    }
}

/*
    Takes the user choice of the day and returns the time of appropriate choice, for classes that take place twice per week
    @param option numerical option of user for time
*/
string timesFromOptionDoubleDay(int option)
{
    switch (option)
    {
    case 1:
        return "08:00-09:30";
        break;

    case 2:
        return "09:30-11:00";
        break;

    case 3:
        return "11:00-12:30";
        break;

    case 4:
        return "12:30-14:00";
        break;

    case 5: 
        return "14:00-15:30";
        break;

    case 6:
        return "15:30-17:00";
        break;
    
    default:
        return "Invalid option";
        break;
    }
}

void createClass() {
    string subject;
    string section;
    string daysChoice;
    string days;
    string time;

    // input the subject
    subject = subjectInputHandler();

    // input the section name
    section = sectionInputHandler();

    // input the days 
    daysChoice = dayInputHandler();
    days = daysFromDayChoice(daysChoice);

    // input the time
    time = timeInputHandler(daysChoice);

    Class createdClass(subject, days, time, section);

    cout << createdClass.getSubject() << endl;
    cout << createdClass.getDays() << endl;
    cout << createdClass.getTime() << endl;
    cout << createdClass.getSectionName() << endl;

    // create class file 
    string fileName = createdClass.getSubject() + "_" + createdClass.getSectionName() + ".txt"; 

    ofstream subjectSectionFile (fileName);

    // placing the inputted information into the Subject_section name file
    if (subjectSectionFile.is_open())
    {
        subjectSectionFile << "Subject: " << subject << endl;
        subjectSectionFile << "Days: " << days << endl;
        subjectSectionFile << "Time: " << time << endl;
        subjectSectionFile << "Section: " << section << endl;
    }
    else
    {
        cout << "Unable to open file " << fileName << endl;
    }

    // input the classroom

    // input the teacher 

    // input the students
}