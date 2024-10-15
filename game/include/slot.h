#pragma once

#include "drawable.h"
#include "draggable.h"
#include "tile.h"

#include <memory>

typedef class Tile Tile;
class Slot : public Drawable, DragTarget
{ 
private:

    //Default width/height of a Slot
    inline static float DefaultWidth = 18;
    inline static float DefaultHeight = 13;


    public:
        
        static const int RenderOrder = 200;

        //The tile owned by this slot
        std::unique_ptr<Tile> tile = nullptr;

        float x; 
        float y;
        float w = DefaultWidth; 
        float h = DefaultHeight;

        Slot(float X, float Y);
        Slot();

        //Centers slots and tiles horizontally given the number in the vector
        static void HorizontalCenterTiles(std::vector<std::shared_ptr<Slot>>* slots, float padding);

        //Swaps the Tile in slots
        static void SwapSlots(Slot* s1, Slot* s2);

        static float GetDefaultWidth()
        {
            return DefaultWidth;
        }
        static float GetDefaultHeight()
        {
            return DefaultWidth;
        }


        bool IsHidden() override {
            return Drawable::IsHidden();
        };
        int GetDrawingOrder() override
        {
            return Drawable::GetOrder();
        }

        Rectangle GetPosition() override;
        void Draw(Rectangle r, Color tint) override;

        void OnDrag(Draggable* d) override;

        std::vector<Drawable*> GetChildren() override;

        void SetTile(std::unique_ptr<Tile> tile);

        void Lock();
        void Unlock();



}; 
