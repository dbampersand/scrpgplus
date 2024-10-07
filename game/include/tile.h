#pragma once

#include "drawable.h"
#include "draggable.h"
#include "colours.h"

#include "raylib.h"

typedef class Slot Slot;
typedef class Player Player;

class Tile : public Draggable, public Drawable, Updatable
{
    public:
        enum TileType
        {
            NullTile,
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
        void Draw(Rectangle r, Color tint) override;

        //Draggable virtuals
        void MoveObject(float x, float y) override;
        Rectangle GetPosition() override;
        Rectangle GetDefaultPosition() override;
        void AddRenderOrder(int amt) override {
            Drawable::AddRenderOrder(amt);
        };
        //NOTE: turn this class to abstract later by = 0 on this
        virtual void ApplyEffect(Player* target, Player* parent, float multiplier) {};

        void ParentTo(Slot* parent);
        void Update(float dt) override {
            if (!parent)
            {
                HideDrawing();
            }
            else
            {
                ShowDrawing();
            }
        };

        bool CanBeDragged() override {
            return !Drawable::IsHidden();
        };
        void DragClick() override;

        int GetDrawingOrder() override
        {
            return Drawable::GetOrder();
        }


        Tile(char c);
        Tile(char c, float mult);
        Tile();
        ~Tile() = default;

private:    

    const std::string CharacterFontPath = "assets/fonts/PlayfairDisplay/PlayfairDisplay-Bold.ttf";
    const std::string MultiplierFontPath = "assets/fonts/PlayfairDisplay/PlayfairDisplay-Regular.ttf";

    inline static float CharacterSize = 12;
    inline static float MultiplierSize = 8;


};

class DamageTile : public Tile
{
    public:
        DamageTile(char c, float mult);
        void ApplyEffect(Player* target, Player* parent, float multiplier);
};
class HealTile : public Tile
{
public:
    HealTile(char c, float mult);

    void ApplyEffect(Player* target, Player* parent, float multiplier);

};
class ShieldTile : public Tile
{
public:
    ShieldTile(char c, float mult);
    void ApplyEffect(Player* target, Player* parent, float multiplier);
};