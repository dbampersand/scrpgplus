#include "sprite.h"
#include "render.h"
#include <iostream>

std::unordered_map<std::string, Texture2D> Sprite::sprites;

void Sprite::Draw(int x, int y, int w, int h, Color tint)
{
    Rectangle r = (Rectangle){(float)x,(float)y,(float)w,(float)h};
    //DrawTextureV(Sprite::AddLoadedSprite(tex),v.ToRLVector2(),tint);
    Texture2D t = Sprite::AddLoadedSprite(tex);
    DrawTexturePro(t,(Rectangle){0,0,(float)t.width,(float)t.height},r,(Vector2){0,0},0,tint);
}
bool Sprite::SpriteExists(std::string path)
{
    return (sprites.find(path) != sprites.end());
}
void Sprite::Draw(int x, int y, int w, int h, Color tint, SPRITE_ALIGN spriteAlign)
{
    Texture2D texture = GetTexture();
    if (spriteAlign == SPRITE_ALIGN::LEFT)
        Draw(x,y,w,h,tint);
    if (spriteAlign == SPRITE_ALIGN::CENTER)
        Draw(x - texture.width/2.0f, y -= texture.height/2.0f,w,h,tint);
    if (spriteAlign == SPRITE_ALIGN::RIGHT)
        Draw(x + texture.width/2.0f, y,w,h,tint);
}

Texture2D Sprite::AddLoadedSprite(std::string path) 
{
    if (path == "")
        return sprites[""];
    if (!SpriteExists(path))
    {
        if (!FileExists(path.c_str()))
        {
            std::cout << "File not found: " << path << "\n";
            fflush(stdout);
            return sprites[""];
        }

        Texture2D t = LoadTexture(path.c_str());
        sprites.insert({path,t});
        return sprites[path];
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
