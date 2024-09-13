#include "gamestate.h" 
#include "UI.h"
#include "player.h"
#include "pccontrolled.h"

int GameState::turnNumber = 0;
std::default_random_engine GameState::rng = std::default_random_engine {};

GameState::State GameState::state;  
std::unique_ptr<Scene> GameState::currentScene;

void GameState::SetState(State state)
{
    GameState::state = state;
    UI::SetGroupsActive(state);
}
void GameState::StartGame()
{
    GameState::SetState(GameState::State::IN_GAME);
    Player::AddPlayer(Player::GetRandomEnemy(0));
    PCControlled::CurrentPlayer = PCControlled("");

    PCControlled::CurrentPlayer.ShowTiles();
}
void GameState::TakeTurn()
{
    turnNumber++;
    if (turnNumber >= Player::players.size())
    {
        turnNumber = 0;
    }
}
void GameState::SeedRNG()
{
    rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
}
