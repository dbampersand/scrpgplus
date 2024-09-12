#pragma once

#include "drawable.h"
#include "updatable.h"

class GameObject : public Drawable, public Updatable
{
    public:
        float x; float y;
        GameObject(std::string path) : Drawable(path, 100), Updatable()
        {
            x = 0; y = 0;
        }   
        void Update(float dt);
        Rectangle GetPosition() { 
            Vector size = GetSize();
            return (Rectangle){(float)x-size.x/2.0f,(float)y-size.y/2.0f,(float)size.x,(float)size.y};
        }
};