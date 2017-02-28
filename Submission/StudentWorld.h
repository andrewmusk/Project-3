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

private:
    std::vector<Actor*> m_actorList[VIEW_HEIGHT][VIEW_WIDTH];
    int gameTicks;
};

#endif // STUDENTWORLD_H_
