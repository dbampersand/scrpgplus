#include "sprite.h"
#include "render.h"
#include <iostream>
#include <algorithm>
#define CUTE_ASEPRITE_IMPLEMENTATION
#include "external/cute_aseprite.h"

std::unordered_map<std::string, Texture2D> Sprite::sprites;
std::unordered_map<std::string, std::vector<Animation>> Sprite::LoadedAnimations;
std::vector<std::string> Sprite::LoadedAseFiles;

int Animator::GetIndex(int x, int y, int w, int h)
{
    return (x * w) + y;
}

void Animator::PlayAnimation(std::string tag)
{
    for (auto& elem : tag)
    {
        elem = std::tolower(elem);
    }
    if (Sprite::LoadedAnimations.contains(GetTagFilename(Filename,tag)))
    {
        std::vector<Animation>* a = &Sprite::LoadedAnimations.at(GetTagFilename(Filename, tag));
        if (CurrentlyPlaying != a)
        {
            Timer = 0;
            CurrentlyPlaying = a;
            CurrentlyPlayingIndex = 0;
        }
    }
    UpdateAnimatorSprite();

}
void Animator::UpdateAnimatorSprite()
{
    SetSprite(&CurrentlyPlaying->at(CurrentlyPlayingIndex).Texture);
}
std::vector<Animation>* Animator::GetIdle()
{
    if (Sprite::LoadedAnimations.find(GetTagFilename(Filename,_IDLE)) == Sprite::LoadedAnimations.end())
    {
        return nullptr;
    }
    return &Sprite::LoadedAnimations.at(GetTagFilename(Filename, _IDLE));
}
void Animator::UpdateAnimator(float dt)
{
    if (!CurrentlyPlaying)
        return;
    Timer += dt;
    Animation current = CurrentlyPlaying->at(CurrentlyPlayingIndex);
    if (Timer >= current.FrameTime)
    {
         CurrentlyPlayingIndex++;
        if (CurrentlyPlayingIndex >= CurrentlyPlaying->size())
            CurrentlyPlayingIndex = 0;
        CurrentlyPlaying = GetIdle();
        Timer = 0;
        UpdateAnimatorSprite();
    }
}
std::string Animator::GetTexName(std::string tag)
{
    std::string full = Filename + "_" + tag;
    return full;
}
std::string Animator::GetTagFilename(std::string fileName, std::string tag)
{
    
    return fileName + "/" + tag;
}
void Animator::AddFrame(std::string fileName, std::string tag, int time, ase_color_t* data, int w, int h)
{
    for (auto& elem : tag)
    {
        elem = std::tolower(elem);
    }
    for (auto& elem : fileName)
    {
        elem = std::tolower(elem);
    }

    Image i = GenImageColor(w, h, Color{ 0,0,0,0 });

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            Color c = Color(data->r, data->g, data->b, data->a);
            data++;
            ImageDrawPixel(&i, x, y, c);
        }
    }
    Texture2D t = LoadTextureFromImage(i);
    UnloadImage(i);

    if (Sprite::LoadedAnimations.find(GetTagFilename(Filename,tag)) == Sprite::LoadedAnimations.end())
    {
        Sprite::LoadedAnimations.insert({ GetTagFilename(Filename,tag), std::vector<Animation>() });
    }
    Animation a;
    a.Texture = t;
    a.FrameTime = time / 1000.0f;
    Sprite::LoadedAnimations.at(GetTagFilename(Filename,tag)).push_back(a);
}
void Sprite::AddSpriteToList(Texture2D tex, std::string name)
{
    sprites.insert({ name,tex });
}
void Sprite::SetSprite(Texture2D* Textu)
{
    tex = Textu;
}
void Sprite::Draw(int x, int y, int w, int h, Color tint)
{
    Rectangle r = Rectangle{(float)x,(float)y,(float)w,(float)h};
    tex = Sprite::AddLoadedSprite(TexName);
    DrawTexturePro(*tex,Rectangle{0,0,(float)tex->width,(float)tex->height},r,Vector2{0,0},0,tint);
}
bool Sprite::SpriteExists(std::string path)
{
    return (sprites.find(path) != sprites.end());
}
void Sprite::Draw(int x, int y, int w, int h, Color tint, SPRITE_ALIGN spriteAlign)
{
    Texture2D* texture = GetTexture();
    if (spriteAlign == SPRITE_ALIGN::LEFT)
        Draw(x,y,w,h,tint);
    if (spriteAlign == SPRITE_ALIGN::CENTER)
        Draw(x - texture->width/2.0f, y - texture->height/2.0f,w,h,tint);
    if (spriteAlign == SPRITE_ALIGN::RIGHT)
        Draw(x + texture->width/2.0f, y,w,h,tint);
}
bool Sprite::IsAse(std::string path)
{
    return path.ends_with(".ase") || path.ends_with(".aseprite");
}
bool Sprite::IsAseLoaded(std::string path)
{
    return std::find(LoadedAseFiles.begin(), LoadedAseFiles.end(),path) != LoadedAseFiles.end();
}
Texture2D* Sprite::AddLoadedSprite(std::string path) 
{
    if (loaded)
        return tex;
    loaded = true;
    if (path == "")
        return &sprites[""];

    if (!FileExists(path.c_str()))
    {
        std::cout << "File not found: " << path << "\n";
        fflush(stdout);
        return &sprites[""];
    }
    if (IsAse(path) && !IsAseLoaded(path))
    {
        Filename = path;
        ase_t* ase = cute_aseprite_load_from_file(path.c_str(), NULL);
        for (int i = 0; i < ase->tag_count; i++)
        {
            ase_tag_t* tag = &ase->tags[i];
            int from = tag->from_frame;
            int to = tag->to_frame;

            for (int j = from; j < to + 1; j++)
            {
                ase_frame_t* frame = ase->frames + j;
                AddFrame(Filename, tag->name, frame->duration_milliseconds, frame->pixels, ase->w, ase->h);
            }
        }
        LoadedAseFiles.push_back(path);
        cute_aseprite_free(ase);

        PlayAnimation("idle");
    }
    else if (IsAse(path) && IsAseLoaded(path))
    {
        Filename = path;
        PlayAnimation("idle");
    }
    else if (!SpriteExists(path))
    {

        Filename = path;
        
        Texture2D t = LoadTexture(path.c_str());
        sprites.insert({path,t});
        return &sprites[path];
    }


    return &sprites[path];
};
Vector2 Sprite::GetTexSize()
{
    Vector2 v = { 0,0 };
    if (tex)
         v = Vector2{(float)tex->width,(float)tex->height};
    return v;
}
void Sprite::GenerateNullSprite()
{
    Image i = GenImageColor(1,1,Color{0,0,0,0});
    Texture2D t = LoadTextureFromImage(i);
    sprites.insert({"",t});
    UnloadImage(i);
}
