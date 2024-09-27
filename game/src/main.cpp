
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
#include <iostream>
#include <chrono>

/*void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}*/
void Init()
{
    //signal(SIGSEGV, handler);
    InitWindow(Render::GetBasisWidth()*2,Render::GetBasisHeight()*2,"scrpg");
    
    GameState::SeedRNG();
    
    Sprite::GenerateNullSprite();

    UI::CreateUI();
    InitPath();

    GameState::currentScene =  std::make_shared<Scene>("assets/scenes/scene_dungeon.png");

    SetTargetFPS(60);

    Dictionary::LoadDict(Dictionary::WordListPath);


    /*Dictionary::LoadDict(Dictionary::WordListPath);
    std::cout << (Trie::TestWord("test") ? "true" : "false") << "\n\n";
    std::cout << (Trie::TestWord("t*ea*i*e") ? "true" : "false") << "\n\n";

    std::cout << (Trie::TestWord("me") ? "true" : "false") << "\n\n";
    std::cout << (Trie::TestWord("likegdsgsdg") ? "true" : "false") << "\n\n";
    std::cout << (Trie::TestWord("appledsgsdgsd") ? "true" : "false") << "\n\n";
    */

   // GameState::currentScene->LoadScene("assets/scenes/scene_dungeon.png");

}


void Update()
{

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
        //(Trie::TestWord("t*ea*i*e") ? "true" : "false");
        (Trie::CheckWord("one*ro**o**st") > 0 ? "true" : "false");

    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";

    float dt = GetFrameTime();

    Updatable::UpdateAll(dt);
    
    Clickable::UpdateClickables();    
    Draggable::CheckDraggables(dt);

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
