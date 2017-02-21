#include "StudentWorld.h"
#include "Field.h"
#include <string>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;

//Function Definitions
string setDisplayText(const StudentWorld* sw);
string formatDisplay(int ticks, int* antArr, int winningAntNumber, vector<string> names);

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
                    m_actorList[j][i].push_back(new Baby_Grass(999,i,j,this));
                    break;
                case Field::rock:
                    m_actorList[j][i].push_back(new Pebble(999,i,j,this));
                    break;
                    
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    gameTicks++;
    
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
                m_actorList[i][j][k]->setChecked(false);
            }
        }
    }
    
    
    //DELETE ALL DEAD ITEMS
    int arr[3];
    int a;
    setGameStatText(formatDisplay(gameTicks, arr, a, getFilenamesOfAntPrograms()));
    if(gameTicks==2000)
    {
        //find winning ant
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


string formatDisplay(int ticks, int* antArr, int winningAntNumber, vector<string> names)
{
    ostringstream oss;
    string s;
    oss << "Ticks";
    oss << setw(5) << ticks;
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
    for (int i = 0; i < m_actorList[y][x].size(); i++)
    {
        if (m_actorList[y][x][i] != nullptr)
        {
            Pebble * pp = dynamic_cast<Pebble*>(m_actorList[y][x][i]);
            if (pp != nullptr)
            {
                return true;
            }
        }
    }
    return false;
}






