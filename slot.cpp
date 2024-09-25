#include "slot.h"
#include "raylib.h"
#include "tile.h"
#include "pccontrolled.h"

int Slot::w = 18; 
int Slot::h = 13;

Rectangle Slot::GetPosition()
{
    return (Rectangle){(float)x,(float)y,(float)w,(float)h};
}
void Slot::Draw(Rectangle r)
{
    DrawRectangle(r.x,r.y,r.width,r.height,WHITE);
}
void SwapSlots(Slot* s1, Slot* s2)
{
    
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

        Slot* previousSlot = t->parent;
        Slot* currentSlot = this;

        //swap and update parent
        std::swap(t->parent->tile,this->tile);

        t2->parent = previousSlot;
        t->parent = currentSlot;


        filled = true;

        Rectangle position = t->GetDefaultPosition();
        Rectangle position2 = t2->GetDefaultPosition();

        t->MoveObject(position.x,position.y);
        t2->MoveObject(position2.x,position2.y);
    }
}