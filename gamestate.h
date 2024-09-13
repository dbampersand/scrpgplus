#pragma once

#include "scene.h"
#include "player.h"
#include <random>

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

        static void SeedRNG();

        static std::default_random_engine rng;

        
    private:
       static State state;  
};