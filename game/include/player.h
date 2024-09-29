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

    Player(std::string sprite);
    virtual ~Player() = default;

    void Update(float dt) override {};

    static std::vector<Player*> players;
    static Player* GetEnemy();

    static Player* GetRandomEnemy(int tier);
    static void AddPlayer(Player* p);

    int GetHP();
    int GetMaxHP();

    virtual void AITurn(int turnOrder, Player* enemyPlayer)
    {
    }
    virtual void TakeTurn(Player* enemyPlayer) = 0;

};

