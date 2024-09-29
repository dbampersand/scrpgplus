#include "player.h"
#include "enemies.h"

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
        Heal(hp);
    }
}
void Player::AddShield(int shield)
{
    this->Shield += shield;
}
void Player::ClearShield()
{
    this->Shield = 0;
}
void Player::AddPlayer(Player* p)
{
    players.push_back(p);
}
Player::Player(std::string sprite) : GameObject(sprite) {
    x = Render::GetBasisWidth() / 2.0f;
    y = Render::GetBasisHeight() / 2.0f;
    HealthBar.Parent = this;

    Heal(maxHP);

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
    hp += amt;
    if (hp > maxHP)
        hp = maxHP;
    HealthBar.UpdateHP(hp, maxHP);
}
void Player::Damage(float amt)
{
    hp -= amt;
    if (hp < 0)
        hp = 0;
    HealthBar.UpdateHP(hp, maxHP);
};
