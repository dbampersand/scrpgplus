#pragma once
#include "player.h"

class AIControlled : public Player
{
public:
	AIControlled(std::string sprite) : Player(sprite) 
	{ };

	virtual void AITurn(int turnOrder, Player* enemyPlayer) = 0;
	int turnOrder;
};