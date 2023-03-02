#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

StudentWorld::~StudentWorld() {
    cleanUp();
}

int StudentWorld::init()
{   
    m_actors.clear();
    m_board = new Board;
    string board_file = assetPath() + "board0" + std::to_string(getBoardNumber()) + ".txt";
    Board::LoadResult result = m_board->loadBoard(board_file);
    if (result == Board::load_fail_file_not_found)
        cerr << "Could not find board01.txt data file\n";
    else if (result == Board::load_fail_bad_format)
        cerr << "Your board was improperly formatted\n";
    else if (result == Board::load_success) {
        cerr << "Successfully loaded board\n";

        for (int x = 0; x < BOARD_WIDTH; x++) {
            for (int y = 0; y < BOARD_HEIGHT; y++) {
                Board::GridEntry ge = m_board->getContentsOf(x, y);
                //cout << (ge == Board::empty);
                switch (ge) {
                case Board::empty:
                    cerr << "Location (" << x << ", " << y << ") is empty\n";
                    break;
                case Board::boo:
                    cerr << "Location (" << x << ", " << y << ") has a Boo and a blue coin square\n";
                    m_actors.push_back(new CoinSquare(IID_BLUE_COIN_SQUARE, x*SPRITE_WIDTH, y*SPRITE_HEIGHT, this, 0));
                    break;
                case Board::bowser:
                    cerr << "Location (" << x << ", " << y << ") has a Bowser and a blue coin square\n";
                    m_actors.push_back(new CoinSquare(IID_BLUE_COIN_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this, 0));
                    break;
                case Board::player:
                    cerr << "Location (" << x << ", " << y << ") has Peach & Yoshi and a blue coin square\n";
                    m_actors.push_back(new CoinSquare(IID_BLUE_COIN_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this, 0));
                    m_peach = new Player(IID_PEACH, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this, Player::PEACH);
                    m_yoshi = new Player(IID_YOSHI, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this, Player::YOSHI);
                    break;

                case Board::blue_coin_square:
                    cerr << "Location (" << x << ", " << y << ") has a blue coin square\n";
                    m_actors.push_back(new CoinSquare(IID_BLUE_COIN_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this, 0));
                    break;
                }
                
            }
            //cout << "\n";
        }
    }

    
    
	startCountdownTimer(99);  // this placeholder causes timeout after 5 seconds
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.

    for (auto p : m_actors) {
        
        if (p->isAlive()) 
            p->doSomething();
    }

    if (m_peach->isAlive())
        m_peach->doSomething();

    if (m_yoshi->isAlive())
        m_yoshi->doSomething();



    for (int i = 0; i < m_actors.size(); i++) {
        auto it = m_actors.begin() + i;
        if (!(*it)->isAlive()) {
            m_actors.erase(it);
            i--;
        }
    }

    

    if (timeRemaining() <= 0) {
        playSound(SOUND_GAME_FINISHED);
        setFinalScore(0, 0);
        return GWSTATUS_PEACH_WON;
    }


    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    if (m_peach != nullptr) {
        delete m_peach;
        m_peach = nullptr;
    }
    if (m_yoshi != nullptr) {
        delete m_yoshi;
        m_yoshi = nullptr;
    }

    if (m_board != nullptr) {
        delete m_board;
        m_board = nullptr;
    }

    for (auto p : m_actors)
        delete p;
    m_actors.clear();
}


bool StudentWorld::canMove(Player* p, int dir) const {

    if (p->getX() % SPRITE_WIDTH || p->getY() % SPRITE_HEIGHT)
        return true;

    int x = p->getX() / SPRITE_WIDTH, y = p->getY() / SPRITE_HEIGHT;
    
    
    if (dir == 0) {
        if (x + 1 >= BOARD_WIDTH || m_board->getContentsOf(x + 1, y) == Board::empty) {
            return false;
        }
        return true;
    }

    if (dir == 90) {
        if (y + 1 >= BOARD_HEIGHT || m_board->getContentsOf(x, y + 1) == Board::empty) {
            return false;
        }
        return true;
    }

    if (dir == 180) {
        
        if (x < 0 || m_board->getContentsOf(x - 1, y) == Board::empty) {
            
            return false;
        }
        return true;
    }

    if (dir == 270) {
        
        if (y < 0 || m_board->getContentsOf(x, y - 1) == Board::empty) {
            return false;
        } 
        return true;
    }

    return false;
}