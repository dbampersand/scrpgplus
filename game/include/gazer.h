#pragma once

#include "aicontrolled.h"
#include <string>

class Gazer : public AIControlled
{
    public:
        Gazer() : AIControlled(std::string("assets/enemies/gazer.aseprite"))
        {   
            name = "Gazer"; 
            SetMaxHP(100,true);
            Damage(90);
        };
        ~Gazer() {};
        void Update(float dt) override {
        };
        void AITurn(int turnOrder, Player* enemyPlayer)
        {
            // do 10 damage and 5 damage altenately
            if (turnOrder % 2 == 0)
            {
                enemyPlayer->Damage(10);
            }
            else
            {
                enemyPlayer->Damage(5);
            }
        }
         void TakeTurn(Player* enemyPlayer) final override {
            AITurn(TurnsTaken,enemyPlayer);
            TurnsTaken++;
        };

};