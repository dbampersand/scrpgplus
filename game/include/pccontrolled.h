#pragma once

#include "player.h"
#include "slot.h"
#include "tile.h"
#include <memory>
#include <unordered_map>
#include <forward_list>

class PCControlled : public  Player
{
    public:
        static PCControlled CurrentPlayer;
        PCControlled& operator=(PCControlled&& other) = default;
        ~PCControlled() = default;
        PCControlled() : Player(""){
        };

        void Update(float dt) override;

        static int DefaultBagSize;

        std::vector<std::shared_ptr<Slot>> PlayerTiles;
        std::vector<std::shared_ptr<Slot>> TilesPlayed;

        std::vector<std::unique_ptr<Tile>> bag;
        std::vector<std::unique_ptr<Tile>> discardedBag; 

        const static int  _MaxTiles = 9;
        void PlayHand();
        void ClearHand();

        float GetMultiplier(std::string hand);
        std::string GetPlayedHand();
        void Attack(float multiplier);
        void HideTiles();
        void ShowTiles();
        void FillDrawBag();
        std::unique_ptr<Tile> DrawTile();
        void AddTilesToBag(std::vector<std::unique_ptr<Tile>>* bag, int numToAdd, char character, float multiplier);

        void ShuffleBag(std::vector<std::unique_ptr<Tile>>* bag);
        void InitBag();
        PCControlled(std::string path);
    
        void TakeTurn(Player* other) override;
        void DrawToMax();

};