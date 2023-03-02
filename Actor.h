#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Base : public GraphObject {
public:
	static const int ALIVE = 1;
	static const int DEAD = 0;
	Base(int imageID, int startX, int startY, StudentWorld* world, int dir = right, int depth = 0, double size = 1.0, int isAlive = ALIVE) : GraphObject(imageID, startX,
		startY, dir, depth, size), m_world(world), m_isAlive(isAlive) {} // contstuctor

	// getters
	StudentWorld* getWorld() const {
		return m_world;
	}

	bool isAlive() const {
		return m_isAlive;
	}

	virtual void doSomething() = 0;


private:
	StudentWorld* m_world;
	int m_isAlive;

};

class Player : public Base {
public:
	static const int WAITING_TO_ROLL_STATE = 0;
	static const int ROLL_STATE = 1;
	static const int PEACH = 1;
	static const int YOSHI = 2;
	Player(int imageID, int startX, int startY, StudentWorld* world, int playerNum, int dir = right, int walkingDir = right, int depth = 0,
		double size = 1.0, int ticksToMove = 0, int state = WAITING_TO_ROLL_STATE, int isAlive = ALIVE) : Base(imageID, startX, startY, world, dir, depth, size),
		m_playerNum(playerNum), m_walkingDir(walkingDir), m_ticksToMove(ticksToMove), m_state(state) {} // contstuctor

	// Getters 
	int getPlayerNum() const {
		return m_playerNum;
	}

	int getwalkingDir() const {
		return m_walkingDir;
	}

	int getState() const {
		return m_state;
	}

	// Setters
	void setState(int state) {
		m_state = state;
	}

	void setWalkingDir(int dir) {
		m_walkingDir = dir;
	}

	void doSomething();

private:
	int m_playerNum;
	int m_walkingDir;
	int m_ticksToMove;
	int m_state;
};


class SquareBase : public Base {
public:
	SquareBase(int imageID, int startX, int startY, StudentWorld* world, int dir = right, int depth = 1, double size = 1.0, int isAlive = ALIVE) : Base(imageID, startX,
		startY, world, dir, depth, size, isAlive) {} // contstuctor


	virtual void doSomething() = 0;
	
private:
	
};

class CoinSquare : public SquareBase {
public:
	static const int BLUE = 0;
	
	CoinSquare(int imageID, int startX, int startY, StudentWorld* world, int color, int dir = right, int depth = 1, double size = 1.0) : SquareBase(imageID, startX,
		startY, world, dir, depth, size), m_color(color) {
			switch (color) {
			case 0:
				m_deltaCoins = 3;
				break;
			}
	} // contstuctor

	void doSomething();
private:
	int m_deltaCoins = 0;
	int m_color;
};

#endif // ACTOR_H_
