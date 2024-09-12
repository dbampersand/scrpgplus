#pragma once

#include "player.h"
#include <string>

class Gazer : public Player
{
    public:
        Gazer() : Player(std::string("assets/enemies/gazer.png"))
        {   
            name = "Gazer";
            SetMaxHP(100,true);
        };
        ~Gazer() {};
        void Update(float dt) override {
        };
};