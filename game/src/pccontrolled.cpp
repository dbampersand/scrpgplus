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
void PCControlled::DrawToMax()
{
    for (std::shared_ptr<Slot> slot : PlayerTiles)
    {
        if (slot->tile == nullptr || slot->tile->character == ' ')
        {
            slot->tile = std::move(DrawTile());
            slot->tile->x = slot->x;
            slot->tile->y = slot->y;
            slot->tile->color = Color{255,0,0,255};
            slot->tile->parent = slot.get();
            slot->filled = true;
            slot->ShowDrawing();

        }
    }
}
void PCControlled::ClearHand()
{
    auto removeFunc = [](std::shared_ptr<Slot> t){ return t->tile->character != ' ';};
    for (int i = 0; i < TilesPlayed.size(); i++)
    {
        if (TilesPlayed[i]->tile->character != ' ')
        {
            std::unique_ptr<Tile> tile = std::move(TilesPlayed[i]->tile);
            tile->parent = nullptr;
            TilesPlayed[i]->tile = std::make_unique<Tile>((' '));
            TilesPlayed[i]->tile->parent = TilesPlayed[i].get();
            TilesPlayed[i]->tile->Selectable = false;
            TilesPlayed[i]->tile->color = Color{0,0,0,0};

            discardedBag.push_back(std::move(tile));
            i--;
        }
    }
    DrawToMax();
}
void PCControlled::PlayHand()
{
    std::string word = GetPlayedHand();
    std::string played = Dictionary::CheckWord(word);
    //invalid hand - not a word
    if (played.size() == 0)
    {
        ClearHand();
        return;
    }
    float multiplier = GetMultiplier(played);
    Attack(multiplier);
    ClearHand();


}
