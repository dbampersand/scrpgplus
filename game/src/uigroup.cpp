#include "uigroup.h"
#include "uielement.h"
#include "raylib.h"
#include "drawable.h"
#include "button.h"
#include "gamestate.h"
#include "UI.h"
#include "button.h"

void UIGroup::Show()
{
    for (std::shared_ptr<UIElement> e : elements)
    {
        e->IsClickable = true;
        e->ShowDrawing();
    }
}
void UIGroup::Hide()
{
    for (std::shared_ptr<UIElement> e : elements)
    {
        e->IsClickable = false;
        e->HideDrawing(); 
    }
}
