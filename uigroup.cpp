#include "uigroup.h"
#include "uielement.h"
#include "raylib.h"
#include "drawable.h"
#include <iostream>
#include "button.h"
#include "gamestate.h"
#include "UI.h"

void UIGroup::Show()
{
    for (std::shared_ptr<UIElement> e : elements)
    {
        e->IsClickable = true;
        e->Hidden = false;
    }
}
void UIGroup::Hide()
{
    for (std::shared_ptr<UIElement> e : elements)
    {
        e->IsClickable = false;
        e->Hidden = true;
    }
}
void UIGroup::UpdateGroup(float dt)
{
   for(std::shared_ptr<UIElement> e : elements)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            e->Clicked();
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            e->Released();
        }
    }
}
void UIGroup::DrawGroup()
{
 /*
    for(std::shared_ptr<UIElement> e : elements)
    {   
       e->Draw();
    }*/
}
