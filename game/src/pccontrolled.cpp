#include "pccontrolled.h"
#include <algorithm>
#include <random>
#include "gamestate.h"
#include "dictionary.h"
#include "particle.h"
#include "board.h"

void PCControlled::Update(float dt)
{
    GameObject::Update(dt);
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
void PCControlled::DiscardTile(std::unique_ptr<Tile> tile)
{
    tile->HideDrawing();
    discardedBag.push_back(std::move(tile));
}
void PCControlled::FillDrawBag()
{
    for (int i = 0; i < discardedBag.size(); i++)
    {
        //Remove from discarded bag and insert into bag
        std::unique_ptr<Tile> drawn = std::move(discardedBag.back());
        discardedBag.pop_back();
        bag.push_back(std::move(drawn));
        i--;
    }
    ShuffleBag(&bag);
}
std::unique_ptr<Tile> PCControlled::DrawTile()
{
    //if we have no Tiles left in the bag, then fill it up again with the contents of DiscardedBag
    if (bag.size() == 0)
    {
        FillDrawBag();
    }

    std::unique_ptr<Tile> drawn = std::move(bag.back());
    bag.pop_back();
    return drawn;
}

void PCControlled::AddTilesToBag(std::vector<std::unique_ptr<Tile>>* bag, int numToAdd, char character, float multiplier, float chanceOfDamage, float chanceOfHeal, float chanceOfShield)
{
    for (int i = 0; i < numToAdd; i++)
    {
        std::unique_ptr<Tile> t;
        //generate random number to decide what tile we've chosen
        float total = chanceOfDamage + chanceOfHeal + chanceOfShield;
        float rand = GameState::RandRange<float>(0, total);

        //damage
        if (rand >= 0 && rand <= chanceOfDamage)
        {
            t = std::make_unique<DamageTile>(character, multiplier);
        }
        //heal
        else if (rand >= chanceOfDamage && rand <= chanceOfDamage + chanceOfHeal)
        {
            t = std::make_unique<HealTile>(character, multiplier);
        }
        //shield
        else if (rand >= chanceOfDamage + chanceOfHeal && rand <= chanceOfDamage + chanceOfHeal + chanceOfShield)
        {
            t = std::make_unique<ShieldTile>(character, multiplier);
        }
        else {
            t = std::make_unique<DamageTile>(character, multiplier);
        }
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

    float damageTileChance = 0.7f;
    float healTileChance = 0.2f;
    float shieldTileChance = 0.1f;


    //Add all the tiles to the bag
    //This line is adding 12 e tiles with a multiplier of 1 and so on
    AddTilesToBag(&bag, 12, 'e', 1, damageTileChance, healTileChance, shieldTileChance);

    AddTilesToBag(&bag, 9, 'a', 1, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 9, 'i', 1, damageTileChance, healTileChance, shieldTileChance);

    AddTilesToBag(&bag, 8, 'o', 1, damageTileChance, healTileChance, shieldTileChance);

    AddTilesToBag(&bag, 6, 'n', 1, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 6, 'r', 1, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 6, 't', 1, damageTileChance, healTileChance, shieldTileChance);

    AddTilesToBag(&bag, 4, 'l', 1, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 4, 's', 1, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 4, 'u', 1, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 4, 'd', 2, damageTileChance, healTileChance, shieldTileChance);

    AddTilesToBag(&bag, 3, 'g', 2, damageTileChance, healTileChance, shieldTileChance);

    AddTilesToBag(&bag, 2, 'b', 3, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 2, 'c', 3, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 2, 'm', 3, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 2, 'p', 3, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 2, 'f', 4, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 2, 'h', 4, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 2, 'v', 4, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 2, 'w', 4, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 2, 'y', 4, damageTileChance, healTileChance, shieldTileChance);

    AddTilesToBag(&bag, 1, 'k', 5, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 1, 'j', 8, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 1, 'x', 8, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 1, 'q', 10, damageTileChance, healTileChance, shieldTileChance);
    AddTilesToBag(&bag, 1, 'z', 10, damageTileChance, healTileChance, shieldTileChance);

    //Wildcards
    AddTilesToBag(&bag, 2, '*', 0, damageTileChance, healTileChance, shieldTileChance);

}

PCControlled::PCControlled(std::string path) : Player(path) {
    int padding = 5;

    //int startX = 139;
    float startX = Render::GetBasisWidth()/2.0f - ((Slot::GetDefaultWidth() * _MaxTiles/2.0f) + (padding * _MaxTiles/2.0f) - padding/2.0f);
    float startY = 200;

    AiControlled = false;

    InitBag();
    ShuffleBag(&bag);

    Board::board = std::make_unique<Board>();

    for (int i = 0; i < _MaxTiles; i++)
    {
        float y = startY;
        std::shared_ptr<Slot> playerTile = std::make_shared<Slot>(0.0f, y);

        playerTile->tile = std::move(DrawTile());
        playerTile->tile->y = y;
        playerTile->tile->parent = playerTile.get();

        PlayerTiles.push_back((playerTile));

        std::shared_ptr<Slot> tilePlayed = std::make_shared<Slot>(0.0f, y + Slot::GetDefaultHeight() + padding);
        TilesPlayed.push_back((tilePlayed));
    }
    Slot::HorizontalCenterTiles(&PlayerTiles,(float)padding);
    Slot::HorizontalCenterTiles(&TilesPlayed,(float)padding);
    
    HideTiles();
};
void PCControlled::Win()
{
    Board::board->Show();
    HideTiles();
    GameState::SetState(GameState::IN_BOARD);
}
void PCControlled::Lose()
{
    Player::HideDrawing();
    HideTiles();
}

void PCControlled::TakeTurn(Player* other)
{
    PlayHand();

    if (other->GetHP() <= 0)
    {
        Win();
    }
}

void PCControlled::ShuffleBag(std::vector<std::unique_ptr<Tile>>* bag)
{
    std::shuffle(std::begin(*bag), std::end(*bag), *GameState::GetRNG());
}
float PCControlled::GetMultiplier(std::string hand)
{
    float totalCharacters = 0;
    for (std::shared_ptr<Slot> s : PCControlled::CurrentPlayer->TilesPlayed)
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
    for (std::shared_ptr<Slot> s : PCControlled::CurrentPlayer->TilesPlayed)
    {
        //if there is no tile here, just ignore that one
        if (s->tile->character != ' ')
            word += s->tile->character;
    }
    return word;
}
void PCControlled::Attack(float multiplier)
{
    for (std::shared_ptr<Slot> s : PCControlled::CurrentPlayer->TilesPlayed)
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
            slot->tile->x = (float)slot->x;
            slot->tile->y = (float)slot->y;
            slot->tile->parent = slot.get();
            slot->ShowDrawing();
        }
    }
}
void PCControlled::ClearHand()
{
    for (int i = 0; i < TilesPlayed.size(); i++)
    {
        //we only want to remove tiles that have characters on them as the other ones are just blank tiles
        if (TilesPlayed[i]->tile->character != ' ')
        {
            std::unique_ptr<Tile> tile = std::move(TilesPlayed[i]->tile);
            tile->parent = nullptr;
            tile->HideDrawing();

            //fill with a blank tile
            TilesPlayed[i]->tile = std::make_unique<Tile>((' '));
            TilesPlayed[i]->tile->parent = TilesPlayed[i].get();
            TilesPlayed[i]->tile->Selectable = false;
            TilesPlayed[i]->tile->color = Color{0,0,0,0};
            TilesPlayed[i]->tile->HideDrawing();

            //discard the tile
            DiscardTile(std::move(tile));
        }
    }
    //Redraw tiles
    DrawToMax();
}
void PCControlled::PlayHand()
{
    std::string word = GetPlayedHand();

    //invalid hand - not a word
    if (!Dictionary::CheckWord(word))
    {
        ClearHand();
        return;
    }
    //we have a valid word
    float multiplier = GetMultiplier(word);
    Attack(multiplier);
    ClearHand();
}
Rectangle PCControlled::GetHealthBarRectangle()
{
    if (PlayerTiles.size() > 0)
    {
        std::shared_ptr<Slot> left = PlayerTiles[0];
        std::shared_ptr<Slot> right = PlayerTiles[PlayerTiles.size() - 1];


        Rectangle r = left->GetPosition();
        r.y -= 15;
        r.height = 10;
        r.width = (right->GetPosition().x + right->GetPosition().width) - PlayerTiles[0]->GetPosition().x;
        return r;
    }
    return Rectangle{ 0,0,0,0 };
}

std::vector<Drawable*> PCControlled::GetChildren()
{
    std::vector<Drawable*> children;
    for (std::shared_ptr<Slot> slot : PlayerTiles)
    {
        children.push_back(slot.get());
    }
    for (std::shared_ptr<Slot> slot : TilesPlayed)
    {
        children.push_back(slot.get());
    }
    children.push_back(GetHealthBar());
    return children;
}
