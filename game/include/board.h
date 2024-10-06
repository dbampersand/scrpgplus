#pragma once

#include "slot.h"

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

	Board();

	inline static std::unique_ptr<Board> board;

	BoardSlot slots[_BOARD_TILE_COUNT_X][_BOARD_TILE_COUNT_Y];
	std::vector<std::shared_ptr<Slot>> PlayerSlots;


	void Show();
	void Hide();
};