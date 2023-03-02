#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include "Actor.h"
#include "GraphObject.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Player;
class Base;

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();

  bool canMove(Player* p, int dir) const;
  ~StudentWorld();

private:
	std::vector<Base*> m_actors;
	Player* m_peach;
	Player* m_yoshi;
	Board* m_board;
	
};

#endif // STUDENTWORLD_H_
