#pragma once
#include "drawable.h"
#include "draggable.h"
#include "tile.h"
#include <memory>

typedef class Tile Tile;
class Slot : public Drawable, DragTarget
{ 
    public:
        std::unique_ptr<Tile> tile;
        bool filled = false;

        Rectangle GetPosition() override;
        void Draw(Rectangle r) override;
        int x; int y; 
        static int w; static int h;
        void AddTile(Tile* t);
        Slot(int X, int Y);
        Slot();
        ~Slot() = default;
        void OnDrag(Draggable* d) override;

        void HideChildren();
        void ShowChildren();
        static void SwapSlots(Slot* s1, Slot* s2);
}; 
