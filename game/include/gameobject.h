#pragma once

#include "drawable.h"
#include "updatable.h"
#include "healthbar.h"
#include "tween.h"

class GameObject : public Drawable, public Updatable
{
    public:
        float x; float y;
        GameObject(std::string path);
        void Update(float dt) override;
        void Draw(Rectangle r) override;
        Rectangle GetPosition() override;
        virtual Rectangle GetHealthBarRectangle();

};