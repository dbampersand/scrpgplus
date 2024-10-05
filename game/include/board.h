#pragma once
#include "draggable.h"
#include "drawable.h"
#include "slot.h"
#include "render.h"

#define _BOARD_TILE_COUNT_X 20
#define _BOARD_TILE_COUNT_Y 15

class BoardSlot : public Slot
{
public:
 	bool locked = false;
	BoardSlot() : Slot() {
	}
};

class Board
{
	inline static BoardSlot slots[_BOARD_TILE_COUNT_X][_BOARD_TILE_COUNT_Y];
	inline static std::unique_ptr<Board> board = std::make_unique<Board>();

	
public:
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

	Board()
	{
		for (int x = 0; x < _BOARD_TILE_COUNT_X; x++)
		{
			for (int y = 0; y < _BOARD_TILE_COUNT_Y; y++)
			{

				float boardWidth = Render::GetBasisWidth();
				float boardHeight = Render::GetBasisHeight() - Render::GetBasisHeight() / 6.0f;

				float padding = 2;

				slots[x][y].w = boardWidth / (float)_BOARD_TILE_COUNT_X - padding;
				slots[x][y].h = boardHeight / (float)_BOARD_TILE_COUNT_Y - padding;

				slots[x][y].x = x * slots[x][y].w + (padding * x); 
				slots[x][y].y = y * slots[x][y].h + (padding * y);


			}
		}
		Hide();
	}
};