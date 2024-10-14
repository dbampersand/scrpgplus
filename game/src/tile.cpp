#include "tile.h"
#include "slot.h"
#include "raylib.h"
#include "pccontrolled.h"
#include <string>
#include "player.h"
void Tile::MoveObject(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Tile::Draw(Rectangle r, Color tint)
{
    DrawRectangle((int)r.x,(int)r.y,(int)r.width,(int)r.height,color);

    //This is the little number at the top left which indicates the tile's power (multiplier)
    Rectangle multiplierRect = r;
    multiplierRect.x += CharacterSize / 2.0f;
    multiplierRect.height /= 2.0f;

    Color shadow = Color{ 20,20,20,128 };

    //Draw 'drop shadow' highlight first, then draw white on top
    Render::DrawText(std::string(1, character), CharacterFontPath, (int)CharacterSize, Rectangle{ r.x + 1,r.y + 1,r.width,r.height }, shadow, Sprite::SPRITE_ALIGN::CENTER);
    Render::DrawText(std::string(1, character), CharacterFontPath, (int)CharacterSize,r, WHITE, Sprite::SPRITE_ALIGN::CENTER);

    if (mutiplier > 0 && character != ' ')
        Render::DrawText(std::to_string((int)mutiplier), MultiplierFontPath, (int)MultiplierSize, multiplierRect, WHITE, Sprite::SPRITE_ALIGN::LEFT);

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
    //We've just clicked on a Tile - we need to move the Tile either from played tiles to reserve tiles or vice versa
    //check top row -> bottom row
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
    character = ' ';
    color = Color{ 100,0,100 };
};

/* Tile types */

//Damage tile:
DamageTile::DamageTile(char c, float mult) : Tile(c, mult)
{
    tileType = Damage;
    color = Colours::Damage;
};
void DamageTile::ApplyEffect(Player* target, Player* parent, float multiplier) {
    target->Damage(mutiplier);
};

//Heal tile:
HealTile::HealTile(char c, float mult) : Tile(c, mult)
{
    tileType = Heal;
    color = Colours::Heal;
};
void HealTile::ApplyEffect(Player* target, Player* parent, float multiplier) {
    parent->Heal(mutiplier);
};


//Shield tile::
ShieldTile::ShieldTile(char c, float mult) : Tile(c, mult)
{
    tileType = Shield;
    color = Colours::Shield;
};
void ShieldTile::ApplyEffect(Player* target, Player* parent, float multiplier) {
    parent->AddShield((int)mutiplier);
};
