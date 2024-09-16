#pragma once

#include "gameobject.h"
#include <map>
#include "render.h"
#include "tile.h"
#include "slot.h"

class Player : public GameObject
{
    private:
        int hp;
        int maxHP;
        bool AiControlled;
    public:
        void SetMaxHP(int hp, bool fill);
        void Heal(int HP);

        std::string name;

        Player(std::string sprite) : GameObject(sprite) {
            x = Render::GetBasisWidth()/2.0f;
            y = Render::GetBasisHeight()/2.0f;
        };
        virtual ~Player() {
        };

        void Update(float dt) override {};

        static std::vector<Player*> players;

        static Player* GetRandomEnemy(int tier);
        static void AddPlayer(Player* p);

        int GetHP() {
            return hp;
        }
        int GetMaxHP() {
            return maxHP;
        }


};

