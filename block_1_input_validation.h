#include <iostream>
#include <string>
#include "class.h"

bool nameValidation(string name) { 

    // check if the name is empty
    if (name.size() < 1) { 
        return false;
    }

    // check if the name has numbers
    if (checkForNumbers(name)) { 
        return false;
    }

    return true; 
}

bool middleInitialValidation(string middleInitial) { 
    
    if (middleInitial.size() == 1) { 

        return isUpper(middleInitial[0]); // if the singular character in middle initial is uppercase
    }
    else if (middleInitial.size() > 1) { 

        return false;
    }
    
    return true; // if the middle initial is empty
}

bool validateHouseNumber(string houseNumInput) {

    if (houseNumInput.size() == 0) { 
        return false;
    }

    if (!isValidInteger(houseNumInput)) { // house number must be an integer type
        return false;
    }

    if (stoi(houseNumInput) < 0 || stoi(houseNumInput)  > 9999) { // house number must be maximum 4 nums
        return false;
    }

    return true;
}

bool validateMobileNumber(string mobileNumInput) { 

    // check if an integer
    if (!isValidInteger(mobileNumInput)) { 
        return false;
    }

    // check if mobile num is of length 11
    if (mobileNumInput.size() != 11) { 
        return false;
    }

    // check if mobile num starts with 09...
    if (mobileNumInput[0] == '0' && mobileNumInput[1] == '9') { 
        return true;
    }
    else {
        return false;
    }

}