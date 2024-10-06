#pragma once
#include "drawable.h"
#include "draggable.h"
#include "tile.h"
#include <memory>

typedef class Tile Tile;
class Slot : public Drawable, DragTarget
{ 
private:
    inline static float DefaultWidth = 18;
    inline static float DefaultHeight = 13;

    public:
        std::unique_ptr<Tile> tile = nullptr;
        bool filled = false;

        Rectangle GetPosition() override;
        void Draw(Rectangle r, Color tint) override;
        float x; float y;
        float w = DefaultWidth; float h = DefaultHeight;
        void AddTile(Tile* t);
        Slot(float X, float Y);
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

        static void HorizontalCenterTiles(std::vector<std::shared_ptr<Slot>>* slots, float padding);

        static void SwapSlots(Slot* s1, Slot* s2);

        static float GetDefaultWidth()
        {
            return DefaultWidth;
        }
        static float GetDefaultHeight()
        {
            return DefaultWidth;
        }

}; 
