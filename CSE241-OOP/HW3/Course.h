#ifndef Course_h
#define Course_h
#include <iostream>
#include <string>
#include "Student.h"
using namespace std;
namespace PA3
{
    class Student;
    class Course//Members: name, code, student references
    {
        public:
            Course(string Course_name,string Course_Code);//which takes name and code info... 
            Course();
            string Course_Name;
            string Course_Code;
            int Number_Of_Team_Members;
            Student *Student_References = nullptr;
        private:

    };
}
#endif