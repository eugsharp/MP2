#include "block_2.h"
#include <iostream>


void roomHandler(Classroom &classroom) { 

    string roomNumber; 
    bool valid; 

    do
    {
        cout << "\nEnter the room number: ";
        getline(cin, roomNumber);

        valid = isValidInteger(roomNumber);

        if (!valid) { 
            cout << "\nInvalid input. Ensure the room number is only comprised of digits. " << endl;
        }

    } while (!valid);
    
    classroom.setRoomNumber(roomNumber);
}

void buildingNameHandler(Classroom &classroom) { 

    string buildingName;
    string buildingAbbreviation;
    bool valid; 

    do
    {
        cout << "\nEnter the building name: ";
        getline(cin, buildingName);

        valid = true;

        if (!valid) { 
            cout << "\nInvalid input. Ensure the room number is ... " << endl;
        }   
        
    } while (!valid);
    
    // building abbreviation
    do
    {
        cout << "\nEnter the building's abbreviation: ";
        getline(cin, buildingAbbreviation);

        valid = allUpper(buildingAbbreviation);

        if (!valid) { 
            cout << "\nInvalid input. Ensure the room number is only comprised of capital letters. " << endl;
        }   
        
    } while (!valid);

    classroom.setBuildingName(buildingName);
    classroom.setBuildingAbbreviation(buildingAbbreviation);

}

void classroomTypeHandler(Classroom &classroom) { 

    string classroomChoice; 
    string laboratoryChoice = "N/A";
    bool valid; 

    do
    {
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

    // if lab, lab type (not lab = N/A lab)
    if (classroomChoice[0] == '1') { 
       
        do
        {
            cout << "\nEnter laboratory type: " << endl;
            cout << "[1] Chemical" << endl;
            cout << "[2] Computer" << endl;
            cout << "[3] Mechanical" << endl;
            cout << "Enter your input: ";
            getline(cin, laboratoryChoice);

            valid = isValidInteger(laboratoryChoice) && withinBounds(laboratoryChoice, 1, 3);

            if (!valid) { 

                cout << "Invalid input. Ensure a number from 1 to 3 is inputted. " << endl;
            }

        } while (!valid);
    }

    classroom.setClassroomType(classroomChoice);
    classroom.setLaboratoryType(laboratoryChoice);
}

void addClassroom() { 

    Classroom classroom; 

    // room name 
    roomHandler(classroom);

    // building name
    buildingNameHandler(classroom);

    // classroom type
    classroomTypeHandler(classroom);

    // create classroom file
    string classroomFileName = classroom.getBuildingAbbreviation() + "_" + classroom.getRoomNumber() + ".txt";
    string classRoomName = classroom.getBuildingAbbreviation() + " " + classroom.getRoomNumber();

    ofstream classFile(classroomFileName);

    if (classFile.is_open()) {
        
        classFile << "Room number: " << classroom.getRoomNumber() << endl;
        classFile << "Building name (complete): " << classroom.getBuildingName() << endl;
        classFile << "Building name (abbreviation): " << classroom.getBuildingAbbreviation() << endl;
        classFile << "Classroom type: " << classroom.getClassroomType() << endl;
        classFile << "Laboratory classroom type: " << classroom.getLaboratoryType() << endl;
        classFile.close();
    } 
    else {

        cout << "Unable to open file" << endl;
    }

    // create classroom list
    // add classroom to the classroom list
    if (!checkIfFileExists("Classroom List.txt")) { 

        ofstream classroomList("Classroom List.txt");
        classroomList << classRoomName << endl;
        classroomList.close();

        cout << "\nClassroom added: " << endl;
        printAllLinesInFile(classroomFileName);
        return;
    }

    ofstream classroomList("Classroom List.txt", ios::app); // open in append mode if it exists already;
    classroomList << classRoomName << endl;
    classroomList.close();

    cout << "\nClassroom added: " << endl;
    printAllLinesInFile(classroomFileName);
}

void displayClassroom() { 

    string abbreviation, roomNumber;
    cout << "\nEnter classroom's building abbreviation: ";
    getline(cin, abbreviation);

    cout << "\nEnter classroom's room number: ";
    getline(cin, roomNumber);

    string fileName = abbreviation + "_" + roomNumber + ".txt";

    if (checkIfFileExists(fileName)) {

        cout << "\nClassroom details: " << endl;
        printAllLinesInFile(fileName);

    } else {
        cout << "\nClassroom " << abbreviation << " " << roomNumber << " does not exist" << endl;
    }
}

void displayAllClassrooms() { 

    string filename = "Classroom List.txt";

    if (!checkIfFileExists(filename)) { 
        cout << "\nNo classroom list found. Please add a classroom first. " << endl;
        return;
    }

    cout << "\nClassroom: " << endl;
    printAllLinesInFile(filename);
}

void deleteClassroom() { 
    
    string abbreviation, roomNumber;
    cout << "\nEnter classroom's building abbreviation: ";
    getline(cin, abbreviation);

    cout << "\nEnter classroom's room number: ";
    getline(cin, roomNumber);

    string fileName = abbreviation + "_" + roomNumber + ".txt";
    string classroomLine = abbreviation + " " + roomNumber;

    if (!checkIfFileExists(fileName)) {

        cout << "\nClassroom " << classroomLine << " does not exist" << endl;
        return;
    }

    // remove classroom file
    if (remove(fileName.c_str()) == 0) {

        cout << "Classroom " << classroomLine << " deleted successfully!" << endl; 
    }  
    else {
        
        cout << "Error: File for class " << classroomLine << " cannot be deleted." << endl;
    }

    ifstream classroomListFile("Classroom list.txt");
    ofstream temp("temp.txt");

    // remove from classroom list
    bool classroomFound = false;
    string line;

    while(getline(classroomListFile, line)) { 

        if (line.find(classroomLine) == string::npos) { 

            temp << line << endl;
        }
        else { 
            classroomFound = true;
        }
    } 

    classroomListFile.close();
    temp.close();

    if (classroomFound) { 

        remove("Classroom List.txt");
        rename("temp.txt", "Classroom List.txt");

    } else {

        // if the classroom wasn't found, remove the temp file
        remove("temp.txt");
        cout << "The classroom you requested does not exist." << endl;
    }
}

void classroomInfo() { 
    string input; 
    int intInput;

    do {
        cout << "\nWhich of the following would you like to do: " << endl;
        cout << "[1] Add a classroom" << endl;
        cout << "[2] Display a classroom" << endl;
        cout << "[3] Display all classrooms" << endl;
        cout << "[4] Delete a classroom" << endl;
        cout << "[5] Back to Main Menu" << endl;

        cout << "Enter your input: ";
        getline(cin, input);


        if (isValidInteger(input)) {
            intInput = stoi(input);
        }
        
        switch (intInput) {
        case 1:
            addClassroom();
            break;

        case 2:
            displayClassroom();
            break;

        case 3:
            displayAllClassrooms();
            break;

        case 4:     
            deleteClassroom();
            break;

        case 5:
            break; 

        default:
            cout << "\nInvalid input. Please pick a number from 1-5.";
            break;
        }


    } while (intInput != 5);
}