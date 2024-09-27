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
Player::Player(std::string sprite) : GameObject(sprite) {
    x = Render::GetBasisWidth() / 2.0f;
    y = Render::GetBasisHeight() / 2.0f;
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


