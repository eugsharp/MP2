#include <iostream>
#include <fstream>
#include <string>

using namespace std; 

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
    Checks to see if the given character is an uppercase character
    @param letter character to check if uppercase
*/
bool isUpper(char letter)
{
    int capitalCounter = 0;

    // Create an array to hold the 26 capital letters
    char capitalLetters[26];
    
    // Populate the array with letters A to Z using ASCII values
    for (int i = 0; i < 26; ++i) {
        capitalLetters[i] = 'A' + i;

        if (letter == capitalLetters[i])
        {
            capitalCounter++; // if there is a match, capital counter will be 1. 
        }
    }

    return capitalCounter > 0; // if not zero, then there was a match
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
    Checks if a given string contains numbers in it
    @param givenString string to check for numbers in it
*/
bool checkForNumbers(string givenString)
{
    int numbersFound = 0;

    // create array of digits
    for (int i = 0; i < givenString.size(); i++)
    {
        if (isdigit(givenString[i]))
        {
            numbersFound++;
        }
    }

    return numbersFound > 0;
}

/*
    Finds a name in a list file
    @param fileName name of list file
    @param name the name you are trying to look for
*/
bool nameValidator(string fileName, string name)
{
    bool validName = false;
    string line;

    // open list file
    ifstream list(fileName);

    if (!list)
    {
        cout << "The list file " << fileName << " does not exist" << endl;
    }

    // check if list file contains the name
    while (getline(list, line))
    {
        // Check if the name is contained within the line
        if (line.find(name) != string::npos) // name was found as a substring
        {
            validName = true;
        }
    }

    return validName;
}

/*
    Determines if the input is an integer. 
    @param input the input of the user
*/
bool integerInputValidation(string input)
{
    bool isAnInteger = true;
    int index = 0;

    // handle inputs with no length
    if (input.size() == 0)
    {
        return false;
    }

    while (index < input.size() && isAnInteger)
    {
        if (isdigit(input[index]) == false) // there are characters which are not numbers
        {
            isAnInteger = false;
        }

        index++;
    }

    return isAnInteger;
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
