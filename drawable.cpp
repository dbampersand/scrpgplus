#include "drawable.h"
#include "sprite.h"
#include "raylib.h"
#include <string>

std::vector<Drawable*> Drawable::drawables;
bool Drawable::isSorted;


void Drawable::Draw()
{
    Rectangle position = GetPosition();
    sprite.Draw(position.x,position.y,WHITE);
}
void Drawable::SetTexture(std::string path) {
    sprite = Sprite(path);
}

bool SortFunc (Drawable* d1, Drawable* d2) 
{ return (d1->GetOrder() < d2->GetOrder()); }

void Drawable::DrawAll()
{
    if (Drawable::IsSorted() == false)
        std::sort(drawables.begin(), drawables.end());
    for (Drawable* d : drawables)
    {
        if (!d->Hidden)
            d->Draw();
    }
}

