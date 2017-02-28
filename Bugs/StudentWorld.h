#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir): GameWorld(assetDir){};
    
    ~StudentWorld();

    virtual int init();

    virtual int move();

    virtual void cleanUp();
    
    int getCurrentTicks() const;
    
    bool isRock(int x, int y) const;
    
    Actor* findFood(int x, int y) const;
    
    void add(int x, int y, Actor  * object);
    
    Actor* getRandomInsect(int x, int y, Actor* biter, int colony = -1);
    
    void wetInsects(int x, int y);
    
    void poisonInsects(int x, int y);
    
    bool checkDanger(Ant* a);
    
    Actor* findPheromone(int x, int y, int colony);
    
    void setAnts(int value, int colony);
    
    int getAnts(int colony);

private:
    std::vector<Actor*> m_actorList[VIEW_HEIGHT][VIEW_WIDTH];
    std::string m_AntsNames[4];
    int m_nAnts[4];
    int gameTicks;
    int m_size;
    int m_winner;
};

#endif // STUDENTWORLD_H_
