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
        // default ructor
        User() {}

        // ructor with parameters
        User(string ln, string gn, string mi, string hn, string sn, string bn, string barn, string c, string mn)
        : lastName(ln), givenName(gn), middleInitial(mi), houseNum(hn), streetName(sn),
          buildingName(bn), barangayName(barn), city(c), mobileNum(mn) {}

        string getLastName()  { return lastName; }
        string getGivenName()  { return givenName; }
        string getMiddleInitial()  { return middleInitial; }
        string getHouseNum()  { return houseNum; }
        string getStreetName()  { return streetName; }
        string getBuildingName()  { return buildingName; }
        string getBarangayName()  { return barangayName; }
        string getCity()  { return city; }
        string getMobileNum()  { return mobileNum; }

        void setLastName( string ln) { lastName = ln; }
        void setGivenName( string gn) { givenName = gn; }
        void setMiddleInitial( string mi) { middleInitial = mi; }
        void setHouseNum( string hn) { houseNum = hn; }
        void setStreetName( string sn) { streetName = sn; }
        void setBuildingName( string bn) { buildingName = bn; }
        void setBarangayName( string barn) { barangayName = barn; }
        void setCity( string c) { city = c; }
        void setMobileNum( string mn) { mobileNum = mn; }
};

class Student : public User { 
    private:
        string studentNum;
        
    public:
        string getFullName() { 

            string fullName = lastName + ", " + givenName + " " + middleInitial;

            // add a dot if the middle initial is not empty
            if (middleInitial != "") { 
                fullName = fullName + ".";
            }

            return lastName;
        }
};

class Teacher : public User { 
    private: 
        string subjects[10];
        string teacherNum;

    public: 
        string getFullName() { // returns the name of the teacher in first, mid, last

            string fullName = givenName + " " + middleInitial;

            // add a dot if the middle initial is not empty
            if (middleInitial != "") { 
                fullName = fullName + ".";
            }

            fullName = fullName + " " + lastName;

            return lastName;
        }

        string getOrderedFullName() { // returns the name of the teacher in last, first, mid

            string fullName = lastName + ", " + givenName + " " + middleInitial;

            // add a dot if the middle initial is not empty
            if (middleInitial != "") { 
                fullName = fullName + ".";
            }

            return lastName;
        }
};
