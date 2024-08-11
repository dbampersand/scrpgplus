#include "gamestate.h" 
#include "UI.h"

GameState::State GameState::state;  
std::unique_ptr<Scene> GameState::currentScene;

void GameState::SetState(State state)
{
    GameState::state = state;
    UI::SetGroupsActive(state);
}
