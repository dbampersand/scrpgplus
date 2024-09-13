#pragma once

#include "sprite.h"
#include "vector.h"
#include <vector>
#include "raylib.h"
    
class Drawable
{
    public:
    
        void SetOrder(int ord) { 
            isSorted = false;
            order = ord; 
        }
            int GetOrder() {
            return order;
        }; 
        static bool IsSorted()
        { return isSorted; }

        virtual Rectangle GetPosition() = 0;
        void AddRenderOrder(int amt) {
            SetOrder(order + amt);
        }

        virtual void Draw(Rectangle r);
        void HideDrawing() { 
            Hidden = true;
            HideChildren();
        }
        void ShowDrawing() {
            Hidden = false;
            ShowChildren();
        }
        bool IsHidden()
        {
            return Hidden;
        }
        virtual void HideChildren() {

        }
        virtual void ShowChildren() {

        }

        ~Drawable()
        {
            drawables.erase(std::remove(drawables.begin(), drawables.end(), this), drawables.end());
        }
        Drawable(std::string path, int index) {
            SetTexture(path);
            drawables.push_back(this);
            isSorted = false;
            SetOrder(index);
        };
        
        void SetTexture(std::string path);
        Vector GetSize() { 
            return sprite.GetTexSize();
        };

        static void DrawAll();
        static std::vector<Drawable*> drawables;
    private:
        Sprite sprite;
        int order = 0;
        static bool isSorted;
        bool Hidden = false;


};