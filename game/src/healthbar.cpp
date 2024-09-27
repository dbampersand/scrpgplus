#include "healthbar.h"

void HealthBar::DrawHealthBar(Rectangle r)
{
    DrawRectangleRounded(r, 0.25, 10, BLACK);

    Rectangle health = r;
    health.width -= padding;
    health.height -= padding;
    health.x += padding / 2.0f;
    health.y += padding / 2.0f;
    health.width *= HP;

    DrawRectangleRounded(health, 0.25, 10, RED);

};