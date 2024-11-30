#include <iostream>
#include <string>
#include <fstream>
#include "teacher.h"

using namespace std;

class Classroom {
private:
    int roomNumber;
    string buildingCompleteName;
    string buildingAbbreviation;
    string classroomType;
    string laboratoryType;

public:
    // constructor with no parameters
    Classroom() { 
        roomNumber = 0;
        buildingCompleteName = "Unknown Building Name";
        buildingAbbreviation = "Unknown Building Abbreviation";
        classroomType = "Unknown Classroom Type";
        laboratoryType = "Unknown Laboratory Type";
    }

    // Constructor with parameters
    Classroom(int rn, string bcn, string ba, string ct, string lt) {
        roomNumber = rn;
        buildingCompleteName = bcn;
        buildingAbbreviation = ba;
        classroomType = ct;
        laboratoryType = lt;
    }

    int getRoomNumber() {
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

    void setRoomNumber(int rn) {
        roomNumber = rn;
    }

    void setBuildingName(string bcn) { 
        buildingCompleteName = bcn;
    }

    void setBuildingAbbreviation(string ba) { 
        buildingAbbreviation = ba;
    }

    void setClassroomType(string ct) { 
        classroomType = ct;
    }

    void setLaboratoryType(string lt) {
        laboratoryType = lt;
    }
};