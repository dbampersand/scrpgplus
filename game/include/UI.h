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
        static std::shared_ptr<Button> _endTurnButton;

    public:

        enum TextFormatting
        {
            ALIGN_LEFT,
            ALIGN_CENTER,
            ALIGN_RIGHT
        };


        //Registers a UIGroup name to a given gamestate, to be automatically shown when the gamestate is changed to
        static void RegisterUIToGameState(GameState::State, std::string);

        //Clears all currently active groups
        static void ClearActiveGroups();
        //Adds a UIGroup to uiGroups so we can later get it by name
        static void AddGroup(UIGroup u);
        //Sets the group active so that it will be shown
        static void SetGroupActive(std::string group);
        //Sets the group inactive so that it will be hidden
        static void SetGroupInactive(std::string group);
        //Gets the group by name
        static UIGroup* GetGroup(std::string name);

        //Initialisation function, creates the UI
        static void CreateUI();

        //The event function for when the start game button is clicked
        static void StartGameButton();
        //The event function for when the end turn button is clicked
        static void EndTurnButton();

        //Enables/disables the end turn button
        static void EnableEndTurnButton(bool enable);

        //Sets a group active based on the gamestate
        static void SetGroupsActive(GameState::State state);

private:

    //Initialisation function, creates the main menu UI
    static void CreateMainMenuUI();
    //Initialisation function, creates the game  UI
    static void CreateGameUI();


};

