#include <iostream>
#include <string>
#include "Robot.h"
using namespace std;
bool match(Robot robot1 , Robot robot2);
/*       case(0):
            return "optimusprime";
        case(1):
            return "robocop";
        case(2):
            return "roomba";
        case(3):
            return "bulldozer";
*/




int main()
{

    //Dear sir.Random numbers are not generated when I remove the delay function so delay because of delay() function in class.

    //Created Robot elements
    Robot robot1(0,10,10);
    Robot robot2(1,10,10);
    Robot robot3(2,10,10);
    Robot robot4(3,10,10);
    Robot robot5;
    /*OPTIMUS ROBOT TEST*/
    match(robot1,robot1);
    match(robot1,robot2);
    match(robot1,robot3);
    match(robot1,robot4);
    match(robot1,robot5);
    
     /*ROBOCOP TEST*/
    match(robot2,robot1);
    match(robot2,robot2);
    match(robot2,robot3);
    match(robot2,robot4);
    match(robot2,robot5);
    /*ROOMBA TEST*/
    match(robot3,robot1);
    match(robot3,robot2);
    match(robot3,robot3);
    match(robot3,robot4);
    match(robot3,robot5);
    /*BULLDOZER TEST*/
    match(robot4,robot1);
    match(robot4,robot2);
    match(robot4,robot3);
    match(robot4,robot4);
    match(robot4,robot5);
    /*DEFAULT TEST*/
    match(robot5,robot1);
    match(robot5,robot2);
    match(robot5,robot3);
    match(robot5,robot4);
    match(robot5,robot5);
    
    
    return 0;
}
bool match(Robot robot1,Robot robot2)
{
    /*creates class element according to situation*/

    Optimusprime type00(robot1.Type,robot1.Strength,robot1.HitPoint);
    Optimusprime type01(robot2.Type,robot2.Strength,robot2.HitPoint);
    Robocop type10(robot1.Type,robot1.Strength,robot1.HitPoint);
    Robocop type11(robot2.Type,robot2.Strength,robot2.HitPoint);
    Roomba type20(robot1.Type,robot1.Strength,robot1.HitPoint);
    Roomba type21(robot2.Type,robot2.Strength,robot2.HitPoint);
    Bulldozer type30(robot1.Type,robot1.Strength,robot1.HitPoint);
    Bulldozer type31(robot2.Type,robot2.Strength,robot2.HitPoint);
    /*transactions are performed by type*/
    if(robot1.getType()=="optimusprime" && robot2.getType() == "optimusprime")
    {
        while(type00.HitPoint > 0 && type01.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;
            type01.HitPoint -= type00.getDamage();
            cout<<"\n\n\n";
            
            if(type01.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type00.HitPoint -= type01.getDamage();
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    else if(robot1.getType()=="optimusprime" && robot2.getType() == "robocop")
    {
        while(type00.HitPoint > 0 && type11.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;
            
            type11.HitPoint -= type00.getDamage();
            cout<<"\n\n\n";
            if(type11.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type00.HitPoint -= type11.getDamage();
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    else if(robot1.getType()=="optimusprime" && robot2.getType() == "roomba")
    {
        while(type00.HitPoint > 0 && type21.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;
            
            type21.HitPoint -= type00.getDamage();
          
            
            if(type21.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type00.HitPoint -= type21.getDamage();
                
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    else if(robot1.getType()=="optimusprime" && robot2.getType() == "bulldozer")
    {
        while(type00.HitPoint > 0 && type31.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;
            
            type31.HitPoint -= type00.getDamage();
            
           
            if(type31.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type00.HitPoint -= type31.getDamage();
                
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    else if(robot1.getType()=="robocop" && robot2.getType() == "optimusprime")
    {
        while(type10.HitPoint > 0 && type01.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;
        
            type01.HitPoint -= type10.getDamage();

            if(type01.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type10.HitPoint -= type01.getDamage();
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    else if(robot1.getType()=="robocop" && robot2.getType() == "robocop")
    {
        while(type10.HitPoint > 0 && type11.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;
            type11.HitPoint -= type10.getDamage();
            if(type11.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type10.HitPoint -= type11.getDamage();
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    else if(robot1.getType()=="robocop" && robot2.getType() == "roomba")
    {
        while(type00.HitPoint > 0 && type21.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;
            type21.HitPoint -= type00.getDamage();
            if(type21.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type00.HitPoint -= type21.getDamage();
                
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    else if(robot1.getType()=="robocop" && robot2.getType() == "bulldozer")
    {
        while(type10.HitPoint > 0 && type31.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;
            type31.HitPoint -= type10.getDamage();
            if(type31.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type10.HitPoint -= type31.getDamage();
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    else if(robot1.getType()=="roomba" && robot2.getType() == "optimusprime")
    {
        while(type20.HitPoint > 0 && type01.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;
            type01.HitPoint -= type20.getDamage();
            if(type01.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type20.HitPoint -= type01.getDamage();
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    else if(robot1.getType()=="roomba" && robot2.getType() == "robocop")
    {
        while(type20.HitPoint > 0 && type11.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;
            type11.HitPoint -= type20.getDamage();
            if(type11.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type20.HitPoint -= type11.getDamage();
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    else if(robot1.getType()=="roomba" && robot2.getType() == "roomba")
    {
        while(type20.HitPoint > 0 && type21.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;
            type21.HitPoint -= type20.getDamage();
            if(type21.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type20.HitPoint -= type21.getDamage();
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    else if(robot1.getType()=="roomba" && robot2.getType() == "bulldozer")
    {
        while(type20.HitPoint > 0 && type31.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;
            type31.HitPoint -= type20.getDamage();
            if(type31.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type20.HitPoint -= type31.getDamage();
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    else if(robot1.getType()=="bulldozer" && robot2.getType() == "optimusprime")
    {
        while(type30.HitPoint > 0 && type01.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;
            type01.HitPoint -= type30.getDamage();
            if(type01.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type30.HitPoint -= type01.getDamage();
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    else if(robot1.getType()=="bulldozer" && robot2.getType() == "robocop")
    {
        while(type30.HitPoint > 0 && type11.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;
            type11.HitPoint -= type30.getDamage();
            if(type11.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type30.HitPoint -= type11.getDamage();
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    else if(robot1.getType()=="bulldozer" && robot2.getType() == "roomba")
    {
        while(type30.HitPoint > 0 && type21.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;          
            type21.HitPoint -= type30.getDamage();
            if(type21.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type30.HitPoint -= type21.getDamage();
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    else if(robot1.getType()=="bulldozer" && robot2.getType() == "bulldozer")
    {
        while(type30.HitPoint > 0 && type31.HitPoint>0)
        {
            cout<<"===1st robot attack order===\n\n\n"<<endl;
            
            type31.HitPoint -= type30.getDamage();
            if(type31.HitPoint>0)
            {
                cout<<"===2nd robot attack order===\n\n\n"<<endl;
                type30.HitPoint -= type31.getDamage();
                cout<<"\n\n\n";
            }
            else
            {
                cout<<"2nd robot destroyed."<<endl;
                cout<<"1st Robot won."<<endl;
                return true;
            }
        
        }
            cout<<"1st Robot destroyed."<<endl;
            cout<<"2nd Robot won."<<endl;       
            return true;
    }
    return true;
}