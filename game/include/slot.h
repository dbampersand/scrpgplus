#pragma once
#include "drawable.h"
#include "draggable.h"
#include "tile.h"
#include <memory>

typedef class Tile Tile;
class Slot : public Drawable, DragTarget
{ 
    public:
        std::unique_ptr<Tile> tile = nullptr;
        bool filled = false;

        Rectangle GetPosition() override;
        void Draw(Rectangle r, Color tint) override;
        int x; int y; 
        static int w; static int h;
        void AddTile(Tile* t);
        Slot(int X, int Y);
        Slot();
        ~Slot() = default;
        void OnDrag(Draggable* d) override;
        bool IsHidden() override {
            return Drawable::IsHidden();
        };
        int GetDrawingOrder() override
        {
            return Drawable::GetOrder();
        }

        void HideChildren();
        void ShowChildren();

        static void HorizontalCenterTiles(std::vector<std::shared_ptr<Slot>>* slots, int padding);

        static void SwapSlots(Slot* s1, Slot* s2);
}; 
