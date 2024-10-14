#include "uielement.h"
#include "UI.h"
#include "render.h"

std::vector<Clickable*> Clickable::Clickables;


/*Rectangle UIElement::GetPosition() { 
    Rectangle r; r.x = x; r.y = y; r.width = w; r.height = h; 
    r = Render::TranslateToScreenSpace(r);
    return r; 
};
*/


Clickable::Clickable()
{
    clicked = false;
    Clickables.push_back(this);
}
Clickable::~Clickable()
{
    if (Clickables.size() > 0)
        Clickables.erase(std::remove(Clickables.begin(), Clickables.end(), this), Clickables.end());
}
bool Clickable::MousedOver(Rectangle r) {
    return CheckCollisionPointRec(Render::GetMousePos(), r);
};
void Clickable::UpdateClickables()
{
    for (Clickable* c : Clickables)
    {
        if (c->IsClickable && !c->IsHidden())
        {
            //if we're over the object 
            if (c->MousedOver(c->GetPosition()))
            {
                //just pressed mouse button
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    c->Clicked();
                    c->clicked = true;
                }
                //just released mouse button
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    c->Released();
                    c->clicked = false;
                }
            }
        }
        //just released mouse button, but not over the clicked element anymore
        if (c->clicked && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            c->clicked = false;
            c->Unclicked();
        }

    }
}


void UIElement::Disable()
{
    IsClickable = false;
}
void UIElement::Enable()
{
    IsClickable = true;
}
Rectangle UIElement::GetPosition()  {
    return Rectangle{ (float)x,(float)y,(float)w,(float)h };
}

UIElement::UIElement(float X, float Y, float W, float H) : Drawable("", 300) {
    x = X - W / 2.0f;
    y = Y - H / 2.0f;
    w = W;
    h = H;
};
