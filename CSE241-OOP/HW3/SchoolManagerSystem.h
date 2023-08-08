#ifndef SchoolManagerSystem_h
#define SchoolManagerSystem_h
#include <iostream>
using namespace std;
namespace PA3
{
    class Student;
    class Course;
    class SchoolManagerSystem
    {
        public:
            SchoolManagerSystem();
            Course* Course_References;
            Student* Student_References;
            int size_student;
            int size_course;
        private:

    };
}
#endif