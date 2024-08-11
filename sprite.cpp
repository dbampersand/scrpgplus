#include "sprite.h"
#include "render.h"
#include <iostream>

std::unordered_map<std::string, Texture2D> Sprite::sprites;


void Sprite::Draw(int x, int y, Color tint)
{
    Vector v = Render::TranslateToScreenSpace((Vector){(float)x,(float)y});
    DrawTextureV(Sprite::AddLoadedSprite(tex),v.ToRLVector2(),tint);
}
bool Sprite::SpriteExists(std::string path)
{
    return (sprites.find(path) != sprites.end());
}
void Sprite::Draw(int x, int y, Color tint, SPRITE_ALIGN spriteAlign)
{
    Texture2D texture = GetTexture();
    if (spriteAlign == SPRITE_ALIGN::LEFT)
        Draw(x,y,tint);
    if (spriteAlign == SPRITE_ALIGN::CENTER)
        Draw(x - texture.width/2.0f, y -= texture.height/2.0f,tint);
    if (spriteAlign == SPRITE_ALIGN::RIGHT)
        Draw(x + texture.width/2.0f, y,tint);
}

Texture2D Sprite::AddLoadedSprite(std::string path) 
{
    if (path == "")
        return sprites[""];

    if (!SpriteExists(path))
    {
        Texture2D t = LoadTexture(path.c_str());
        sprites.insert({path,t});
        return sprites[path];
    }

    if (!FileExists(path.c_str()))
    {
        std::cout << "File not found: " << path << "\n";
        fflush(stdout);
        return sprites[""];
    }

    return sprites[path];
};
Vector Sprite::GetTexSize()
{
    Texture2D t = AddLoadedSprite(tex);
    Vector v = (Vector){(float)t.width,(float)t.height};
    return v;
}
void Sprite::GenerateNullSprite()
{
    Image i = GenImageColor(1,1,MAGENTA);
    Texture2D t = LoadTextureFromImage(i);
    sprites.insert({"",t});
}
