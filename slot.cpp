#include "slot.h"
#include "raylib.h"
#include "tile.h"
#include <iostream>

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
        
        //filled = true;
        filled = true;

        //update old parent

        Tile* selectedTile = t;
        Slot* selectedSlot = this;
        Slot* previousSlot = selectedTile->parent;
        Tile* previousTile = &this->tile;

        Tile temp = *previousTile;

        selectedSlot->tile = *selectedTile;
        previousSlot->tile = temp;
        
        selectedSlot->tile.parent = selectedSlot;
        previousSlot->tile.parent = previousSlot;

        Rectangle position = t->GetDefaultPosition();
        Rectangle position2 = this->tile.GetDefaultPosition();

        t->MoveObject(position.x,position.y);
        tile.MoveObject(position2.x,position2.y);

        //std::shared_ptr<Slot> oldSlot = t->parent;

        //std::shared_ptr<Tile> newSlotTile = std::shared_ptr<Tile>(t);
        //std::shared_ptr<Tile> oldSlotTile = std::shared_ptr<Tile>(oldSlot->tile);
        //oldSlot->tile = this->tile;
        //this->tile = newSlotTile;

    }
}