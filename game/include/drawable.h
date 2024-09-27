#pragma once

#include "sprite.h"
#include <vector>
#include "raylib.h"
    
class Drawable
{
    public:
    
        void SetOrder(int ord);
        int GetOrder();

        static bool IsSorted();

        virtual Rectangle GetPosition() = 0;
        void AddRenderOrder(int amt);

        virtual void Draw(Rectangle r);
        void HideDrawing();
        void ShowDrawing();
        bool IsHidden();
        virtual void HideChildren() {

        }
        virtual void ShowChildren() {

        }

        ~Drawable();
        Drawable(std::string path, int index);
        
        void SetTexture(std::string path);
        Vector2 GetSize();
        static void DrawAll();
        static std::vector<Drawable*> drawables;
    private:
        Sprite sprite;
        int order = 0;
        static bool isSorted;
        bool Hidden = false;


};