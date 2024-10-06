#pragma once

#include "raylib.h"
#include "sprite.h"
#include <map>
class Render
{
    public:
        static Camera camera;

        //Translates world space to screen space given a Rectangle (position and size)
        static Rectangle TranslateToScreenSpace(Rectangle r);
        //Translates world space to screen space given a Vector2 (position)
        static Vector2 TranslateToScreenSpace(Vector2 v);

        //Translates screen space to world space given a Rectangle (position and size)
        static Rectangle TranslateToWorldSpace(Rectangle r);
        //Translates screen space to world space given a Vector2 (position)
        static Vector2 TranslateToWorldSpace(Vector2 v);

        //Returns the screen size scale - the current screen size divided by the base screen size
        static Vector2 GetScreenSizeScale();

        //Returns the basis width - the default 'scene' size by which everything is placed
        static float GetBasisWidth() { return _BasisWidth;};
        //Returns the basis height - the default 'scene' size by which everything is placed
        static float GetBasisHeight() { return _BasisHeight;};

        //Returns the screen center in world space
        static Vector2 GetScreenCenter();

        //Returns the mouse position in world space
        static Vector2 GetMousePos();

        //Draws text in screen space
        static void DrawText(std::string text, std::string fontPath, int size, Rectangle screenSpaceRect, Color color, Sprite::SPRITE_ALIGN align);

    private:
        //the default 'scene' size by which everything is placed
        static const int _BasisWidth = 480;
        static const int _BasisHeight = 270;

        //string->font map so we can lazy load any fonts and store them just by path
        //the second value is a map of font size to font so we just need to store a given font in a single size once
        inline static std::map<std::string, std::map<int, Font>> fonts;


};
