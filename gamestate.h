#pragma once

#include "scene.h"

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
        
    private:
       static State state;  
};