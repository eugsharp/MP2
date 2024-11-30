#include "block_1.h"
#include <iostream>

void addTeacher() { 

}

void displayTeacher() { 

}

void displayAllTeachers() { 

}

void deleteTeacher() { 
    
}

void teacherInfo() { 
    string input; 
    int intInput;

    do {

        cout << "\nWhich of the following would you like to do: " << endl;
        cout << "[1] Add a teacher" << endl;
        cout << "[2] Display a teacher" << endl;
        cout << "[3] Display all teachers" << endl;
        cout << "[4] Delete a teacher" << endl;
        cout << "[5] Back to Main Menu" << endl;

        cout << "Enter your input: ";
        getline(cin, input);


        if (isValidInteger(input)) {
            intInput = stoi(input);
        }
        
        switch (intInput) {
        case 1:
            
            break;

        case 2:
            
            break;

        case 3:
            
            break;

        case 4:     
            
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