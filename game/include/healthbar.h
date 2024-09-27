#pragma once

#include "drawable.h"
#include "updatable.h"
#include "tween.h"  
class HealthBar
{   
    public:
    HealthBar() {
        HP = 0;
    };
    bool shouldDraw = true;
    float HP = 0;
    float padding = 4;
    Tween<float> HealthBarTween = Tween<float>(&HP,Tween<float>::EaseOutQuad, 0.25f);
    void UpdateHP(float newHP, float maxHP)
    {
        HP = newHP / maxHP;
    }
    void DrawHealthBar(Rectangle r)
    {   
        DrawRectangleRounded(r,0.25,10,BLACK);

        Rectangle health = r;
        health.width -= padding;
        health.height -= padding;
        health.x += padding / 2.0f;
        health.y += padding / 2.0f;
        health.width *= HP;

        DrawRectangleRounded(health,0.25,10,RED);

    };  
};