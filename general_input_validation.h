#include <string>
#include <iostream>

using namespace std;

bool isValidInteger(string input) {

    for (int i = 0; i < input.size(); i++) { 

        if (!isdigit(input[i])) { // if the character isnt a digit, therefore the whole string isnt an integer
            return false; 
        }
    }
    
    // since passed the loop, must be an integer
    return true;
}

bool withinBounds (string input, int lowerBound, int upperBound) { 

    if (!isValidInteger(input)) { 
        cout << "\nInput" << input << "is not an integer. " << endl;
        return false;
    }

    int intInput = stoi(input);

    return intInput >= lowerBound && intInput <= upperBound;
}

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

bool allUpper(string line) { 
    
    int index = 0;
    bool allIsUpper = true;

    while(index < line.size() && allIsUpper) { 

        if (!isUpper(line[index])) { 
            allIsUpper = false;
        }
        index++;
    }
    
    return allIsUpper;
}

bool stringLongerThan1(string line) { 
    return line.size() > 0;
}