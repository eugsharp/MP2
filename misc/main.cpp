#include <iostream>
#include <fstream>
#include "deguzman_header.h"
using namespace std;

int main() {
    int userDecision; // holds the user's choice from the menu
    int menuLoop = 1; // used for menu loop
    int teacherCounter; // used to count how many teachers are in the files

    while(menuLoop == 1) {
        //Menu for entire system
        cout<<"Menu"<<endl;
        cout<<"1. Add new teacher"<<endl;
        cout<<"2. Display a teacher's information"<<endl;
        cout<<"3. Display all teachers"<<endl;
        cout<<"4. Delete a teacher"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"Enter number of your choice: ";
        cin>>userDecision;
        if(cin.fail()) { //if input is not an integer, clears userDecision value and sets to -1
            cin.clear();
            cin.ignore(1000, '\n');
            userDecision = -1;
        }
        switch(userDecision) {
            case 1:
                addTeacher();
                break;

            case 2:
                teacherCounter = displayTeachers(); // displays a list of all teachers and returns a value that is equal to the amount of teachers
                displaySingleTeacherInfo(teacherCounter); // asks user which teacher to access and displays relevant information
                break;

            case 3:
                displayAllTeachers();
                break;

            case 4:
                teacherCounter = displayTeachers(); // displays a list of all teachers and returns a value that is equal to the amount of teachers
                deleteFile(teacherCounter); // asks user which teacher to delete then deletes all relevant information regarding the teacher
                break;

            case 5: // exits the system
                menuLoop = 0;
                break;

            default:
                cout<<endl<<"Invalid input."<<endl<<"Please input a number from the choices."<<endl<<endl;
                continue;
        }
    }
}
