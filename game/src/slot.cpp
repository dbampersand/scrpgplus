#include "slot.h"
#include "raylib.h"
#include "tile.h"
#include "pccontrolled.h"


Rectangle Slot::GetPosition()
{
    return Rectangle{(float)x,(float)y,(float)w,(float)h};
}
void Slot::Draw(Rectangle r, Color tint)
{
    if (IsLocked())
    {
        tint.r /= 2;
        tint.g /= 2;
        tint.b /= 2;
    }
    DrawRectangle((int)r.x,(int)r.y,(int)r.width,(int)r.height,tint);
}
void Slot::SwapSlots(Slot* s1, Slot* s2)
{
    std::swap(s1->tile,s2->tile);
    s1->tile->parent = s1;
    s2->tile->parent = s2;

    Rectangle position = s1->tile->GetDefaultPosition();
    Rectangle position2 = s1->tile->GetDefaultPosition();

    s1->tile->MoveObject(position.x,position.y);
    s2->tile->MoveObject(position2.x,position2.y);

}
void Slot::OnDrag(Draggable* dr)
{

    if (((Tile*)dr) != NULL) 
    {
        Tile* t = (Tile*)dr;
        Tile* t2 = this->tile.get();

        SwapSlots(t->parent,this);

        Rectangle position = t->GetDefaultPosition();
        Rectangle position2 = t2->GetDefaultPosition();

        t->MoveObject(position.x,position.y);
        t2->MoveObject(position2.x,position2.y);
    }
}
Slot::Slot(float X, float Y) : Drawable(std::string(""), 200) {
    x = X; y = Y;

    //create blank tile
    tile = std::make_unique<Tile>((' '));
    tile->x = X;
    tile->y = Y;
    tile->Selectable = false;
    tile->color = Color{ 0,0,0,0 };
    tile->parent = (this);

};
Slot::Slot() : Drawable(std::string(""), 200) {
    x = 0; y = 0;

    //create blank tile
    tile = std::make_unique<Tile>((' '));
    tile->x = x;
    tile->y = y;
    tile->Selectable = false;
    tile->color = Color{ 0,0,0,0 };
    tile->parent = (this);
};
std::vector<Drawable*> Slot::GetChildren()
{
    std::vector<Drawable*> children;
    children.push_back(tile.get());

    if (tile)
    {
    }
    return children;
}
void Slot::HorizontalCenterTiles(std::vector<std::shared_ptr<Slot>>* slots, float padding)
{
    if (slots->size() <= 0)
        return;

    std::shared_ptr<Slot> slot = (*slots)[0];

    int startX = (int)(Render::GetBasisWidth() / 2.0f - ((slot->w * slots->size() / 2.0f) + (padding * slots->size() / 2.0f) - padding / 2.0f));

    for (int i = 0; i < slots->size(); i++)
    {
        float x = startX + (slot->w * i) + (padding * i);
        (*slots)[i]->x = x;
        if ((*slots)[i]->tile)
            (*slots)[i]->tile->x = x;
    }
}
void Slot::SetTile(std::unique_ptr<Tile> Tile)
{
    tile = std::move(Tile);
    tile->x = x;
    tile->y = y;
    tile->parent = (this);
}
void Slot::Lock()
{
    DragTarget::SetLocked(true);
    if (tile)
        tile->SetLocked(true);
}
void Slot::Unlock()
{
    DragTarget::SetLocked(false);
    if (tile)
        tile->SetLocked(false);

}

