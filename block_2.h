#include <iostream>
#include "block_1.h"

void teacherNameHandler(Teacher &teacher, void (*teacherInfoFunction)()) { 
    string lastName;
    string firstName;
    string middleInitial;
    bool valid;

    // Prompt for last name
    do {
        cout << "\nEnter teacher's last name: ";
        getline(cin, lastName);

        valid = nameValidation(lastName);
        if (!valid) {
            cout << "Invalid last name. Ensure it contains no numbers and is not blank." << endl;
        }
    } while (!valid);

    // Prompt for given name
    do {
        cout << "\nEnter teacher's given name: ";
        getline(cin, firstName);

        valid = nameValidation(firstName);
        if (!valid) {
            cout << "Invalid given name. Ensure it contains no numbers and is not blank." << endl;
        }
    } while (!valid);

    // check if a teacher of the same name already exists 
    if (checkIfFileExists(lastName + "_" + firstName + ".txt")) { 

        cout << "\nError: Teacher already exists. " << endl;
        teacherInfoFunction();
        return;
    }

    // Prompt for middle initial
    do {
        cout << "\nEnter teacher's middle initial (you may leave this blank if the teacher has no middle initial): ";
        getline(cin, middleInitial);

        valid = middleInitialValidation(middleInitial);
        if (!valid) {
            cout << "Invalid middle initial. Ensure it is a single uppercase letter or blank." << endl;
        }
    } while (!valid);

    // Set the validated values to the teacher object
    teacher.setGivenName(firstName);
    teacher.setLastName(lastName);
    teacher.setMiddleInitial(middleInitial);
}

void teacherAddressHandler(Teacher &teacher) {
    string houseNumber;
    string streetName; 
    string subdivision;
    string barangayName;
    string cityMunicipality;
    bool valid;

    do
    {
        cout << "\nEnter House Number: ";
        getline(cin, houseNumber);

        valid = validateHouseNumber(houseNumber);

        if (!valid) { 
            cout << "\nInvalid input. Ensure the house number are digits only, and a maximum of 4 numbers." << endl;
        }

    } while (!valid);

    do
    {
        cout << "\nEnter Street Name (or leave blank if no street name): ";
        getline(cin, streetName);

        valid = streetName.size() >= 0;

    } while (!valid);

    do
    {
        cout << "\nEnter Subdivision/Building Name (or leave blank if no subdivision/building name): ";
        getline(cin, subdivision);

        valid = subdivision.size() >= 0;

    } while (!valid);
    

    do
    {
        cout << "\nEnter Barangay Name: ";
        getline(cin, barangayName);

        valid = barangayName.size() > 0;

        if (!valid) { 
            cout << "\nInvalid input. Ensure your input isn't blank. " << endl;
        }

    } while (!valid);
    
    do
    {
        cout << "\nEnter City/Municipality: ";
        getline(cin, cityMunicipality);

        valid = cityMunicipality.size() > 0;

        if (!valid) { 
            cout << "\nInvalid input. Ensure your input isn't blank. " << endl;
        }

    } while (!valid);

    teacher.setHouseNum(houseNumber);
    teacher.setStreetName(streetName);
    teacher.setBuildingName(subdivision);
    teacher.setBarangayName(barangayName);
    teacher.setCity(cityMunicipality);
}

void teacherMobileHandler(Teacher &teacher) { 
    
    string mobileNumber;
    bool valid;

    do
    {
        cout << "\nEnter teacher's mobile number: ";
        getline(cin, mobileNumber);

        valid = validateMobileNumber(mobileNumber);

        if (!valid) { 
            cout << "\nInvalid input. Mobile number must start with '09' and be 11 digits long. " << endl; 
        }

    } while (!valid);

    teacher.setMobileNum(mobileNumber);
}

void teacherSubjectHandler(Teacher &teacher, string inputHistory = "") { 
    string choice;
    bool valid;

    do
    {
        cout << "\nEnter choice of subject: " << endl;
        cout << "[1] Programming" << endl;
        cout << "[2] Drafting" << endl;
        cout << "[3] Data Analysis" << endl;
        cout << "[4] Circuits 1" << endl;
        cout << "[5] Circuits 2" << endl;
        cout << "[6] OOP" << endl;
        cout << "[7] Electronics 1" << endl;
        cout << "[8] Electronics 2" << endl;
        cout << "[9] Logic Circuits" << endl;
        cout << "[10] Microprocessors" << endl;
        cout << "Enter your input: ";
        getline(cin, choice);

        valid = isValidInteger(choice) && withinBounds(choice, 1, 10);

        if (!valid) { 

            cout << "Invalid input. Ensure you put a number from 1 to 10." << endl;
        }

    } while (!valid);

    // consider duplicates
    if (inputHistory.find(choice) != string::npos) { // a duplicate was found 

        cout << "Your choice was already made. Please do not repeat subjects. " << endl;
        teacherSubjectHandler(teacher, inputHistory);
        return;
    }

    inputHistory = inputHistory + choice;

    // add subject to teacher object
    teacher.setSubject(choice);

    if (teacher.getNumOfSubjects() >= 10) { 
        cout << "Maximum subjects reached. " << endl;
        return;
    }
    
    do
    {
        cout << "Would you like to add another subject? " << endl;
        cout << "[1] Yes" << endl;
        cout << "[2] No" << endl;
        cout << "Enter your input: ";
        getline(cin, choice);

        valid = isValidInteger(choice) && withinBounds(choice, 1, 2);

        if (!valid) { 
            cout << "Invalid input. Ensure you put either 1 or 2." << endl;
        }
        else {
            switch (stoi(choice))
            {
            case 1:
                teacherSubjectHandler(teacher, inputHistory);
                return;
                break;
            
            case 2:
                return;
                break;

            // no need for default as input was limited to 1 and 2.
            }
        }

        
    } while (!valid);
}

void addTeacher(void (*teacherInfoFunction)()) { 
    Teacher teacher;

    teacherNameHandler(teacher, teacherInfoFunction);

    teacherAddressHandler(teacher);

    teacherMobileHandler(teacher);

    // teacher subjects
    teacherSubjectHandler(teacher);
    
    teacher.generateNum();

    // create teacher file
    string teacherFileName = teacher.getLastName() + "_" + teacher.getGivenName() + ".txt";
    ofstream teacherFile (teacherFileName);

    if (teacherFile.is_open()) { 

        teacherFile << teacher.getOrderedFullName() << endl;
        teacherFile << teacher.getFullAddress() << endl;
        teacherFile << teacher.getMobileNum() << endl;
        teacherFile << teacher.getSubjects() << endl;
        teacherFile << "Teacher # " << teacher.getNum() << endl;

    }
    else {
        cout << "Unable to open file " << teacherFileName;
    }
    teacherFile.close();


    // add teacher to the teacher list
    if (!checkIfFileExists("Teacher List.txt")) { 

        ofstream teacherList("Teacher List.txt");
        teacherList << teacher.getNum() << " " << teacher.getOrderedFullName() << endl;
        teacherList.close();

        cout << "\nTeacher added: " << endl;
        printAllLinesInFile(teacherFileName);
        return;
    }

    ofstream teacherList("Teacher List.txt", ios::app); // open in append mode if it exists already;
    teacherList << teacher.getNum() << " " <<  teacher.getOrderedFullName() << endl;
    teacherList.close();

    cout << "\nTeacher added: " << endl;
    printAllLinesInFile(teacherFileName);
}

void displayTeacher() { 
    string lastNameInput, firstNameInput;
    cout << "\nEnter teacher's last name: ";
    getline(cin, lastNameInput);

    cout << "\nEnter teacher's first name: ";
    getline(cin, firstNameInput);

    string fileName = lastNameInput + "_" + firstNameInput + ".txt";

    if (checkIfFileExists(fileName)) {

        cout << "\nTeacher details: " << endl;
        printAllLinesInFile(fileName);

    } else {
        cout << "\nTeacher " << firstNameInput << " " << lastNameInput << " does not exist" << endl;
    }
}

void displayAllTeachers() { 

    string filename = "Teacher List.txt";

    if (!checkIfFileExists(filename)) { 
        cout << "\nNo teacher list found. Please add a teacher first. " << endl;
        return;
    }

    cout << "\nTeachers: " << endl;
    printAllLinesInFile(filename);
}

void deleteTeacher() { 
    string lastNameInput, firstNameInput;
    cout << "\nEnter teacher's last name: ";
    getline(cin, lastNameInput);

    cout << "\nEnter teacher's first name: ";
    getline(cin, firstNameInput);

    string fileName = lastNameInput + "_" + firstNameInput + ".txt";

    if (!checkIfFileExists(fileName)) {

        cout << "\nTeacher " << firstNameInput << " " << lastNameInput << " does not exist" << endl;
        return;
    }

    // remove teacher file
    if (remove(fileName.c_str()) == 0) {

        cout << "Teacher " << lastNameInput << " " << firstNameInput << " deleted successfully!" << endl; 
    }  
    else {
        
        cout << "Error: File for teacher " << lastNameInput << " " << firstNameInput << " cannot be deleted." << endl;
    }

    ifstream teacherListFile("Teacher list.txt");
    ofstream temp("temp.txt");

    // remove from teacher list
    bool teacherFound = false;
    string line;

    while(getline(teacherListFile, line)) { 

        if (line.find(lastNameInput + ", " + firstNameInput) == string::npos) { 

            temp << line << endl;
        }
        else { 
            teacherFound = true;
        }
    } 

    teacherListFile.close();
    temp.close();

    if (teacherFound) { 

        remove("Teacher List.txt");
        rename("temp.txt", "Teacher List.txt");

    } else {

        // if the teacher wasn't found, remove the temp file
        remove("temp.txt");
        cout << "The teacher you requested does not exist." << endl;
    }
}

void teacherInfo() { 
    string input; 
    int intInput;

    do {
        cout << "\nWhich of the following would you like to do: " << endl;
        cout << "[1] Add a teacher" << endl;
        cout << "[2] Display a teacher" << endl;
        cout << "[3] Display all teachers" << endl;
        cout << "[4] Delete a teacher" << endl;
        cout << "[5] Back to Main Menu" << endl;

        cout << "Enter your input: ";
        getline(cin, input);


        if (isValidInteger(input)) {
            intInput = stoi(input);
        }
        
        switch (intInput) {
        case 1:
            addTeacher(teacherInfo);
            break;

        case 2:
            displayTeacher();
            break;

        case 3:
            displayAllTeachers();
            break;

        case 4:     
            deleteTeacher();
            break;

        case 5:
            break; 

        default:
            cout << "\nInvalid input. Please pick a number from 1-5.";
            break;
        }


    } while (intInput != 5);
}