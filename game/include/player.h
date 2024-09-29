#pragma once

#include "gameobject.h"
#include <map>
#include "render.h"

class Player : public GameObject
{
private:
    int hp = 100;
    int maxHP = 100;
    int Shield;
    HealthBar HealthBar;
protected:
    bool AiControlled;
public:
    void SetMaxHP(int hp, bool fill);
    void AddShield(int shield);
    void ClearShield();


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
    void Heal(float amt);
    void Damage(float amt);


    virtual void AITurn(int turnOrder, Player* enemyPlayer)
    {
    }
    virtual void TakeTurn(Player* enemyPlayer) = 0;

};

