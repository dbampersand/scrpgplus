#pragma once

#include "sprite.h"
#include "drawable.h"

class Scene : public Drawable
{
    public:
        void DrawScene();
        Scene(std::string path) : Drawable(path,0) {
        }

        Rectangle GetPosition() override;
        //static std::unique_ptr<Scene> currentScene;
};