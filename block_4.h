#include <iostream>
#include "block_3.h"
#include <filesystem>

using namespace std; 

string subjectInputHandler() {
    string subject;
    bool valid;

    cout << "\nWhat is the name of the subject?" << endl;
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

    do {
        cout << "Enter your input: ";
        getline(cin, subject);

        valid = isValidInteger(subject) && withinBounds(subject, 1, 10);

        if (!valid) { 
            cout << "\nInvalid input. Please input a number from 1 to 10. " << endl;
        }
    }
    while(!valid);

    return subjectNameFromOption(stoi(subject));
}

string sectionInputHandler() { 
    string section;
    bool valid;

    cout << "\nWhat is the name of the section?" << endl;

    do
    {
        cout << "Enter your input: ";
        getline(cin, section);

        valid = allUpper(section);

        if (!valid) { 
            cout << "\nInvalid input. Please use only capital letters. " << endl;
        }

    } while (!valid);
    
    return section;
}

string dayInputHandler() {

    string daysChoice;
    bool valid; 

    cout << "\nOn what days does this class take place?" << endl;
    cout << "[1] Monday and Thursday" << endl;
    cout << "[2] Tuesday and Friday" << endl;
    cout << "[3] Monday only" << endl;
    cout << "[4] Tuesday only" << endl;
    cout << "[5] Wednesday only" << endl;
    cout << "[6] Thursday only" << endl;
    cout << "[7] Friday only" << endl;
    cout << "[8] Saturday only" << endl;

    do { 
        cout << "Enter your input: ";
        getline(cin, daysChoice);

        valid = isValidInteger(daysChoice) && withinBounds(daysChoice, 1, 8);

        if (!valid) { 
            cout << "\nInvalid input. Please input a number from 1 to 8. " << endl;
        }

    } while (!valid);

    return daysChoice;
}

string timeInputHandler(string daysChoice) { 
    string time;
    bool valid;

    if (!isValidInteger(daysChoice)) { 
        cout << "Choice of day not a valid integer. " << endl;
        return "";
    }

    int intDaysChoice = stoi(daysChoice);

    cout << "\nAt what time does this class take place?" << endl;

    if (intDaysChoice <= 2) { // 2 days a week
        cout << "[1] 08:00-09:30" << endl;
        cout << "[2] 09:30-11:00" << endl;
        cout << "[3] 11:00-12:30" << endl;
        cout << "[4] 12:30-14:00" << endl;
        cout << "[5] 14:00-15:30" << endl;
        cout << "[6] 15:30-17:00" << endl;

        do {

            cout << "Enter your input: ";
            getline(cin, time);

            valid = isValidInteger(time) && withinBounds(time, 1, 6);

            if (!valid) { 
                cout << "\nInvalid input. Please input a number from 1 to 6. " << endl;
            }

        } while (!valid);

        return timesFromOptionDoubleDay(stoi(time));
    }
    else { // 1 day a week
        cout << "[1] 08:00-11:00" << endl;
        cout << "[2] 11:00-14:00" << endl;
        cout << "[3] 14:00-15:00" << endl;

        do {

            cout << "Enter your input: ";
            getline(cin, time);

            valid = isValidInteger(time) && withinBounds(time, 1, 3);

            if (!valid) { 
                cout << "\nInvalid input. Please input a number from 1 to 3. " << endl;
            }

        } while (!valid);
        
        return timesFromOptionSingleDay(stoi(time));
    }
}

void createClass() {
    string subject;
    string section;
    string days;
    string time;

    // input the subject
    subject = subjectInputHandler();

    // input the section name
    section = sectionInputHandler();

    // input the days 
    days = dayInputHandler();

    // input the time
    time = timeInputHandler(days);

    // convert days from its number choice
    days = daysFromDayChoice(days);

    Class createdClass(subject, days, time, section);

    // create class file 
    string fileName = subject + "_" + section + ".txt"; 

    ofstream subjectSectionFile (fileName);

    // placing the inputted information into the Subject_section name file
    if (subjectSectionFile.is_open()) {

        subjectSectionFile << "Subject: " << subject << endl;
        subjectSectionFile << "Days: " << days << endl;
        subjectSectionFile << "Time: " << time << endl;
        subjectSectionFile << "Section: " << section << endl;
    }
    else {

        cout << "Unable to open file " << fileName << endl;
    }

    // input the classroom

    // input the teacher 

    // input the students

    // class list.txt
    string classListFilename = "Class list.txt";

    if (checkIfFileExists(classListFilename)) { 

        ofstream classListFile (classListFilename, ios::app);
        classListFile << subject << " " << section << endl;

    } else { 

        ofstream classListFile (classListFilename);
        classListFile << subject << " " << section << endl;
    }

    subjectSectionFile.close();

    // goes back to main menu, but greet before
    cout << "\nClass created: " << endl;
    printAllLinesInFile(fileName);
}

void displayAnotherClass(void (*displayClassFunction)()) { 
    
    string choiceToRepeat;
    bool valid; 
    // Ask if user would like to repeat
    cout << "\nWould you like to display another class?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;

    do {
        cout << "Enter your option: ";
        getline(cin, choiceToRepeat);

        valid = isValidInteger(choiceToRepeat) && withinBounds(choiceToRepeat, 1, 2);

        if (!valid) {

            cout << "Invalid input. Please enter either 1 or 2." << endl;
        }

    } while (!valid);

    switch (stoi(choiceToRepeat)) { 
        case 1:
            displayClassFunction();
        case 2: 
            break;

        // no need for default since 1 and 2 were already checked for 
    }
}

void displayClass() { 

    string subjectInput, sectionInput, fileName;

    cout << "\nWhat is the subject of the class you would like to display?" << endl;
    cout << "Enter your input: ";

    getline(cin, subjectInput);

    cout << "\nWhat is the section of the class you would like to display?" << endl;
    cout << "Enter your input: ";

    getline(cin, sectionInput);

    // Search for the file and print its contents based on the inputs
    fileName = subjectInput + "_" + sectionInput + ".txt";

    // Validate if file exists
    if (!checkIfFileExists(fileName)) {
        cout << "\nThe class " << subjectInput << " " << sectionInput << " does not exist." << endl;
        displayAnotherClass(displayClass);
        return;
    }

    cout << "\nHere is the information for the class: " << subjectInput << " " << sectionInput << endl;
    cout << '\n';
    printAllLinesInFile(fileName);

    displayAnotherClass(displayClass);
}

void displayAllClasses() { 

    string filename = "Class list.txt";

    if (!checkIfFileExists(filename)) { 
        cout << "\nNo class list found. Consider making a class first. " << endl;
        return;
    }

    cout << "\nClasses: " << endl;
    printAllLinesInFile(filename);
}

void deleteAnotherClass(void (*deleteClassFunction)()) { 
    string choiceToRepeat;
    bool valid; 
    // Ask if user would like to repeat
    cout << "\nWould you like to delete another class?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;

    do {
        cout << "Enter your option: ";
        getline(cin, choiceToRepeat);

        valid = isValidInteger(choiceToRepeat) && withinBounds(choiceToRepeat, 1, 2);

        if (!valid) {

            cout << "Invalid input. Please enter either 1 or 2." << endl;
        }

    } while (!valid);

    switch (stoi(choiceToRepeat)) { 
        case 1:
            deleteClassFunction();
        case 2: 
            break;

        // no need for default since 1 and 2 were already checked for 
    }
}

void deleteClass() { 
 
    string subjectInput;
    string sectionInput;
    string fileName;
    string className;

    cout << "\nWhat is the subject of the class you would like to delete?" << endl;
    cout << "Enter your input: ";

    getline(cin, subjectInput);

    cout << "\nWhat is the section of the class you would like to delete?" << endl;
    cout << "Enter your input: ";

    getline(cin, sectionInput);

    fileName = subjectInput + "_" + sectionInput + ".txt";
    className = subjectInput + " " + sectionInput;

    // Validate if class file exists
    if (!checkIfFileExists(fileName)) {

        cout << "\nThe class " << className << " does not exist." << endl;
        deleteAnotherClass(deleteClass);
        return;
    }

    // remove the class file
    if (remove(fileName.c_str()) == 0) {

        cout << "Class" << className << " deleted successfully!" << endl; 
    }  
    else {
        
        cout << "Error: File for class " << className << " cannot be deleted." << endl;
    }

    // validate if class list file exists
    if (!checkIfFileExists("Class list.txt")) { 

        cout << "Error opening Class list.txt! Try creating a class first." << endl;
        return;
    }

    ifstream classListFile("Class list.txt");
    ofstream temp("temp.txt");

    // delete line from class list file
    bool classFound = false;
    string line;

    while (getline(classListFile, line)) { 

        if (line != className) { 

            temp << line << endl;
        } else { 

            classFound = true;
        }
    }

    classListFile.close();
    temp.close();

    if (classFound) { 

        // replace the original file with the temp file
        remove("Class list.txt");          
        rename("temp.txt", "Class list.txt"); 
    }
    else { 

        // if the class wasn't found, remove the temp file
        remove("temp.txt");
        cout << "The class you requested does not exist." << endl;
    }

    // ask to repeat
    deleteAnotherClass(deleteClass);
}

void classroomRegistration() { 

    string input; 
    int intInput;

    do {

        cout << "\nWhich of the following would you like to do: " << endl;
        cout << "[1] Create a class" << endl;
        cout << "[2] Display a class" << endl;
        cout << "[3] Display all classes" << endl;
        cout << "[4] Delete a class" << endl;
        cout << "[5] Back to Main Menu" << endl;

        cout << "Enter your input: ";
        getline(cin, input);


        if (isValidInteger(input)) {
            intInput = stoi(input);
        }
        
        switch (intInput) {
        case 1:
            createClass();
            break;

        case 2:
            displayClass();
            break;

        case 3:
            displayAllClasses();
            break;

        case 4:     
            deleteClass();
            break;

        case 5:
            break; 

        default:
            cout << "\nInvalid input. Please pick a number from 1-4.";
            break;
        }

        cout << endl;

    } while (intInput != 5);
    
}