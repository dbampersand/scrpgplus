#pragma once
#include "player.h"

class AIControlled : public Player
{
public:
	AIControlled(std::string sprite);

	virtual void AITurn(int turnOrder, Player* enemyPlayer) = 0;
	
	//The number of turns this player has taken
	int TurnsTaken = 0;
	
	//Creates particles when attacked by the player
	void CreateAttackedParticles(float damage);

	std::vector<Drawable*> GetChildren() override;

};	

