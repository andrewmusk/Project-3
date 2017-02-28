#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


//CONSTRUCTORS
Actor::Actor(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
GraphObject(imageID,startX,startY,dir,depth)
{
    m_currentWorld = currentWorld;
    beenChecked = false;
}

Pebble::Pebble(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
Actor(IID_ROCK,startX,startY,currentWorld,dir,depth)
{
    setMovable(false);
}

Energy::Energy(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
Actor(imageID,startX,startY,currentWorld,dir,depth)
{
    
}

Active::Active(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
Energy(imageID,startX, startY,currentWorld,dir,depth)
{
    m_isAlive = true;
    m_isMobile = true;
    setMovable(true);
}

Baby_Grass::Baby_Grass(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
Active(IID_BABY_GRASSHOPPER,startX,startY,currentWorld,dir,1)
{
    int ran = randInt(0, 3);
    switch (ran) {
        case 0:
            setDirection(up);
            break;
        case 1:
            setDirection(down);
        case 2:
            setDirection(right);
        case 3:
            setDirection(left);
    }
    m_distance = randInt(2, 10);
    setEnergy(500);
    setMobility(0);
    setAlive(true);
    m_isSleeping = 0;
}


//GETTERS AND SETTERS
//ENERGY
void Energy::setEnergy(int value)
{
    m_energy = value;
}
int Energy::getEnergy()
{
    return m_energy;
}
bool Actor::getChecked()
{
    return beenChecked;
}
void Actor::setChecked(bool value)
{
    beenChecked = value;
}
bool Actor::getMovable()
{
    return m_isMovable;
}
void Actor::setMovable(bool value)
{
    m_isMovable = value;
}


//ACTIVE
void Active::setAlive(bool value)
{
    m_isAlive = value;
}
void Active::setMobility(int value)
{
    m_isMobile = value;
}
int Active::getMobility()
{
    return m_isMobile;
}


//OTHER MEMBER FUNCTIONS

void Baby_Grass::doSomething()
{
    setEnergy(getEnergy()-1);
    std::cout << getEnergy() << std::endl;
    if(getEnergy()==0)
    {
        //ASK STUDENT WORLD TO ADD FOOD HERE
        setAlive(false);
        return;
    }
    if(m_isSleeping>0)
    {
        m_isSleeping--;
        return;
    }

    if(m_distance==0)
    {
        int ran = randInt(0, 3);
        switch (ran) {
            case 0:
                setDirection(up);
                break;
            case 1:
                setDirection(down);
                break;
            case 2:
                setDirection(right);
                break;
            case 3:
                setDirection(left);
                break;
        }
        m_distance = randInt(2, 10);
    }
    m_distance--;
    
    if(getDirection()==up)
    {
        if(!(getWorld()->isRock(getX(),getY()-1)))
            moveTo(getX(),getY()-1);
        else
            m_distance=0;
        
    }
    if(getDirection()==down)
    {
        if(!(getWorld()->isRock(getX(),getY()+1)))
            moveTo(getX(),getY()+1);
        else
            m_distance=0;
    }
    if(getDirection()==right)
    {
        if(!(getWorld()->isRock(getX()+1,getY())))
            moveTo(getX()+1,getY());
        else
            m_distance=0;
    }
    if(getDirection()==left)
    {
        if(!(getWorld()->isRock(getX()-1,getY())))
            moveTo(getX()-1,getY());
        else
            m_distance=0;
    }
    m_isSleeping = 2;
}
