#pragma once

#include "draggable.h"
#include "drawable.h"
#include "slot.h"
#include "render.h"

#define _BOARD_TILE_COUNT_X 20
#define _BOARD_TILE_COUNT_Y 15
#define _BOARD_PLAYER_SLOTS 8

class BoardSlot : public Slot
{
public:
 	bool locked = false;
	BoardSlot() : Slot() {
		Drawable::AddRenderOrder(1);
		Drawable::SetTint(Color{ 200, 200, 200, 255 });
	}
};

class Board
{
public:

	inline static std::unique_ptr<Board> board;

	BoardSlot slots[_BOARD_TILE_COUNT_X][_BOARD_TILE_COUNT_Y];
	std::vector<std::shared_ptr<Slot>> PlayerSlots;


	
	void Show()
	{
		for (int x = 0; x < _BOARD_TILE_COUNT_X; x++)
		{
			for (int y = 0; y < _BOARD_TILE_COUNT_Y; y++)
			{
				slots[x][y].ShowDrawing();
			}
		}
	}
	void Hide()
	{
		for (int x = 0; x < _BOARD_TILE_COUNT_X; x++)
		{
			for (int y = 0; y < _BOARD_TILE_COUNT_Y; y++)
			{
				slots[x][y].HideDrawing();
			}
		}
	}
	~Board()
	{

	}
	Board()
	{
		float padding = 2;

		float boardWidth = Render::GetBasisWidth();
		float boardHeight = Render::GetBasisHeight() - Render::GetBasisHeight() / 6.0f;

		Board::PlayerSlots.clear();

		for (int x = 0; x < _BOARD_TILE_COUNT_X; x++)
		{
			for (int y = 0; y < _BOARD_TILE_COUNT_Y; y++)
			{
				slots[x][y].w = boardWidth / (float)_BOARD_TILE_COUNT_X - padding;
				slots[x][y].h = boardHeight / (float)_BOARD_TILE_COUNT_Y - padding;

				slots[x][y].x = x * slots[x][y].w + (padding * x); 
				slots[x][y].y = y * slots[x][y].h + (padding * y);
			}
		}
		for (int i = 0; i < _BOARD_PLAYER_SLOTS; i++)
		{
			std::shared_ptr<Slot> playerTile = std::make_shared<Slot>(0, boardHeight + padding);
			Board::PlayerSlots.push_back(playerTile);
		}
		Slot::HorizontalCenterTiles(&PlayerSlots, padding);
		Hide();
	}
};