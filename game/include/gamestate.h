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
        //Sets the current gamestate
        static void SetState(State state);
        //Returns the current gamestate
        static State GetState() { return state; };
        
        //Starts the game - creates the players and board
        static void StartGame();

        //End the current turn and changes to the other player
        static void TakeTurn();

        //Initialise the random number generator
        static void SeedRNG();
        //Returns a random number between lower and upper in a given type
        template <typename T> static
        T RandRange(T lower, T upper)
        {
            std::uniform_real_distribution<> dist{ lower, upper };
            return (T)dist(rng);
        }

        //returns the RNG engine
        static std::default_random_engine* GetRNG()
        {
            return &rng;
        }

        static std::shared_ptr<Scene> currentScene;
        //Who is currently taking their turn
        static PlayerTurnType player;
        
    private:
       static State state;  
       static std::default_random_engine rng;


};