#include "gamestate.h" 
#include "UI.h"
#include "player.h"
#include "pccontrolled.h"

int GameState::turnNumber = 0;

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
}
void GameState::TakeTurn()
{
    turnNumber++;
    if (turnNumber >= Player::players.size())
    {
        turnNumber = 0;
    }
}
