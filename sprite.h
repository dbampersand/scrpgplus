#pragma once

#include "raylib.h"
#include <string>
#include "loadable.h"
#include <unordered_map>
#include "vector.h"

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
        void Draw(int x, int y, Color tint);
        void Draw(int x, int y, Color tint, SPRITE_ALIGN spriteAlign);
        Vector GetTexSize();
        
        Texture2D AddLoadedSprite(std::string path);
        Texture2D GetTexture() { return AddLoadedSprite(tex); };
        static void GenerateNullSprite();

    private:
        static std::unordered_map<std::string, Texture2D> sprites;
        std::string tex;
        bool SpriteExists(std::string path);

};  