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

void PCControlled::HideTiles()
{
    for (std::shared_ptr<Slot> s : PlayerTiles)
    {
        s->HideDrawing();
        if (s->tile)
            s->tile->HideDrawing();
    }
    for (std::shared_ptr<Slot> s : TilesPlayed)
    {
        s->HideDrawing();
        if (s->tile)
            s->tile->HideDrawing();

    }
}

void PCControlled::ShowTiles()
{
    for (std::shared_ptr<Slot> s : PlayerTiles)
    {
        s->ShowDrawing();
        if (s->tile)
            s->tile->ShowDrawing();
    }
    for (std::shared_ptr<Slot> s : TilesPlayed)
    {
        s->ShowDrawing();
        if (s->tile)
            s->tile->ShowDrawing();

    }
}
void PCControlled::FillDrawBag()
{
    for (int i = 0; i < discardedBag.size(); i++)
    {
        std::unique_ptr<Tile> drawn = std::move(discardedBag.back());
        discardedBag.pop_back();
        bag.push_back(std::move(drawn));
        i--;
    }
    ShuffleBag(&bag);
}
std::unique_ptr<Tile> PCControlled::DrawTile()
{
    if (bag.size() == 0)
    {
        FillDrawBag();
    }
    std::unique_ptr<Tile> drawn = std::move(bag.back());
    bag.pop_back();
    return drawn;
}

void PCControlled::AddTilesToBag(std::vector<std::unique_ptr<Tile>>* bag, int numToAdd, char character, float multiplier)
{
    for (int i = 0; i < 1; i++)
    {
        std::unique_ptr<DamageTile> t = std::make_unique<DamageTile>(character, multiplier);
        t->HideDrawing();
        bag->push_back(std::move(t));
    }
}
void PCControlled::InitBag()
{

    bag.clear();
    discardedBag.clear();
    PlayerTiles.clear();
    TilesPlayed.clear();

    AddTilesToBag(&bag, 12, 'e', 1);

    AddTilesToBag(&bag, 9, 'a', 1);
    AddTilesToBag(&bag, 9, 'i', 1);

    AddTilesToBag(&bag, 8, 'o', 1);

    AddTilesToBag(&bag, 6, 'n', 1);
    AddTilesToBag(&bag, 6, 'r', 1);
    AddTilesToBag(&bag, 6, 't', 1);

    AddTilesToBag(&bag, 4, 'l', 1);
    AddTilesToBag(&bag, 4, 's', 1);
    AddTilesToBag(&bag, 4, 'u', 1);
    AddTilesToBag(&bag, 4, 'd', 2);

    AddTilesToBag(&bag, 3, 'g', 2);

    AddTilesToBag(&bag, 2, 'b', 3);
    AddTilesToBag(&bag, 2, 'c', 3);
    AddTilesToBag(&bag, 2, 'm', 3);
    AddTilesToBag(&bag, 2, 'p', 3);
    AddTilesToBag(&bag, 2, 'f', 4);
    AddTilesToBag(&bag, 2, 'h', 4);
    AddTilesToBag(&bag, 2, 'v', 4);
    AddTilesToBag(&bag, 2, 'w', 4);
    AddTilesToBag(&bag, 2, 'y', 4);

    AddTilesToBag(&bag, 1, 'k', 5);
    AddTilesToBag(&bag, 1, 'j', 8);
    AddTilesToBag(&bag, 1, 'x', 8);
    AddTilesToBag(&bag, 1, 'q', 10);
    AddTilesToBag(&bag, 1, 'z', 10);

    AddTilesToBag(&bag, 2, '*', 0);

}

PCControlled::PCControlled(std::string path) : Player(path) {
    HealthBar.shouldDraw = false;
    int startX = 139;
    int startY = 200;
    int padding = 5;

    InitBag();
    ShuffleBag(&bag);

    for (int i = 0; i < _MaxTiles; i++)
    {
        int x = startX + (Slot::w * i) + (padding * i);
        int y = startY;
        std::shared_ptr<Slot> playerTile = std::make_shared<Slot>(x, y);

        playerTile->tile = std::move(DrawTile());
        playerTile->tile->x = x;
        playerTile->tile->y = y;
        playerTile->tile->color = Color{ 255,0,0,255 };
        playerTile->tile->parent = playerTile.get();
        playerTile->filled = true;


        PlayerTiles.push_back((playerTile));

        std::shared_ptr<Slot> tilePlayed = std::make_shared<Slot>(x, y + Slot::h + padding);
        tilePlayed->tile = std::make_unique<Tile>((' '));
        tilePlayed->tile->Selectable = false;
        tilePlayed->tile->color = Color{ 0,0,0,0 };
        tilePlayed->tile->parent = tilePlayed.get();
        TilesPlayed.push_back((tilePlayed));
    }
    HideTiles();
};
void PCControlled::TakeTurn(Player* other)
{
    PlayHand();
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
