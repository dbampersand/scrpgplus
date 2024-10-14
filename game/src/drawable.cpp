#include "drawable.h"
#include "sprite.h"
#include "raylib.h"
#include <string>
#include "render.h"
#include "UI.h"
#include <algorithm>

std::vector<Drawable*> Drawable::drawables;

bool Drawable::isSorted;

void Drawable::SetOrder(int ord) {
    isSorted = false;
    order = ord;
}
int Drawable::GetOrder() const {
    return order;
};
bool Drawable::IsSorted()
{
    return isSorted;
}
void Drawable::AddRenderOrder(int amt) {
    SetOrder(order + amt);
}
void Drawable::HideDrawing() {
    Hidden = true;
    HideChildren();
}
void Drawable::ShowDrawing() {
    Hidden = false;
    ShowChildren();
}
bool Drawable::IsHidden() const
{
    return Hidden;
}
Drawable::~Drawable()
{
    //if element 'this' exists inside drawables, remove it
    //the std::find should always be true and so isn't strictly necessary however optimising this probably isn't needed
    if (drawables.size() > 0 && std::find(drawables.begin(), drawables.end(), this) != drawables.end())
        drawables.erase(std::remove(drawables.begin(), drawables.end(), this), drawables.end());
}
Drawable::Drawable(std::string path, int index) {
    SetTexture(path);
    drawables.push_back(this);
    isSorted = false;
    SetOrder(index);
};
Vector2 Drawable::GetSize() {
    return sprite.GetTexSize();
};

void Drawable::Draw(Rectangle r, Color tint)
{
    sprite.Draw((int)r.x,(int)r.y,(int)r.width,(int)r.height,tint);
}
void Drawable::SetTexture(std::string path) {
    sprite = Sprite(path);
}

bool SortFunc(Drawable* d1, Drawable* d2) 
{ return (d1->GetOrder() < d2->GetOrder()); }




void Drawable::DrawAll(float dt)
{
    //if we are unsorted, sort it by draw order / z-index first
    if (Drawable::IsSorted() == false)
    {
        std::sort(drawables.begin(), drawables.end(), SortFunc);
        isSorted = true;
    }
    for (Drawable* d : drawables)
    {
        if (!d->IsHidden())
        {
            //update animator first, which will change the texture if it needs to
            d->sprite.UpdateAnimator(dt);

            Rectangle r = Render::TranslateToScreenSpace(d->GetPosition());
            if (d->ShadowEnabled())
                d->DrawShadow(r);
            d->Draw(r,d->Tint);
        }
        else
        {
               
        }
    }
}
void Drawable::DrawShadow(Rectangle r)
{
    if (IsShaderReady(ShadowShader))
    {
        r.x += 10;
        r.y += 10;
        BeginShaderMode(ShadowShader);
        Draw(r, Color{ 255,255,255,255 });
        EndShaderMode();
    }
    else
    {
        ShadowShader = LoadShader(0, "assets/shaders/shadow.fs");
    }

}

