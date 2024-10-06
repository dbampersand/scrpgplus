#include "UI.h"
#include "button.h"
#include <algorithm>
#include "gamestate.h"
#include "pccontrolled.h"
#include "dictionary.h"
#include "button.h"

#include <iostream>

std::unordered_map<std::string, UIGroup> UI::uiGroups;
std::vector<UIGroup*> UI::activeGroups;
std::unordered_map<GameState::State, std::vector<std::string>> UI::gameStateUI;
std::shared_ptr<Button> UI::_endTurnButton;


void UI::SetGroupsActive(GameState::State state)
{
    for(std::unordered_map<GameState::State, std::vector<std::string>>::iterator it = UI::gameStateUI.begin(); it != UI::gameStateUI.end(); it++)
    {
        std::vector<std::string> names = it->second;
        
        for (std::string name : names)
        {
            UIGroup* g = GetGroup(name);
            if (it->first == state)
            {
                g->Show();
            }
            else
            {
                g->Hide();
            }
        }
    }
}
UIGroup* UI::GetGroup(std::string name)
{
    for(std::unordered_map<std::string, UIGroup>::iterator it = UI::uiGroups.begin(); it != UI::uiGroups.end(); it++)
    {
        if (it->first == name)
            return &it->second;
    }
    return nullptr;
}


void UI::StartGameButton()
{
    GameState::StartGame();
}
void UI::EndTurnButton()
{
    GameState::TakeTurn();
}
void UI::CreateMainMenuUI()
{
    UIGroup u = UIGroup("MainMenu");
    std::shared_ptr<Button> b = std::make_shared<Button>(100,100,80,35,UI::StartGameButton);
    
    b->SetText("Start Game");
    u.AddElement<Button>(b);

    UI::AddGroup(u);
    UI::RegisterUIToGameState(GameState::State::IN_MENU, "MainMenu");
}
void UI::CreateGameUI()
{
    UIGroup u = UIGroup("InGame");
    _endTurnButton = std::make_shared<Button>(Render::GetBasisWidth()/2.0f,Render::GetBasisHeight() - 20,160,25,UI::EndTurnButton);
    
    _endTurnButton->SetText("End turn");
    u.AddElement<Button>(_endTurnButton);

    UI::AddGroup(u);
    UI::RegisterUIToGameState(GameState::State::IN_GAME, "InGame");
}

void UI::CreateUI()
{
    UI::CreateMainMenuUI();
    UI::CreateGameUI();
}
void UI::AddGroup(UIGroup u)
{
    UI::uiGroups.insert({u.name,u});
}
void UI::SetGroupActive(std::string group)
{
    for(const UIGroup* u : UI::activeGroups)
    {
        //already added the group
        if (u->name == group)
            return;
    }
    for(auto& g : UI::uiGroups)
    {
        if (g.second.name == group)
            UI::activeGroups.push_back(&g.second);   
    }
}
void UI::SetGroupInactive(std::string group)
{
    int ind = 0;

    for(const UIGroup* u : activeGroups)
    {
        if (u->name == group)
        {
            activeGroups.erase(activeGroups.begin()+ind);
            break;
        }
        ind++;
    }
}

void UI::ClearActiveGroups()
{
    activeGroups.clear();
}

void UI::RegisterUIToGameState(GameState::State stateToAdd,  std::string name)
{
    bool exists = false;
    for(std::unordered_map<GameState::State, std::vector<std::string>>::iterator it = UI::gameStateUI.begin(); it != UI::gameStateUI.end(); it++)
    {
        GameState::State state = it->first;
        bool shouldAdd = false;

        for (std::string s : it->second)
        {
            if (s == name)
            {
                exists = true;
                shouldAdd = true;
                break;
            }
        }
        if (shouldAdd)
        {
            exists = true;
            it->second.push_back(name);
        }
    }
    if (!exists)
    {
        std::vector<std::string> str;
        str.push_back(name);
        UI::gameStateUI.insert({stateToAdd,str});
    }
}
void UI::EnableEndTurnButton(bool enable)
{
    if (enable)
        _endTurnButton->Enable();
    else
        _endTurnButton->Disable();
}

void UI::ConsolePrint(std::string str)
{
    std::cout << str;
}
