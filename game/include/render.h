#pragma once

#include "raylib.h"
#include "sprite.h"
#include <map>
class Render
{
    public:
        static Camera camera;
        Sprite* GetSprite(std::string path);

        static Rectangle TranslateToScreenSpace(Rectangle r);
        static Vector2 TranslateToScreenSpace(Vector2 v);
               
        static Rectangle TranslateToWorldSpace(Rectangle r);
        static Vector2 TranslateToWorldSpace(Vector2 v);

        static Vector2 GetScreenSizeScale();

        static float GetBasisWidth() { return _BasisWidth;};
        static float GetBasisHeight() { return _BasisHeight;};

        static Vector2 GetScreenCenter();
        static void Draw(float dt);
        static Vector2 GetMousePos();

        static void DrawText(std::string text, std::string fontPath, int size, Rectangle screenSpaceRect, Color color, Sprite::SPRITE_ALIGN align);

        //string->font map so we can lazy load any fonts and store them just by path
        inline static std::map<std::string, std::map<int,Font>> fonts;
    private:
        //static void LoadSprite(std::string path);

        static const int _BasisWidth = 480;
        static const int _BasisHeight = 270;


};
