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
        GameObject(std::string path);
        void Heal(float amt);
        void Damage(float amt);
        void Update(float dt) override;
        void Draw(Rectangle r) override;
        Rectangle GetPosition() override;
        virtual Rectangle GetHealthBarRectangle();

};