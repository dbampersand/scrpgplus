#pragma once

#include "sprite.h"
#include "drawable.h"

class Scene : public Drawable
{
    public:
        void DrawScene();
        void Draw() override;
        Scene(std::string path) : Drawable(path) {
            LoadScene(path);
        }
        void LoadScene(std::string background);

        Rectangle GetPosition() override;
        //static std::unique_ptr<Scene> currentScene;
};