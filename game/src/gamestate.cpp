#include "gamestate.h" 
#include "UI.h"
#include "player.h"
#include "pccontrolled.h"
#include "Timer.h"
#include "board.h"
#include <chrono>

std::default_random_engine GameState::rng = std::default_random_engine {};

GameState::State GameState::state;  
std::shared_ptr<Scene> GameState::currentScene;
GameState::PlayerTurnType GameState::player = PC_PLAYER;

void GameState::HideState(State currentState)
{
    if (state == State::IN_GAME)
    {
        if (PCControlled::CurrentPlayer)
            PCControlled::CurrentPlayer->HideDrawing();
        if (Player::players.size() > 0 && Player::players[0])
            Player::players[0]->HideDrawing();
    }


    if (state == State::IN_BOARD)
    {
        Board::board->Hide();

    }

}

void GameState::SetState(State state)
{
    //Hide the current state objects
    HideState(GameState::state);

    //show the new ones
    GameState::state = state;
    UI::SetGroupsActive(state);
     
    if (state == State::IN_GAME)
    {
        if (PCControlled::CurrentPlayer)
            PCControlled::CurrentPlayer->ShowTiles();
        PCControlled::CurrentPlayer->ShowTiles();

    }

    if (state == State::IN_BOARD)
    {
        Board::board->Show();
    }

}
void GameState::StartGame()
{
    Player::AddPlayer(Player::GetRandomEnemy(0));
    PCControlled::CurrentPlayer = nullptr;
    PCControlled::CurrentPlayer = std::make_unique<PCControlled>(""); 
    GameState::SetState(GameState::State::IN_GAME);

}
void GameState::TakeTurn()
{
    UI::EnableEndTurnButton(false);

    //if it's currently the human player's turn and they have just ended their turn
    if (GameState::player == PC_PLAYER)
    { 

        //Change back to the player's turn after a given amount of time
        auto func = []() -> void {
            GameState::player = PC_PLAYER;
            UI::EnableEndTurnButton(true);
        };
        Timer::CreateTimer(func, 0.5f);

        //take the player's turn
        PCControlled::CurrentPlayer->TakeTurn(Player::players[0]);

        //set the AI player to active
        GameState::player = AI_PLAYER;
        Player::players[0]->SetTint(Color{ 255,255,255,255 });

        //take the AI player's turn and then change back to the human's turn after an amount of time
        auto aiTurnFunc = []() -> void {
            Player::players[0]->TakeTurn(PCControlled::CurrentPlayer.get());
            Player::players[0]->SetTint(Player::players[0]->GetNotActiveTint());
            };
        Timer::CreateTimer(aiTurnFunc, 0.25f);
    }
}
void GameState::SeedRNG()
{
    rng.seed((unsigned int)(std::chrono::system_clock::now().time_since_epoch().count()));
}
