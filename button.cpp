#include "button.h"
#include "raylib.h"
#include "uigroup.h"
#include "UI.h"
#include <iostream>
void Button::Draw()
{
    std::cout <<"Ggg\n\n";
    Button* b = (Button*)this;
    Rectangle r = this->GetPosition();
    DrawRectangle(r.x,r.y,r.width,r.height,background);
    DrawRectangle(r.x+1,r.y+1,r.width-2,r.height-2,foreground);
    if (!text.empty())
        UI::DrawText(GetFontDefault(),text.c_str(),r.x+r.width/2.0f,r.y+r.height/2.0f,10,background,UI::ALIGN_CENTER);

}
void Button::Clicked()
{
    if (MousedOver(this->GetPosition()))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            clicked = true;
        }
    }
}

void Button::Released()
{ 

    if (clicked && MousedOver(this->GetPosition()) && callback != nullptr) 
    {
        callback();
    }
    clicked = false;
}
