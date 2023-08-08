#include <iostream>
#include "Student.h"
using namespace std;
using namespace PA3;


Student::Student(string Name,int Num)
{
    this-> Student_Name = Name;
    this-> Student_ID_Number = Num;
    this-> Course_References = nullptr;
    this -> Member_Course_Num = 0;
}
Student::Student()
{
    this-> Course_References = nullptr;
    this -> Member_Course_Num = 0;

}