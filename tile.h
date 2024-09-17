#pragma once

#include "drawable.h"
#include "draggable.h"
#include "raylib.h"
#include "gameobject.h"
typedef class Slot Slot;

class Tile : public Draggable, public Drawable, Updatable
{
    public:
        enum TileType
        {
            Damage,
            Heal,
            Shield
        };
        char character; 
        float mutiplier;
        Slot* parent = nullptr;
        Color color;
        TileType tileType;

        float x; float y; float w; float h;
        void Draw(Rectangle r) override;

        //Draggable virtuals
        void MoveObject(float x, float y) override;
        Rectangle GetPosition() override;
        Rectangle GetDefaultPosition() override;
        void AddRenderOrder(int amt) override {
            Drawable::AddRenderOrder(amt);
        };
        //NOTE: turn this class to abstract later by =0 on this
        virtual void ApplyEffect(GameObject* target, GameObject* parent, float multiplier) {};

        void ParentTo(Slot* parent);
        void Update(float dt) override {
            if (!parent)
                HideDrawing();
            else
                ShowDrawing();
        };

        Tile(char c) : Drawable(std::string(""),600)
        {
            character = c;
            mutiplier = 1;
        };
        Tile(char c, float mult) : Drawable(std::string(""),600)
        {
            character = c;
            mutiplier = mult;
        };

        Tile() : Drawable(std::string(""),600) {
            mutiplier = 1;
        };   
        ~Tile() {};
        
};

class DamageTile : public Tile
{
    public:
    DamageTile(char c, float mult) : Tile(c, mult)
    {
        tileType = Damage;
    };
    void ApplyEffect(GameObject* target, GameObject* parent, float multiplier) override {
        target->Damage(mutiplier);
    };
};
class HealTile : Tile
{
    HealTile()
    {
        tileType = Heal;
    };

    void ApplyEffect(GameObject* target, GameObject* parent, float multiplier) override {
        parent->Heal(mutiplier);
    };

};
class ShieldTile : Tile
{
    ShieldTile()
    {
        tileType = Shield;
    };

};