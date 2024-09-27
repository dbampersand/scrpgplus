#pragma once

#include "raylib.h"
#include <string>
#include "loadable.h"
#include <unordered_map>

class Sprite
{
    public:
        enum SPRITE_ALIGN {
            LEFT,
            CENTER,
            RIGHT,
        };

        Sprite(std::string Path) {
            tex = Path;
        };
        Sprite() {};
        void Draw(int x, int y, int w, int h, Color tint);
        void Draw(int x, int y, int w, int h, Color tint, SPRITE_ALIGN spriteAlign);
        Vector2 GetTexSize();
        
        Texture2D AddLoadedSprite(std::string path);
        Texture2D GetTexture() { return AddLoadedSprite(tex); };
        static void GenerateNullSprite();

    private:
        static std::unordered_map<std::string, Texture2D> sprites;
        std::string tex;
        bool SpriteExists(std::string path);

};  