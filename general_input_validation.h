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

