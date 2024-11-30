#include "general_input_validation.h"
#include "util_funcs.h"
#include "option_handlers.h"

class User { 
    protected:
        string lastName;
        string givenName;
        string middleInitial;
        string houseNum;
        string streetName;
        string buildingName;
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

        string getFullAddress() { 
            string fullAddress = houseNum + ", ";
            
            if (!streetName.empty()) { 
                fullAddress = fullAddress + streetName + ", ";
            }

            if (!buildingName.empty()) { 
                fullAddress = fullAddress + buildingName + ", ";
            }

            fullAddress = fullAddress + barangayName + ", " + city;
            
            return fullAddress;
        }

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
        // Default constructor for Student class
        Student() : User(), studentNum("") {}

        // Constructor with parameters for Student class
        Student(string ln, string gn, string mi, string hn, string sn, string bn, string barn, string c, string mn, string snum)
        : User(ln, gn, mi, hn, sn, bn, barn, c, mn), studentNum(snum) {}

        string getFullName() { 

            string fullName = lastName + ", " + givenName + " " + middleInitial;

            // add a dot if the middle initial is not empty
            if (middleInitial != "") { 
                fullName = fullName + ".";
            }

            return fullName;
        }

        void generateNum() { 

            int lineCount = 0;
            int intStudentNum;
            
            // check if student list file exists
            if (!checkIfFileExists("Student List.txt")) { 
                // if not, 24-001
                studentNum = "24-001";
                return;
            }
            
            ifstream studentFile("Student List.txt");

            // if it does, count how many lines there are 
            string line;
            while(getline(studentFile, line)) { 
                lineCount++;
            }

            studentFile.close();

            // 24-num of lines + 1 with zeros
            intStudentNum = lineCount + 1;

            studentNum = "24-" + createNDigitNum(3, intStudentNum);
        }

        string getNum() { 
            return studentNum;
        }
};

class Teacher : public User { 
    private: 
        string subjects[10];
        string teacherNum;

    public: 
        // Default constructor for Teacher class
        Teacher() : User(), teacherNum("") {
            // Initialize subjects array to empty strings
            for (int i = 0; i < 10; ++i) {
                subjects[i] = "";
            }
        }

        // Constructor with parameters for Teacher class
        Teacher(string ln, string gn, string mi, string hn, string sn, string bn, string barn, string c, string mn, string tnum)
        : User(ln, gn, mi, hn, sn, bn, barn, c, mn), teacherNum(tnum) {
            // Initialize subjects array to empty strings
            for (int i = 0; i < 10; ++i) {
                subjects[i] = "";
            }
        }

        string getFullName() { // returns the name of the teacher in first, mid, last

            string fullName = givenName + " " + middleInitial;

            // add a dot if the middle initial is not empty
            if (!middleInitial.empty()) { 
                fullName = fullName + ".";
            }

            fullName = fullName + " " + lastName;

            return lastName;
        }

        string getOrderedFullName() { // returns the name of the teacher in last, first, mid

            string fullName = lastName + ", " + givenName + " " + middleInitial;

            // add a dot if the middle initial is not empty
            if (!middleInitial.empty()) { 
                fullName = fullName + ".";
            }

            return lastName;
        }

        void generateNum() { 

        }
};
