#include "player.h"
#include "enemies.h"

std::vector<Player*> Player::players;

//todo: do this automatically from derived classes?
Player* Player::GetRandomEnemy(int tier)
{
    return (Player*)(new Gazer());
}
void Player::Heal(int HP)
{
    hp += HP;
    if (hp > maxHP)
        hp = maxHP;
}
void Player::SetMaxHP(int hp, bool fill)
{
    this->maxHP = hp;
    if (fill)
    {
        Heal(hp);
    }
}

void Player::AddPlayer(Player* p)
{
    players.push_back(p);
}