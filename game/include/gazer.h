#pragma once

#include "aicontrolled.h"
#include <string>

class Gazer : public AIControlled
{
    public:
        Gazer() : AIControlled(std::string("assets/enemies/gazer.png"))
        {   
            name = "Gazer";
            SetMaxHP(100,true);
        };
        ~Gazer() {};
        void Update(float dt) override {
        };
        void AITurn(int turnOrder, Player* enemyPlayer)
        {
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
            AITurn(turnOrder,enemyPlayer);
            turnOrder++;
        };

};