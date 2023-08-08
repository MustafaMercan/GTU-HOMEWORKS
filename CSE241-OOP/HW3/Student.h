#ifndef Student_h
#define Student_h
#include <iostream>
#include <string>
#include "Course.h"
using namespace std;

namespace PA3
{
    class Course;
    class Student
    {
        public:
            Student(string Name,int Num);
            Student();
            string Student_Name;
            int Student_ID_Number;
            int Member_Course_Num;
            Course *Course_References = nullptr; 
        private:
        
    };
}
#endif