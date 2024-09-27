#include "gameobject.h"

void GameObject::Update(float dt)
{
}

GameObject::GameObject(std::string path) : Drawable(path, 100), Updatable()
{
    x = 0; y = 0;
    Heal(maxHP);
    Damage(10);
};
void GameObject::Heal(float amt)
{
    hp += amt;
    if (hp > maxHP)
        hp = maxHP;
    HealthBar.UpdateHP(hp, maxHP);
}
void GameObject::Damage(float amt)
{
    hp -= amt;
    if (hp < 0)
        hp = 0;
    HealthBar.UpdateHP(hp, maxHP);
};
void GameObject::Draw(Rectangle r)  {
    Rectangle healthBar = r;
    healthBar.height = 20;
    Drawable::Draw(r);
    HealthBar.DrawHealthBar(healthBar);

};
Rectangle GameObject::GetPosition()  {
    Vector2 size = GetSize();
    return Rectangle{ (float)x - size.x / 2.0f,(float)y - size.y / 2.0f,(float)size.x,(float)size.y };
}
