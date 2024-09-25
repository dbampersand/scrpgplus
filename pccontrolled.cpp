#include "pccontrolled.h"
#include <algorithm>
#include <random>
#include "gamestate.h"
#include "dictionary.h"

PCControlled PCControlled::CurrentPlayer = PCControlled();
int PCControlled::DefaultBagSize = 100;

void PCControlled::Update(float dt)
{
}

void PCControlled::ShuffleBag(std::vector<std::unique_ptr<Tile>>* bag)
{
    std::shuffle(std::begin(*bag), std::end(*bag), GameState::rng);
}
float PCControlled::GetMultiplier(std::string hand)
{
    float totalCharacters = 0;
    for (std::shared_ptr<Slot> s : PCControlled::CurrentPlayer.TilesPlayed)
    {
        if (s->tile->character != ' ')
        {
            totalCharacters++;
        }
    }
    return totalCharacters / 2.0f;
}
std::string PCControlled::GetPlayedHand()
{
    std::string word = "";
    for (std::shared_ptr<Slot> s : PCControlled::CurrentPlayer.TilesPlayed)
    {
        if (s->tile->character != ' ')
            word += s->tile->character;
    }
    return word;
}
void PCControlled::Attack(float multiplier)
{
    for (std::shared_ptr<Slot> s : PCControlled::CurrentPlayer.TilesPlayed)
    {
        s->tile->ApplyEffect(Player::GetEnemy(),this,multiplier);
    }
}
void PCControlled::ClearHand()
{
    auto removeFunc = [](std::shared_ptr<Slot> t){ return t->tile->character != ' ';};
    for (int i = 0; i < TilesPlayed.size(); i++)
    {
        if (TilesPlayed[i]->tile->character != ' ')
        {
            //discardedBag.push_back(std::move(TilesPlayed[i]->tile));
            for (int j = 0; j < PlayerTiles.size(); j++)
            {
                if (PlayerTiles[j]->tile->character == ' ')
                {
                   // std::swap(TilesPlayed[i]->tile, PlayerTiles[j]->tile);
                }
            }
            //tilesPlayed[i]->tile = ;
            //i--;
        }
    }
    //discardedBag.push_back(std::unique_ptr<Tile>(t->tile));

    //TilesPlayed.erase();

}
void PCControlled::PlayHand()
{
    std::string word = GetPlayedHand();
    std::string played = Dictionary::CheckWord(word);
    ClearHand();
    //invalid hand - not a word
    if (played.size() == 0)
    {
        return;
    }
    float multiplier = GetMultiplier(played);
    Attack(multiplier);

}
