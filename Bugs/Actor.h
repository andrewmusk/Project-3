#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "Compiler.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

//                                  GraphObject
//                                        |
//                                      Actor
//                                        |
//                      Energy      ----      -----------------------------------    Pebble
//                        |                                                            |
//         Active  ----       ----  Food  --- Pheromone ---- Anthill    Poison   ----     ---- Water
//            |
// Ant ----      ---- Baby Grass
//                        |
//                    Ad. Grass



class Compiler;
class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir = right, int depth=1);
    virtual ~Actor();
    virtual void doSomething()=0;
    StudentWorld * getWorld(){return m_currentWorld;};
    bool getChecked();
    void setChecked(bool value);
    bool isNotRock();
    void setNotRock(bool value);
    bool isEatable();
    void setEatable(bool calue);
    void setAlive(bool value);
    bool isAlive();
    void setBiteable(bool value);
    bool isBiteable();
    bool isStunnable();
    void setStunnable(bool value);
    bool isDangerous();
    void setDangerous(bool value);
private:
    StudentWorld* m_currentWorld;
    bool m_isChecked;
    bool m_isNotRock;
    bool m_isEatable;
    bool m_isAlive;
    bool m_isBiteable;
    bool m_isStunnable;
    bool m_isDangerous;
};

//FIRST LEVEL
class Pebble: public Actor
{
public:
    Pebble(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir = right, int depth=1);
    void doSomething(){return;};
private:
};

class Poison: public Actor
{
public:
    Poison(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir = right, int depth=2);
    virtual void doSomething();
};

class Water: public Actor
{
public:
    Water(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir = right, int depth=2);
    virtual void doSomething();
};


//FIRST LEVEL
class Energy: public Actor
{
public:
    Energy(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir = right, int depth=1);
    virtual void doSomething()=0;
    void setEnergy(int value);
    int getEnergy();
    virtual bool eat(int amount);
    bool checkDead();
private:
    int m_energy;
};

//SECOND LEVEL
class Active: public Energy
{
public:
    Active(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir = right, int depth=1);
    void setStunnedAsleep(int val);
    int getStunnedAsleep();
    void setRandomDir();
    bool checkStunnedAsleep();
    void addFood(int amount);
    bool move();
    bool isWet();
    void setWet(bool value);
    bool bite(int damage);
    //bool Activate();
private:
    int m_isSleepStunned;
    bool m_isWet;
};

//THIRD LEVEL
class Ant: public Active
{
public:
    Ant(int homeX, int homeY ,int colony, Compiler* compiler, int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir = right, int depth=1);
    virtual void doSomething();
    virtual bool eat();
    int getColony();
    void setBitten(bool value);
    void addPheromone();
    void interpret();
    void interpret_if(Compiler::Command cmd);
    bool checkPheromone(int x, int y, int colony);
private:
    int m_colony;
    Compiler* m_compiler;
    int m_holding;
    int m_instruction;
    int m_lastRand;
    bool m_wasBlocked;
    bool m_wasBitten;
    int m_homeX, m_homeY;
};

class Baby_Grass: public Active
{
public:
    Baby_Grass(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir = right, int depth=1);
    virtual void doSomething();
    void setDistance(int move);
    int getDistance();
    void checkDoneWalking();
private:
    int m_distance;
    
};

//FOUR LEVEL

class Adult_Grass: public Baby_Grass
{
public:
    Adult_Grass(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir = right, int depth=1);
    virtual void doSomething();
};

//SECOND LEVEL

class Food: public Energy
{
public:
    Food(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir = right, int depth=2);
    virtual void doSomething();
};


class Pheromone: public Energy
{
public:
    Pheromone(int colonyNumber, int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir =right , int depth=2);
    virtual void doSomething();
    int getColony();
private:
    int m_colonyNumber;
};

class Anthill: public Energy
{
public:
    Anthill(int colonyNumber, Compiler* compiler, int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir = right, int depth = 2);
    virtual void doSomething();
    void giveBirth();
    virtual ~Anthill();
private:
    int m_colonyNumber;
    Compiler* m_compiler;
};





#endif // ACTOR_H_
