#include "StudentWorld.h"
#include "Field.h"
#include "Compiler.h"
#include <string>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;

//Function Definitions
string setDisplayText(const StudentWorld* sw);
string formatDisplay(int ticks, int* antArr, string* names ,int winner, int size =4 );

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

int StudentWorld::init()
{
    int GameTicks = 0;
    Field current;
    std::string filename = getFieldFilename();
    std::cout << filename << endl;
    std::string error;
    Field::LoadResult result  = current.loadField(filename,error);
    int  x_anthill[4];
    int y_anthill[4];
    if(result != Field::LoadResult::load_success)
    {
        setError(filename + " " + error);
        cout << error << endl;
        return false; // something bad happened!
    }
    
    for(int i = 0; i < VIEW_WIDTH ; i++)
    {
        for(int j=0; j< VIEW_HEIGHT; j++)
        {
            Field::FieldItem item = current.getContentsOf(i,j);
            switch (item)
            {
                case Field::grasshopper:
                    m_actorList[j][i].push_back(new Baby_Grass(IID_BABY_GRASSHOPPER,i,j,this));
                    cout << "The grasshopper was set to have x and y " << i << "  " << j << endl;
                    break;
                case Field::rock:
                    m_actorList[j][i].push_back(new Pebble(IID_ROCK,i,j,this));
                    break;
                case Field::food:
                    m_actorList[j][i].push_back(new Food(IID_FOOD,i,j,this));
                    break;
                case Field::water:
                    m_actorList[j][i].push_back(new Water(IID_WATER_POOL,i,j,this));
                    break;
                case Field::poison:
                    m_actorList[j][i].push_back(new Poison(IID_POISON,i,j,this));
                    break;
                case Field::anthill0:
                    x_anthill[0] = i;
                    y_anthill[0] = j;
                    cout << i << j << endl;
                    break;
                case Field::anthill1:
                    x_anthill[1] = i;
                    y_anthill[1] = j;
                    break;
                case Field::anthill2:
                    x_anthill[2] = i;
                    y_anthill[2] = j;
                    break;
                case Field::anthill3:
                    x_anthill[3] = i;
                    y_anthill[3] = j;
                    break;
                case Field::empty:
                    break;
            }
        }
    }
    
    
    
    
    Compiler* c_ant_compiler;
    Anthill *c_antHill;
    vector<string> fileNames = getFilenamesOfAntPrograms();
    for(int k =0; k<fileNames.size(); k++)
    {
        m_size++;
        cout << "The bugfile names are: " <<filename[k] << endl;
        c_ant_compiler = new Compiler;
        std::string error;
        if (!c_ant_compiler->compile(fileNames[k], error) )
        {
            setError(fileNames[k] + " " + error);
            return GWSTATUS_LEVEL_ERROR;
        }
        c_antHill = new Anthill(k,c_ant_compiler,IID_ANT_HILL,x_anthill[k],y_anthill[k],this);
              
        add(x_anthill[k], y_anthill[k], c_antHill);
        m_AntsNames[k] = c_ant_compiler -> getColonyName();
    }
    
    m_winner = -1;
   
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    gameTicks++;
    
    vector<Actor*> have_checked;
    
    for(int i = 0; i < VIEW_WIDTH; i ++)
    {
        for(int j=0 ; j < VIEW_HEIGHT ; j++)
        {
            for(int k = 0; k< m_actorList[i][j].size(); k++)
            {
                if (!m_actorList[i][j][k]->getChecked())
                {
                    //CHECK IF IT IS ALIVE AND IF IT CAN MOVE
                    int initialX, initialY, finalX, finalY;
                    
                    initialX = m_actorList[i][j][k]->getX();
                    initialY = m_actorList[i][j][k]->getY();
                    
                    m_actorList[i][j][k]->doSomething();
                    
                    
                    finalX = m_actorList[i][j][k]->getX();
                    finalY = m_actorList[i][j][k]->getY();
                    
                    if(initialX!=finalX || initialY!=finalY)
                    {
                        m_actorList[i][j][k]->setChecked(true);
                        Actor* temp = m_actorList[i][j][k];
                        m_actorList[i][j].erase(m_actorList[i][j].begin()+k);
                        k--;
                        m_actorList[finalY][finalX].push_back(temp);
                        have_checked.push_back(temp);
                    }
                    
                }
            }
        }
    }
    
    for(int i = 0; i < VIEW_WIDTH; i ++)
    {
        for(int j=0 ; j < VIEW_HEIGHT ; j++)
        {
            for(int k = 0; k< m_actorList[i][j].size(); k++)
            {
               if(!m_actorList[i][j][k] -> isAlive())
               {
                   cout << "Deleted the dirty fuck  aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << endl << endl;
                   delete m_actorList[i][j][k];
                   m_actorList[i][j].erase(m_actorList[i][j].begin() + k);
               }
            }
        }
    }
     cout << endl << endl << endl;
    
    for(int i = 0 ; i < have_checked.size() ; i++)
    {
                have_checked[i]->setChecked(false);
    }
    
    
    //DELETE ALL DEAD ITEMS
    
    
    setGameStatText(formatDisplay(gameTicks, m_nAnts, m_AntsNames, m_winner, m_size));
    
    if(gameTicks==2000)
    {
        //find winning ant
        if(m_nAnts[m_winner] > 5)
        {
           setWinner(m_AntsNames[m_winner]);
            return GWSTATUS_PLAYER_WON;
        }
        
        
        return GWSTATUS_NO_WINNER;
    }
    return GWSTATUS_CONTINUE_GAME;
}



void StudentWorld::cleanUp()
{
    for(int i = 0; i < VIEW_WIDTH; i ++)
    {
        for(int j=0 ; j < VIEW_HEIGHT ; j++)
        {
            for(int k = 0; k< m_actorList[i][j].size(); k++)
            {
                cout << "Cleaned up" << endl;
                delete m_actorList[i][j].back();
                m_actorList[i][j].pop_back();
            }
        }
    }
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}
int StudentWorld::getCurrentTicks() const
{
    return gameTicks;
}


string formatDisplay(int ticks, int* antArr, string* names, int winner, int size)
{
    ostringstream oss;
    string s;
    //ticks
    oss << "Ticks";
    oss << setw(5) << (2000-ticks);
    //spaces in between
    oss << " -  ";
    for(int i = 0; i< size ;i++)
    {
        string player;
        player = player + names[i];
        if(i == winner)
        {
            player = "*" + player;
        }
        string num;
        if(antArr[i]<10)
            num = "0" + to_string(antArr[i]);
        else
            num = to_string(antArr[i]);
        
        player = player + ": " + num;
        
        if(i < size-1)
            oss << player << "  ";
        else
            oss << player;
    }
    return oss.str();
}
    /*cerr << names.size() << endl;
    //names[winningAntNumber] = names[winningAntNumber]+"*";
    for(int i = 0; i < 4; i++)
    {
        oss.fill('0');
        oss << names[i] << ": " << setw(2) << antArr[i] << "  ";
    }
    s = oss.str();
    return s;
}

string setDisplayText(const StudentWorld* sw)
{
    int ticks = sw->getCurrentTicks();
    vector<string> names = sw->getFilenamesOfAntPrograms();
    int antsAnt0, antsAnt1, antsAnt2, antsAnt3;
    int winningAntNumber;
    antsAnt0 = 0;
    antsAnt1 = 0;
    antsAnt2 = 0;
    antsAnt3 = 0;
    int antArr[4] = {antsAnt0,antsAnt1,antsAnt2,antsAnt3};
    winningAntNumber = antsAnt0;
    // Create a string from your statistics, of the form:
    // Ticks: 1134 - AmyAnt: 32 BillyAnt: 33 SuzieAnt*: 77 IgorAnt: 05
    string s = formatDisplay(ticks,antArr,winningAntNumber,names);
    // Finally, update the display text at the top of the screen with your
    // newly created stats
    return s;
}*/

bool StudentWorld::isRock(int x, int y) const
{
    if(x>=VIEW_WIDTH||y>=VIEW_HEIGHT||x<0||y<0)
        return true;
    for (int i = 0; i < m_actorList[y][x].size(); i++)
    {
        if (m_actorList[y][x][i] != nullptr)
        {
            if(!m_actorList[y][x][i] -> isNotRock())
            {
                return true;
            }
                
        }
    }
    return false;
}

Actor* StudentWorld::findFood(int x, int y) const
{
    for (int i = 0; i < m_actorList[y][x].size(); i++)
    {
        if (m_actorList[y][x][i] != nullptr)
        {
            if(m_actorList[y][x][i] -> isEatable())
            {
                return m_actorList[y][x][i];
            }
            
        }
    }
    return nullptr;
}

void StudentWorld::add(int x, int y, Actor  * object)
{
    m_actorList[y][x].push_back(object);
}

Actor* StudentWorld::getRandomInsect(int x, int y, Actor* p, int colony){
    
    std::vector<Actor*> v;
    
    for (int i = 0; i < m_actorList[y][x].size(); i++){
        
        if (m_actorList[y][x][i] != nullptr){
            
            if (m_actorList[y][x][i] -> isBiteable() && m_actorList[y][x][i] != p)
            {
                Ant* option = dynamic_cast<Ant*>(m_actorList[y][x][i]);
                Ant* original = dynamic_cast<Ant*>(p);
                if(option == nullptr)
                    v.push_back(m_actorList[y][x][i]);
                else
                {
                    if(original!= nullptr)
                    {
                        if(!(option -> getColony() == original-> getColony()))
                        {
                            v.push_back(m_actorList[y][x][i]);
                        }
                    }
                }
            }
            
        }
    }
    if (v.size() == 0)
    {
        return nullptr;
    }
    int rand = randInt(0, v.size()-1);
    return v[rand];
}

void StudentWorld::wetInsects(int x, int y)
{
    for(int k = 0; k < m_actorList[y][x].size(); k++)
    {
        if(m_actorList[y][x][k] -> isStunnable())
        {
            Active* insect = dynamic_cast<Active*>(m_actorList[y][x][k]);
            if(insect!=nullptr)
            {
                if(!insect->isWet())
                {
                    insect -> setWet(true);
                    insect -> setStunnedAsleep(insect ->getStunnedAsleep() +2);
                }
            }
                
        }
    }
}

void StudentWorld::poisonInsects(int x, int y)
{
    for(int k = 0; k < m_actorList[y][x].size(); k++)
    {
        if(m_actorList[y][x][k] -> isStunnable())
        {
            Active* insect = dynamic_cast<Active*>(m_actorList[y][x][k]);
            if(insect!=nullptr)
            {
                insect -> setEnergy(insect -> getEnergy() - 150);
                if(insect -> checkDead())
                {
                    insect->addFood(100);
                }
            }
        }
    }
}



bool StudentWorld::checkDanger(Ant* a)
{
    vector<Actor*> pos;
    if (a -> getDirection() == GraphObject::Direction::up)
    {
        pos = m_actorList[a -> getY() - 1][a -> getX()];
    }
    else if (a -> getDirection() == GraphObject::Direction::down)
    {
        pos = m_actorList[a -> getY() + 1][a -> getX()];
    }
    else if (a -> getDirection() == GraphObject::Direction::left)
    {
        pos = m_actorList[a -> getY()][a -> getX() - 1];
    }
    else if (a -> getDirection() == GraphObject::Direction::right)
    {
        pos = m_actorList[a -> getY()][a -> getX() + 1];
    }
    
    for (int k = 0; k < pos.size(); k++)
    {
        if (pos[k]->isDangerous()) // if it is dangerous to ants
        {
            Ant* antman = dynamic_cast<Ant*>(pos[k]); //changes to ant
            
            if(antman != nullptr)// if it is an ant
            {
               if(antman -> getColony() == a -> getColony()) // if they are in the same colony, it is not dangerous
                   continue;// check the next insect
            }
               return true; // if it is not in same colony and dangerous, return true
        }
        
    }
    return false;
}

Actor * StudentWorld::findPheromone(int x, int y, int colony)
{
    for (int i = 0; i < m_actorList[y][x].size(); i++)
    {
        if (m_actorList[y][x][i] != nullptr)
        {
            Pheromone* r = dynamic_cast<Pheromone*>(m_actorList[y][x][i]);
            if(r != nullptr && (colony == r->getColony()))
            {
                return m_actorList[y][x][i];
            }
        }
    }
    return nullptr;
}

void StudentWorld::setAnts(int value, int colony)
{
    m_nAnts[colony] = value;
    bool biggest = true;
    for(int j =0 ; j< m_size ; j++)
    {
        if(colony != j)
            if(m_nAnts[colony] <= m_nAnts[j])
                biggest = false;
    }
    
    if(biggest)
    {
        m_winner = colony;
    }
}

int StudentWorld::getAnts(int colony)
{
    return m_nAnts[colony];
}




