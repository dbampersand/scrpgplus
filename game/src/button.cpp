#include "button.h"
#include "raylib.h"
#include "uigroup.h"
#include "UI.h"

Button::Button(int X, int Y, int W, int H, void (*Callback)()) : UIElement(X, Y, W, H) {
    callback = Callback;
};

void Button::SetText(std::string str) {
    this->text = str;
};

void Button::Draw(Rectangle r, Color tint)
{
    Button* b = (Button*)this;
    Color c = foreground;
    if (!this->IsClickable)
    {
        c.r /= 2;
        c.g /= 2;
        c.b /= 2;
    }
    // draw background - the line around it 
    DrawRectangle(r.x,r.y,r.width,r.height,background);
    // draw foreground colour
    DrawRectangle(r.x+1,r.y+1,r.width-2,r.height-2,c);

    if (!text.empty())
        Render::DrawText(text.c_str(), "assets/fonts/PlayfairDisplay/PlayfairDisplay-Bold.ttf", 12, Rectangle{ r.x + r.width / 2.0f,r.y + r.height / 2.0f,10 }, background, Sprite::SPRITE_ALIGN::CENTER);
}

void Button::Clicked()
{
    if (MousedOver(this->GetPosition()))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            this->DisableShadow();
            clicked = true;
        }
    }
}

void Button::Released()
{ 
    this->EnableShadow();

    if (clicked && MousedOver(this->GetPosition()) && callback != nullptr) 
    {
        callback();
    }
    clicked = false;
}

void Button::Unclicked()
{
    this->EnableShadow();
}
