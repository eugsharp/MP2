#include <iostream>
#include "block_1_and_2_input_validation.h"

void studentNameHandler(Student &student, void (*studentRegistrationFunction)()) { 
    string lastName;
    string firstName;
    string middleInitial;
    bool valid;

    // Prompt for last name
    do {
        cout << "\nEnter student's last name: ";
        getline(cin, lastName);

        valid = nameValidation(lastName);
        if (!valid) {
            cout << "Invalid last name. Ensure it contains no numbers and is not blank." << endl;
        }
    } while (!valid);

    // Prompt for given name
    do {
        cout << "\nEnter student's given name: ";
        getline(cin, firstName);

        valid = nameValidation(firstName);
        if (!valid) {
            cout << "Invalid given name. Ensure it contains no numbers and is not blank." << endl;
        }
    } while (!valid);

    // check if a student of the same name already exists 
    if (checkIfFileExists(lastName + "_" + firstName + ".txt")) { 

        cout << "\nError: Student already exists. " << endl;
        studentRegistrationFunction();
        return;
    }

    // Prompt for middle initial
    do {
        cout << "\nEnter student's middle initial (you may leave this blank if the student has no middle initial): ";
        getline(cin, middleInitial);

        valid = middleInitialValidation(middleInitial);
        if (!valid) {
            cout << "Invalid middle initial. Ensure it is a single uppercase letter or blank." << endl;
        }
    } while (!valid);

    // Set the validated values to the student object
    student.setGivenName(firstName);
    student.setLastName(lastName);
    student.setMiddleInitial(middleInitial);
}

void studentAddressHandler(Student &student) { 
    string houseNumber;
    string streetName; 
    string subdivision;
    string barangayName;
    string cityMunicipality;
    bool valid;

    // input and validation for house number
    do
    {
        cout << "\nEnter House Number: ";
        getline(cin, houseNumber);

        valid = validateHouseNumber(houseNumber);

        if (!valid) { 
            cout << "\nInvalid input. Ensure the house number are digits only, and a maximum of 4 numbers." << endl;
        }

    } while (!valid);

    // input and validation for street name
    do
    {
        cout << "\nEnter Street Name (or leave blank if no street name): ";
        getline(cin, streetName);

        valid = streetName.size() >= 0;

    } while (!valid);

    // input and validation for subdivision/building name
    do
    {
        cout << "\nEnter Subdivision/Building Name (or leave blank if no subdivision/building name): ";
        getline(cin, subdivision);

        valid = subdivision.size() >= 0;

    } while (!valid);
    
    // input and validation for barangay
    do
    {
        cout << "\nEnter Barangay Name: ";
        getline(cin, barangayName);

        valid = barangayName.size() > 0;

        if (!valid) { 
            cout << "\nInvalid input. Ensure your input isn't blank. " << endl;
        }

    } while (!valid);
    
    // input and validation for city
    do
    {
        cout << "\nEnter City/Municipality: ";
        getline(cin, cityMunicipality);

        valid = cityMunicipality.size() > 0;

        if (!valid) { 
            cout << "\nInvalid input. Ensure your input isn't blank. " << endl;
        }

    } while (!valid);

    // set values in the student object
    student.setHouseNum(houseNumber);
    student.setStreetName(streetName);
    student.setBuildingName(subdivision);
    student.setBarangayName(barangayName);
    student.setCity(cityMunicipality);
}

void studentMobileHandler(Student &student) { 
    
    string mobileNumber;
    bool valid;

    // input and validation of mobile number
    do
    {
        cout << "\nEnter student's mobile number: ";
        getline(cin, mobileNumber);

        valid = validateMobileNumber(mobileNumber);

        if (!valid) { 
            cout << "\nInvalid input. Mobile number must start with '09' and be 11 digits long. " << endl; 
        }

    } while (!valid);

    student.setMobileNum(mobileNumber);
}

void addStudent(void (*studentRegistrationFunction)()) { 
    Student student;

    // student name input
    studentNameHandler(student, studentRegistrationFunction);

    // student address input
    studentAddressHandler(student);

    // mobile number input
    studentMobileHandler(student);
    
    // generate student num
    student.generateNum();

    // create student file
    string studentFileName = student.getLastName() + "_" + student.getGivenName() + ".txt";
    ofstream studentFile (studentFileName);

    if (studentFile.is_open()) { 

        studentFile << student.getFullName() << endl;
        studentFile << student.getFullAddress() << endl;
        studentFile << student.getMobileNum() << endl;
        studentFile << "Student # " << student.getNum() << endl;

    }
    else {
        cout << "Unable to open file " << studentFileName;
    }
    studentFile.close();


    // add student to the student list
    if (!checkIfFileExists("Student List.txt")) { 

        ofstream studentList("Student List.txt");
        studentList << student.getNum() << " " << student.getFullName() << endl;
        studentList.close();

        cout << "\nStudent added: " << endl;
        printAllLinesInFile(studentFileName);
        return;
    }

    ofstream studentList("Student List.txt", ios::app); // open in append mode if it exists already;
    studentList << student.getNum() << " " <<  student.getFullName() << endl;
    studentList.close();

    cout << "\nStudent added: " << endl;
    printAllLinesInFile(studentFileName);
}

void displayStudent() { 

    string lastNameInput, firstNameInput;
    cout << "\nEnter student's last name: ";
    getline(cin, lastNameInput);

    cout << "\nEnter student's first name: ";
    getline(cin, firstNameInput);

    string fileName = lastNameInput + "_" + firstNameInput + ".txt";

    if (checkIfFileExists(fileName)) {

        cout << "\nStudent details: " << endl;
        printAllLinesInFile(fileName);

    } else {
        cout << "\nStudent " << firstNameInput << " " << lastNameInput << " does not exist" << endl;
    }
}

void displayAllStudents() { 

    string filename = "Student List.txt";

    if (!checkIfFileExists(filename)) { 
        cout << "\nNo student list found. Please add a student first. " << endl;
        return;
    }

    cout << "\nStudents: " << endl;
    printAllLinesInFile(filename);
}

void deleteStudent() { 

    string lastNameInput, firstNameInput;
    cout << "\nEnter student's last name: ";
    getline(cin, lastNameInput);

    cout << "\nEnter student's first name: ";
    getline(cin, firstNameInput);

    string fileName = lastNameInput + "_" + firstNameInput + ".txt";

    if (!checkIfFileExists(fileName)) {

        cout << "\nStudent " << firstNameInput << " " << lastNameInput << " does not exist" << endl;
        return;
    }

    // remove student file
    if (remove(fileName.c_str()) == 0) {

        cout << "Student " << lastNameInput << " " << firstNameInput << " deleted successfully!" << endl; 
    }  
    else {
        
        cout << "Error: File for student " << lastNameInput << " " << firstNameInput << " cannot be deleted." << endl;
    }

    ifstream studentListFile("Student list.txt");
    ofstream temp("temp.txt");

    // remove from student list
    bool studentFound = false;
    string line;

    while(getline(studentListFile, line)) { 

        if (line.find(lastNameInput + ", " + firstNameInput) == string::npos) { 

            temp << line << endl;
        }
        else { 
            studentFound = true;
        }
    } 

    studentListFile.close();
    temp.close();

    if (studentFound) { 

        remove("Student List.txt");
        rename("temp.txt", "Student List.txt");

    } else {

        // if the student wasn't found, remove the temp file
        remove("temp.txt");
        cout << "The student you requested does not exist." << endl;
    }
}

void studentRegistration() { 
    
    string input; 
    int intInput;

    do {
        cout << "\nWhich of the following would you like to do: " << endl;
        cout << "[1] Add a student" << endl;
        cout << "[2] Display a student" << endl;
        cout << "[3] Display all students" << endl;
        cout << "[4] Delete a student" << endl;
        cout << "[5] Back to Main Menu" << endl;

        cout << "Enter your input: ";
        getline(cin, input);

        if (isValidInteger(input)) {
            intInput = stoi(input);
        }
        
        switch (intInput) {
        case 1:
            addStudent(studentRegistration);
            break;

        case 2:
            displayStudent();
            break;

        case 3:
            displayAllStudents();
            break;

        case 4:     
            deleteStudent();
            break;

        case 5:
            break; 

        default:
            cout << "\nInvalid input. Please pick a number from 1-5.";
            break;
        }


    } while (intInput != 5);
}