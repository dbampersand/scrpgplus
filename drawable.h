#pragma once

#include "sprite.h"
#include "vector.h"
#include <vector>
#include "raylib.h"

class Drawable
{
    public:
    
        void SetOrder(unsigned int ord) { 
            isSorted = false;
            order = ord; 
        }
        unsigned int GetOrder() {return order;}; 
        static bool IsSorted()
        { return isSorted; }

        virtual Rectangle GetPosition() = 0;

        virtual void Draw();

        bool Hidden = false;

        ~Drawable()
        {
            drawables.erase(std::remove(drawables.begin(), drawables.end(), this), drawables.end());
        }
        Drawable(std::string path) {

            drawables.push_back(this);
            isSorted = false;
        };
        
        void SetTexture(std::string path);
        Vector GetSize() { return sprite.GetTexSize();};

        static void DrawAll();
        static std::vector<Drawable*> drawables;
    private:
        Sprite sprite;
        unsigned int order;
        static bool isSorted;


};