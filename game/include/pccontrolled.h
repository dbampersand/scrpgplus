#pragma once

#include "player.h"
#include "slot.h"
#include "tile.h"

#include <memory>

//Class for the human behind the computer
class PCControlled : public Player
{
public:
        inline static std::unique_ptr<PCControlled> CurrentPlayer;

        PCControlled(std::string path);

        PCControlled() : Player("") {
        };

        //The first row of tiles - these are the the tiles that aren't currently being played
        std::vector<std::shared_ptr<Slot>> PlayerTiles;
        //The second row of tiles - these are the tiles that are currently being played as a word
        std::vector<std::shared_ptr<Slot>> TilesPlayed;

        //Bag of tiles which are to be drawn from immediately
        std::vector<std::unique_ptr<Tile>> bag;
        //Discarded tiles - when this is full it will be shuffled back into bag
        std::vector<std::unique_ptr<Tile>> discardedBag; 

        //If we have beaten the current opponent, move to the Board screen
        void Win();
        //We have been defeated by the opponent, move to end screen
        void Lose();

        //Hide the tile UI
        void HideTiles();
        //Show the tile UI
        void ShowTiles();

        //Gets the multiplier for a hand - this is to be used as a multiplier for the base value of your hand and is based on the number of characters in the word
        float GetMultiplier(std::string hand);
        
        //Returns the tiles in TilesPlayed as a string
        std::string GetPlayedHand();

        //Attack the opponent with your currently played hand
        void Attack(float multiplier);

        void TakeTurn(Player* other) override;
        void Update(float dt) override;

private:

    //Play a hand, attacking if it TilesPlayed represents a valid word
    void PlayHand();
    //Move any tiles from TilesPlayed to DiscardedBag and then draw a fresh hand to PlayerTiles
    void ClearHand();


    //Swaps and shuffles the discarded bag and bag so that bag is full of the discarded tiles, now ready to be drawn again
    void FillDrawBag();
    //Draws and removes a Tile from the bag
    std::unique_ptr<Tile> DrawTile();
    //Adds a tile to the bag a given number of times with a character and a multiplier. 
    //ChanceOfDamage, ChanceOfHeal and ChanceOfShield are the probability it will be a damage tile, healing tile of shielding tile respectively, and should be between 0-1
    void AddTilesToBag(std::vector<std::unique_ptr<Tile>>* bag, int numToAdd, char character, float multiplier, float chanceOfDamage, float chanceOfHeal, float chanceOfShield);
    //Shuffles the bag, randomising its contents
    void ShuffleBag(std::vector<std::unique_ptr<Tile>>* bag);
    //Initialises the bag to default contents
    void InitBag();
    //Draws the required number of Tiles to PlayerTiles; e.g. if you still have 8 tiles left over and 12 slots, it will draw 4 new tiles 
    void DrawToMax();


    Rectangle GetHealthBarRectangle() override;

    //Number of slots to be created
    const static int  _MaxTiles = 12;


};