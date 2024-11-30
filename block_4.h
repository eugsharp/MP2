#include <iostream>
#include "block_3.h"

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

    cout << "\nWhat is the name of the section?" << endl;
    cout << "Enter your input: ";
    getline(cin, section);

    // section input validation

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
    string fileName = createdClass.getSubject() + "_" + createdClass.getSectionName() + ".txt"; 

    ofstream subjectSectionFile (fileName);

    // placing the inputted information into the Subject_section name file
    if (subjectSectionFile.is_open())
    {
        subjectSectionFile << "Subject: " << subject << endl;
        subjectSectionFile << "Days: " << days << endl;
        subjectSectionFile << "Time: " << time << endl;
        subjectSectionFile << "Section: " << section << endl;
    }
    else
    {
        cout << "Unable to open file " << fileName << endl;
    }

    // input the classroom

    // input the teacher 

    // input the students

    subjectSectionFile.close();

    // goes back to main menu, but greet before
    cout << "\nClass created: " << endl;
    printAllLinesInFile(fileName);
}

void displayClass() { 

}

void displayAllClasses() { 

}

void deleteClass() { 

}

void classroomRegistration() { 

    string input; 
    int intInput;

    cout << "\nWhich of the following would you like to do: " << endl;

    cout << "[1] Create a class" << endl;
    cout << "[2] Display a class" << endl;
    cout << "[3] Display all classes" << endl;
    cout << "[4] Delete a class" << endl;

    do {

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
            
            break;

        case 3:
            
            break;

        case 4:     

            break;

        default:
            cout << "\nInvalid input. Please pick a number from 1-4.";
            break;
        }

        cout << endl;

    } while (intInput != 5);
    
}