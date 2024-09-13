#pragma once

#include "scene.h"
#include "player.h"

class GameState
{
    public:
        enum State {
            IN_MENU,
            IN_GAME
        };
        static void SetState(State state);
        static State GetState() { return state; };
        static std::unique_ptr<Scene> currentScene;
        static void StartGame();

        static int turnNumber;
        static void TakeTurn();

        
    private:
       static State state;  
};