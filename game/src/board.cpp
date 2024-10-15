#include "board.h"
#include "render.h"
#include "pccontrolled.h"
#include "dictionary.h"

Board::Board()
{
	float padding = 2;

	float boardWidth = Render::GetBasisWidth();
	float boardHeight = Render::GetBasisHeight() - Render::GetBasisHeight() / 6.0f;

	int slotW = boardWidth / (float)_BOARD_TILE_COUNT_X - padding;
	int slotH = boardHeight / (float)_BOARD_TILE_COUNT_Y - padding;


	Board::PlayerSlots.clear();

	for (int x = 0; x < _BOARD_TILE_COUNT_X; x++)
	{
		for (int y = 0; y < _BOARD_TILE_COUNT_Y; y++)
		{
			//Create grid of Slots
			slots[x][y].w = slotW;
			slots[x][y].h = slotH;

			slots[x][y].x = (x * slots[x][y].w + (padding * x));
			slots[x][y].y = (y * slots[x][y].h + (padding * y));
		}
	}
	//Initialise slots and center them horizontally
	for (int i = 0; i < _BOARD_PLAYER_SLOTS; i++)
	{
		std::shared_ptr<BoardSlot> playerTile = std::make_shared<BoardSlot>(0.0f, boardHeight + padding, slotW, slotH);
		Board::PlayerSlots.push_back(playerTile);
	}
	std::vector<std::shared_ptr<Slot>> slotsCasted;
	for (std::shared_ptr<BoardSlot> tile : PlayerSlots)
	{
		slotsCasted.push_back(tile);
	}

	Slot::HorizontalCenterTiles(&slotsCasted, padding);
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

void Board::DrawTiles(PCControlled* player)
{
	for (std::shared_ptr<BoardSlot> bs : PlayerSlots)
	{
		if (bs->tile && bs->tile->character != ' ')
			player->DiscardTile(std::move(bs->tile));
		bs->SetTile(std::move(player->DrawTile()));
	}
}
BoardWord Board::CheckTileVertical(int tileX, int tileY, bool* IsAWord)
{
	int boundsMinY = tileX;
	int boundsMaxY = tileX;

	int valueDamage = 0;
	int valueShield = 0;
	int valueHeal = 0;

	//get bounds min on vertical axis (top side of the tile played)
	for (int y = tileY; y >= 0; y--)
	{
		if (!board->slots[tileX][y].tile || board->slots[tileX][y].tile->character == ' ')
		{
			boundsMinY = y+1;
			break;
		}
		if (y == 0)
			boundsMinY = 0;
	}
	//get bounds max on vertical axis (bottom side of the tile played)
	for (int y = tileY; y < _BOARD_TILE_COUNT_Y; y++)
	{
		if (!board->slots[tileX][y].tile || board->slots[tileX][y].tile->character == ' ')
		{
			boundsMaxY = y-1;
			break;
		}
		if (y == _BOARD_TILE_COUNT_Y - 1)
		{
			boundsMaxY = y-1;
		}
	}
	std::string vertical = "";
	for (int y = boundsMinY; y <= boundsMaxY; y++)
	{
		Tile* t = board->slots[tileX][y].tile.get();

		if (t->tileType == Tile::Damage)
			valueDamage += t->mutiplier;
		if (t->tileType == Tile::Shield)
			valueShield += t->mutiplier;
		if (t->tileType == Tile::Heal)
			valueHeal += t->mutiplier;

		vertical += t->character;
	}

	*IsAWord = false;

	if (vertical.size() > 1)
	{
		*IsAWord = true;
		if (!Dictionary::CheckWord(vertical))
		{
			*IsAWord = false;
		}
	}

	BoardWord boardTile = BoardWord(tileX,boundsMinY,valueDamage,valueHeal,valueShield,vertical, false);

	return boardTile;
}
BoardWord Board::CheckTileHorizontal(int tileX, int tileY, bool* IsAWord)
{
	int boundsMinX = tileX;
	int boundsMaxX = tileX;

	int valueDamage = 0;
	int valueShield = 0;
	int valueHeal = 0;


	//get bounds min on horizontal axis (left side of the tile played)
	for (int x = tileX; x >= 0; x--)
	{
		if (!board->slots[x][tileY].tile || board->slots[x][tileY].tile->character == ' ')
		{
			boundsMinX = x+1;
			break;
		}
		if (x == 0)
			boundsMinX = 0;
	}
	//get bounds max on horizontal axis (right side of the tile played)
	for (int x = tileX; x < _BOARD_TILE_COUNT_X; x++)
	{
		if (!board->slots[x][tileY].tile || board->slots[x][tileY].tile->character == ' ')
		{
			boundsMaxX = x-1;
			break;
		}
		if (x == _BOARD_TILE_COUNT_X - 1)
		{
			boundsMaxX = x;
		}

	}
	std::string horizontal = "";
	//get the word on the horizontal and vertical axes
	for (int x = boundsMinX; x <= boundsMaxX; x++)
	{
		Tile* t = board->slots[x][tileY].tile.get();

		if (t->tileType == Tile::Damage)
			valueDamage += t->mutiplier;
		if (t->tileType == Tile::Shield)
			valueShield += t->mutiplier;
		if (t->tileType == Tile::Heal)
			valueHeal += t->mutiplier;

		horizontal += t->character;
	}
	
	//if they have >1 character in them, then they are words we need to check
	*IsAWord = false;
	if (horizontal.size() > 1)
	{
		*IsAWord = true;
		if (!Dictionary::CheckWord(horizontal))
		{
			*IsAWord = false;
		}
	}

	BoardWord boardTile = BoardWord(boundsMinX, tileY, valueDamage, valueHeal, valueShield, horizontal, true);

	return boardTile;
}
void Board::CleanBadPlayedBoard()
{
	for (int x = 0; x < _BOARD_TILE_COUNT_X; x++)
	{
		for (int y = 0; y < _BOARD_TILE_COUNT_Y; y++)
		{
			if (Board::board->slots[x][y].tile && Board::board->slots[x][y].tile->character != ' ' && !Board::board->slots[x][y].tile->IsLocked())
			{
				PCControlled::CurrentPlayer->DiscardTile(std::move(Board::board->slots[x][y].tile));
				Board::board->slots[x][y].SetTile(std::move(std::make_unique<Tile>()));

			}
		}
	}
}
std::vector<BoardWord> Board::CheckBoardWords(bool* correct)
{
	std::vector<BoardWord> words;
	*correct = true;

	//Check if the entire board state is correct now - i.e. we don't have any orphaned characters that aren't part of a valid word
	bool filledSlots[_BOARD_TILE_COUNT_X][_BOARD_TILE_COUNT_Y];
	memset(filledSlots, true, _BOARD_TILE_COUNT_X*_BOARD_TILE_COUNT_Y*sizeof(filledSlots[0][0]));


	for (int x = 0; x < _BOARD_TILE_COUNT_X; x++)
	{
		for (int y = 0; y < _BOARD_TILE_COUNT_Y; y++)
		{
			//if not locked -> this is a new tile, we need to check it for words
			if (Board::board->slots[x][y].tile && Board::board->slots[x][y].tile->character != ' ' && !Board::board->slots[x][y].tile->IsLocked())
			{
				bool verticalWord = false;
				bool horizontalWord = false;

				BoardWord vertical = CheckTileVertical(x, y, &verticalWord);
				BoardWord horizontal = CheckTileHorizontal(x, y, &horizontalWord);

				if (verticalWord && std::find(words.begin(), words.end(), vertical) == words.end())
				{
					words.push_back(vertical);
				}
				if (horizontalWord && std::find(words.begin(), words.end(), horizontal) == words.end())
				{
					words.push_back(horizontal);
				}
				filledSlots[x][y] = false;

			}
		}
	}

	//Check if the entire board state is correct now - i.e. we don't have any orphaned characters that aren't part of a valid word
	for (BoardWord word : words)
	{
		if (word.horizontal)
		{
			for (int x = 0; x < word.word.size(); x++)
			{
				filledSlots[word.x+x][word.y] = true;
			}
		}
		else
		{
			for (int y = 0; y < word.word.size(); y++)
			{
				filledSlots[word.x][word.y+y] = true;
			}
		}

	}

	//do final check to see if all filled slots are accounted for (they are all valid words)
	for (int x = 0; x < _BOARD_TILE_COUNT_X; x++)
	{
		for (int y = 0; y < _BOARD_TILE_COUNT_Y; y++)
		{
			if (filledSlots[x][y] == false)
				*correct = false;
		}
	}
	

	return words;
}