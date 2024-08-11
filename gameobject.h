#pragma once

#include "drawable.h"
#include "updatable.h"

class GameObject : public Drawable, public Updatable
{
    public:
        int x; int y;
        GameObject(std::string path) : Drawable(path), Updatable()
        {

        }   
        void Update(float dt);
        Rectangle GetPosition() { 
            Vector size = GetSize();
            return (Rectangle){(float)x,(float)y,(float)size.x,(float)size.y};
        }
};