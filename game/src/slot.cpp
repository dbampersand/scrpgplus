#include "slot.h"
#include "raylib.h"
#include "tile.h"
#include "pccontrolled.h"

int Slot::w = 18; 
int Slot::h = 13;

Rectangle Slot::GetPosition()
{
    return Rectangle{(float)x,(float)y,(float)w,(float)h};
}
void Slot::Draw(Rectangle r)
{
    DrawRectangle(r.x,r.y,r.width,r.height,WHITE);
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

    //if (filled)
    {
      //  Rectangle position = dr->GetDefaultPosition();
        //dr->MoveObject(position.x,position.y);
    }


    if (((Tile*)dr) != NULL) 
    {
        Tile* t = (Tile*)dr;
        Tile* t2 = this->tile.get();

        /*Slot* previousSlot = t->parent;
        Slot* currentSlot = this;

        //swap and update parent
        std::swap(t->parent->tile,this->tile);

        t2->parent = previousSlot;
        t->parent = currentSlot;*/

        SwapSlots(t->parent,this);


        filled = true;

        Rectangle position = t->GetDefaultPosition();
        Rectangle position2 = t2->GetDefaultPosition();

        t->MoveObject(position.x,position.y);
        t2->MoveObject(position2.x,position2.y);
    }
}
Slot::Slot(int X, int Y) : Drawable(std::string(""), 200) {
    x = X; y = Y;
    tile = NULL;
};
Slot::Slot() : Drawable(std::string(""), 200) {

};
void Slot::HideChildren() 
{
    tile->HideDrawing();
}
void Slot::ShowChildren() 
{
    tile->ShowDrawing();
}
