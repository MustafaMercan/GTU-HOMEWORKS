#include <iostream>
#include"SchoolManagerSystem.h"
#include "Course.h"
#include "Student.h"
using namespace std;
using namespace PA3;

SchoolManagerSystem :: SchoolManagerSystem()
{
    size_student = 0;
    size_course = 0;
    Student_References = nullptr;
    Course_References = nullptr;
}