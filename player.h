#pragma once

#include "gameobject.h"

class Player : GameObject
{
    private:
        int hp;
        int maxHP;
        bool AiControlled;
    public:
        Player(std::string sprite) : GameObject(sprite) {};
        ~Player() {};

        void Update(float dt);
        static std::vector<Player*> players;


        void AddPlayer()
        {

        }

        int GetHP() {
            return hp;
        }
        int GetMaxHP() {
            return maxHP;
        }


};