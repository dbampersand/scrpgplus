#include "board.h"
#include "render.h"

Board::Board()
{
	float padding = 2;

	float boardWidth = Render::GetBasisWidth();
	float boardHeight = Render::GetBasisHeight() - Render::GetBasisHeight() / 6.0f;

	Board::PlayerSlots.clear();

	for (int x = 0; x < _BOARD_TILE_COUNT_X; x++)
	{
		for (int y = 0; y < _BOARD_TILE_COUNT_Y; y++)
		{
			//Create grid of Slots
			slots[x][y].w = boardWidth / (float)_BOARD_TILE_COUNT_X - padding;
			slots[x][y].h = boardHeight / (float)_BOARD_TILE_COUNT_Y - padding;

			slots[x][y].x = (x * slots[x][y].w + (padding * x));
			slots[x][y].y = (y * slots[x][y].h + (padding * y));
		}
	}
	for (int i = 0; i < _BOARD_PLAYER_SLOTS; i++)
	{
		std::shared_ptr<Slot> playerTile = std::make_shared<Slot>(0.0f, boardHeight + padding);
		Board::PlayerSlots.push_back(playerTile);
	}
	Slot::HorizontalCenterTiles(&PlayerSlots, padding);
	Hide();
}


void Board::Show()
{
	//show all board slots and player slots
	for (int x = 0; x < _BOARD_TILE_COUNT_X; x++)
	{
		for (int y = 0; y < _BOARD_TILE_COUNT_Y; y++)
		{
			slots[x][y].ShowDrawing();
		}
	}
	for (int i = 0; i < PlayerSlots.size(); i++)
	{
		PlayerSlots[i]->ShowDrawing();
	}
}
void Board::Hide()
{
	//hide all board slots and player slots
	for (int x = 0; x < _BOARD_TILE_COUNT_X; x++)
	{
		for (int y = 0; y < _BOARD_TILE_COUNT_Y; y++)
		{
			slots[x][y].HideDrawing();
		}
	}
	for (int i = 0; i < PlayerSlots.size(); i++)
	{
		PlayerSlots[i]->HideDrawing();
	}

}

