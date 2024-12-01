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
        // default constructor
        User() {}

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

        string getFullName() { 

            string fullName = lastName + ", " + givenName;

            // add a dot if the middle initial is not empty
            if (!middleInitial.empty()) { 
                fullName = fullName + " " + middleInitial + ".";
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
        int numOfSubjects;

    public: 
        // Default constructor for Teacher class
        Teacher() : User(), teacherNum("") {
            // Initialize subjects array to empty strings
            for (int i = 0; i < 10; ++i) {
                subjects[i] = "";
            }

            numOfSubjects = 0;
        }

        string getFullName() { // returns the name of the teacher in first, mid, last

            string fullName = givenName + " " + middleInitial;

            // add a dot if the middle initial is not empty
            if (!middleInitial.empty()) { 
                fullName = fullName + "." + " ";
            }

            fullName = fullName + lastName;

            return fullName;
        }

        string getOrderedFullName() { // returns the name of the teacher in last, first, mid

            string fullName = lastName + ", " + givenName;

            // add a dot if the middle initial is not empty
            if (!middleInitial.empty()) { 
                fullName = fullName + " " + middleInitial + ".";
            }

            return fullName;
        }

        void generateNum() { 
            int lineCount = 0;
            int intTeacherNum;
            
            // check if student list file exists
            if (!checkIfFileExists("Teacher List.txt")) { 
                // if not, 01-001
                teacherNum = "01-001";
                return;
            }
            
            ifstream teacherFile("Teacher List.txt");

            // if it does, count how many lines there are 
            string line;
            while(getline(teacherFile, line)) { 
                lineCount++;
            }

            teacherFile.close();

            // 01-num of lines + 1 with zeros
            intTeacherNum = lineCount + 1;

            teacherNum = "01-" + createNDigitNum(3, intTeacherNum);
        }

        string getNum() { 
            return teacherNum;
        }

        void setSubject(string subject) { 

            if (numOfSubjects >= 10) { 

                cout << "Maximum subjects reached. " << endl;
                return;
            }
            
            subjects[numOfSubjects] = subjectNameFromOption(stoi(subject));
            numOfSubjects++;
        }

        int getNumOfSubjects() { 
            return numOfSubjects;
        }

        string getSubjects() {
            string allSubjects = "";

            for (int i = 0; i < numOfSubjects; i++)
            {
                allSubjects = allSubjects + subjects[i];

                if (i != numOfSubjects - 1) {
                    allSubjects = allSubjects + ", ";
                }
            }
            
            return allSubjects;
        }
};
