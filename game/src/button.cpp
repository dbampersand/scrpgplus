#include "button.h"
#include "raylib.h"
#include "uigroup.h"
#include "UI.h"

Button::Button(float X, float Y, float W, float H, void (*Callback)()) : UIElement(X, Y, W, H) {
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
    DrawRectangle((int)r.x,(int)r.y,(int)r.width,(int)r.height,background);
    // draw foreground colour
    DrawRectangle((int)r.x+1, (int)r.y+1, (int)r.width-2, (int)r.height-2,c);

    if (!text.empty())
        Render::DrawText(text.c_str(), "assets/fonts/PlayfairDisplay/PlayfairDisplay-Bold.ttf", 12, Rectangle{ r.x + r.width / 2.0f,r.y + r.height / 2.0f,10 }, background, Sprite::SPRITE_ALIGN::CENTER);
}

void Button::Clicked()
{   
    this->DisableShadow();
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
