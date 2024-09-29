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
        //NOTE: turn this class to abstract later by = 0 on this
        virtual void ApplyEffect(GameObject* target, GameObject* parent, float multiplier) {};

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
        Font* GetCharacterFont()
        {
            return &CharacterFont;
        }
        void SetFont(std::string characterFontPath, float characterSize, std::string multiplierFontPath, float multiplierSize)
        {
            CharacterFont = LoadFont(characterFontPath.c_str());
            MultiplierFont = LoadFont(multiplierFontPath.c_str());

        }
        Tile(char c);
        Tile(char c, float mult);
        Tile();
        ~Tile() = default;

private:    
    Font CharacterFont{ 0 };
    Font MultiplierFont{ 0 };

    const std::string CharacterFontPath = "assets/fonts/PlayfairDisplay/PlayfairDisplay-Bold.ttf";
    const std::string MultiplierFontPath = "assets/fonts/PlayfairDisplay/PlayfairDisplay-Regular.ttf";

    inline static float CharacterSize = 12;
    inline static float MultiplierSize = 8;


};

class DamageTile : public Tile
{
    public:
    DamageTile(char c, float mult) : Tile(c, mult)
    {
        tileType = Damage;
        color = Color{ 200,0,60,255 };
    };
    void ApplyEffect(GameObject* target, GameObject* parent, float multiplier) override {
        target->Damage(mutiplier);
    };
};
class HealTile : public Tile
{
public:
    HealTile(char c, float mult) : Tile(c, mult)
    {
        tileType = Heal;
        color = Color{ 93,200,44,255 };
    };

    void ApplyEffect(GameObject* target, GameObject* parent, float multiplier) override {
        parent->Heal(mutiplier);
    };

};
class ShieldTile : public Tile
{
public:
    ShieldTile(char c, float mult) : Tile(c, mult)
    {
        tileType = Shield;
        color = Color{ 235,194,73,255 };
    };

};