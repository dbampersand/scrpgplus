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
    //The amount of time for this frame to play for
    float FrameTime;
};

class Animator
{
    float Timer = 0;
    //The current animation playing as a vector of all the frames and time to switch
    std::vector<Animation>* CurrentlyPlaying = nullptr;
    //The current index (the one we're currently on) of the CurrentlyPlaying animation vector 
    int CurrentlyPlayingIndex = 0;

public:
    //Adds a tagged frame to the Animator
    void AddFrame(std::string fileName, std::string tag, int time, ase_color_t* data, int w, int h);
    //Plays an animation given a tag (e.g. "idle", "attack")
    void PlayAnimation(std::string tag);
    //Updates the animator to automatically move to the next frame when the timer has reached the frametime
    void UpdateAnimator(float dt);
    //Gets the Idle animation
    std::vector<Animation>* GetIdle();
    //To be overridden - sets the current sprite to a Texture2D
    virtual void SetSprite(Texture2D* Textu) = 0;

    //Gets the current Sprite that the Animator should be on given the time and calls SetSprite
    void UpdateAnimatorSprite();

    //Returns the full name of a tagged texture name, e.g. assets/enemies/gazer.aseprite/idle 
    //i.e. appends /tagname to the filename
    std::string GetTagFilename(std::string fileName, std::string tag);
    //Filename associated with the aseprite file 
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
        //Draws the sprite where x,y are the top left coordinate
        void Draw(int x, int y, int w, int h, Color tint);
        //Draws the sprite, aligned to a position:
        //SPRITE_ALIGN::LEFT means x,y is the top left coordinate
        //SPRITE_ALIGN::CENTER means x,y is the middle coordinate
        //SPRITE_ALIGN::RIGHT means x,y is the top right coordinate
        void Draw(int x, int y, int w, int h, Color tint, SPRITE_ALIGN spriteAlign);

        //Gets the sprite texture size
        Vector2 GetTexSize();
        
        //Loads a sprite and adds it to either LoadedAnimations (ase file) or sprites (other image formats, e.g. .png)
        Texture2D* AddLoadedSprite(std::string path);
        //Returns the current texture
        Texture2D* GetTexture() { 
            return tex; 
        };
        //Generates a null sprite and assigns it to the name ""
        static void GenerateNullSprite();
        //Sets the current sprite to a Texture2D
        void SetSprite(Texture2D* Textu) final override;
        //Adds the Sprite to the list of sprites so it can be accessed by the path without reloading
        void AddSpriteToList(Texture2D tex, std::string path);

        static std::unordered_map<std::string, std::vector<Animation>> LoadedAnimations;
        static std::vector<std::string> LoadedAseFiles;

    private:
        static std::unordered_map<std::string, Texture2D> sprites;

        Texture2D* tex = nullptr;
        std::string TexName = "";
        bool loaded = false;
        
        //Checks if the sprite exists inside of the list of all loaded sprites
        bool SpriteExists(std::string path);

        //Checks if a file is an Aseprite file
        static bool IsAse(std::string path);
        //Checks if an Aseprite file is loaded
        static bool IsAseLoaded(std::string path);


};  