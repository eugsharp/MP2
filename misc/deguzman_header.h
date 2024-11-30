#include <iostream>
using namespace std;

inline int loop = 0; // used for looping in input-validation systems
inline int lineCounter = 0; // used for counting lines
inline char lineReader[300]; // used for reading lines
inline unsigned char unsignedLineReader[3];
inline int numberInput; // number that the user inputs
inline char fileName[100];
inline fstream displayFile;
inline fstream readFile;
inline fstream writeFile;

class teacherManager{
public:
    teacherManager(string lN, string fN, string mI, string s, string sd, string b, string c, string hN, long long mN){
    lastName = lN;
    firstName = fN;
    middleInitial = mI;
    street = s;
    subdivision = sd;
    barangay = c;
    city = c;
    houseNumber = hN;
    mobileNumber = mN;

}
void addTeacher();

private:
    string lastName, firstName, middleInitial; // name-related variables of teacher
    string street, subdivision, barangay, city;  // address variables
    string houseNumber;
    long long mobileNumber;
};


inline string checkEmptyInput(string userInput) {
    if (userInput == "N/A" ||
        userInput == "none" ||
        userInput == "n/a" ||
        userInput == " ") return "";
    else return userInput;
}

inline void createTeacherNumber(char* teacherNumber) { //makes teacher number
    int numberCounter = 0;
    readFile.open("Teacher List.txt"); //gets the highest teacher number in the file
    if(readFile.is_open()) {
        while(readFile.getline(lineReader, 100)) {
            unsignedLineReader[0] = lineReader[3];
            unsignedLineReader[1] = lineReader[4];
            unsignedLineReader[2] = lineReader[5];
            int hundredthsNumber = unsignedLineReader [0];
            int tenthsNumber = unsignedLineReader[1];
            int digitsNumber = unsignedLineReader[2];
            numberCounter = ((hundredthsNumber - '0')*100) + ((tenthsNumber - '0')*10) + digitsNumber - '0';
        }
        numberCounter++;
        readFile.close();
    }
    if (numberCounter == '0') numberCounter = 1;
    teacherNumber[0] = '0';
    teacherNumber[1] = '1';
    teacherNumber[2] = '-';
    teacherNumber[3] = '0' + (numberCounter / 100);
    teacherNumber[4] = '0'+(numberCounter /10 % 10);
    teacherNumber[5] = '0' + (numberCounter % 10);
    teacherNumber[6] = '\0';
}

inline void teacherManager::addTeacher() {
    string teacherSubject[50][10]; // used for storage of subjects
    int subjectCounterX = 0, subjectCounterY = 0; // used for storing subjects into arrays
    int subjectLoop;
    string subjectInput; // subject input of user
    char teacherNumber[8]; // stores teacher number

    cout<<"Enter Last Name: ";
    cin.ignore();
    getline(cin, lastName);
    cout<<"Enter First Name: ";
    getline(cin, firstName);

    readFile.open(lastName + "_" += firstName + ".txt"); // checks if file already exists
    if (readFile.is_open()) {
        readFile.close();
        cout<<"Teacher already exists."<<endl;
        return; // exits function if it exists
    }

    cout<<"Enter Middle Name: ";
    getline(cin, middleInitial);
    middleInitial = checkEmptyInput(middleInitial);
    cout<<"Enter House Number: ";
    cin>>houseNumber;
    cout<<"Enter Street Name: ";
    cin.ignore();
    getline(cin, street);
    street = checkEmptyInput(street);
    cout<<"Enter Subdivision: ";
    getline(cin, subdivision);
    subdivision = checkEmptyInput(subdivision);
    cout<<"Enter Barangay: ";
    getline(cin, barangay);
    cout<<"Enter City: ";
    getline(cin, city);
    loop = 0;
    while(loop == 0) { // input validation
        cout<<"Enter Mobile Number: (+63) ";
        cin>>mobileNumber;
        if(cin.fail()) { //input validation
            cout<<endl<<"Invalid input please enter a number."<<endl;
            cin.clear();
            cin.ignore(100,'\n');
        } else loop = 1;    
    }
    cin.ignore();
    cout<<endl<<"LIST OF AVAILABLE SUBJECTS TO TEACH:"<<endl;
    cout<<"Programming"<<endl
        <<"Drafting"<<endl
        <<"Data Analysis"<<endl
        <<"Circuits 1"<<endl
        <<"Circuits 2"<<endl
        <<"OOP"<<endl
        <<"Electronics 1"<<endl
        <<"Electronics 2"<<endl
        <<"Logic Circuits"<<endl
        <<"Microprocessors"<<endl;
    subjectLoop = 1; // used for looping the prompt of entering a subject
    while(subjectLoop <= 10) {
        cout<<"Enter Subjects to Teach: ";
        getline(cin, subjectInput);
        if(subjectInput.empty() || subjectInput == " ") {
            subjectCounterX = 0;
            break;
        }
        if ((subjectInput == "Programming" || subjectInput == "Drafting" ||
            subjectInput == "Data Analysis" || subjectInput == "Circuits 1" ||
            subjectInput == "Circuits 2" || subjectInput == "OOP" || subjectInput == "Electronics 1" ||
            subjectInput == "Electronics 2" || subjectInput == "Logic Circuits" ||
            subjectInput == "Microprocessors") && subjectCounterX < 10) {
            teacherSubject[subjectCounterY][subjectCounterX] = subjectInput;
            subjectCounterX++;
            subjectLoop++;
            } else {
                cout<<"Invalid subject. Please try again."<<endl;
            }
    } subjectCounterY++; subjectCounterX = 0;

    createTeacherNumber(teacherNumber);

    cout<<"Your employee number is: "<<teacherNumber<<endl;
    writeFile.open(lastName + "_" += firstName + ".txt", ios::out);
    if (writeFile.is_open()) {
        writeFile<<lastName<<", "<<firstName<<" "<<middleInitial<<endl;
        if (street.empty() && subdivision.empty()) {
            writeFile<<houseNumber<<" "<<barangay<<" "<<city<<endl;
        } else if(street.empty()) {
            writeFile<<houseNumber<<" "<<subdivision<<" "<<barangay<<" "<<city<<endl;
        } else if (subdivision.empty()) {
            writeFile<<houseNumber<<" "<<street<<" "<<barangay<<" "<<city<<endl;
        } else writeFile<<houseNumber<<" "<<street<<" "<<subdivision<<" "<<barangay<<" "<<city<<endl;
        writeFile<<"0"<<mobileNumber<<endl;
        writeFile<<"Employee # "<<teacherNumber<<endl;
        writeFile<<"Subjects: ";
        bool firstSubject = true;
        for(int x=0; x<10; x++) {
            if(teacherSubject[subjectCounterY-1][x].empty()) {
                break;
            }
            if(!(firstSubject)) {
                writeFile<<", ";
            }
            writeFile<<teacherSubject[subjectCounterY-1][x];
            firstSubject = false;
        }
        writeFile.close();
    }
    // inputs the information into three files: teacher list file, display file, and file name files
    writeFile.open("Teacher List.txt", ios::app); //inputs info into Teacher List file
    if (writeFile.is_open()) {
        writeFile<<teacherNumber<<" "<<lastName<<", "<<firstName<<" "<<middleInitial<<endl;
        writeFile.close();
    }
    writeFile.open("teacher display file.txt", ios::app); //inputs info into display file, which contains a numbered list of all teachers
    if (writeFile.is_open()) {
        writeFile<<lastName<<", "<<firstName<<" "<<middleInitial<<endl;
        writeFile.close();
    }
    writeFile.open("teacher file names.txt", ios::app); // inputs file into file names file, which contains the name of the individual teacher files
    if (writeFile.is_open()) {
        writeFile<<lastName + "_" + firstName + ".txt"<<endl;
        writeFile.close();
    }
}

inline int displayTeachers() {
    // displays a list of all teachers and returns a value that is equal to the amount of teachers
    string displayTeacherName;
    cout<<endl<<"LIST OF ALL TEACHERS:"<<endl;
    displayFile.open("teacher display file.txt");
    int teacherCounter = 0;
    if(displayFile.is_open()) {
        if(!(getline(displayFile, displayTeacherName))) {
            cout<<"There is no available data."<<endl<<endl;
        } else {
            cout<<teacherCounter+1<<". "<<displayTeacherName<<endl;
            teacherCounter++;
            while(getline(displayFile, displayTeacherName)) {
                cout<<teacherCounter+1<<". "<<displayTeacherName<<endl;
                teacherCounter++;
            }
        }
        displayFile.close();
    }
    return teacherCounter;
}

inline void displayAllTeachers() {
    string allTeacherInfo;
    cout<<endl<<"LIST OF ALL TEACHERS:"<<endl;
    displayFile.open("Teacher List.txt");
    if (displayFile.is_open()) {
        if(!getline(displayFile, allTeacherInfo)) {
            cout<<"There is no available data."<<endl<<endl;
            return;
        } else {
            cout<<allTeacherInfo<<endl;
            while(getline(displayFile, allTeacherInfo)) {
                cout<<allTeacherInfo<<endl;
            }
        }
        displayFile.close();
    }
}

inline void displaySingleTeacherInfo(int teacherCounter) {
    string teacherFileName;
    if(teacherCounter <= 0) return;
    loop = 0;
    cout<<endl<<"Which teacher's information would you like to access?"<<endl<<"Enter the number of your choice: ";
    cin>>numberInput;
    while (loop == 0) {
        if(numberInput > teacherCounter || numberInput <= 0) { //input validation
            cout<<endl<<"Invalid input please enter a number from the list of teachers"<<endl<<"Enter the number of your choice: ";
            cin>>numberInput;
        } else {
            displayFile.open("teacher file names.txt"); //reads the file name of chosen teacher
            if(displayFile.is_open()) {
                while(displayFile.getline(lineReader, 100)) {
                    lineCounter++;
                    if(lineCounter == numberInput) {
                        teacherFileName = lineReader; //inputs file name into a variable
                        break;
                    }
                }
                displayFile.close();
                loop = 1;
            } lineCounter = 0;

        }
    }

    displayFile.open(teacherFileName);
    if(displayFile.is_open()) { //reads specific teacher file and prints out all the info
        while(displayFile.getline(lineReader, 300)) {
            cout<<lineReader<<endl;
        }
        displayFile.close();
    }
}

inline void deleteFile(int teacherCounter) {
    fstream deleteTeacherInfoFile;
    fstream deleteTempFile;
    if(teacherCounter <= 0) return;
    loop = 0;
    cout<<endl<<"Which teacher would you like to delete?"<<endl<<"Enter the number of your choice: ";
    cin>>numberInput;
    while (loop == 0) {
        if(numberInput > teacherCounter || numberInput <= 0) { // input validation
            cout<<endl<<"Invalid input please enter a number from the list of teachers"<<endl<<"Enter the number of your choice: ";
            cin>>numberInput;
        } else {
            deleteTeacherInfoFile.open("Teacher List.txt"); // for Teacher List file
            deleteTempFile.open("tempTeacherList.txt", ios::out);
            lineCounter = 0;
            while (deleteTeacherInfoFile.getline(lineReader, 100)) {
                lineCounter++;
                if(lineCounter != numberInput) {
                    deleteTempFile<<lineReader<<endl;
                }
            }
            deleteTeacherInfoFile.close();
            deleteTempFile.close();
            remove("Teacher List.txt");
            rename("tempTeacherList.txt", "Teacher List.txt");  // end of Teacher List file

            deleteTeacherInfoFile.open("teacher display file.txt");  // for display file
            deleteTempFile.open("tempDisplayFile.txt", ios::out);
            lineCounter = 0;
            while (deleteTeacherInfoFile.getline(lineReader, 100)) {
                lineCounter++;
                if(lineCounter != numberInput) {
                    deleteTempFile<<lineReader<<endl;
                }
            }
            deleteTeacherInfoFile.close();
            deleteTempFile.close();
            remove("teacher display file.txt");
            rename("tempDisplayFile.txt", "teacher display file.txt"); // end of display file

            deleteTeacherInfoFile.open("teacher file names.txt"); // for file names file
            deleteTempFile.open("tempFileNames.txt", ios::out);
            lineCounter = 0;
            while (deleteTeacherInfoFile.getline(lineReader, 100)) {
                lineCounter++;
                if(lineCounter != numberInput) {
                    deleteTempFile<<lineReader<<endl;
                } else {
                    int i = 0;
                    while (lineReader[i] != '\0' && i < 100) {
                        fileName[i] = lineReader[i];
                        i++;
                    }
                    fileName[i] = '\0';
                }
            }
            deleteTeacherInfoFile.close();
            deleteTempFile.close();
            remove("teacher file names.txt");
            rename("tempFileNames.txt", "teacher file names.txt"); // end of file names file
            remove(fileName); // deletes the specific teacher's unique file

            loop = 1;
        }
    }
}
