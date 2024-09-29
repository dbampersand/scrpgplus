#include "healthbar.h"
#include "render.h"
#include "gameobject.h"
#include <iostream>
void HealthBar::DrawHealthBar(Rectangle r)
{
    DrawRectangleRounded(r, 0.25, 10, BLACK);

    //clamp to between 0-1
    float hpVal = std::max(0.0f,std::min(1.0f, HP));
    float shieldVal = std::max(0.0f,std::min(1.0f,Shield));

    Rectangle health = r;
    health.width -= padding;
    health.height -= padding;
    health.x += padding / 2.0f;
    health.y += padding / 2.0f;
    health.width *= (hpVal);

    Rectangle shield = r;
    shield.width -= padding;
    shield.height -= padding;
    shield.width *= (shieldVal);
    shield.x += (padding / 2.0f) + health.width - shield.width;
    shield.y += padding / 2.0f;

    DrawRectangleRounded(health, 0.25, 10, RED);
    DrawRectangleRounded(shield, 0.25, 10, YELLOW);
};

Rectangle HealthBar::GetPosition()  {
    return Parent->GetHealthBarRectangle();
};
