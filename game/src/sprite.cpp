#include "sprite.h"
#include "render.h"
#include "UI.h"
#include "script.h"


#include <string>
#include <sstream>
#include <tuple>
#include <any>

#include <algorithm>
#define CUTE_ASEPRITE_IMPLEMENTATION
#include "external/cute_aseprite.h"

std::unordered_map<std::string, Texture2D> Sprite::sprites;
std::unordered_map<std::string, std::vector<Animation>> Sprite::LoadedAnimations;
std::vector<std::string> Sprite::LoadedAseFiles;


void Animator::PlayAnimation(std::string tag)
{
    //convert tag to lowercase
    //TODO: could just check at compile time if string is lowercase
    for (auto& elem : tag)
    {
        elem = std::tolower(elem);
    }
    //if we've got the tag, play it
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
std::string Trim(std::string str, const char* delimiter)
{
    str.erase(0, str.find_first_not_of(delimiter));
    str.erase(str.find_last_not_of(delimiter) + 1);
    return str;
}
void Animator::PlayScript(std::string script)
{
    std::stringstream stream = std::stringstream(script);

    std::string functionToken;
    std::string argumentToken;

    char lineDelimiter = ';';
    
    char argumentDelimiter = ',';

    std::string functionName;

    std::vector<std::any> test;
    while (std::getline(stream, functionToken, lineDelimiter)) {
        std::string function = std::string(functionToken);

        std::string functionName = function.substr(0, function.find('('));

        int argumentsStart = function.find('(')+1;
        int argumentsEnd = function.find(')')-1;

        //if we have both ( and ) in the string
        if (argumentsStart >= 0 && argumentsEnd >= 0)
        {
            std::string argumentsStr = function.substr(argumentsStart, argumentsEnd);

            std::stringstream argumentsStream = std::stringstream(argumentsStr);
            while (std::getline(argumentsStream, argumentToken, argumentDelimiter)) {
                std::string trimmed = Trim(argumentToken, "\t\n\r\f\v()");
                if (argumentToken[0] == '\"')
                {
                    std::string quotationsTrimmed = Trim(trimmed, "\"");
                    test.push_back(quotationsTrimmed);
                }
                else
                {
                    test.push_back((float)atof(trimmed.c_str()));
                }
            }
        }
        Script::CallFunction(functionName, test);
    }
}
void Animator::UpdateAnimatorSprite()
{
    SetSprite(&CurrentlyPlaying->at(CurrentlyPlayingIndex).Texture,  Filename);
    //if we have a script attached as user data to the frame
    if (CurrentlyPlaying->at(CurrentlyPlayingIndex).script.size() > 0)
    {
        PlayScript(CurrentlyPlaying->at(CurrentlyPlayingIndex).script);
    }
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
std::string Animator::GetTagFilename(std::string fileName, std::string tag)
{
    return fileName + "/" + tag;
}
void Animator::AddFrame(std::string fileName, std::string tag, int time, ase_color_t* data, int w, int h, const char* udata)
{
    for (auto& elem : tag)
    {
        elem = std::tolower(elem);
    }
    for (auto& elem : fileName)
    {
        elem = std::tolower(elem);
    }

    //Generate new image, and fill it with the image data
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
    //load to GPU and drop the CPU copy
    Texture2D t = LoadTextureFromImage(i);
    UnloadImage(i);

    //if we don't already have the tag, then add it to the list
    if (Sprite::LoadedAnimations.find(GetTagFilename(Filename,tag)) == Sprite::LoadedAnimations.end())
    {
        Sprite::LoadedAnimations.insert({ GetTagFilename(Filename,tag), std::vector<Animation>() });
    }

    Animation a { 0 };
    a.Texture = t;
    //frametime is in milliseconds
    a.FrameTime = time / 1000.0f;
    if (udata)
        a.script = std::string(udata);
    Sprite::LoadedAnimations.at(GetTagFilename(Filename,tag)).push_back(a);
}
void Sprite::AddSpriteToList(Texture2D tex, std::string path)
{
    sprites.insert({ path,tex });
}
void Sprite::SetSprite(Texture2D* Textu, std::string fileName)
{
    tex = Textu;
    TexName = fileName;
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
        Draw((int)(x - texture->width/2.0f), (int)(y - texture->height/2.0f),w,h,tint);
    if (spriteAlign == SPRITE_ALIGN::RIGHT)
        Draw((int)(x + texture->width/2.0f), y,w,h,tint);
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
        UI::ConsolePrint("File not found: " + path + "\n");
        fflush(stdout);
        return &sprites[""];
    }
    //if we are an Aseprite file and the file isn't loaded, we need to load it
    if (IsAse(path) && !IsAseLoaded(path))
    {
        Filename = path;
        ase_t* ase = cute_aseprite_load_from_file(path.c_str(), NULL);
        //for every tag in the file, load the frames they point to individually
        for (int i = 0; i < ase->tag_count; i++)
        {
            ase_tag_t* tag = &ase->tags[i];
            int from = tag->from_frame;
            int to = tag->to_frame;

            for (int j = from; j < to + 1; j++)
            {
                ase_frame_t* frame = ase->frames + j;
                AddFrame(Filename, tag->name, frame->duration_milliseconds, frame->pixels, ase->w, ase->h, frame->cels->udata.text);
            }
        }
        LoadedAseFiles.push_back(path);
        cute_aseprite_free(ase);

        PlayAnimation("idle");
        return tex;
    }
    //if we are an Aseprite file but it's already loaded
    else if (IsAse(path) && IsAseLoaded(path))
    {
        Filename = path;
        PlayAnimation("idle");
        return tex;
    }
    //otherwise we're a normal image format like png and it isn't loaded
    else if (!SpriteExists(path))
    {
        Filename = path;
        
        Texture2D t = LoadTexture(path.c_str());
        sprites.insert({path,t});
        return &sprites[path];
    }

    //it is a normal image format and we've already loaded it
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
