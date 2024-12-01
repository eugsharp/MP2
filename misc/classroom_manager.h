#include <iostream>
#include "classroom.h"

#ifndef CLASSROOM_MANAGER_H
#define CLASSROOM_MANAGER_H
using namespace std;

class ClassroomManager : public ClassroomProgram {
private:
    // user prompts
    int getRoomNumber();
    int getClassroomIndex();
    string getBuildingAbbreviation();
    string chooseLaboratoryType(const int &classroomIndex);
    bool foundRoomInList(string &roomFilename, string &response);
    void removeFromList(const string &item);
    const string classroomName[3] = {"Laboratory", "Small lecture", "Big lecture"};
    const string laboratoryType[3][3] = {{"Chemical", "Computer", "Mechanical"},
                                         {"N/A", "N/A", "N/A"},
                                         {"N/A", "N/A", "N/A"}};

public:
    ClassroomManager() = default;
    void addClassroom();
    void showAllClassrooms();
    void showOneClassroom();
    void deleteClassroom();
};

// shows all classrooms
inline void ClassroomManager::showAllClassrooms(){
    cout << endl;
    readFile("ClassroomList.txt", &roomCount);
}

//Removes the specific input in the file
inline void ClassroomManager::removeFromList(const string& item) {
    vector<string> rooms; //Using a vector to store rooms

    ifstream list("ClassroomList.txt");
    if (list.is_open()) {
        string line;
        while (getline(list, line)) {
            if (inUpperCase(line) != inUpperCase(item)) {
                rooms.push_back(line); //Collects the rooms that wasn't inputted
            }
        }
        list.close();
    } else cout << "Unable to open file" << endl;

    ofstream output("ClassroomList.txt", ofstream::out | ofstream::trunc); //Truncate mode clears the contents of the file
    if (output.is_open()) {
        for (const auto& room : rooms) {
            output << room << endl; //Write back the valid rooms
        }
        output.close();
    } else cout << "Unable to open file" << endl;
}

//Gets room number
inline int ClassroomManager::getRoomNumber() {
    int roomNumber;
    bool invalid;
    do {
        cout << "Enter room number: ";
        cin >> roomNumber;
        invalid = cin.fail() || roomNumber <= 0;
        if (invalid) {
            cin.clear();
            cout << "\nInvalid input. Ensure the room number is only comprised of digits. " << endl;
        }
        cin.ignore(1000, '\n');
    } while (invalid);
    return roomNumber;
}

//Gets Classroom index from 1-3
inline int ClassroomManager::getClassroomIndex() {
    int classroomIndex;
    string classroomChoice;
    bool valid;
    do {
        cout << "\nEnter classroom type: " << endl;
        cout << "[1] Laboratory" << endl;
        cout << "[2] Small leture" << endl;
        cout << "[3] Big leture" << endl;
        cout << "Enter your input: ";
        getline(cin, classroomChoice);

        valid = isValidInteger(classroomChoice) && withinBounds(classroomChoice, 1, 3);

        if (!valid) { 
            cout << "Invalid input. Ensure a number from 1 to 3 is inputted. " << endl;
        }

    } while (!valid); 
    classroomIndex = stoi(classroomChoice);
    return classroomIndex - 1;
}

//Choose the laboratory type
inline string ClassroomManager::chooseLaboratoryType(const int &classroomIndex) {
    int laboratoryIndex;
    string laboratoryChoice;
    bool valid;

    if (classroomName[classroomIndex] != "Laboratory") return laboratoryType[classroomIndex][classroomIndex];

    do {
        cout << "Select laboratory type. If N/A just select any number from 1-3: " << endl;
        for (int lab = 0; lab < 3; lab++) {
            cout << "[" << lab + 1 << "]" << " " << laboratoryType[classroomIndex][lab] << endl;
        }

        cout << "Enter your input: ";
        getline(cin, laboratoryChoice);

        valid = isValidInteger(laboratoryChoice) && withinBounds(laboratoryChoice, 1, 3);

        if (!valid) { 
            cout << "Invalid input. Ensure a number from 1 to 3 is inputted. " << endl;
        }

    } while (!valid); 
    laboratoryIndex = stoi(laboratoryChoice);
    
    return laboratoryType[classroomIndex][laboratoryIndex - 1];
}

//Gets the building abbreviation
inline string ClassroomManager::getBuildingAbbreviation() {
    string buildingAbbreviation;
    bool valid;
     do
    {
        cout << "\nEnter the building's abbreviation: ";
        getline(cin, buildingAbbreviation);

        valid = allUpper(buildingAbbreviation);

        if (!valid) { 
            cout << "\nInvalid input. Ensure the room number is only comprised of capital letters. " << endl;
        }   
    } while (!valid);

    return buildingAbbreviation;
}

//Adds the classroom
void ClassroomManager::addClassroom() {

    int roomNumber = getRoomNumber();
    string buildingCompleteName, buildingAbbreviation;
    string laboratory = "N/A";
    cout << endl;

    cout << "Enter complete building name: ";
    getline(cin, buildingCompleteName);
    buildingAbbreviation = getBuildingAbbreviation();
    string buildingABBR = inUpperCase(buildingAbbreviation);
    string thingIsAlready = buildingABBR + " " + to_string(roomNumber);

    if (!inList(thingIsAlready)) {
        int classroomIndex = getClassroomIndex();
        string classroomType = classroomName[classroomIndex];
        laboratory = chooseLaboratoryType(classroomIndex);

        Classroom newClassroom(roomNumber, buildingCompleteName, buildingABBR, classroomType, laboratory);
        newClassroom.createClassroom();

        cout << "To recap your input: " << endl;
        newClassroom.displayClassroomInfo();
        cout << "Data stored in the database." << endl;
        roomCount++;
    } else {
        cout << "Classroom already exists" << endl;
    }
}

//If the room is found in the database
inline bool ClassroomManager::foundRoomInList(string& roomFilename, string& response) {
    string responseBLDG, roomNumber;
    cout << "\nEnter classroom's building abbreviation: ";
    getline(cin, responseBLDG);
    cout << "\nEnter classroom's room number: ";
    getline(cin, roomNumber);
    
    response = responseBLDG + " " + roomNumber;
    bool found = inList(response);
    if (found) getFilename(response, roomFilename);
    return found;
}

//shows one classroom
inline void ClassroomManager::showOneClassroom() {
    string showFilename, numberResponse;
    cout << endl;

    if (foundRoomInList(showFilename, numberResponse)) {
        ifstream roomFile(showFilename);
        if (roomFile.is_open()) {
            readFile(showFilename, nullptr); // Assuming this reads and displays the content
        } else {
            cout << "Classroom file not found: " << showFilename << endl;
        }
    } else cout << "Classroom not found" << endl;
}

//Delete classroom function
inline void ClassroomManager::deleteClassroom() {
    string filename, response;
    cout << endl;

    if (foundRoomInList(filename,response)) {
        removeFromList(response);
        cout << "Deleting file " << filename << "..." << endl;
        if (remove(filename.c_str()) != 0) {
            cout << "Error deleting file " << filename << endl;
        } else {
            cout << "File deleted successfully." << endl;
            roomCount--;
        }
    } else cout << "Classroom not found in the list." << endl;
}

//Main program turned into class
inline int ClassroomProgram::main() {
    ClassroomManager manager;
    bool proceed = true;

    while (proceed) {
       programMain();

       switch (command) {
           case 1:
               manager.addClassroom();
           break;
           case 2:
               manager.showAllClassrooms();
           break;
           case 3:
               manager.showOneClassroom();
           break;
           case 4:
               manager.deleteClassroom();
           break;
           case 5:
               proceed = false;
           break; 

           default:
            cout << "\nInvalid input. Please pick a number from 1-5.";
           break;
       }
   }
   return 0;
}

#endif
