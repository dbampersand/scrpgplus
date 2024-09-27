#include "tile.h"
#include "slot.h"
#include "raylib.h"
#include "pccontrolled.h"
void Tile::MoveObject(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Tile::Draw(Rectangle r)
{
    int charSize = 12;
    DrawRectangle(r.x,r.y,r.width,r.height,color);
    DrawTextCodepoint(GetFontDefault(), character,Vector2{r.x+r.width/2.0f - charSize/4.0f,r.y+r.height/2.0f - charSize/2.0f},charSize,WHITE);
}
Rectangle Tile::GetPosition()
{
    return Rectangle{x,y,(float)Slot::w,(float)Slot::h};
}

Rectangle Tile::GetDefaultPosition() 
{
    if (parent)
    {
        return Rectangle{(float)parent->x,(float)parent->y,(float)Slot::w,(float)Slot::h};
    }
    else return GetPosition();
}
void Tile::DragClick() 
{
    for (std::shared_ptr<Slot> topRow : PCControlled::CurrentPlayer.PlayerTiles)
    {
        if (this == topRow->tile.get())
        {
            //current on the top row - move to the first free slot on the bottom row
            for (std::shared_ptr<Slot> bottomRow : PCControlled::CurrentPlayer.TilesPlayed)
            {
                if (bottomRow->tile && bottomRow->tile->character == ' ')
                {
                    Slot::SwapSlots(bottomRow.get(),this->parent);
                    return;
                }
            }
        }
    }
    //check bottom row -> top row
    for (std::shared_ptr<Slot> bottomRow : PCControlled::CurrentPlayer.TilesPlayed)
    {
        if (this == bottomRow->tile.get())
        {
            //current on the bottom row - move to the first free slot on the top row
            for (std::shared_ptr<Slot> topRow : PCControlled::CurrentPlayer.PlayerTiles)
            {
                if (topRow->tile && topRow->tile->character == ' ')
                {
                    Slot::SwapSlots(topRow.get(),this->parent);
                    return;
                }
            }
        }
    }


};
