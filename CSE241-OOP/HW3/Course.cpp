#include <iostream>
#include <string>
#include "Course.h"
using namespace std;
using namespace PA3;
Course :: Course(string Course_name,string Course_code)
{
    this->Course_Name = Course_name;
    this->Course_Code = Course_code;
    this->Student_References = nullptr;
    this->Number_Of_Team_Members = 0;
}
Course :: Course()
{
    this->Student_References = nullptr;
    this->Number_Of_Team_Members = 0;
}