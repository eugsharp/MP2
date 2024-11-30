#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Helper function to convert a string to uppercase
 inline string inUpperCase(string inputLetter) {
       string upperCaseForm = inputLetter;
       for (int i = 0; i < inputLetter.length(); i++)
           upperCaseForm[i] = toupper(inputLetter[i]);
       return upperCaseForm;
   }


class Classroom {
private:
    int roomNumber;
    string buildingCompleteName;
    string buildingAbbreviation;
    string classroomType;
    string laboratoryType;

public:
    // Constructor
    Classroom(int rn, const string &bcn, const string &ba, const string &ct, const string &lt)
        : roomNumber(rn), buildingCompleteName(bcn), buildingAbbreviation(ba),
          classroomType(ct), laboratoryType(lt) {}

    // Method to create a classroom file
    void createClassroom();
    // Method to append classroom info to the list
    void appendToList() const;
    // Method to display classroom information
    void displayClassroomInfo() const;
};

void Classroom::createClassroom() {
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

void Classroom::appendToList() const {
    ofstream rooms_file("ClassroomList.txt", ios::app);
    if (rooms_file.is_open()) {
        rooms_file << buildingAbbreviation << " " << roomNumber << endl;
        rooms_file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

void Classroom::displayClassroomInfo() const {
    cout << "Room number: " << roomNumber << endl;
    cout << "Building name: " << buildingCompleteName << endl;
    cout << "Abbreviation: " << buildingAbbreviation << endl;
    cout << "Classroom Type: " << classroomType << endl;
    cout << "Laboratory type: " << laboratoryType << endl;
}

class ClassroomManager {
private:
    int roomCount;
    const string messages[2] = {"Welcome! Would you like to enter a classroom? [yes/no] ",
                                "Would you like to do more? [yes/no] "};
    const string classroomName[3] = {"Laboratory", "Small lecture", "Big lecture"};
    const string laboratoryType[3][3] = {{"Chemical", "Computer", "Mechanical"},
                                         {"N/A", "N/A", "N/A"},
                                         {"N/A", "N/A", "N/A"}};

    // Utility methods
    void createBlankList();
    void readFile(const string &filename, int *linesCount);
    bool continueMain(int &messageIndex);
    bool inList(const string &item);
    void programMain(int &command);
    int getRoomNumber();
    int getClassroomIndex();
    string getBuildingAbbreviation();
    string chooseLaboratoryType(const int &classroomIndex);
    void getFilename(const string &buildingRoom, string &filename);
    bool foundRoomInList(string &roomFilename, string &response);
    void removeFromList(const string &item);

public:
    ClassroomManager() : roomCount(0) {}
    void addClassroom();
    void showAllClassrooms();
    void showOneClassroom();
    void deleteClassroom(int &roomCount);
};

// Definitions of ClassroomManager methods

void ClassroomManager::createBlankList() {
    ofstream list("ClassroomList.txt");
    list.close();
}

void ClassroomManager::readFile(const string &filename, int *linesCount) {
    ifstream list(filename);
    if (list.is_open()) {
        string line;
        if (linesCount) {
            *linesCount = 0;
        }
        cout << "Showing you the current list of classrooms: " << endl;
        while (getline(list, line)) {
            cout << line << endl;
            if (linesCount) {
                (*linesCount)++;
            }
        }
        list.close();
    } else {
        createBlankList();
    }
}

bool ClassroomManager::continueMain(int &messageIndex) {
    string response;
    cout << messages[messageIndex];
    if (messageIndex == 0) {
        messageIndex += 1;
    }

    while (true) {
        getline(cin, response);
        string repeat = inUpperCase(response);

        if (repeat == "YES" || repeat == "Y") {
            return true;
        } else if (repeat == "NO" || repeat == "N") {
            return false;
        }
    }
}

bool ClassroomManager::inList(const string &item) {
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

void ClassroomManager::programMain(int &command) {
    if (roomCount == 0) {
        command = 1;
    }
    if (roomCount > 0) {
        bool invalid = false;
        cout << "1: Add a classroom" << endl;
        cout << "2: Show all classrooms" << endl;
        cout << "3: Show one classroom" << endl;
        cout << "4: Delete a classroom" << endl;
        do {
            cout << "Enter desired command (1-4): ";
            cin >> command;

            invalid = cin.fail() || command < 1 || command > 4;
            cin.ignore(1000, '\n');
            if (invalid) {
                cout << "Please enter a number from 1-4 only." << endl;
            }
        } while (invalid);
    }
}

int ClassroomManager::getRoomNumber() {
    int roomNumber;
    bool invalid;
    do {
        cout << "Enter room number: ";
        cin >> roomNumber;
        invalid = cin.fail() || roomNumber <= 0;
        if (invalid) {
            cin.clear();
            cout << "Invalid input. Please enter a positive integer." << endl;
        }
        cin.ignore(1000, '\n');
    } while (invalid);
    return roomNumber;
}

int ClassroomManager::getClassroomIndex() {
    int classroomIndex;
    bool invalid;
    do {
        cout << "Enter classroom type (1 for Laboratory, 2 for Small lecture, 3 for Big lecture): ";
        cin >> classroomIndex;
        invalid = cin.fail() || classroomIndex < 1 || classroomIndex > 3;
        if (invalid) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter 1, 2, or 3." << endl;
        }
    } while (invalid);
    return classroomIndex - 1;
}

string ClassroomManager::chooseLaboratoryType(const int &classroomIndex) {
    int laboratoryIndex;
    bool invalid;

    do {
        cout << "Select laboratory type. If N/A just select any number from 1-3: " << endl;
        for (int lab = 0; lab < 3; lab++) {
            cout << lab + 1 << " " << laboratoryType[classroomIndex][lab] << endl;
        }
        cin >> laboratoryIndex;
        invalid = cin.fail() || laboratoryIndex < 1 || laboratoryIndex > 3;
        if (invalid) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please select a valid number." << endl;
        }
    } while (invalid);
    return laboratoryType[classroomIndex][laboratoryIndex - 1];
}

string ClassroomManager::getBuildingAbbreviation() {
    string buildingAbbreviation;
    bool invalid;
    do {
        cout << "Enter abbreviation (letters only): ";
        cin >> buildingAbbreviation;
        cin.ignore(1000, '\n');
        invalid = false;
        for (char c : buildingAbbreviation) {
            if (!isalpha(c)) {
                invalid = true;
                break;
            }
        }
        if (invalid) {
            cout << "Invalid input. Please enter letters only." << endl;
        }
    } while (invalid);
    return inUpperCase(buildingAbbreviation);
}

void ClassroomManager::addClassroom() {
    int roomNumber = getRoomNumber();
    string buildingCompleteName, buildingAbbreviation;
    string laboratory = "N/A";

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

inline void ClassroomManager::getFilename(const string& buildingRoom, string& filename) {
    size_t spacePos = buildingRoom.find(' ');
    if (spacePos != string::npos) {
        string abbr = buildingRoom.substr(0, spacePos);
        string roomNum = buildingRoom.substr(spacePos + 1);
        filename = inUpperCase(abbr) + "_" + roomNum + ".txt";
    } else filename = inUpperCase(buildingRoom) + ".txt";
}

//If the room is found in the database
inline bool ClassroomManager::foundRoomInList(string& roomFilename, string& response) {
    cout << "Please input Building abbreviation followed by a space and the room number: ";
    getline(cin, response);
    bool found = inList(response);
    if (found) getFilename(response, roomFilename);
    return found;
}

//shows one classroom
inline void ClassroomManager::showOneClassroom() {
    string showFilename, numberResponse;

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
inline void ClassroomManager::deleteClassroom(int& roomCount) {
    string filename, response;
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

