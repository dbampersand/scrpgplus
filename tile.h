#pragma once

#include "drawable.h"
#include "draggable.h"
#include "raylib.h"

typedef class Slot Slot;
class Tile : Draggable, Drawable, Updatable
{
    public:
        char character;
        float mutiplier;
        Slot* parent = nullptr;
        Color color;

        float x; float y; float w; float h;
        void Draw(Rectangle r) override;

        //Draggable virtuals
        void MoveObject(float x, float y) override;
        Rectangle GetPosition() override;
        Rectangle GetDefaultPosition() override;
        void AddRenderOrder(int amt) override {
            Drawable::AddRenderOrder(amt);
        };


        void ParentTo(Slot* parent);
        void Update(float dt) override {
            if (!parent)
                Drawable::Hidden = true;
            else
                Drawable::Hidden = false;
        };


        Tile(char c) : Drawable(std::string(""),600)
        {
            character = c;
            parent = NULL;
        };
        Tile(char c, float mult) : Drawable(std::string(""),600)
        {
            character = c;
            mutiplier = mult;
            parent = NULL;
        };

        Tile() : Drawable(std::string(""),600) {
            parent = NULL;
        };   
        ~Tile() {};
};

class DamageTile : Tile
{

};
class HealTile : Tile
{

};
class ShieldTile : Tile
{

};