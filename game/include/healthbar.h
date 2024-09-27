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
    void DrawHealthBar(Rectangle r);

};