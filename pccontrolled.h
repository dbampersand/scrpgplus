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
        
        void HideTiles()
        {
            for (std::shared_ptr<Slot> s : PlayerTiles)
            {
                s->HideDrawing();
            }
            for (std::shared_ptr<Slot> s : TilesPlayed)
            {
                s->HideDrawing();
            }
        }
        void ShowTiles()
        {
            for (std::shared_ptr<Slot> s : PlayerTiles)
            {
                s->ShowDrawing();
            }
            for (std::shared_ptr<Slot> s : TilesPlayed)
            {
                s->ShowDrawing();
            }
        }

        std::unique_ptr<Tile> DrawTile()
        {
            std::unique_ptr<Tile> drawn = std::move(bag.back());
            bag.pop_back();
            return drawn;
        }
        void AddTilesToBag(std::vector<std::unique_ptr<Tile>>* bag, int numToAdd, char character, float multiplier)
        {
            for (int i = 0; i < numToAdd; i++)
            {
                std::unique_ptr<DamageTile> t =  std::make_unique<DamageTile>(character,multiplier); 
                bag->push_back(std::move(t));
            }
        }

        void ShuffleBag(std::vector<std::unique_ptr<Tile>>* bag);
        void InitBag()
        {

            bag.clear();
            discardedBag.clear();
            PlayerTiles.clear();
            TilesPlayed.clear();

            AddTilesToBag(&bag,12,'e',1);

            AddTilesToBag(&bag,9,'a',1);
            AddTilesToBag(&bag,9,'i',1);

            AddTilesToBag(&bag,8,'o',1);

            AddTilesToBag(&bag,6,'n',1);
            AddTilesToBag(&bag,6,'r',1);
            AddTilesToBag(&bag,6,'t',1);

            AddTilesToBag(&bag,4,'l',1);
            AddTilesToBag(&bag,4,'s',1);
            AddTilesToBag(&bag,4,'u',1);
            AddTilesToBag(&bag,4,'d',2);

            AddTilesToBag(&bag,3,'g',2);

            AddTilesToBag(&bag,2,'b',3);
            AddTilesToBag(&bag,2,'c',3);
            AddTilesToBag(&bag,2,'m',3);
            AddTilesToBag(&bag,2,'p',3);
            AddTilesToBag(&bag,2,'f',4);
            AddTilesToBag(&bag,2,'h',4);
            AddTilesToBag(&bag,2,'v',4);
            AddTilesToBag(&bag,2,'w',4);
            AddTilesToBag(&bag,2,'y',4);

            AddTilesToBag(&bag,1,'k',5);
            AddTilesToBag(&bag,1,'j',8);
            AddTilesToBag(&bag,1,'x',8);
            AddTilesToBag(&bag,1,'q',10);
            AddTilesToBag(&bag,1,'z',10);

            AddTilesToBag(&bag,2,'*',0); 

        }
        PCControlled(std::string path) : Player(path) {
            HealthBar.shouldDraw = false;
            int startX = 139;
            int startY = 200;
            int padding = 5;
            
            InitBag();
            ShuffleBag(&bag);
            
            for (int i = 0; i < _MaxTiles; i++)
            {
                int x = startX + (Slot::w*i) + (padding*i);
                int y = startY;
                std::shared_ptr<Slot> playerTile = std::make_shared<Slot>(x,y);

                playerTile->tile = std::move(DrawTile());
                playerTile->tile->x = x;
                playerTile->tile->y = y;
                playerTile->tile->color = (Color){255,0,0,255};
                playerTile->tile->parent = playerTile.get();
                playerTile->filled = true;


                PlayerTiles.push_back((playerTile));
                
                std::shared_ptr<Slot> tilePlayed = std::make_shared<Slot>(x,y+Slot::h+padding);
                tilePlayed->tile = std::make_unique<Tile>((' '));
                tilePlayed->tile->Selectable = false;
                tilePlayed->tile->color = (Color){0,0,0,0};
                tilePlayed->tile->parent = tilePlayed.get();
                TilesPlayed.push_back((tilePlayed));
            }
            HideTiles();
        };    
        void TakeTurn(Player* other) override
        {
            PlayHand();
        }
};