#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>
#include "Compiler.h"
using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


//CONSTRUCTORS
Actor::Actor(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
GraphObject(imageID,startX,startY,dir,depth)
{
    m_currentWorld = currentWorld;
    m_isChecked = false;
    m_isEatable = false;
    m_isNotRock = true;
    m_isAlive = true;
    m_isBiteable = false;
    m_isStunnable = false;
}

Pebble::Pebble(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
Actor(IID_ROCK,startX,startY,currentWorld,dir,depth)
{
    setNotRock(false);
}

Energy::Energy(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
Actor(imageID,startX,startY,currentWorld,dir,depth)
{
    
}

Active::Active(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
Energy(imageID,startX, startY,currentWorld,dir,depth)
{
    m_isSleepStunned = true;
    setBiteable(true);
    setWet(false);
    setDangerous(true);
}

Baby_Grass::Baby_Grass(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
Active(IID_BABY_GRASSHOPPER,startX,startY,currentWorld,dir,1)
{
    setRandomDir();
    setDistance(randInt(2, 10));
    setEnergy(500);
    setStunnedAsleep(0);
    
    setStunnable(true);
}

Food::Food(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
Energy(imageID,startX,startY,currentWorld,dir,depth)
{
    setEatable(true);
    setEnergy(6000);
}

Pheromone::Pheromone(int colonyNumber, int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
Energy(imageID,startX,startY,currentWorld,dir,depth)
{
    m_colonyNumber = colonyNumber;  
    setEnergy(256);
}

Anthill::Anthill(int colonyNumber, Compiler* compiler ,int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
Energy(imageID,startX,startY,currentWorld,dir,2)
{
    m_colonyNumber = colonyNumber;
    m_compiler = compiler;
    
    setEnergy(8999);
}


Adult_Grass::Adult_Grass(int imageID, int startX, int startY, StudentWorld * studentWorld, Direction dir, int depth) : Baby_Grass(IID_ADULT_GRASSHOPPER, startX, startY, studentWorld)
{
    setEnergy(1600);
    setDistance(randInt(2, 10));
    setStunnedAsleep(0);
    setRandomDir();
    
    setStunnable(false);
}

Water::Water(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
Actor(IID_WATER_POOL,startX,startY,currentWorld,dir,2)
{
    
}

Poison::Poison(int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
Actor(IID_POISON,startX,startY,currentWorld,dir,2)
{
    setDangerous(true);
}

Ant::Ant(int homeX, int homeY, int colony, Compiler* compiler, int imageID, int startX, int startY, StudentWorld* currentWorld, Direction dir, int depth):
Active(imageID,startX,startY,currentWorld,dir,1)
{
    m_compiler = compiler;
    m_colony = colony;
    m_holding = 0;
    m_instruction = 0;
    m_lastRand = 0;
    m_wasBlocked = false;
    m_wasBitten = false;
    m_homeX = homeX;
    m_homeY = homeY;
    
    setEnergy(1500);
    setRandomDir();
    setStunnedAsleep(0);
    
    //actor bools
    setStunnable(true);
}

// DESTRUCTOR

Actor::~Actor()
{
}

Anthill::~Anthill()
{
    delete m_compiler;
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
    return m_isChecked;
}
void Actor::setChecked(bool value)
{
    m_isChecked = value;
}
bool Actor::isNotRock()
{
    return m_isNotRock;
}
void Actor::setNotRock(bool value)
{
    m_isNotRock = value;
}
bool Actor::isEatable()
{
    return m_isEatable;
}
void Actor::setEatable(bool value)
{
    m_isEatable = value;
}
void Active::setStunnedAsleep(int val)
{
    m_isSleepStunned = val;
}
int Active::getStunnedAsleep()
{
    return m_isSleepStunned;
}
void Actor::setAlive(bool value)
{
    m_isAlive = value;
}
bool Actor::isAlive()
{
    return m_isAlive;
}
void Actor::setBiteable(bool value)
{
    m_isBiteable = value;
}
bool Actor::isBiteable()
{
    return m_isBiteable;
}
void  Baby_Grass::setDistance(int move)
{
    m_distance = move;
}
int Baby_Grass::getDistance()
{
    return m_distance;
}
void Active::setWet(bool value)
{
     m_isWet = value;
}
bool Active::isWet()
{
    return m_isWet;
}
bool Actor::isStunnable()
{
    return m_isStunnable;
}
void Actor::setStunnable(bool value)
{
    m_isStunnable = value;
}
int Ant::getColony()
{
    return m_colony;
}
void Ant::setBitten(bool value)
{
    m_wasBitten = value;
}
bool Actor::isDangerous()
{
    return m_isDangerous;
}
void Actor::setDangerous(bool value)
{
    m_isDangerous = value;
}
int Pheromone::getColony()
{
    return m_colonyNumber;
}

//DO SOMETHINGS

void Baby_Grass::doSomething()
{
    //#1
    setEnergy(getEnergy()-1);
    //#2
    if(checkDead())
    {
        addFood(100);
        return;
    }
    
    //#3
    if(checkStunnedAsleep())
    {
        return;
    }
    
    //#4
    //#5
    if(getEnergy() >= 1600)
    {
        //CREATE ADULT GRASSHOPPER
        Adult_Grass* daddy = new Adult_Grass(IID_ADULT_GRASSHOPPER,getX(),getY(),getWorld());
        getWorld() -> add(getX(), getY(), daddy);
        setAlive(false);
        //CREATE FOOD ON SQUARE
        addFood(100);
        return;
    }
    
    //#6 Eating the food on the current square
    bool eaten = eat(200);
    cout << "It is moving and energy: " << getEnergy() << endl;
    //#7 If eaten then 50% chance you will move
    if(eaten)
    {
        if(randInt(0, 1))
       {
           setStunnedAsleep(2);
           return;
       }
    }
    //#8 If distance currently zero then give new direction and distance
    checkDoneWalking();
    //#9 Decrease the distance because you are about to move
    m_distance--;
    //#10 Move decreases distance and moves or just sets distance 0
    int moved = move();
    if(!moved)
    {
        m_distance = 0;
    }
    
    //#12 Make it sleep again
    setStunnedAsleep(2);
}

void Adult_Grass::doSomething()
{
    //#1
    setEnergy(getEnergy()-1);
    //#2
    if(checkDead())
    {
        addFood(100);
        return;
    }
    //#3
    if(checkStunnedAsleep())
    {
        return;
    }
    //#4
    //DOING SOMETHING
    //#5
    if(randInt(1, 3)==1)
    {
        if(bite(50))
        {
            setStunnedAsleep(2);
            return;
        }
    }
    //#6
    if(randInt(1, 10)==1)
    {
        cout << "THIS MOFUCKER IS ABOUT TO SEND IT BIG TIME" << endl;
        bool foundOne = false;
        int i=0 ,j=0;
        while(i < 11 && !foundOne)
        {
            while( j < 11 && !foundOne)
            {
                double distance = sqrt(i*i + j*j);
                if(distance <= 10)
                {
                    if(!getWorld() -> isRock(getX() + i, getY() + j))
                    {
                        foundOne = true;
                    }
                }
                j++;
            }
            i++;
        }
        if(foundOne)
        {
            bool found = false;
            int x,y;
            while(!found)
            {
                int radius = randInt(1, 10);
                double angle = randInt(1, 360);
                x = radius * cos((angle/180 *  M_PI));
                y = radius * sin((angle/180 *  M_PI));
                if (!getWorld() -> isRock(getX() + x, getY() + y) && !(x==0 && y==0))
                {
                    cout << "AND HE SENT IT " << x << "   and y " << y << endl;
                    moveTo(getX()+x, getY()+y);
                    found = true;
                }
            }
        }
    }
    //#7
    bool eaten = eat(200);
    
    cout << "ADAD: It is moving and energy:" << getEnergy() << endl;
    //#8
    if(eaten)
    {
        if(randInt(0, 1))
        {
            setStunnedAsleep(2);
            return;
        }
    }
    //#9
    checkDoneWalking();
    setDistance(getDistance()-1);
    //#10
    if(!move())
        setDistance(0);
    //#11
    //#12
    setStunnedAsleep(2);
    return;
}
void Food::doSomething()
{
    cout << "The food is:" << getEnergy() << endl;
    return;
}

void Water::doSomething()
{
    getWorld()->wetInsects(getX(), getY());
    return;
}

void Poison::doSomething()
{
    getWorld()->poisonInsects(getX(), getY());
}

void Anthill::doSomething()
{
    //#1
    setEnergy(getEnergy()-1);
    //#2
    if(checkDead())
    {
        return;
    }
    //#3
    eat(10000);
    //#4
    cout << "Anthill energy:" << getEnergy() << endl;
    if(getEnergy()>=2000)
    {
        int imageID;
        switch (m_colonyNumber) {
            case 0:
                imageID = IID_ANT_TYPE0;
                break;
            case 1:
                imageID = IID_ANT_TYPE1;
                break;
            case 2:
                imageID = IID_ANT_TYPE2;
                break;
            case 3:
                imageID = IID_ANT_TYPE3;
                break;
        }
        
        Ant* baby = new Ant(getX(), getY(), m_colonyNumber, m_compiler,imageID, getX(), getY(), getWorld());
        getWorld()-> add(getX(), getY(), baby);
        
        setEnergy(getEnergy()-1500);
        
        int current = getWorld() -> getAnts(m_colonyNumber);
        getWorld() -> setAnts(current+1, m_colonyNumber);
        
        cout << "ANTHILL NO. :" << m_colonyNumber << " is making some babies" << endl;
    }
    return;
}

void Ant::doSomething()
{
    
    if(getX()==m_homeX && getY()==m_homeY)
    {
        cout << getColony() << "  THIS LITTLE ANT BABY HAS COME HOME WITH " << m_holding << " FOOD" << endl;
    }
    
    
    //#1 Decrease the ants energy
    setEnergy(getEnergy()-1);
    //#2 check if the ant is dead
    if(checkDead())
    {
        addFood(100);
        return;
    }
    cout << "My ant has energy :" << getEnergy() <<" with h:" << m_holding << endl;
    //#3 Check if the ant is stunned
    if(checkStunnedAsleep())
    {
        return;
    }
    //#4
    //a and b
    interpret();
}//ant do something

void Pheromone::doSomething()
{
    //decrease the pheromones points
    setEnergy(getEnergy()-1);
    //check if it is dead and if so it'll be set to dead
    checkDead();
}


//OTHER MEMBER FUNCTIONS

//ENERGY

bool Energy::eat(int amount)
{
    Actor* temp = getWorld()->findFood(getX(), getY()); //find's food on a spot and should return Food pointer
    Food* c_food = dynamic_cast<Food*>(temp); //dynamic cast to food which will work
    //precautionary
    if(c_food!=nullptr)
    {
        int meal = c_food->getEnergy(); //get the amount of food
        if(meal > 0) //check that there is still food on this spot
        {
            if(meal<=amount) // if the amount to eat is greater than what's left
            {
                setEnergy(getEnergy() + meal); // eat all the food left in food
                c_food -> setEnergy(c_food -> getEnergy()-meal);
                c_food -> setAlive(false); // kill the food object
            }
            else{
                setEnergy(getEnergy() + amount); // otherwise eat the intended amount
                c_food->setEnergy(meal-amount); // decrease this amount from food
            }
            return true; // return true if it ate food
        }
    }
    return false; // otherwise it didn't eat
}

//ACTIVE

void Active::setRandomDir() //generating and setting a direction for a random object
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
}

bool Energy::checkDead() //checks if an energy object is dead
{
    if(getEnergy()<=0 && isAlive()) // check if energy below or equal to zero and not already dead
    {
        setAlive(false); //kills the object
        return true; // return that the object has died
    }
    return false; // otherwise return normal.
}

bool Active::checkStunnedAsleep() //check if the object is stunned(by water) or sleeping like grasshopper
{
    if(getStunnedAsleep() > 0)
    {
        cout << "Sleeping: " << getStunnedAsleep() << endl;
        setStunnedAsleep(getStunnedAsleep()-1); // if it is sleeping, you decrement turn of sleep
        return true;
    }
    return false; // otherwise if not sleepoing return
}

void Active::addFood(int amount) //adding food to a coordinate when an insect dies or when ant drops food
{
    Food* temp = dynamic_cast<Food*>(getWorld()->findFood(getX(), getY())); //check if there is already food on the coord
    if(temp==nullptr) // if no food
    {
        cout << "IN the new food" << endl;
        Food* drop  = new Food(IID_FOOD, getX(), getY(), getWorld()); // create a new food object
        drop -> setEnergy(amount); //set the energy of the food to amount
        getWorld() -> add(getX(), getY(), drop); // add it to the data structure
    }
    else
    {
        cout << "In the old food" << endl;
        temp -> setEnergy(temp -> getEnergy()+amount); // otherwise add food to the exisiting object
    }
    return;
}

bool Active::move()
{
    if(getDirection()==up)
    {
        if(!(getWorld()->isRock(getX(),getY()-1)))
            moveTo(getX(),getY()-1);
        else
            return false;
    }
    if(getDirection()==down)
    {
        if(!(getWorld()->isRock(getX(),getY()+1)))
            moveTo(getX(),getY()+1);
        else
            return false;
    }
    if(getDirection()==right)
    {
        if(!(getWorld()->isRock(getX()+1,getY())))
            moveTo(getX()+1,getY());
        else
            return false;
    }
    if(getDirection()==left)
    {
        if(!(getWorld()->isRock(getX()-1,getY())))
            moveTo(getX()-1,getY());
        else
            return false;
    }
    setWet(false);
    return true;
}

bool Active::bite(int damage)
{
    Ant* p = dynamic_cast<Ant*>(this);
    Actor* rand;
    if(p!=nullptr)
        rand = getWorld() -> getRandomInsect(getX(), getY(),this, p -> getColony());
    else
        rand = getWorld() -> getRandomInsect(getX(), getY(), this);
    
    if(rand!=nullptr && rand->isAlive())
    {
        cout << "YO WE ARE ABOUT TO EAT THIS FAT FUCKING LITTLE INSECT ON THE SAME SQUARE AS ME" << endl;
        Active* randInsect = dynamic_cast<Active*>(rand);
        if(randInsect!=nullptr)
        {
            randInsect -> setEnergy(randInsect->getEnergy() - damage);
            if(randInsect -> checkDead())
            {
                addFood(100);
                return true;
            }
            
            //If it bit an ant, set ant bitten to true
            Ant* ifAnt = dynamic_cast<Ant*>(randInsect);
            if(ifAnt!=nullptr)
                ifAnt->setBitten(true);
            
            //If it bit an adult grasshopper, the AG has the option to bite back
            Adult_Grass* ifAdultGrass = dynamic_cast<Adult_Grass*>(randInsect);
            cout << "WE ACTUALLY RAN THIS FUCKING THING with " << ifAdultGrass << endl;
            if(ifAdultGrass!=nullptr)
            {
                if(randInt(0, 1)==1)
                {
                    ifAdultGrass -> bite(50);
                }
            }
        }
        else
            cout << "THERE IS A FAT FUCKING ERROR" << endl;
        return true;
    }
    return false;
}
//bite(50,-1);
//bite(10, getColony())

void Anthill::giveBirth()
{
    
}

//BABY GRASSHOPPER

void Baby_Grass::checkDoneWalking()
{
    if(m_distance==0)
    {
        setRandomDir();
        setDistance(randInt(2, 10));
    }
}

//ANT

bool Ant::eat()
{
    if(m_holding>0)
    {
        if(m_holding<100)
        {
            setEnergy(getEnergy()+m_holding);
            m_holding = 0;
        }
        else{
            setEnergy(getEnergy()+100);
            m_holding = m_holding - 100;
        }
        return true;
    }
    else{
        return false;
    }
}

void Ant::addPheromone()
{
    if (getWorld() -> findPheromone(getX(),getY(),getColony()) == nullptr)
    {
        Pheromone * p = new Pheromone(getColony(), IID_PHEROMONE_TYPE0+getColony(), getX(), getY(), getWorld());
        getWorld() -> add(getX(), getY(), p);
        return;
    }
    else
    {
        Pheromone* phero = dynamic_cast<Pheromone*>(getWorld() -> findPheromone(getX(),getY(),getColony()));
        phero -> setEnergy(getEnergy() + 256);
        if(phero->getEnergy() > 768)
            phero->setEnergy(768);
        return;
    }
}

bool Ant::checkPheromone(int x, int y, int colony)
{
    Actor* phero;
    int direction = getDirection();
    
    if(direction == up)
        phero = getWorld() -> findPheromone(getX(), getY()-1, getColony());
    else if(direction == down)
        phero = getWorld() -> findPheromone(getX(), getY()+1, getColony());
    else if(direction == right)
        phero = getWorld() -> findPheromone(getX()+1, getY(), getColony());
    else if (direction == left)
        phero = getWorld() -> findPheromone(getX()-1, getY(), getColony());
    
    
    if (phero == nullptr)
    {
        return false;
    }
    else
    {
        Pheromone* found = dynamic_cast<Pheromone*>(phero);
        if(found != nullptr)
        {
            if(found -> getEnergy()>0)
                return true;
            else
                return false;
        }
        else
            return false;
    }
}

void Ant::interpret()
{
    Compiler::Command cmd;
    int counter = 0;
    bool flag = false;
    
    while(!flag)
    {
        if(!m_compiler->getCommand(m_instruction, cmd))
        {
            cout << "IT CAN'T Read the instruction " << endl;
            
            setAlive(false);
            return;
        }
        //c
        //cout << "The ants are on instruction no. :" << m_instruction << endl;
        counter++;
        switch (cmd.opcode)
        {
            case Compiler::moveForward:
            {
                flag = true;
                bool moved = move();
                if(moved)
                {
                    m_wasBlocked = false;
                    m_wasBitten = false;
                }
                else{
                    m_wasBlocked = true;
                }
                m_instruction++;
                break;
            }
            case Compiler::eatFood:
            {
                flag = true;
                eat();
                m_instruction++;
                break;
            }
            case Compiler::dropFood:
            {
                flag = true;
                if(m_holding>0)
                {
                    addFood(m_holding);
                    m_holding = 0;
                }
                m_instruction++;
                break;
            }
            case Compiler::bite:
            {
                flag = true;
                bite(15);
                m_instruction++;
                break;
            }
            case Compiler::pickupFood:
            {
                flag = true;
                int energy_before = getEnergy();
                if(m_holding<=1400)
                {
                    Energy::eat(400);
                }
                else{
                    Energy::eat(1800-m_holding);
                }
                int energy_after = getEnergy();
                m_holding = m_holding + (energy_after-energy_before);
                setEnergy(energy_before);
                m_instruction++;
                break;
            }
            case Compiler::emitPheromone:
            {
                flag = true;
                addPheromone();
                m_instruction++;
                break;
            }
            case Compiler::faceRandomDirection:
            {
                flag = true;
                setRandomDir();
                m_instruction++;
                break;
            }
            case Compiler::rotateClockwise:
            {
                int current = getDirection();
                if(current == up)
                {
                    setDirection(right);
                }
                else if(current == right)
                {
                    setDirection(down);
                }
                else if(current == down)
                {
                    setDirection(left);
                }
                else if(current == left)
                {
                    setDirection(up);
                }
                break;
            }
            case Compiler::rotateCounterClockwise:
            {
                int current = getDirection();
                if(current == up)
                {
                    setDirection(left);
                }
                else if(current == right)
                {
                    setDirection(up);
                }
                else if(current == down)
                {
                    setDirection(right);
                }
                else if(current == left)
                {
                    setDirection(down);
                }
                break;
            }
            case Compiler::generateRandomNumber:
            {
                if(stoi(cmd.operand1)==0)
                {
                    m_lastRand = 0;
                }
                else
                {
                    m_lastRand = randInt(0, stoi(cmd.operand1)-1);
                }
                //cout << "rand num was "<< m_lastRand << endl;
                m_instruction++;
                break;
            }
            case Compiler::goto_command:
            {
                m_instruction = stoi(cmd.operand1);
                break;
            }
            case Compiler::if_command:
            {
                interpret_if(cmd);
            }//if case
        }//switch
        if(counter==10)
            flag=true;
    }//while loop
    return;
}

void Ant::interpret_if(Compiler::Command cmd)
{
    int next = stoi(cmd.operand2);
    switch(stoi(cmd.operand1))
    {
        case Compiler::Condition::last_random_number_was_zero:
        {
            if(m_lastRand==0)
                m_instruction = next;
            else
                m_instruction++;
            break;
        }
        case Compiler::Condition::i_am_carrying_food:
        {
            if(m_holding>0)
                m_instruction = next;
            else
                m_instruction++;
            break;
        }
        case Compiler::Condition::i_am_hungry:
        {
            if(getEnergy()<=25)
                m_instruction = next;
            else
                m_instruction++;
            break;
        }
        case Compiler::Condition::i_am_standing_with_an_enemy:
        {
            Actor* rand = getWorld()->getRandomInsect(getX(), getY(), this, getColony());
            if(rand!=nullptr)
                m_instruction = next;
            else
                m_instruction++;
            break;
        }
        case Compiler::Condition::i_am_standing_on_food:
        {
            Actor* object = getWorld()->findFood(getX(), getY());
            Food* c_food = dynamic_cast<Food*>(object);
            if(c_food!=nullptr)
                m_instruction = next;
            else
                m_instruction++;
            break;
        }
        case Compiler::Condition::i_am_standing_on_my_anthill:
        {
            if((getX()==m_homeX)&&(getY()==m_homeY))
                m_instruction = next;
            else
                m_instruction++;
            break;
        }
        case Compiler::Condition::i_smell_pheromone_in_front_of_me:
        {
            if(checkPheromone(getX(), getY(), getColony()))
                m_instruction = next;
            else
                m_instruction++;
            break;
        }
        case Compiler::Condition::i_smell_danger_in_front_of_me:
        {
            bool val = getWorld()->checkDanger(this);
            if(val)
            {
                m_instruction = next;
            }
            else
                m_instruction++;
            break;
        }
        case Compiler::Condition::i_was_bit:
        {
            if(m_wasBitten)
            {
                m_instruction = next;
            }
            else
                m_instruction++;
            break;
        }
        case Compiler::Condition::i_was_blocked_from_moving:
        {
            if(m_wasBlocked)
            {
                m_instruction = next;
            }
            else
                m_instruction++;
            break;
        }//blocked case
            break;
    }//switch
}

