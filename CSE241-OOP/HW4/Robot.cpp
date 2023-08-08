#include <iostream>
#include <string>
#include <ctime>
#include "Robot.h"
using namespace std;
int Robot :: getDamage()
{
    srand(time(0));
    delay();
    int damage = (rand() % Strength) + 1;
    cout << getType() << " attacks for " <<damage << " points!" << endl;
    return damage;
}
void Robot :: delay()//function created to generate random numbers
{
    int x,y,z,t;
    for(x=0;x<100;x++)
    {
        for(y=0;y<110;y++)
        {
            for(z=0;z<100;z++)
            {
                for(t=0;t<100;t++)
                {

                }
            }
        }
    }           
  
}
int Roomba :: getDamage()
{
    total_damage = 0;
    total_damage = Robot :: getDamage();
    cout<<getType()<<" robot double attacked extra damage is "<< total_damage <<" points!"<<endl;
    total_damage = total_damage * 2;
    cout<<getType()<<"Robot's total attack in this round is "<<total_damage<<" points!"<<endl;
    return total_damage;
}
int Bulldozer :: getDamage()
{
    total_damage = 0;
    total_damage = Robot :: getDamage();
    cout<<getType()<<"Robot's total attack in this round is "<<total_damage<<" points!"<<endl;
    return total_damage;
}
string Robot :: getType()
{
    switch(Type)
    {
        case(0):
            return "optimusprime";
        case(1):
            return "robocop";
        case(2):
            return "roomba";
        case(3):
            return "bulldozer";
    }
    return "unkown";
}
int Humanic :: getDamage()
{
    srand(time(0));
    //total_damage = 0;
    int tmp;
    bool damage_or_not = false;
    int damage;
    damage = Robot :: getDamage();
    tmp = rand() % 100 + 1;

    if(tmp > 0 && tmp < 11)//Checks whether the given probability is fulfilled
        damage_or_not = true;

    if(damage_or_not)//and act accordingly
    {
        cout<<getType()<<" robot tactical nuke attacked : + 50 points!"<<endl;
        damage = damage + 50;
    }
    return damage;
}
int Optimusprime :: getDamage()
{
    bool strong_or_weak = false;
    total_damage = 0;
    srand(time(0));
    int tmp = rand() % 100 +1 ;
    total_damage = Humanic :: getDamage();
    
    if(tmp>0 && tmp <16)
        strong_or_weak = true;

    if(strong_or_weak)
    {
        cout<<getType()<<" robot strong attacked that doubles the normal amount of damage"<<endl;
        total_damage = total_damage * 2;
    }
    cout<<getType()<<"Robot's total attack in this round is "<<total_damage<<" points!"<<endl;
    return total_damage;
}
int Robocop :: getDamage()
{
    total_damage = 0;
    total_damage += Humanic :: getDamage();
    cout<<getType()<<"Robot's Total attack in this round is"<<total_damage<<" points!"<<endl;
    return total_damage;
}