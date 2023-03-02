#include "Actor.h"
#include "StudentWorld.h"
#include "GameController.h"
#include "GameWorld.h"
#include "GameConstants.h"
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/* ---------------------------------------------------------------------------------
Base Class Implementaions
--------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------
Player Class Implementaions
--------------------------------------------------------------------------------- */

void Player::doSomething() {
	int dieRoll = -1;
	switch (getState()) {
	case 0:
		
		
		switch (getWorld()->getAction(m_playerNum)) {
		case ACTION_ROLL:
			dieRoll = randInt(1, 10);
			m_ticksToMove = dieRoll * 8;
			m_state = 1;
			break;
		default:
			return; 
		}

		
	case 1:
		
		if (!getWorld()->canMove(this, m_walkingDir)) {
			if (m_walkingDir == right || m_walkingDir == left) {
				if (getWorld()->canMove(this, up))
					setWalkingDir(90);
				else
					setWalkingDir(270);
			}
			else {
				if (getWorld()->canMove(this, right))
					setWalkingDir(0);
				else
					setWalkingDir(180);
			}
		}
	default:
		moveAtAngle(m_walkingDir, 2);
		if (--m_ticksToMove == 0)
			m_state = WAITING_TO_ROLL_STATE;
	}

}


/* ---------------------------------------------------------------------------------
CoinSquare Class Implementaions
--------------------------------------------------------------------------------- */

void CoinSquare::doSomething() {
	if (!isAlive())
		return;

}

