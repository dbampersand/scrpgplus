#pragma once

#include "raylib.h"

#include "gamestate.h"
#include "uigroup.h"

#include <unordered_map>
#include <map>
#include <string>

class UI
{
    
    private:

        static std::unordered_map<std::string, UIGroup> uiGroups;
        static std::unordered_map<GameState::State, std::vector<std::string>> gameStateUI;

        static std::vector<UIGroup*> activeGroups;

    public:


        static void RegisterUIToGameState(GameState::State, std::string);

        static void ClearActiveGroups();
        static void AddGroup(UIGroup u);
        static void SetGroupActive(std::string group);
        static void SetGroupInactive(std::string group);
        static UIGroup* GetGroup(std::string name);
       
        enum TextFormatting
        {
            ALIGN_LEFT,
            ALIGN_CENTER,
            ALIGN_RIGHT
        };
        
        static void DrawUI();
        static void UpdateUI(float dt);
        static void CreateMainMenuUI();
        static void CreateUI();
        static void DrawText(Font f, const char* c, int x, int y, int fontSize, Color col, TextFormatting format);
        static void StartGameButton();
        static void SetGroupsActive(GameState::State state);

};

