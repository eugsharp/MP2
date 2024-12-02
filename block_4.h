#include <iostream>
#include "block_3.h"
#include <filesystem>

#define MAX_STUDENTS 30

int numberOfClasses() { 

    int count = 0;

    // opens class list file
    string filename = "Class list.txt";

    if (!checkIfFileExists(filename)) { 

        return 0;
    }

    // counts how many lines have content
    ifstream classList (filename);

    string line;

    while(getline(classList, line)) { 

        if (line != "") { 

            count ++;
        }
    }

    return count;
}

int numberOfSubjects(string subject) { 

    int count = 0;

    // opens class list file 
    string filename = "Class list.txt";

    if (!checkIfFileExists(filename)) { 

        return 0;
    }

    // counts how many times "subject" is found
    ifstream classList (filename);

    string line;

    while(getline(classList, line)) { 

        if (line.find(subject) != string::npos) { 

            count ++;
        }
    }

    return count;

    return count;
}

void subjectInputHandler(Class &userClass) {
    string subject;
    bool valid;

    do {
        cout << "\nEnter subject name: " << endl;
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
        cout << "Enter your input: ";
        getline(cin, subject);

        valid = isValidInteger(subject) && withinBounds(subject, 1, 10); 

        if (!valid) { 
            cout << "\nInvalid input. Please input a number from 1 to 10. " << endl;
        }
    }
    while(!valid);

    if (numberOfSubjects(subjectNameFromOption(stoi(subject))) >= 2) { 

        cout << "Maximum classes with this subject reached. Please select a different subject. " << endl;
        subjectInputHandler(userClass);
        return;
    }

    userClass.setSubject(subject);
}

void sectionInputHandler(Class &userClass, void (*classRegistrationFunction)()) { 
    string section;
    bool valid;

    cout << "\nWhat is the name of the section?" << endl;

    do
    {
        cout << "Enter your input: ";
        getline(cin, section);

        valid = allUpper(section); 

        if (!valid) { 
            cout << "\nInvalid input. Please use only capital letters. " << endl;
        }

    } while (!valid);

    // check if a classroom of the same name already exists 
    if (checkIfFileExists(userClass.getSubject() + "_" + section + ".txt")) { 

        cout << "\nError: Class already exists. " << endl;
        classRegistrationFunction();
        return;
    }

    userClass.setSectionName(section);
}

void dayInputHandler(Class &userClass) {

    string daysChoice;
    bool valid; 

    cout << "\nEnter the days in which this class takes place: " << endl;
    cout << "[1] Monday and Thursday" << endl;
    cout << "[2] Tuesday and Friday" << endl;
    cout << "[3] Monday only" << endl;
    cout << "[4] Tuesday only" << endl;
    cout << "[5] Wednesday only" << endl;
    cout << "[6] Thursday only" << endl;
    cout << "[7] Friday only" << endl;
    cout << "[8] Saturday only" << endl;
    cout << "Enter your input: ";

    do { 
        cout << "Enter your input: ";
        getline(cin, daysChoice);

        valid = isValidInteger(daysChoice) && withinBounds(daysChoice, 1, 8);

        if (!valid) { 
            cout << "\nInvalid input. Please input a number from 1 to 8. " << endl;
        }

    } while (!valid);

    userClass.setDays(daysChoice);
}

void timeInputHandler(Class &userClass) { 

    string timeChoice;
    bool valid; 

    cout << "\nEnter the time in which the class takes place: " << endl;

    do
    {
        switch (userClass.getDaysPerWeek())
        {
        // 1 day per week

        case 1:
            cout << "[1] 08:00-11:00" << endl;
            cout << "[2] 11:00-14:00" << endl;
            cout << "[3] 14:00-15:00" << endl;  
            cout << "Enter your input: ";
            getline(cin, timeChoice);

            valid = isValidInteger(timeChoice) && withinBounds(timeChoice, 1,3);

            if (!valid) {
                cout << "Invalid input. Please input a number from 1 to 3" << endl;
            }
            break;

        // 2 days per week
        case 2:
            cout << "[1] 08:00-09:30" << endl;
            cout << "[2] 09:30-11:00" << endl;
            cout << "[3] 11:00-12:30" << endl;
            cout << "[4] 12:30-14:00" << endl;
            cout << "[5] 14:00-15:30" << endl;
            cout << "[6] 15:30-17:00" << endl;
            cout << "Enter your input: ";
            getline(cin, timeChoice);

            valid = isValidInteger(timeChoice) && withinBounds(timeChoice, 1, 6);

            if (!valid) {
                cout << "Invalid input. Please input a number from 1 to 6" << endl;
            }
            break;
        
        // error
        default:
            cout << "Error: Days per week not 1 or 2. " << endl; 
            break;
        }
        
    } while (!valid);

    userClass.setTime(timeChoice);
    
}

void addClassroomToClass(Class &userClass) { 

    string classroom;
    string abbreviation;
    string roomNum;

    // ask for building abbreviation
    cout << "\nEnter the building name abbreviation of the classroom: ";
    getline(cin ,abbreviation);

    // ask for the room number
    cout << "\nEnter the room number of the classroom: ";
    getline(cin, roomNum);
    
    classroom = abbreviation + " " + roomNum;
    
    // check if classroom is in classroom list (classroom list should exist because of validation in create class function)
    ifstream classroomListFile ("Classroom list.txt");

    if (!classroomListFile) { 

        cout << "Could not open Classroom list.txt" << endl;
    }

    string line;
    bool classroomExists = false;



    while (getline(classroomListFile, line))
    {
        if (line.find(classroom) != string::npos && checkIfFileExists(abbreviation + "_" + roomNum + ".txt")) { 

            classroomExists = true;
        }
    }

    classroomListFile.close();

    if (!classroomExists) { 
        cout << "Classroom " << classroom << " does not exist. " << endl;
        cout << "Ensure the classroom you enter is in the classroom list. " << endl;
        cout << "Classroom list: " << endl;
        printAllLinesInFile("Classroom list.txt");
        addClassroomToClass(userClass); // loop the function
        return;
    }

    userClass.setClassroom(classroom);
}

void addTeacherToClass(Class &userClass) { 

    string teacherName;
    string lastName;
    string firstName;
    string middleInitial;

    // create temporary teacher object
    Teacher tempTeacher;

    // ask for teacher last name 
    cout << "\nEnter teacher's last name: ";
    getline(cin, lastName);
    tempTeacher.setLastName(lastName);

    // ask for teacher first name
    cout << "\nEnter teacher's first name: ";
    getline(cin, firstName);
    tempTeacher.setGivenName(firstName);

    // ask for teacher middle initial (if there is)
    cout << "\nEnter teacher's middle initial (if teacher does not have one, leave blank): ";
    getline(cin, middleInitial);
    tempTeacher.setMiddleInitial(middleInitial);

    // get full name (ordered)
    teacherName = tempTeacher.getOrderedFullName();

    // check if its in teacher list
    ifstream teacherListFile ("Teacher list.txt");

    if (!teacherListFile) { 

        cout << "Could not open Teacher list.txt" << endl;
    }

    string line;
    bool teacherExists = false;

    while (getline(teacherListFile, line))
    {
        if (line.find(teacherName) != string::npos && checkIfFileExists(lastName + "_" + firstName + ".txt")) { 

            teacherExists = true;
        }
    }

    // check if teacher is in teacher list (teacher list should exist because of validation in create class function)
    if (!teacherExists) { 
        
        cout << "Teacher " << teacherName << " does not exist. " << endl;
        cout << "Ensure the teacher you enter is in the teacher list. " << endl;
        cout << "Teacher list: " << endl;
        printAllLinesInFile("Teacher list.txt");
        addTeacherToClass(userClass); // loop the function
        return;
    }

    userClass.setTeacherName(tempTeacher.getFullName()); // unordered due to specifications

}

void enlistStudents(Class &userClass, string filename) { 

    string studentName;
    string studentNumber;
    string lastName;
    string firstName; 
    string middleInitial;
    int numOfStudents;
    string choiceToRepeat;
    bool valid;

    // create temporary student object
    Student tempStudent;

    // determine the amount of students so far
    numOfStudents = userClass.getStudentCount();

    // check if already at 30 students
    if (numOfStudents >= MAX_STUDENTS) { 

        cout << "\nReached maximum student count. " << endl;
        return;
    }

    // show amt of students remaining
    cout << "\nYou have " << MAX_STUDENTS - numOfStudents << " remaining students to add. " << endl;

    // ask for student last name
    cout << "\nEnter student's last name: ";
    getline(cin, lastName);
    tempStudent.setLastName(lastName);

    // ask for student first name
    cout << "\nEnter student's first name: ";
    getline(cin, firstName);
    tempStudent.setGivenName(firstName);

    // ask for student middle initial (if there is)
    cout << "\nEnter student's middle initial (if student has none, leave blank): ";
    getline(cin, middleInitial);
    tempStudent.setMiddleInitial(middleInitial);

    // get full name
    studentName = tempStudent.getFullName();

    // check if name on student list
    // check if its in student list
    ifstream studentListFile ("Student list.txt");

    if (!studentListFile) { 

        cout << "\nCould not open Student list.txt" << endl;
    }

    string line;
    bool studentExists = false;

    // if (checkIfFileExists(lastName + "_" + firstName + ".txt")) { 
    //     cout << "\nFile " << lastName + "_" + firstName + ".txt" << " exists." << endl;
    // } 
    // else { 
    //     cout << "\nFile  " << lastName + "_" + firstName + ".txt" << " does not exist." << endl;
    // }

    while (getline(studentListFile, line))
    {
        if (line.find(studentName) != string::npos && checkIfFileExists(lastName + "_" + firstName + ".txt")) { 

            studentExists = true;
        }
    }

    // if (studentExists) { 
    //     cout << "\nstudent exists" << endl;
    // }

    // check if student is in student list (student list should exist because of validation in create class function)
    if (!studentExists) { 
        
        cout << "\nStudent " << studentName << " does not exist. " << endl;
        cout << "Ensure the student you enter is in the student list. " << endl;
        cout << "Student list: " << endl;
        printAllLinesInFile("Student list.txt");
        enlistStudents(userClass, filename); // loop the function
        return;
    }

    // add name and number to list 
    studentNumber = getStudentNumberByFile(studentName, "Student list.txt");
    userClass.addStudent(studentNumber, studentName);

    numOfStudents++;
    userClass.setStudentCount(numOfStudents);

    // ask to add another student
    do
    {
        cout << "\nWould you like to add another student?" << endl;
        cout << "[1] Yes" << endl;
        cout << "[2] No" << endl;
        cout << "Enter your input: " ;
        getline(cin, choiceToRepeat);

        valid = isValidInteger(choiceToRepeat) && withinBounds(choiceToRepeat, 1, 2);

        if (!valid) { 
            cout << "\nInvalid input. Please pick either 1 or 2. " << endl;
        }

    } while (!valid);

    switch (stoi(choiceToRepeat))
    {
    case 1:
        enlistStudents(userClass, filename);
        break;

    case 2:
        break;
    
        // no need for default as 1 and 2 was accounted for 
    }

    // sort the student list
    userClass.sortStudents();
}

bool createClassEligibility() { 

    string classroomList = "Classroom list.txt";
    string teacherList = "Teacher list.txt";
    string studentList = "Student list.txt";
    
    // amt of classes isnt 20
    if (numberOfClasses() >= 20) { 
        cout << "\nNumber of classes already at 20. " << endl;
        return false;
    }

    // files exist
    // check if classroom list exists
    if (!checkIfFileExists(classroomList)) { 

        cout << "\nClassroom list does not exist. Please create a classroom first. " << endl;
    }

    // check if teacher list exists
    if (!checkIfFileExists(teacherList)) { 

        cout << "\nTeacher list does not exist. Please create a teacher first. " << endl;
    }

    // check if student list exists
    if (!checkIfFileExists(studentList)) { 

        cout << "\nStudent list does not exist. Please create a student first. " << endl;
    }

    // if any one of these are not satisfied, ineligible
    if (!checkIfFileExists(classroomList) || !checkIfFileExists(teacherList) || !checkIfFileExists(studentList)) { 

        return false;
    }

    // files arent empty
    if (fileIsEmpty(classroomList)) { 

        cout << "\nClassroom list is empty. Please create a classroom first. " << endl;
    }

    if (fileIsEmpty(teacherList)) {
        cout << "\nTeacher list is empty. Please add teachers." << endl;
    }

    if (fileIsEmpty(studentList)) {
        cout << "\nStudent list is empty. Please add students." << endl;
    }

    // if any one of these are not satisfied, ineligible
    if (!checkIfFileExists(classroomList) || !checkIfFileExists(teacherList) || !checkIfFileExists(studentList)) { 

        return false;
    }

    return true;
}

void createClass(void (*classRegistrationFunction)()) {

    Class userClass; 

    if (!createClassEligibility()) {
        return;
    }
    
    // subject input 
    subjectInputHandler(userClass);

    // section input 
    sectionInputHandler(userClass, classRegistrationFunction);

    // days input 
    dayInputHandler(userClass);

    // time input 
    timeInputHandler(userClass);

    // create class file
    string classFilename = userClass.getSubject() + "_" + userClass.getSectionName() + ".txt";
    string className = userClass.getSubject() + " " + userClass.getSectionName();
    ofstream classFile (classFilename);

    if (classFile.is_open()) {

        classFile << "Subject: " << userClass.getSubject() << endl;
        classFile << "Days: " << userClass.getDays() << endl;
        classFile << "Time: " << userClass.getTime() << endl;
        classFile << "Section name: " << userClass.getSectionName() << endl;

    }
    else { 
        
        cout << "Could not open " << classFilename << endl;
    }

    classFile.close();

    // classroom input 
    addClassroomToClass(userClass);

    // add classroom to file
    ofstream classFileAppend (classFilename, ios::app);

    if (classFileAppend.is_open()) {

        classFileAppend << "Classroom: " << userClass.getClassroom() << endl;
    }
    else { 
        
        cout << "Could not open " << classFilename << endl;
    }

    // teacher input 
    addTeacherToClass(userClass);

    // add teacher to file
    if (classFileAppend.is_open()) {

        classFileAppend << "Teacher: " << userClass.getTeacherName() << endl;
    }
    else { 
        
        cout << "Could not open " << classFilename << endl;
    }

    // student input
    enlistStudents(userClass,classFilename);
    
    // add students to file
    userClass.addStudentsToFile(classFilename);

    classFileAppend.close();

    // create class list/add to class list
    if (checkIfFileExists("Class list.txt")) { 

        ofstream classListFile ("Class list.txt", ios::app);

        classListFile << className << endl;

        classListFile.close();
    } 
    else {

        ofstream classListFile ("Class list.txt");

        classListFile << className << endl;

        classListFile.close();
    }

    cout << "\nClassroom created: " << endl;
    printAllLinesInFile(classFilename);
}

void displayAnotherClass(void (*displayClassFunction)()) { // use of pointer to use a function as a parameter
    
    string choiceToRepeat;
    bool valid; 
    // Ask if user would like to repeat
    cout << "\nWould you like to display another class?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;

    do {
        cout << "Enter your option: ";
        getline(cin, choiceToRepeat);

        valid = isValidInteger(choiceToRepeat) && withinBounds(choiceToRepeat, 1, 2);

        if (!valid) {

            cout << "Invalid input. Please enter either 1 or 2." << endl;
        }

    } while (!valid);

    switch (stoi(choiceToRepeat)) { 
        case 1:
            displayClassFunction();
        case 2: 
            break;

        // no need for default since 1 and 2 were already checked for 
    }
}

void displayClass() { 

    string subjectInput, sectionInput, fileName;

    cout << "\nWhat is the subject of the class you would like to display?" << endl;
    cout << "Enter your input: ";

    getline(cin, subjectInput);

    cout << "\nWhat is the section of the class you would like to display?" << endl;
    cout << "Enter your input: ";

    getline(cin, sectionInput);

    // Search for the file and print its contents based on the inputs
    fileName = subjectInput + "_" + sectionInput + ".txt";

    // Validate if file exists
    if (!checkIfFileExists(fileName)) {
        cout << "\nThe class " << subjectInput << " " << sectionInput << " does not exist." << endl;
        displayAnotherClass(displayClass);
        return;
    }

    cout << "\nHere is the information for the class: " << subjectInput << " " << sectionInput << endl;
    cout << '\n';
    printAllLinesInFile(fileName);

    displayAnotherClass(displayClass);
}

void displayAllClasses() { 

    string filename = "Class list.txt";

    if (!checkIfFileExists(filename)) { 
        cout << "\nNo class list found. Consider making a class first. " << endl;
        return;
    }

    cout << "\nClasses: " << endl;
    printAllLinesInFile(filename);
}

void deleteAnotherClass(void (*deleteClassFunction)()) { // use of pointer to use a function as a parameter
    string choiceToRepeat;
    bool valid; 
    // Ask if user would like to repeat
    cout << "\nWould you like to delete another class?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;

    do {
        cout << "Enter your option: ";
        getline(cin, choiceToRepeat);

        valid = isValidInteger(choiceToRepeat) && withinBounds(choiceToRepeat, 1, 2);

        if (!valid) {

            cout << "Invalid input. Please enter either 1 or 2." << endl;
        }

    } while (!valid);

    switch (stoi(choiceToRepeat)) { 
        case 1:
            deleteClassFunction();
        case 2: 
            break;

        // no need for default since 1 and 2 were already checked for 
    }
}

void deleteClass() { 
 
    string subjectInput;
    string sectionInput;
    string fileName;
    string className;

    cout << "\nWhat is the subject of the class you would like to delete?" << endl;
    cout << "Enter your input: ";

    getline(cin, subjectInput);

    cout << "\nWhat is the section of the class you would like to delete?" << endl;
    cout << "Enter your input: ";

    getline(cin, sectionInput);

    fileName = subjectInput + "_" + sectionInput + ".txt";
    className = subjectInput + " " + sectionInput;

    // Validate if class file exists
    if (!checkIfFileExists(fileName)) {

        cout << "\nThe class " << className << " does not exist." << endl;
        deleteAnotherClass(deleteClass);
        return;
    }

    // remove the class file
    if (remove(fileName.c_str()) == 0) {

        cout << "Class " << className << " deleted successfully!" << endl; 
    }  
    else {
        
        cout << "Error: File for class " << className << " cannot be deleted." << endl;
    }

    // validate if class list file exists
    if (!checkIfFileExists("Class list.txt")) { 

        cout << "Error opening Class list.txt! Try creating a class first." << endl;
        return;
    }

    ifstream classListFile("Class list.txt");
    ofstream temp("temp.txt");

    // delete line from class list file
    bool classFound = false;
    string line;

    while (getline(classListFile, line)) { 

        if (line != className) { 

            temp << line << endl;
        } else { 

            classFound = true;
        }
    }

    classListFile.close();
    temp.close();

    if (classFound) { 

        // replace the original file with the temp file
        remove("Class list.txt");          
        rename("temp.txt", "Class list.txt"); 
    }
    else { 

        // if the class wasn't found, remove the temp file
        remove("temp.txt");
        cout << "The class you requested does not exist." << endl;
    }

    // ask to repeat
    deleteAnotherClass(deleteClass);
}

void classRegistration() { 

    string input; 
    int intInput;

    do {

        cout << "\nWhich of the following would you like to do: " << endl;
        cout << "[1] Create a class" << endl;
        cout << "[2] Display a class" << endl;
        cout << "[3] Display all classes" << endl;
        cout << "[4] Delete a class" << endl;
        cout << "[5] Back to Main Menu" << endl;

        cout << "Enter your input: ";
        getline(cin, input);


        if (isValidInteger(input)) {
            intInput = stoi(input);
        }
        
        switch (intInput) {
        case 1:
            createClass(classRegistration);
            break;

        case 2:
            displayClass();
            break;

        case 3:
            displayAllClasses();
            break;

        case 4:     
            deleteClass();
            break;

        case 5:
            break; 

        default:
            cout << "\nInvalid input. Please pick a number from 1-5.";
            break;
        }

    } while (intInput != 5);
    
}