#pragma once

#include "slot.h"

#define _BOARD_TILE_COUNT_X 20
#define _BOARD_TILE_COUNT_Y 15
#define _BOARD_PLAYER_SLOTS 8

typedef class PCControlled PCControlled;

struct BoardWord
{
	int x; int y;
	int valueDamage;
	int valueHeal;
	int valueShield;
	std::string word;
	bool horizontal = false;

	BoardWord(int X, int Y, int ValueDamage, int ValueHeal, int ValueShield, std::string Word, bool Horizontal)
	{
		x = X;
		y = Y;
		valueDamage = ValueDamage;
		valueHeal = ValueHeal;
		valueShield = ValueShield;
		word = Word;

		horizontal = Horizontal;

	}
	bool operator==(const BoardWord& rhs) {
		return x == rhs.x && y == rhs.y && word == rhs.word;
	}
};

class BoardSlot : public Slot
{
public:
 	bool locked = false;
	BoardSlot(float X, float Y) : Slot(X, Y) {
		Drawable::SetTint(Color{ 200, 200, 200, 255 });
	}
	BoardSlot()
	{
		Drawable::SetTint(Color{ 200, 200, 200, 255 });
	}
};

class Board
{
public:

	Board();

	inline static std::unique_ptr<Board> board;

	BoardSlot slots[_BOARD_TILE_COUNT_X][_BOARD_TILE_COUNT_Y];
	std::vector<std::shared_ptr<BoardSlot>> PlayerSlots;

	void Show();
	void Hide();

	//Checks the board words. The bool* is set to false if a word is invalid, or true if the entire board is valid
	//returns a vector of all the new, valid words that have just been added
	std::vector<BoardWord> CheckBoardWords(bool* Correct);

	BoardWord CheckTileVertical(int tileX, int tileY, bool* IsAWord);
	BoardWord CheckTileHorizontal(int tileX, int tileY, bool* IsAWord);

	//Called when any word is incorrect in the board state. Removes all just-played tiles.
	void CleanBadPlayedBoard();

	void DrawTiles(PCControlled* player);

};
