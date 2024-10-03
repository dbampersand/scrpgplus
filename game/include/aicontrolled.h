#pragma once
#include "player.h"
#include "gamestate.h"
#include "particle.h"
#include "colours.h"
class AIControlled : public Player
{
public:
	AIControlled(std::string sprite) : Player(sprite) 
	{
		SetTint(GetNotActiveTint());
	};

	virtual void AITurn(int turnOrder, Player* enemyPlayer) = 0;
	int turnOrder;

	void CreateAttackedParticles(float damage)
	{
		Rectangle r = GetPosition();
		
		Vector2 v = Vector2{ r.x + r.width/2, r.y + r.height/2 };

		for (int i = 0; i  < damage*8; i++)
		{
			Particle::CreateParticle(v, GameState::RandRange<float>(0, 360), Colours::Damage, 3.0f, 2.0f, GameState::RandRange<float>(0,200), 200, Particle::BasicUpdate);
		}
	}
};	