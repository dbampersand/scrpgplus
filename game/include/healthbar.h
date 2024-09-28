#pragma once

#include "drawable.h"
#include "updatable.h"
#include "tween.h"  
typedef class GameObject GameObject;
class HealthBar : Drawable
{
    public:
        HealthBar() : Drawable("", 600)
        {
            HP = 0;
            position = Rectangle{ 0,0,0,0 };
        };
        GameObject* Parent;
        bool shouldDraw = true;
        float HP = 0;
        float padding = 4;
        Tween<float> HealthBarTween = Tween<float>(&HP,Tween<float>::EaseOutQuad, 0.25f);
        Rectangle position;
        void UpdateHP(float newHP, float maxHP)
        {
            HP = newHP / maxHP;
        }
        void DrawHealthBar(Rectangle r);
        void Draw(Rectangle r) {
            DrawHealthBar(r);
        }
        Rectangle GetPosition() override;

};