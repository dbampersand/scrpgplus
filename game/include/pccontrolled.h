#pragma once

#include "player.h"
#include "slot.h"
#include "tile.h"
#include <memory>
#include <unordered_map>
#include <forward_list>

class PCControlled : public Player
{
public:
    inline static std::unique_ptr<PCControlled> CurrentPlayer;
    //PCControlled& operator=(PCControlled&& other) = default;

        PCControlled(std::string path);

        PCControlled() : Player("") {
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
    
        void TakeTurn(Player* other) override;
        void DrawToMax();
        Rectangle GetHealthBarRectangle() override;
};