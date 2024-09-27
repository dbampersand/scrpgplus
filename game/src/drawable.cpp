#include "drawable.h"
#include "sprite.h"
#include "raylib.h"
#include <string>
#include "render.h"
#include <algorithm>

std::vector<Drawable*> Drawable::drawables;
bool Drawable::isSorted;

void Drawable::SetOrder(int ord) {
    isSorted = false;
    order = ord;
}
int Drawable::GetOrder() {
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
bool Drawable::IsHidden()
{
    return Hidden;
}
Drawable::~Drawable()
{
    //if element 'this' exists inside drawables, remove it
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

void Drawable::Draw(Rectangle r)
{
    sprite.Draw(r.x,r.y,r.width,r.height,WHITE);
}
void Drawable::SetTexture(std::string path) {
    sprite = Sprite(path);
}

bool SortFunc(Drawable* d1, Drawable* d2) 
{ return (d1->GetOrder() < d2->GetOrder()); }

void Drawable::DrawAll()
{
    if (Drawable::IsSorted() == false)
    {
        std::sort(drawables.begin(), drawables.end(), SortFunc);
        isSorted = true;
    }
    for (Drawable* d : drawables)
    {
        if (!d->IsHidden())
        {
            Rectangle r = Render::TranslateToScreenSpace(d->GetPosition());
            d->Draw(r);
        }
        else
        {
            
        }
    }
}

