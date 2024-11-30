#include <iostream>
#include "block_1_input_validation.h"

void studentNameHandler(Student &student) { 
    string lastName;
    string firstName;
    string middleInitial;
    bool valid;

    // Prompt for last name
    do {
        cout << "Enter student's last name: ";
        getline(cin, lastName);

        valid = nameValidation(lastName);
        if (!valid) {
            cout << "Invalid last name. Ensure it contains no numbers and is not blank." << endl;
        }
    } while (!valid);

    // Prompt for given name
    do {
        cout << "Enter student's given name: ";
        getline(cin, firstName);

        valid = nameValidation(firstName);
        if (!valid) {
            cout << "Invalid given name. Ensure it contains no numbers and is not blank." << endl;
        }
    } while (!valid);

    // Prompt for middle initial
    do {
        cout << "Enter student's middle initial (you may leave this blank if the student has no middle initial): ";
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


void addressHandler(Student &student) { 
    string houseNumber;
    string streetName; 
    string subdivision;
    string barangayName;
    string cityMunicipality;
    bool valid;

    do
    {
        cout << "Enter House Number: ";
        getline(cin, houseNumber);

        valid = validateHouseNumber(houseNumber);

        if (!valid) { 
            cout << "\nInvalid input. Ensure the house number are digits only, and a maximum of 4 numbers." << endl;
        }

    } while (!valid);

    do
    {
        cout << "Enter Street Name (or leave blank if no street name): ";
        getline(cin, streetName);

        valid = streetName.size() >= 0;

    } while (!valid);

    do
    {
        cout << "Enter Subdivision/Building Name (or leave blank if no subdivision/building name): ";
        getline(cin, subdivision);

        valid = subdivision.size() >= 0;

    } while (!valid);
    

    do
    {
        cout << "Enter Barangay Name: ";
        getline(cin, barangayName);

        valid = barangayName.size() > 0;

        if (!valid) { 
            cout << "\nInvalid input. Ensure your input isn't blank. " << endl;
        }

    } while (!valid);
    
    do
    {
        cout << "Enter City/Municipality: ";
        getline(cin, cityMunicipality);

        valid = cityMunicipality.size() > 0;

        if (!valid) { 
            cout << "\nInvalid input. Ensure your input isn't blank. " << endl;
        }

    } while (!valid);

    student.setHouseNum(houseNumber);
    student.setStreetName(streetName);
    student.setBuildingName(subdivision);
    student.setBarangayName(barangayName);
    student.setCity(cityMunicipality);
}

void mobileHandler(Student &student) { 
    
    string mobileNumber;
    bool valid;

    do
    {
        cout << "Enter your mobile number: ";
        getline(cin, mobileNumber);

        valid = validateMobileNumber(mobileNumber);

        if (!valid) { 
            cout << "\nInvalid input. Mobile number must start with '09' and be 11 digits long. " << endl; 
        }

    } while (!valid);

    student.setMobileNum(mobileNumber);
}

void addStudent() { 
    Student student;

    studentNameHandler(student);

    addressHandler(student);

    mobileHandler(student);
    
    //studentNumber = generateStudentNumber();
    // cout << "Student added successfully! Student # " << studentNumber << "\n";

    cout << student.getFullName() << endl;
    cout << student.getFullAddress() << endl;
    cout << student.getMobileNum() << endl;
}

void displayStudent() { 
    cout << "displaying student!" << endl;

}

void displayAllStudents() { 
    cout << "displaying all students!" << endl;

}

void deleteStudent() { 
    cout << "deleting student!" << endl;

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
            addStudent();
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

        cout << endl;

    } while (intInput != 5);
}