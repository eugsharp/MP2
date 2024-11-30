#include <iostream>
#include <string>
#include "general_input_validation.h"
#include <fstream>

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

    int setRoomNumber(int rn) {
        roomNumber = rn;
    }

    string setBuildingName(string bcn) { 
        buildingCompleteName = bcn;
    }

    string setBuildingAbbreviation(string ba) { 
        buildingAbbreviation = ba;
    }

    string setClassroomType(string ct) { 
        classroomType = ct;
    }

    string setLaboratoryType(string lt) {
        laboratoryType = lt;
    }
};