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
        bool success = false;
        std::vector<BoardWord> words = Board::board->CheckBoardWords(&success);
        if (success)
        {
            for (BoardWord b : words)
            {
                PCControlled::CurrentPlayer->AddToMultiplier(Tile::TileType::Damage, b.valueDamage);
                PCControlled::CurrentPlayer->AddToMultiplier(Tile::TileType::Heal, b.valueHeal);
                PCControlled::CurrentPlayer->AddToMultiplier(Tile::TileType::Shield, b.valueShield);
            }
        }
        if (!success)
        {
            Board::board->CleanBadPlayedBoard();
        }
        for (BoardWord word : words)
            UI::ConsolePrint(word.word);

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
        Player::players.clear();

        Player::players.push_back(Player::GetRandomEnemy(0));

        if (PCControlled::CurrentPlayer)
            PCControlled::CurrentPlayer->ShowDrawing();
        PCControlled::CurrentPlayer->ShowTiles();

    }

    if (state == State::IN_BOARD)
    {
        Board::board->DrawTiles(PCControlled::CurrentPlayer.get());
        Board::board->Show();
    }

}
void GameState::StartGame()
{
    //Player::AddPlayer(Player::GetRandomEnemy(0));
    PCControlled::CurrentPlayer = nullptr;
    PCControlled::CurrentPlayer = std::make_unique<PCControlled>(""); 
    GameState::SetState(GameState::State::IN_GAME);

}
void GameState::TakeBoardTurn()
{
    GameState::SetState(GameState::IN_GAME);

    for (int x = 0; x < _BOARD_TILE_COUNT_X; x++)
    {
        for (int y = 0; y < _BOARD_TILE_COUNT_Y; y++)
        {
            if (Board::board->slots[x][y].tile && Board::board->slots[x][y].tile->character != ' ')
            {
                Board::board->slots[x][y].Lock();
                Board::board->slots[x][y].tile->Lock();
            }

        }
    }
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

        if (Player::players[0]->GetHP() > 0)
        {
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
}
void GameState::SeedRNG()
{
    rng.seed((unsigned int)(std::chrono::system_clock::now().time_since_epoch().count()));
}
