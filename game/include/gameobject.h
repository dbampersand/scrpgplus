#pragma once

#include "drawable.h"
#include "updatable.h"
#include "healthbar.h"

class GameObject : public Drawable, public Updatable
{
    public:
        //TODO: set this to private and create a factory function
        GameObject(std::string path);

        
        void Update(float dt) override;
        void Draw(Rectangle r, Color tint) override;
        Rectangle GetPosition() override;

        //Returns the position that the Health bar rectangle should use
        virtual Rectangle GetHealthBarRectangle();

        float x; float y;

        
};