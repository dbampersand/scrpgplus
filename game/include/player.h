#pragma once

#include "gameobject.h"
#include "render.h"

class Player : public GameObject
{
public:
    //Sets the max health points of the player. If fill is true, then a heal of that value will also be applied.
    void SetMaxHP(int hp, bool fill);
    //Gets the players' max health points
    int GetMaxHP() const;
    //Gets the players' current health points
    int GetHP() const;
    //Heals the player by an amount, will not exceed MaxHP
    void Heal(float amt);
    //Damages the player for an amount
    void Damage(float amt);

    //Adds shield to the player
    void AddShield(int shield);
    //Clears the players' current shield
    void ClearShield();

    //Called when a player is attacked
    void Attacked(float damage);
    //To be overridden with custom logic for creating 'blood' particles when a Player is attacked
    virtual void CreateAttackedParticles(float damage) {};


    //Gets the player opposite this player, i.e. the human player if this is the AI player, or the AI player if this is the human
    static Player* GetEnemy();

    //Returns true if it is currently this players' turn
    bool IsThisPlayersTurn() const;
    
    HealthBar* GetHealthBar()
    {
        return &healthBar;
    }

    //Returns the tint value to be applied to the player's sprite that indicates it is not their turn
    Color GetNotActiveTint() const
    {
        return NotActiveTint;
    };

    //Gets a random fresh Enemy of a given tier 
    static Player* GetRandomEnemy(int tier);
    //Adds a player to the combat
    static void AddPlayer(Player* p);

    Player(std::string sprite);

    void Update(float dt) override {};
    //To be overridden with custom logic for the AI's turn
    virtual void AITurn(int turnOrder, Player* enemyPlayer) {};
    //To be overridden with custom logic for the Player's turn
    virtual void TakeTurn(Player* enemyPlayer) = 0;

    std::string GetName() override { return name; }


    static std::vector<Player*> players;
    std::string name;

private:
    int hp = 100;
    int maxHP = 100;
    int Shield;
    HealthBar healthBar;
    Color NotActiveTint = Color{ 128,128,128,255 };

protected:
    bool AiControlled;

};

