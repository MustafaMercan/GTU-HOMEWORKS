#ifndef Robot_h
#define Robot_h
#include <iostream>
#include <string>
using namespace std;
class Roomba;
class Robot{

    public:
        int Type;
        int HitPoint;
        int Strength;
        int total_damage;
        void delay();
        Robot(int newType,int newStrength,int newHitpoint)
        {
            Type = newType;
            Strength = newStrength;
            HitPoint = newHitpoint;
            total_damage = 0;          
        }
        Robot() { 
            Type = 3;
            Strength = 10;
            HitPoint = 10;
        }
        int getDamage();
        string getType();
};
class Roomba : public Robot{
    public:
        Roomba(int newType,int newStrength,int newHitpoint){
            Type = newType;
            Strength = newStrength;
            HitPoint = newHitpoint;
            total_damage = 0;
         }
        int getDamage();
};
class Bulldozer : public Robot{
    public:
        Bulldozer(int newType,int newStrength,int newHitpoint)
        {
            Type = newType;
            Strength = newStrength;
            HitPoint = newHitpoint;
            total_damage = 0;
        }
        int getDamage();
};
class Humanic : public Robot{
    public:
        Humanic()
        {
        }
        int getDamage();
};
class Optimusprime : public Humanic{
    public:
        Optimusprime(int newType,int newStrength,int newHitpoint)
        {
            Type = newType;
            Strength = newStrength;
            HitPoint = newHitpoint;
            total_damage = 0;       
        }
        Optimusprime(){ }
        int getDamage();
};
class Robocop : public Humanic{
    public:
        Robocop(int newType,int newStrength,int newHitpoint)
        {
            Type = newType;
            Strength = newStrength;
            HitPoint = newHitpoint;
            total_damage = 0;             
        }
        int getDamage();


};


#endif
