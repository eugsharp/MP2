#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "classroom_program.h"

#ifndef CLASSROOM_H
#define CLASSROOM_H
using namespace std;

class Classroom : public ClassroomProgram {
private:
    int roomNumber;
    string buildingCompleteName;
    string buildingAbbreviation;
    string classroomType;
    string laboratoryType;

public:
    // Constructor
    Classroom() = default;
    Classroom(int rn, const string &bcn, const string &ba, const string &ct, const string &lt)
        : roomNumber(rn), buildingCompleteName(bcn), buildingAbbreviation(ba),
          classroomType(ct), laboratoryType(lt) {}

    // Method to create a classroom file
    void createClassroom();
    // Method to append classroom info to the list
    void appendToList();
    // Method to display classroom information
    void displayClassroomInfo() const;
    void listRoomsAlphabetically() const;
};

// Helper functions

//Lists the rooms inside the file alphabetically
inline void Classroom::listRoomsAlphabetically() const {
    ifstream list("ClassroomList.txt");
    vector<string> rooms;
    string line;
    while (getline(list, line)) {
        rooms.push_back(line);
    }
    list.close();

    // Sort the list alphabetically
    for (size_t i = 0; i < rooms.size(); ++i) {
        for (size_t j = 0; j < rooms.size() - 1; ++j) {
            if (rooms[j] > rooms[j + 1]) {
                swap(rooms[j], rooms[j + 1]);
            }
        }
    }

    // ofstream output("ClassroomList.txt", ofstream::out | ofstream::trunc); //Truncate mode clears the contents of the file
    //     if (output.is_open()) {
    //         for (const auto& room : rooms) {
    //             output << room << endl; //Write back the sorted list
    //             cout << room << endl; //Display the sorted list
    //         }
    //         output.close();
    //     } else cout << "Unable to open file" << endl;
    // }
}
//Main Program Functions

//Creates the file
inline void Classroom::createClassroom() {
    string filename = buildingAbbreviation + "_" + to_string(roomNumber) + ".txt";
    ofstream room_file(filename);
    if (room_file.is_open()) {
        room_file << "Room number: " << roomNumber << endl;
        room_file << "Building name (complete): " << buildingCompleteName << endl;
        room_file << "Building name (abbreviation): " << buildingAbbreviation << endl;
        room_file << "Classroom type: " << classroomType << endl;
        room_file << "Laboratory classroom type: " << laboratoryType << endl;
        room_file.close();
        appendToList();
    } else {
        cout << "Unable to open file" << endl;
    }
}

// Appends the abbreviation to the list of complete list file
inline void Classroom::appendToList() {
    ofstream rooms_file("ClassroomList.txt", ios::app);
    if (rooms_file.is_open()) {
        rooms_file << buildingAbbreviation << " " << roomNumber << endl;
        rooms_file.close();
        updateRoomCount(+1);
        cout << "Room count after adding: " << roomCount << endl;
        listRoomsAlphabetically();
    } else {
        cout << "Unable to open file" << endl;
    }
}

//Displays the classroom information
inline void Classroom::displayClassroomInfo() const {
    cout << "Room number: " << roomNumber << endl;
    cout << "Building name: " << buildingCompleteName << endl;
    cout << "Abbreviation: " << buildingAbbreviation << endl;
    cout << "Classroom Type: " << classroomType << endl;
    cout << "Laboratory type: " << laboratoryType << endl;
}

#endif
