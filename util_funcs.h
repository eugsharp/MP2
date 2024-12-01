#include <iostream>
#include <fstream>
#include <string>

/*
    Prints all lines in a given file
    @param fileName name of the desired file to print
*/
void printAllLinesInFile(string fileName) 
{
    ifstream file(fileName);  
    string line;

    if (!file.is_open()) 
    {
        cout << "Error: Could not open the file " << fileName << endl;
    }

    while (getline(file, line)) 
    {  
        cout << line << endl; 
    }

    file.close();  
}


/*
    Creates an N digit number such that it fills the rest of the leading digits with 0s
    @param n desired amount of digits
    @param actualNumber the actual number you want to change the amount of digits of 
*/
string createNDigitNum(int n, int actualNumber)
{
    string nDigitNum;
    string zeros;

    nDigitNum = to_string(actualNumber); // first make the number the actual number without zeros

    while (nDigitNum.length() < n)
    {
        nDigitNum.insert(0, 1, '0'); // keep prepending 0s until N digits are reached
    }

    return nDigitNum;
}


/*
    Sorts array of integers from lowest to highest
    @param array array to sort
    @param size size of array
*/
void sort(int array[], int size) 
{
    for (int i = 0; i < size - 1; i++)
    {
        if (array[i] > array[i+1]) 
        { 
            int temp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = temp;
        }
    }

    for (int i = 0; i < size - 1; i++)
    {
        if (array[i] > array[i + 1]) 
        { 
            sort(array, size);
        }
    }
}

bool checkIfFileExists(string filename) { 
    ifstream file(filename);
    
    if (file) { 
        file.close();
        return true;
    }
    else { 
        file.close();
        return false;
    }
}


string getStudentNumberByFile(string studentName, string fileName) {
    ifstream file(fileName);
    string line;
    
    // Check if the file was successfully opened
    if (!file.is_open()) {
        cout << "Error: Could not open file!" << endl;
        return "";
    }

    // Read through each line in the file
    while (getline(file, line)) {
        
        // If the student name is found in the line
        if (line.find(studentName) != string::npos) {
            // Extract the student number from the start of the line (assumes the number is the first part of the line)
            string studentNumber = line.substr(0, 6); 
            file.close();
            return studentNumber;
        }
    }

    file.close();
    return "Student not found"; // Return this if the name wasn't found in the file
}

string getStudentNameByFile(string studentNum, string fileName) {
    ifstream file(fileName);
    string line;
    
    // Check if the file was successfully opened
    if (!file.is_open()) {
        cout << "Error: Could not open file!" << endl;
        return "";
    }

    // Read through each line in the file
    while (getline(file, line)) {
        
        // If the student name is found in the line
        if (line.find(studentNum) != string::npos) {
            // Extract the student number from the start of the line (assumes the number is the first part of the line)
            string studentName = line.erase(0, 7); 
            file.close();
            return studentName;
        }
    }

    file.close();
    return "Student not found"; // Return this if the name wasn't found in the file
}

bool fileIsEmpty(string filename)
{
    ifstream file (filename);

    return file.peek() == ifstream::traits_type::eof(); // determines if the beginning of the file is the same as the end of the file
}
