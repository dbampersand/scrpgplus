#pragma once

#include "drawable.h"
#include "updatable.h"
#include "healthbar.h"
#include "tween.h"

class GameObject : public Drawable, public Updatable
{
    public:
        float x; float y;
        float hp = 100;
        float maxHP = 100; 
        HealthBar HealthBar;
        GameObject(std::string path) : Drawable(path, 100), Updatable()
        {
            x = 0; y = 0;
            Heal(maxHP);
            Damage(10);
        };   
        void Heal(float amt)
        {
            hp += amt;
            if (hp > maxHP)
                hp = maxHP;
            HealthBar.UpdateHP(hp,maxHP);
        }
        void Damage(float amt)
        {
            hp -= amt;
            if (hp < 0)
                hp = 0;
            HealthBar.UpdateHP(hp,maxHP);
        };
        void Update(float dt) override;
        void Draw(Rectangle r) override {
            Rectangle healthBar = r;
            healthBar.height = 20;
            Drawable::Draw(r);
            HealthBar.DrawHealthBar(healthBar);

        };  
        Rectangle GetPosition() override { 
            Vector size = GetSize();
            return (Rectangle){(float)x-size.x/2.0f,(float)y-size.y/2.0f,(float)size.x,(float)size.y};
        }
};