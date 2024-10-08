#pragma once

#include "drawable.h"

class Scene : public Drawable
{
    public:
        void DrawScene();
        Scene(std::string path) : Drawable(path,0) {
            DisableShadow();
        }

        Rectangle GetPosition() override;
};