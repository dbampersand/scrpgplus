#pragma once

#include "drawable.h"
#include "tween.h"  

typedef class GameObject GameObject;
class HealthBar : Drawable
{
    public:
        HealthBar() : Drawable("", 600)
        {
            Parent = nullptr;
            HP = 0;
            Shield = 0;
        };
        //Parent object this is tied to
        GameObject* Parent;

        bool shouldDraw = true;

        //Updates the HP and shield values for the health bar
        void UpdateHP(float newHP, float maxHP, float shield)
        {
            HP = (newHP+shield) / (maxHP+shield);
            Shield = shield / (maxHP);
        }

private:
    float HP = 0;
    float Shield = 0;
    float padding = 4;

    //Automated tweens for health bar and shield bar
    Tween<float> HealthBarTween = Tween<float>(&HP, Tween<float>::EaseOutQuad, 0.25f);
    Tween<float> ShieldBarTween = Tween<float>(&Shield, Tween<float>::EaseOutQuad, 0.1f);
    
    //Draws the health bar
    void DrawHealthBar(Rectangle r);


    void Draw(Rectangle r, Color tint) override {
        DrawHealthBar(r);
    }
    Rectangle GetPosition() override;

};