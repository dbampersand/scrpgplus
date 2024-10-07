#include "healthbar.h"
#include "render.h"
#include "gameobject.h"
#include "colours.h"

void HealthBar::DrawHealthBar(Rectangle r) const
{
    DrawRectangleRounded(r, 0.25, 10, Colours::UIGray);

    //clamp to between 0-1
    float hpVal = std::max(0.0f,std::min(1.0f, HP));
    float shieldVal = std::max(0.0f,std::min(1.0f,Shield));

    //Create the part of the rectangle that represents the health (red part)
    Rectangle health = r;
    health.width -= padding;
    health.height -= padding;
    health.x += padding / 2.0f;
    health.y += padding / 2.0f;
    health.width *= (hpVal);

    //Create the part of the rectangle that represents the shield (yellow part)
    //this is based on the proportion of their shield to their health and placed on the right hand side
    Rectangle shield = r;
    shield.width -= padding;
    shield.height -= padding;
    shield.width *= (shieldVal);
    shield.x += (padding / 2.0f) + health.width - shield.width;
    shield.y += padding / 2.0f;

    DrawRectangleRounded(health, 0.25, 10, Colours::Damage);
    DrawRectangleRounded(shield, 0.25, 10, Colours::Shield);
};

Rectangle HealthBar::GetPosition()  {
    return Parent->GetHealthBarRectangle();
};
