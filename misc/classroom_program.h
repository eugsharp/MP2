#include <iostream>
#include "users.h"

#ifndef CLASSROOM_PROGRAM_H
#define CLASSROOM_PROGRAM_H
using namespace std;

// Helper function to convert a string to uppercase
inline string inUpperCase(string inputLetter) {
    string upperCaseForm = inputLetter;
    for (int i = 0; i < inputLetter.length(); i++)
        upperCaseForm[i] =  toupper(inputLetter[i]);
    return upperCaseForm;
}

class ClassroomProgram {
private:
    string repeat;
    int command;

protected:
    // Utility methods
    int roomCount;
    int countRooms();
    void createBlankList();
    void readFile(const string &filename, int *linesCount);
    bool continueMain();
    void programMain();
    bool inList(const string &item);
    void updateRoomCount(int increment);
    void getFilename(const string &buildingRoom, string &filename);

public:
    ClassroomProgram() : roomCount(countRooms()){}; // program setup
    int main(); // program interaction, see classroom_manager.h
};

//Creates an empty file
inline void ClassroomProgram::createBlankList(){
    ofstream list("ClassroomList.txt");
    list.close();
}

//updates count and displays the list of classrooms
void ClassroomProgram::readFile(const string &filename, int *linesCount) {
    ifstream list(filename);
    if (!list.is_open()) {
        createBlankList();
        return;
    }
    string line;
    if (linesCount) {
        *linesCount = 0;
    }
    cout << "Showing you the current list of classrooms: " << endl;
    while (getline(list, line)) {
        cout << line << endl;
        if (linesCount) (*linesCount)++;
    }
    list.close();
}

//Counts the rooms inside the file
inline int ClassroomProgram::countRooms() {
    int count = 0;
    ifstream list("ClassroomList.txt");
    if (list.is_open()) {
        string line;
        while (getline(list, line)) {
            count++;
        }
        list.close();
    }
    roomCount = count;  // Store the count in the roomCount variable
    return count;
}

//Helper that updates the room count
inline void ClassroomProgram::updateRoomCount(int increment) {
    roomCount += increment;
}

//Checks if the program is inlist
inline bool ClassroomProgram::inList(const string &item) {
    ifstream list("ClassroomList.txt");
    if (list.is_open()) {
        string line;
        while (getline(list, line)) {
            if (inUpperCase(line) == inUpperCase(item)) {
                list.close();
                return true;
            }
        }
        list.close();
    } else {
        createBlankList();
    }
    return false;
}

//Program where they would input
inline void ClassroomProgram::programMain() {
    bool invalid = false;
    cout << "\nWhat would you like to do? " << endl;
    cout << "[1] Add a classroom" << endl;
    cout << "[2] Show all classrooms" << endl;
    cout << "[3] Show one classroom" << endl;
    cout << "[4] Delete a classroom" << endl;
    cout << "[5] Back to Main Menu" << endl;
    do {
        cout << "Enter desired command (1-5): ";
        cin >> command;

        invalid = cin.fail() || command < 1 || command > 5;
        cin.clear();
        cin.ignore(1000, '\n');
        if (invalid) {
            cout << "Please enter a number from 1-5 only." << endl;
        } else {
            if ((countRooms() == 0) && (command == 2 || command == 3 || command == 4)) {
                cout << "No classrooms are in the database at the moment. Please add a classroom first." << endl;
                invalid = true;
            }else {
                invalid = false;
            }
        }
    } while (invalid);
}

inline void ClassroomProgram::getFilename(const string& buildingRoom, string& filename) {
    size_t spacePos = buildingRoom.find(' ');
    if (spacePos != string::npos) {
        string abbr = buildingRoom.substr(0, spacePos);
        string roomNum = buildingRoom.substr(spacePos + 1);
        filename = inUpperCase(abbr) + "_" + roomNum + ".txt";
    } else filename = inUpperCase(buildingRoom) + ".txt";
}
#endif
