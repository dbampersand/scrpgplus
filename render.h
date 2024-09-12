#pragma once

#include "raylib.h"
#include "sprite.h"
#include "vector.h"

class Render
{
    public:
        static Camera camera;
        Sprite* GetSprite(std::string path);

        static Rectangle TranslateToScreenSpace(Rectangle r);
        static Vector TranslateToScreenSpace(Vector v);
               
        static Vector GetScreenSizeScale();

        static float GetBasisWidth() { return _BasisWidth;};
        static float GetBasisHeight() { return _BasisHeight;};

        static Vector GetScreenCenter();
        static void Draw(float dt);
        static Vector2 GetMousePos();
    private:
        //static void LoadSprite(std::string path);

        static const int _BasisWidth = 480;
        static const int _BasisHeight = 270;


};
