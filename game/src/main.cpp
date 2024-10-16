
#include "player.h"
#include "gamestate.h"
#include "uielement.h"
#include "UI.h"
#include "raylib.h"
#include "button.h"
#include "render.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "path.h"
#include "updatable.h"
#include "scene.h"
#include <memory>
#include "dictionary.h"
#include "Timer.h"
#include <chrono>
#include "draggable.h"
#include "particle.h"
#include "colours.h"
#include "board.h"
#include "script.h"

#include <iostream>

void Init()
{
    InitWindow((int)(Render::GetBasisWidth()*4),(int)(Render::GetBasisHeight()*4),"scrpg");
    
    GameState::SeedRNG();
    
    Sprite::GenerateNullSprite();

    UI::CreateUI();
    InitPath();

    GameState::currentScene = std::make_shared<Scene>("assets/scenes/scene_dungeon.png");

    SetTargetFPS(60);

    Dictionary::InitDictionary();
    
   // GameState::currentScene->LoadScene("assets/scenes/scene_dungeon.png");

}

void EndCleanup()
{
    Dictionary::ClearThreads();
}
void Update()
{
    float dt = GetFrameTime();

    Updatable::UpdateAll(dt);

    Particle::UpdateAllParticles(dt);
    Clickable::UpdateClickables();    
    Draggable::CheckDraggables(dt);

    Updatable::LateUpdateAll(dt);
}

void Draw()
{
    float dt = GetFrameTime();

    BeginDrawing();
    ClearBackground(Colours::UIGray);
    
    Drawable::DrawAll(dt);
    
    EndDrawing();
}

int main()
{
    Init(); 
    Script::InitScript();
    Animator::PlayScript("PlaySound(\"test\",0.5)");
    GameState::SetState(GameState::IN_MENU);

    bool shouldExit = false;
    while (!shouldExit)
    {
        Update();
        Draw();

        if (WindowShouldClose())
            shouldExit = true;
        fflush(stdout);
    }
    EndCleanup();
    CloseWindow();

    //note: call to exit() here as otherwise destructors are called in an arbitrary order and can crash just before it exits (although the destructors in this case are safe with a find) 
    exit(0);
}
