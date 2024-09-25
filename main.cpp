
#include "player.h"
#include "gamestate.h"
#include "uielement.h"
#include "UI.h"
#include "raylib.h"
#include "button.h"
#include "render.h"
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "path.h"
#include "updatable.h"
#include "scene.h"
#include <memory>
#include "dictionary.h"
#include "Timer.h"
#include <iostream>

void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}
void Init()
{
    signal(SIGSEGV, handler);
    InitWindow(Render::GetBasisWidth()*2,Render::GetBasisHeight()*2,"scrpg");
    
    GameState::SeedRNG();
    
    Sprite::GenerateNullSprite();

    UI::CreateUI();
    InitPath();

    GameState::currentScene =  std::make_shared<Scene>("assets/scenes/scene_dungeon.png");

    SetTargetFPS(60);

   // GameState::currentScene->LoadScene("assets/scenes/scene_dungeon.png");

}


void Update()
{
    float dt = GetFrameTime();

    Updatable::UpdateAll(dt);
    
    Clickable::UpdateClickables();    
    Draggable::CheckDraggables();

    Updatable::LateUpdateAll(dt);

}

void Draw()
{
    float dt = GetFrameTime();

    BeginDrawing();
    ClearBackground(BLACK);
    
    //Render::Draw(dt);
    Drawable::DrawAll();
    // UI::DrawUI();   
    
    EndDrawing();
}

int main()
{

    Init(); 
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
    CloseWindow();
}
