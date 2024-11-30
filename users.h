#include "general_input_validation.h"
#include "util_funcs.h"
#include "option_handlers.h"

#include <iomanip>

using namespace std;

class User { 
    protected:
        string lastName;
        string givenName;
        string middleInitial = "";
        string houseNum;
        string streetName = "";
        string buildingName = "";
        string barangayName;
        string city;
        string mobileNum;
    public:
        // default constructor
        User() {}

        // constructor with parameters
        User(string ln, string gn, string mi, string hn, string sn, string bn, string barn, string c, string mn)
        : lastName(ln), givenName(gn), middleInitial(mi), houseNum(hn), streetName(sn),
          buildingName(bn), barangayName(barn), city(c), mobileNum(mn) {}
};

class Student : public User { 

};

class Teacher : public User { 
    private: 
        string subjects[10];
};
