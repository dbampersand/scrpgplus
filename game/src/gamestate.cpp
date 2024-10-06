#include "gamestate.h" 
#include "UI.h"
#include "player.h"
#include "pccontrolled.h"
#include "Timer.h"

#include <chrono>

std::default_random_engine GameState::rng = std::default_random_engine {};

GameState::State GameState::state;  
std::shared_ptr<Scene> GameState::currentScene;
GameState::PlayerTurnType GameState::player = PC_PLAYER;

void GameState::SetState(State state)
{
    GameState::state = state;
    UI::SetGroupsActive(state);
}
void GameState::StartGame()
{
    GameState::SetState(GameState::State::IN_GAME);
    Player::AddPlayer(Player::GetRandomEnemy(0));
    PCControlled::CurrentPlayer = nullptr;
    PCControlled::CurrentPlayer = std::make_unique<PCControlled>(""); 

    PCControlled::CurrentPlayer->ShowTiles();
}
void GameState::TakeTurn()
{
    UI::EnableEndTurnButton(false);

    if (GameState::player == PC_PLAYER)
    { 
        auto func = []() -> void {
            GameState::player = PC_PLAYER;
            UI::EnableEndTurnButton(true);
        };
        
        Timer::CreateTimer(func, 0.5f);
        GameState::player = AI_PLAYER;
        PCControlled::CurrentPlayer->TakeTurn(Player::players[0]);
        Player::players[0]->SetTint(Player::players[0]->GetNotActiveTint());
        Player::players[0]->SetTint(Color{ 255,255,255,255 });


        auto aiTurnFunc = []() -> void {
            GameState::player = PC_PLAYER;
            Player::players[0]->TakeTurn(PCControlled::CurrentPlayer.get());
            Player::players[0]->SetTint(Player::players[0]->GetNotActiveTint());
            };
        Timer::CreateTimer(aiTurnFunc, 0.25f);
    }
}
void GameState::SeedRNG()
{
    rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
}
