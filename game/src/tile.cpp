#include "tile.h"
#include "slot.h"
#include "raylib.h"
#include "pccontrolled.h"
#include <string>
void Tile::MoveObject(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Tile::Draw(Rectangle r, Color tint)
{
    if (!IsFontReady(CharacterFont) || !IsFontReady(MultiplierFont))
    {
        SetFont(CharacterFontPath, CharacterSize,  MultiplierFontPath, MultiplierSize);
    }
    DrawRectangle((int)r.x,(int)r.y,(int)r.width,(int)r.height,color);

    Rectangle multiplierRect = r;
    multiplierRect.x += CharacterSize / 2.0f;
    multiplierRect.height /= 2.0f;

    Color shadow = Color{ 20,20,20,128 };

    Render::DrawText(std::string(1, character), CharacterFontPath, CharacterSize, Rectangle{ r.x + 1,r.y + 1,r.width,r.height }, shadow, Sprite::SPRITE_ALIGN::CENTER);
    Render::DrawText(std::string(1, character), CharacterFontPath, CharacterSize,r, WHITE, Sprite::SPRITE_ALIGN::CENTER);

    if (mutiplier > 0 && character != ' ')
        Render::DrawText(std::to_string((int)mutiplier), MultiplierFontPath, MultiplierSize, multiplierRect, WHITE, Sprite::SPRITE_ALIGN::LEFT);

    //DrawTextCodepoint(CharacterFont, character,Vector2{r.x+r.width/2.0f - CharacterSize /4.0f,r.y+r.height/2.0f - CharacterSize /2.0f}, CharacterSize,WHITE);
    //DrawTextEx(MultiplierFont, std::to_string((int)mutiplier).c_str(), Vector2{r.x+6,r.y}, MultiplierSize, 1, WHITE);

}
Rectangle Tile::GetPosition()
{
    Vector2 size = { 0,0 };
    if (parent)
        size = Vector2{ parent->w, parent->h };

    return Rectangle{x,y,size.x,size.y};
}

Rectangle Tile::GetDefaultPosition() 
{
    if (parent)
    {
        return Rectangle{(float)parent->x,(float)parent->y,parent->w,parent->h};
    }
    else return GetPosition();
}
void Tile::DragClick() 
{
    for (std::shared_ptr<Slot> topRow : PCControlled::CurrentPlayer->PlayerTiles)
    {
        if (this == topRow->tile.get())
        {
            //current on the top row - move to the first free slot on the bottom row
            for (std::shared_ptr<Slot> bottomRow : PCControlled::CurrentPlayer->TilesPlayed)
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
    for (std::shared_ptr<Slot> bottomRow : PCControlled::CurrentPlayer->TilesPlayed)
    {
        if (this == bottomRow->tile.get())
        {
            //current on the bottom row - move to the first free slot on the top row
            for (std::shared_ptr<Slot> topRow : PCControlled::CurrentPlayer->PlayerTiles)
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

Tile::Tile(char c) : Drawable(std::string(""), 600)
{
    tileType = TileType::NullTile;
    x = 0; y = 0; w = 0; h = 0;
    character = c;
    mutiplier = 1;
    DisableShadow();
    color = Color{ 100,0,100 };
};
Tile::Tile(char c, float mult) : Drawable(std::string(""), 600)
{
    tileType = TileType::NullTile;
    x = 0; y = 0; w = 0; h = 0;
    character = c;
    mutiplier = mult;
    DisableShadow();
    color = Color{ 100,0,100 };
};

Tile::Tile() : Drawable(std::string(""), 600) {
    tileType = TileType::NullTile;
    x = 0; y = 0; w = 0; h = 0;
    mutiplier = 0;
    DisableShadow();
    character = 0;
    color = Color{ 100,0,100 };
};

