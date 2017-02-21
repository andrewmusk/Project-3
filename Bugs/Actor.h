#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

//                                  GraphObject
//                                        |
//                                      Actor
//                                        |
//                      Energy  -------      -------   Pebble
//                        |                               |
//         Active  ----       ----  Food   Poison   ----     ---- Water
//            |                       |
// Ant ----      ---- Baby Grass   Pheromone
//                        |           |
//                    Ad. Grass    Anthill




class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir = right, int depth=1);
    virtual void doSomething()=0;
    const StudentWorld* getWorld(){return m_currentWorld;};
    bool getChecked();
    void setChecked(bool value);
private:
    StudentWorld* m_currentWorld;
    bool beenChecked;
};

//FIRST LEVEL
class Pebble: public Actor
{
public:
    Pebble(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir = right, int depth=1);
    void doSomething(){return;
    };
private:
};

//SECOND LEVEL
class Poison: public Pebble
{
    
};

class Water: public Pebble
{
    
};


//FIRST LEVEL
class Energy: public Actor
{
public:
    Energy(int imageID, int startX, int startY,StudentWorld* currentWorld, Direction dir = right, int depth=1);
    void setEnergy(int value);
    int getEnergy();
    virtual void doSomething()=0;
private:
    int m_energy;
};

//SECOND LEVEL
class Active: public Energy
{
public:
    Active(int imageID, int startX, int startY,StudentWorld* currentWorld, Direction dir = right, int depth=1);
    void setAlive(bool value);
    void setMobility(int value);
    int getMobility();
    //bool Activate();
private:
    bool m_isAlive;
    int m_isMobile;
};

//THIRD LEVEL
class Ant: public Active
{
    
};

class Baby_Grass: public Active
{
public:
    Baby_Grass(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir = right, int depth=1);
    virtual void doSomething();
    void setSleep(int value);
private:
    int m_isSleeping;
    int m_distance;
    
};

//FOUR LEVEL

class Adult_Grass: public Baby_Grass
{
    
};

//SECOND LEVEL

class Food: public Energy
{
    
};

//THIRD LEVEL

class Pheromone: public Food
{
    
};

//FOURTH LEVEL

class Anthill: public Pheromone
{
    
};





#endif // ACTOR_H_
