#include <iostream>
#include <string>
#include <fstream>
#include "users.h"

class Classroom {
private:
    string roomNumber;
    string buildingCompleteName;
    string buildingAbbreviation;
    string classroomType;
    string laboratoryType;

public:
    // constructor with no parameters
    Classroom() {}

    // Constructor with parameters
    Classroom(string rn, string bcn, string ba, string ct, string lt) {
        roomNumber = rn;
        buildingCompleteName = bcn;
        buildingAbbreviation = ba;
        classroomType = ct;
        laboratoryType = lt;
    }

    string getRoomNumber() {
        return roomNumber;
    }

    string getBuildingName() { 
        return buildingCompleteName;
    }

    string getBuildingAbbreviation() { 
        return buildingAbbreviation;
    }

    string getClassroomType() { 
        return classroomType;
    }

    string getLaboratoryType() {
        return laboratoryType;
    }

    void setRoomNumber(string rn) {
        roomNumber = rn;
    }

    void setBuildingName(string bcn) { 
        buildingCompleteName = bcn;
    }

    void setBuildingAbbreviation(string ba) { 
        buildingAbbreviation = ba;
    }

    void setClassroomType(string ct) { 
        
        // classroom type will either be 1, 2, or 3

        if (ct[0] == '1') { 

            classroomType = "Laboratory";
        }
        else if (ct[0] == '2') { 

            classroomType = "Small lecture";
        }
        else if (ct[0] == '3') { 

            classroomType = "Big lecture";
        }
        else { 

            cout << "Invalid classroom choice for classroom type. " << endl;
        }
    }

    void setLaboratoryType(string lt) {

        // lab type will either be 1, 2, 3, or N/A

        if (lt[0] == '1') { 

            laboratoryType = "Chemical";
        }
        else if (lt[0] == '2') { 

            laboratoryType = "Computer";
        }
        else if (lt[0] == '3') { 

            laboratoryType = "Mechanical";
        }
        else if (lt == "N/A") { 

            laboratoryType = "N/A";
        }
        else { 

            cout << "Invalid classroom choice for classroom type. " << endl;
        }
    }
};