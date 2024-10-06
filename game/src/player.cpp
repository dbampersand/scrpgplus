#include "player.h"
#include "enemies.h"
#include "particle.h"
#include "gamestate.h"

std::vector<Player*> Player::players;

//todo: do this automatically from derived classes?
Player* Player::GetRandomEnemy(int tier)
{
    return (Player*)(new Gazer());
}
void Player::SetMaxHP(int hp, bool fill)
{
    this->maxHP = hp;
    if (fill)
    {
        Heal((int)hp);
    }
}
void Player::AddShield(int shield)
{
    this->Shield += shield;
    HealthBar.UpdateHP(hp, maxHP, Shield);
}
void Player::ClearShield()
{
    this->Shield = 0;
    HealthBar.UpdateHP(hp, maxHP, Shield);
}
void Player::AddPlayer(Player* p)
{
    players.push_back(p);
}
Player::Player(std::string sprite) : GameObject(sprite) {
    x = Render::GetBasisWidth() / 2.0f;
    y = Render::GetBasisHeight() / 2.0f;
    HealthBar.Parent = this;

    ClearShield();
    Heal(maxHP);
    //AddShield(200);
};
Player* Player::GetEnemy() {
    if (players.size() > 0)
        return players[0];
    else
        return nullptr;
};
int Player::GetHP() {
    return hp;
}
int Player::GetMaxHP() {
    return maxHP;
}

void Player::Heal(float amt)
{
    hp += (int)amt;
    if (hp > maxHP)
        hp = maxHP;
    HealthBar.UpdateHP(hp, maxHP, Shield);
}
void Player::Damage(float amt)
{
    float leftover = 0;
    Shield -= (int)amt;
    if (Shield < 0)
    {
        leftover = (int)-Shield;
        Shield = 0;
    }
    hp -= (int)leftover;
    if (hp < 0)
        hp = 0;
    HealthBar.UpdateHP(hp, maxHP, Shield);
    Attacked(amt);
};
void Player::Attacked(float damage)
{
    CreateAttackedParticles(damage);
}
bool Player::IsThisPlayersTurn()
{
    if (AiControlled && GameState::player == GameState::PlayerTurnType::AI_PLAYER)
        return true;
    if (!AiControlled && GameState::player == GameState::PlayerTurnType::PC_PLAYER)
        return true;
    return false;
}
