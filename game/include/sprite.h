#pragma once

#include "raylib.h"
#include <string>
#include "loadable.h"
#include <unordered_map>
#include "external/cute_aseprite.h"

#define _IDLE "idle"

class Animation
{
public:
    Texture2D Texture;
    float FrameTime;
    bool loop = false;
};

class Animator
{
    float Timer = 0;
    std::vector<Animation>* CurrentlyPlaying = nullptr;
    int CurrentlyPlayingIndex = 0;
    int GetIndex(int x, int y, int w, int h);

public:

    void AddFrame(std::string fileName, std::string tag, int time, ase_color_t* data, int w, int h);
    void PlayAnimation(std::string tag);
    void UpdateAnimator(float dt);
    std::vector<Animation>* GetIdle();
    virtual void SetSprite(Texture2D* Textu) = 0;

    void UpdateAnimatorSprite();

    std::string GetTexName(std::string tag);
    std::string GetTagFilename(std::string fileName, std::string tag);


    std::string Filename;

};
class Sprite : public Animator
{
    public:
        enum SPRITE_ALIGN {
            LEFT,
            CENTER,
            RIGHT,
        };

        Sprite(std::string Path) {
            TexName = Path;
            //tex = AddLoadedSprite(Path);
        };
        Sprite() {};
        void Draw(int x, int y, int w, int h, Color tint);
        void Draw(int x, int y, int w, int h, Color tint, SPRITE_ALIGN spriteAlign);
        Vector2 GetTexSize();
        
        Texture2D* AddLoadedSprite(std::string path);
        Texture2D* GetTexture() { 
            return tex; 
        };
        static void GenerateNullSprite();
        void SetSprite(Texture2D* Textu) final override;
        void AddSpriteToList(Texture2D tex, std::string name);

        static std::unordered_map<std::string, std::vector<Animation>> LoadedAnimations;
        static std::vector<std::string> LoadedAseFiles;


    private:
        static std::unordered_map<std::string, Texture2D> sprites;

        Texture2D* tex = nullptr;
        std::string TexName = "";
        bool loaded = false;
        //std::string tex;
        
        bool SpriteExists(std::string path);

        static bool IsAse(std::string path);
        static bool IsAseLoaded(std::string path);


};  