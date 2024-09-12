#include "tile.h"
#include "slot.h"
#include "raylib.h"

void Tile::MoveObject(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Tile::Draw(Rectangle r)
{
    int charSize = 12;
    DrawRectangle(r.x,r.y,r.width,r.height,color);
    DrawTextCodepoint(GetFontDefault(), character,(Vector2){r.x+r.width/2.0f - charSize/4.0f,r.y+r.height/2.0f - charSize/2.0f},charSize,WHITE);
}
Rectangle Tile::GetPosition()
{
    return (Rectangle){x,y,(float)Slot::w,(float)Slot::h};
}

Rectangle Tile::GetDefaultPosition() 
{
    if (parent)
    {
        return (Rectangle){(float)parent->x,(float)parent->y,(float)Slot::w,(float)Slot::h};
    }
    else return GetPosition();
}