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
        enum PlayerTurnType {
            PC_PLAYER,
            AI_PLAYER
        };
        static void SetState(State state);
        static State GetState() { return state; };
        static std::shared_ptr<Scene> currentScene;
        static void StartGame();

        static PlayerTurnType player;
        static void TakeTurn();

        static void SeedRNG();
        template <typename T> static
        T RandRange(T lower, T upper)
        {
            std::uniform_real_distribution<> dist{ lower, upper };
            return (T)dist(rng);
        }

        static std::default_random_engine rng;

        static int CurrentTurn;

        
    private:
       static State state;  
};