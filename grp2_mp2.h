#include <iostream> 
#include "block_4.h"

void mainMenu() { 
    string input;
    int intInput = 0;

    do {

        cout << "What would you like to do?" << endl;
        cout << "[1] Register a student" << endl;
        cout << "[2] Create information for a teacher" << endl;
        cout << "[3] Create information for a classroom" << endl;
        cout << "[4] Register a Class" << endl;
        cout << "[5] Quit the Program" << endl;

        cout << "Enter your input: ";
        getline(cin, input);


        if (isValidInteger(input)) {
            intInput = stoi(input);
        }
        
        switch (intInput) {
        case 1:
            studentRegistration();
            break;

        case 2:
            teacherInfo();
            break;

        case 3:
            classroomInfo();
            break;

        case 4:
            classroomRegistration();
            break;

        case 5:
            cout << "Exiting the program. Goodbye!" << endl;
            break;

        default:
            cout << "\nInvalid input. Please pick a number from 1-5.";
            break;
        }

        cout << endl;

    } while (intInput != 5);
}
