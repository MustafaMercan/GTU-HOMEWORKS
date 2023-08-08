#include <iostream>
#include "SchoolManagerSystem.h"//+
#include "Course.h"
#include "Student.h"

using namespace std;
using namespace PA3;
//===================================================//
//===================================================//
void menu(SchoolManagerSystem &System_Informations);
//===================================================//
void student_menu(SchoolManagerSystem &System_Informations);
void add_student(SchoolManagerSystem &System_Informations);
void select_student(SchoolManagerSystem &System_Informations);
bool check_student_name_id(SchoolManagerSystem System_Informations,string full_name,int ID,int &loc);
void delete_student(SchoolManagerSystem &System_Informations,string full_name,int ID);
void add_selected_student_to_a_course(SchoolManagerSystem &System_Informations,string full_name,int ID);
void student_registration_process(SchoolManagerSystem &System_Informations,int select_index,int loc,string full_name , int ID);
void add_a_member_to_course_class(SchoolManagerSystem &System_Informations,int select_index,Student Students);
void drop_selected_student_from_a_course(SchoolManagerSystem &System_Informations,string full_name,int ID);
void delete_student_in_course(SchoolManagerSystem &System_Informations,string full_name,int ID,int select_index);
void delete_student_in_another_courses(SchoolManagerSystem &System_Informations,string full_name,int ID);
//===================================================//
void course_menu(SchoolManagerSystem &System_Informations);
void add_course(SchoolManagerSystem &System_Informations);
void select_course(SchoolManagerSystem &System_Informations);
void list_students_registered_to_the_selected_course(SchoolManagerSystem &System_Informations,string code,string name);
void delete_course(SchoolManagerSystem &System_Informations,string code,string name);//bi bak buna en son
bool check_courses_name(SchoolManagerSystem System_Informations,string code,string name,int &loc);
bool check_student_to_course_or_not(SchoolManagerSystem &System_Informations,int loc);
void delete_course_from_student_references(SchoolManagerSystem &System_Informations,string code,string name);
void split_array_for_course_name_and_code(string str,string &name,string &code);
//=============================================================//
void list_all_students(SchoolManagerSystem System_Informations);
//=============================================================//
void list_all_courses(SchoolManagerSystem System_Informations);


int main()
{
    SchoolManagerSystem test1;
    menu(test1);

    return 0;
}
void menu(SchoolManagerSystem &System_Informations)//Menu function
{
    int process;
    cout<<"Main_menu"<<endl;
    do
    {
        cout<<"0 exit\n1 Student\n2 Course\n3 List_all_students\n4 List_all_courses"<<endl;
        cout<<">>";
        cin>>process;
        switch(process)
        {
            case 0:
                exit(1);
            case 1:
                student_menu(System_Informations);
                break;
            case 2:
                course_menu(System_Informations);
                break;
            case 3:
                list_all_students(System_Informations);
                break;
            case 4:
                list_all_courses(System_Informations);
                break;
                
        }

    }while(process != 0);
}
void student_menu(SchoolManagerSystem &System_Informations)//Student Menu
{
    int process;
    do
    {
        cout<<"0 up"<<endl;;
        cout<<"1 add_student"<<endl;
        cout<<"2 select_student"<<endl;
        cout<<">>";
        cin>>process;
        if(process == 1)
        {
            add_student(System_Informations);
        }
        else if(process == 2)
        {
            select_student(System_Informations);//+
        }
    }while(process != 0);
}
void add_student(SchoolManagerSystem &System_Informations)//required function to add students
{
    int process;
    string name_1,surname_1;
    int ID;
    int i;
    string name;

    cout<<">>";
    cin>>name_1>>surname_1>>ID;

    name = name_1 + " " + surname_1;
    

    if(System_Informations.size_student == 0)
    {
        System_Informations.Student_References = new Student;
        Student *tmp = new Student(name,ID);
        System_Informations.Student_References[0].Student_Name = tmp[0].Student_Name;
        System_Informations.Student_References[0].Student_ID_Number =tmp[0].Student_ID_Number;
        
    }
    else
    {
        Student *tmp;
        Student *tmp_2 = new Student(name,ID);
        tmp = new Student[System_Informations.size_student+1];
        for(i=0;i<System_Informations.size_student;i++)//Backup is done first.
        {
            tmp[i].Student_ID_Number = System_Informations.Student_References[i].Student_ID_Number;
            tmp[i].Student_Name = System_Informations.Student_References[i].Student_Name;
        }
        System_Informations.Student_References = new Student[System_Informations.size_student + 2];
        for(i=0;i<System_Informations.size_student;i++)//backed up information is restored
        {
            System_Informations.Student_References[i].Student_ID_Number = tmp[i].Student_ID_Number;
            System_Informations.Student_References[i].Student_Name = tmp[i].Student_Name;
        }
        System_Informations.Student_References[System_Informations.size_student].Student_Name = tmp_2[0].Student_Name;//Finally, the requested information is added.
        System_Informations.Student_References[System_Informations.size_student].Student_ID_Number = tmp_2[0].Student_ID_Number;
    }
    System_Informations.size_student++;
}
void select_student(SchoolManagerSystem &System_Informations)//Select student menu
{
    string name,surname;
    string full_name;
    int ID;
    int loc;
    int process;
    cout<<">>";
    cin>>name>>surname>>ID;
    full_name = name + " " + surname;
    do
    {
        cout<<"0 up\n";
        cout<<"1 delete_student\n";
        cout<<"2 add_selected_student_to_a_course\n";
        cout<<"3 drop_selected_student_from_a_course\n";
        cout<<">>";
        cin>>process;
        if(process==1)
        {
            delete_student(System_Informations,full_name,ID);
            process = 0;
        }
        else if(process == 2)
        {
            add_selected_student_to_a_course(System_Informations,full_name,ID);
        }
        else if(process == 3)
        {
            drop_selected_student_from_a_course(System_Informations,full_name,ID);
        }
    }while(process!= 0);
}
void course_menu(SchoolManagerSystem &System_Informations)
{
    int process;
    do
    {
        cout<<"0 up\n";
        cout<<"1 add_course\n";
        cout<<"2 select_course\n";
        cout<<">>";
        cin>>process;
        if(process == 1)
        {
            add_course(System_Informations);
        }
        else if(process == 2)
        {
            select_course(System_Informations);
        }
    }while(process != 0);
}
void add_course(SchoolManagerSystem& System_Informations)
{
    string name,code;
    string str;

    cout<<">>";
    cin.ignore();
    getline(cin,str);
    split_array_for_course_name_and_code(str,name,code);
    //cout<<"add course code->"<<code<<"->"<<name<<endl;

    //Backup is done first.
    //backed up information is restored
    //Finally, the requested information is added.
    int i;
    if(System_Informations.size_course == 0)
    {

        Course *tmp = new Course(name,code);
        System_Informations.Course_References = new Course;
        System_Informations.Course_References[0].Course_Name = tmp[0].Course_Name;
        System_Informations.Course_References[0].Course_Code = tmp[0].Course_Code;
    }
    else
    {
        Course *tmp;
        Course *tmp_2 = new Course(name,code);
        tmp = new Course[System_Informations.size_course+1];
        for(i=0;i<System_Informations.size_course;i++)
        {
            tmp[i].Course_Name = System_Informations.Course_References[i].Course_Name;
            tmp[i].Course_Code = System_Informations.Course_References[i].Course_Code;          
        }
        System_Informations.Course_References = new Course[System_Informations.size_course + 2 ];
        for(i=0;i<System_Informations.size_course;i++)
        {
            System_Informations.Course_References[i].Course_Name = tmp[i].Course_Name;
            System_Informations.Course_References[i].Course_Code = tmp[i].Course_Code;  
        }
        System_Informations.Course_References[System_Informations.size_course].Course_Name = tmp_2[0].Course_Name;
        System_Informations.Course_References[System_Informations.size_course].Course_Code = tmp_2[0].Course_Code;
    }
    System_Informations.size_course++;
}
void select_course(SchoolManagerSystem &System_Informations)
{
    string name;
    string code;
    string str;
    int process;
    int empty;
    do
    {
        cout<<">>";
        cin.ignore();
        getline(cin,str);
        split_array_for_course_name_and_code(str,name,code);
        if(check_courses_name(System_Informations,code,name,empty))//checks course name if it is exists
        {
            cout<<"0 up\n";
            cout<<"1 delete_course\n";
            cout<<"2 list_students_registered_to_the_selected_course\n";
            cout<<">>";
            cin>>process;
            if(process == 1)
            {
                delete_course(System_Informations,code,name);
                process=0;
            }
            else if(process == 2)
            {
                list_students_registered_to_the_selected_course(System_Informations,code,name);
                process=0;
            }
        }
    }while(process != 0);
}
void delete_course(SchoolManagerSystem &System_Informations,string code,string name)
{
    int i;
    int loc;
    int j=0;
    if(check_courses_name(System_Informations,code,name,loc))//checks if the course exists
    {
        //Backup is done first.
        //backed up information is restored
        //Finally, the requested information is added.
        Course *tmp;
        tmp = new Course[System_Informations.size_course];
        for(i=0,j=0;i<System_Informations.size_course;i++)
        {
            if(i != loc)
            {
                tmp[j].Course_Name = System_Informations.Course_References[i].Course_Name;
                tmp[j].Course_Code = System_Informations.Course_References[i].Course_Code;
                j++;
            }
        }
        System_Informations.Course_References = new Course[System_Informations.size_course];
        System_Informations.size_course--;
        for(i=0;i<System_Informations.size_course;i++)
        {
            System_Informations.Course_References[i].Course_Name = tmp[i].Course_Name;
            System_Informations.Course_References[i].Course_Code = tmp[i].Course_Code;
        }
        loc = -999;
        
    }
    delete_course_from_student_references(System_Informations,code,name);//Deleting the course name inside student_references
}
void list_students_registered_to_the_selected_course(SchoolManagerSystem &System_Informations,string code,string name)
{
    int i,index = -99;
    for(i=0;i<System_Informations.size_course;i++)//detect the index
    {
        if(System_Informations.Course_References[i].Course_Name == name && System_Informations.Course_References[i].Course_Code == code)
        {
            index = i;
            break;
        }
    }
    if(index != -99)
    {
        for(i=0;i<System_Informations.Course_References[index].Number_Of_Team_Members;i++)
        {
            cout<<"Student -> "<<System_Informations.Course_References[index].Student_References[i].Student_Name;
            cout<<" Student's ID number -> "<<System_Informations.Course_References[index].Student_References[i].Student_ID_Number<<endl;;
        }
    }
}
bool check_courses_name(SchoolManagerSystem System_Informations,string code,string name,int &loc)
{
    int i;
    for(i=0;i<System_Informations.size_course;i++)
    {
        if(System_Informations.Course_References[i].Course_Name == name && System_Informations.Course_References[i].Course_Code==code)
        {
            loc = i;//detect index
            return true;
        }
    }
    return false;
}
bool check_student_name_id(SchoolManagerSystem System_Informations,string full_name,int ID,int &loc)
{
    //Checking if the student's name exists
    int i;
    for(i=0;i<System_Informations.size_student;i++)
    {
        if(System_Informations.Student_References[i].Student_Name == full_name && System_Informations.Student_References[i].Student_ID_Number==ID)
        {
            loc = i;
            return true;
        }
    }
    return false;
}
void delete_student(SchoolManagerSystem &System_Informations,string full_name,int ID)//??
{
    int i;
    int loc;
    int j;
    Student *tmp;
    tmp = new Student[System_Informations.size_student];
        //Backup is done first.
        //backed up information is restored
        //Finally, the requested information is added.
    for(i=0,j=0;i<System_Informations.size_student;i++)
    {
        if(check_student_name_id(System_Informations,full_name,ID,loc))
        {
            if(i!= loc)
            {
                tmp[j].Student_ID_Number = System_Informations.Student_References[i].Student_ID_Number;
                tmp[j].Student_Name = System_Informations.Student_References[i].Student_Name;
                j++;
            }
        }
    }
    System_Informations.size_student--;
    System_Informations.Student_References = new Student[System_Informations.size_student];
    for(i=0;i<System_Informations.size_student;i++)
    {
        System_Informations.Student_References[i].Student_ID_Number = tmp[i].Student_ID_Number;
        System_Informations.Student_References[i].Student_Name = tmp[i].Student_Name;
    }
    
    delete_student_in_another_courses(System_Informations,full_name,ID);//deleted student's information is deleted from inside course references
    
}
void add_selected_student_to_a_course(SchoolManagerSystem &System_Informations,string full_name,int ID)
{
    int i = 0,j=0;
    int index = 0;
    int loc = 0;
    int count = 0;
    int select_index;
    bool check = true;
    while(System_Informations.Student_References[i].Student_Name != full_name && System_Informations.Student_References[i].Student_ID_Number != ID)
        i++;
    loc = i;
    //detects indexes of selected information
    if(System_Informations.size_course != 0)
    {
        for(i=0;i<System_Informations.size_course;i++)
        {
            for(j=0;j<System_Informations.Student_References[loc].Member_Course_Num;j++)
            {
                if(System_Informations.Course_References[i].Course_Name ==System_Informations.Student_References[loc].Course_References[j].Course_Name)
                {
                    if(System_Informations.Course_References[i].Course_Code ==System_Informations.Student_References[loc].Course_References[j].Course_Code)
                    {
                        check = false;
                        count++;
                    }
                }
            }
            if(check)
            {
                cout<<i-count+1<<" "<<System_Informations.Course_References[i].Course_Code<<" "<<System_Informations.Course_References[i].Course_Name<<endl;
                index++;
            }
            check = true;
        }
        cout<<">>";
        cin>>select_index;
        student_registration_process(System_Informations,select_index+count-1,loc,full_name,ID);
    }

}
void drop_selected_student_from_a_course(SchoolManagerSystem &System_Informations,string full_name,int ID)
{
            //Backup is done first.
        //backed up information is restored
        //Finally, the requested information is added.
    int loc;
    int i,j=0;
    int select_index;
    int count = 0;
    for(i=0;i<System_Informations.size_student;i++)
    {
        if(System_Informations.Student_References[i].Student_Name == full_name &&System_Informations.Student_References[i].Student_ID_Number == ID )
        {
            loc = i;
            break;
        }
    }
    if(System_Informations.Student_References[loc].Member_Course_Num != 0)
    {
        for(i=0;i<System_Informations.Student_References[loc].Member_Course_Num;i++)
        {
            cout<<i+1<<" "<<System_Informations.Student_References[loc].Course_References[i].Course_Name<<"->"<<System_Informations.Student_References[loc].Course_References[i].Course_Code<<endl;  
        }
        cout<<">>";
        cin>>select_index;
        select_index--;
        Course *tmp = new Course[System_Informations.Student_References[loc].Member_Course_Num];
        for(i=0;i<System_Informations.Student_References[loc].Member_Course_Num;i++)
        {
            if(i != select_index)
            {
                tmp[j].Course_Name = System_Informations.Student_References[loc].Course_References[i].Course_Name;
                tmp[j].Course_Code = System_Informations.Student_References[loc].Course_References[i].Course_Code;
            }
        }
        j=0;
        System_Informations.Student_References[loc].Member_Course_Num--;
        System_Informations.Student_References[loc].Course_References = new Course[System_Informations.Student_References[loc].Member_Course_Num + 1];
        for(i=0;i<System_Informations.Student_References[loc].Member_Course_Num;i++)
        {
            System_Informations.Student_References[loc].Course_References[i].Course_Name = tmp[i].Course_Name;
            System_Informations.Student_References[loc].Course_References[i].Course_Code = tmp[i].Course_Code;
        }
        
        delete_student_in_course(System_Informations,full_name,ID,select_index);
    }
}


void student_registration_process(SchoolManagerSystem &System_Informations,int select_index,int loc,string full_name , int ID)
{
            //Backup is done first.
        //backed up information is restored
        //Finally, the requested information is added.
    string Selected_Course_Name = System_Informations.Course_References[select_index].Course_Name;
    string Selected_Course_Code = System_Informations.Course_References[select_index].Course_Code;
    int size;
    int i;
    
    if(System_Informations.Student_References[loc].Member_Course_Num == 0)
    {
        
        System_Informations.Student_References[loc].Course_References = new Course(Selected_Course_Name,Selected_Course_Code);
        System_Informations.Student_References[loc].Member_Course_Num++;

    }
    else 
    {
        Course *tmp = new Course[System_Informations.Student_References[loc].Member_Course_Num+1];
        for(i=0;i<System_Informations.Student_References[loc].Member_Course_Num;i++)
        {
            tmp[i].Course_Name = System_Informations.Student_References[loc].Course_References[i].Course_Name;
            tmp[i].Course_Code = System_Informations.Student_References[loc].Course_References[i].Course_Code;
        }
        
        System_Informations.Student_References[loc].Course_References = new Course[System_Informations.Student_References[loc].Member_Course_Num+2];
        for(i=0;i<System_Informations.Student_References[loc].Member_Course_Num;i++)
        {
            System_Informations.Student_References[loc].Course_References[i].Course_Name = tmp[i].Course_Name;
            System_Informations.Student_References[loc].Course_References[i].Course_Code = tmp[i].Course_Code;
        }
        System_Informations.Student_References[loc].Course_References[System_Informations.Student_References[loc].Member_Course_Num].Course_Name = Selected_Course_Name;
        System_Informations.Student_References[loc].Course_References[System_Informations.Student_References[loc].Member_Course_Num].Course_Code = Selected_Course_Code;
        System_Informations.Student_References[loc].Member_Course_Num++;
        
    }
    add_a_member_to_course_class(System_Informations,select_index,System_Informations.Student_References[loc]);
}
void add_a_member_to_course_class(SchoolManagerSystem &System_Informations,int select_index,Student Students)
{
               //Backup is done first.
        //backed up information is restored
        //Finally, the requested information is added.
    string student_name = Students.Student_Name;
    int student_id = Students.Student_ID_Number;
    if(System_Informations.Course_References[select_index].Number_Of_Team_Members == 0)
    {
        System_Informations.Course_References[select_index].Student_References = new Student(student_name,student_id);
        System_Informations.Course_References[select_index].Number_Of_Team_Members++;
    }
    else
    {
        Student *tmp = new Student[System_Informations.Course_References[select_index].Number_Of_Team_Members+1];
        for(int i = 0;i<System_Informations.Course_References[select_index].Number_Of_Team_Members;i++)
        {
            tmp[i].Student_Name = System_Informations.Course_References[select_index].Student_References[i].Student_Name;
            tmp[i].Student_ID_Number = System_Informations.Course_References[select_index].Student_References[i].Student_ID_Number;
        }
        System_Informations.Course_References[select_index].Student_References = new Student[System_Informations.Course_References[select_index].Number_Of_Team_Members+1];
        for(int i = 0;i<System_Informations.Course_References[select_index].Number_Of_Team_Members;i++)
        {
            System_Informations.Course_References[select_index].Student_References[i].Student_Name =tmp[i].Student_Name;
            System_Informations.Course_References[select_index].Student_References[i].Student_ID_Number =tmp[i].Student_ID_Number;
        }
        System_Informations.Course_References[select_index].Student_References[System_Informations.Course_References[select_index].Number_Of_Team_Members].Student_Name = student_name;
        System_Informations.Course_References[select_index].Student_References[System_Informations.Course_References[select_index].Number_Of_Team_Members].Student_ID_Number = student_id;
        System_Informations.Course_References[select_index].Number_Of_Team_Members++;
        
    }
}
void delete_student_in_course(SchoolManagerSystem &System_Informations,string full_name,int ID,int select_index)
{

     for(int i = 0;i<System_Informations.Course_References[select_index].Number_Of_Team_Members ; i++)
     {
         cout<<System_Informations.Course_References[select_index].Student_References[i].Student_Name<<endl;
     }

     Student *tmp = new Student[System_Informations.Course_References[select_index].Number_Of_Team_Members];
     int j = 0;
     for(int i = 0;i<System_Informations.Course_References[select_index].Number_Of_Team_Members;i++)
     {
         if(System_Informations.Course_References[select_index].Student_References[i].Student_Name != full_name)
         {
            if(System_Informations.Course_References[select_index].Student_References[i].Student_ID_Number != ID)
            {
               tmp[j].Student_Name = System_Informations.Course_References[select_index].Student_References[i].Student_Name;
               tmp[j].Student_ID_Number = System_Informations.Course_References[select_index].Student_References[i].Student_ID_Number;
               j++;
            }
         }
     }
     System_Informations.Course_References[select_index].Number_Of_Team_Members--;
     System_Informations.Course_References[select_index].Student_References = new Student[System_Informations.Course_References[select_index].Number_Of_Team_Members +2];
     for(int i = 0;i<System_Informations.Course_References[select_index].Number_Of_Team_Members;i++)
     {
         System_Informations.Course_References[select_index].Student_References[i].Student_Name = tmp[i].Student_Name;
         System_Informations.Course_References[select_index].Student_References[i].Student_ID_Number = tmp[i].Student_ID_Number;

     }
}
void list_all_students(SchoolManagerSystem System_Informations)
{
    int i;
    for(i=0;i<System_Informations.size_student;i++)
    {
        cout<<"Name Surname -> "<<System_Informations.Student_References[i].Student_Name;
        cout<<" Student ID number ->"<<System_Informations.Student_References[i].Student_ID_Number<<endl;
    }
}
void list_all_courses(SchoolManagerSystem System_Informations)
{
    int i;
    for(i=0;i<System_Informations.size_course;i++)
    {
        cout<<"Course's Code ->"<<System_Informations.Course_References[i].Course_Code;
        cout<<" Course's Name ->"<<System_Informations.Course_References[i].Course_Name<<endl;
    }
}
void delete_course_from_student_references(SchoolManagerSystem &System_Informations,string code,string name)
{
    int loc,index;
    int check;
    int index_2;
    int l;
    for(int i = 0,check=-99,loc=-99,index=-99; i <System_Informations.size_student;i++)
    {
        for(int j=0;j<System_Informations.Student_References[j].Member_Course_Num-1;j++)
        {
            if(System_Informations.Student_References[i].Course_References[j].Course_Name == name)
            {
                if(System_Informations.Student_References[i].Course_References[j].Course_Code == code)
                {
                    check = 1;
                    loc = i;
                    index = j;
                    break;
                }
            }   
        }
        if(check == 1)
        {
            Course *tmp = new Course[System_Informations.Student_References[loc].Member_Course_Num + 2];
            for(int m = 0,l=0;m<System_Informations.Student_References[loc].Member_Course_Num;m++)
            {
                if(m!= index)
                {
                    tmp[l].Course_Name = System_Informations.Student_References[loc].Course_References[m].Course_Name;
                    tmp[l].Course_Code = System_Informations.Student_References[loc].Course_References[m].Course_Code;
                    l++;
                }
            }
            System_Informations.Student_References[loc].Course_References = new Course[System_Informations.Student_References[loc].Member_Course_Num];
            System_Informations.Student_References[loc].Member_Course_Num--;
            for(int m = 0;m<System_Informations.Student_References[loc].Member_Course_Num;m++)
            {
                System_Informations.Student_References[loc].Course_References[m].Course_Name = tmp[m].Course_Name; 
                System_Informations.Student_References[loc].Course_References[m].Course_Code = tmp[m].Course_Code;
            }
            
        }
    }
}
void delete_student_in_another_courses(SchoolManagerSystem &System_Informations,string full_name,int ID)//kursun içinden öğrenci silcez.
{
    int loc,index;
    int check;
    int index_2;
    int l = 0;
    for(int i = 0,check=-99,loc=-99,index=-99 ; i < System_Informations.size_course;i++)
    {
        for(int j = 0;j<System_Informations.Course_References[i].Number_Of_Team_Members;j++)
        {
            if(System_Informations.Course_References[i].Student_References[j].Student_Name == full_name)
            {
                if(System_Informations.Course_References[i].Student_References[j].Student_ID_Number == ID)
                {
                    check = 1;
                    loc = i ;
                    index = j;
                    break;
                }
            }
        }
        if(check==1)
        {
            Student *tmp = new Student[System_Informations.Course_References[loc].Number_Of_Team_Members + 2];
            for(int m = 0,l=0; m<System_Informations.Course_References[loc].Number_Of_Team_Members;m++)
            {
                if(m != index)
                {
                    tmp[l].Student_Name = System_Informations.Course_References[loc].Student_References[m].Student_Name;
                    tmp[l].Student_ID_Number = System_Informations.Course_References[loc].Student_References[m].Student_ID_Number;
                    l++;
                }
            }
            System_Informations.Course_References[loc].Student_References = new Student[System_Informations.Course_References[loc].Number_Of_Team_Members];
            System_Informations.Course_References[loc].Number_Of_Team_Members--;
            for(int m=0;m<System_Informations.Course_References[loc].Number_Of_Team_Members;m++)
            {
                System_Informations.Course_References[loc].Student_References[m].Student_Name = tmp[m].Student_Name;
                System_Informations.Course_References[loc].Student_References[m].Student_ID_Number = tmp[m].Student_ID_Number;
            }
        }
    }
}
void split_array_for_course_name_and_code(string str,string &name,string &code)
{
    int i =0;
    while(i<str.length())
    {
        if(str[i] != ' ')
        {
            code += str[i];
        }
        else
        {
            break;
        }
        i++;
    }
    while(i<str.length())
    {
        name += str[i];
        i++;
    }
}
