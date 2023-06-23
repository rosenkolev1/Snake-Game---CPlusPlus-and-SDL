#include "Snake.h"

Snake::Snake(const GlobalParams& globalParams, TilePos initialSpawnPos)
	:GP(globalParams)
{
	this->tiles = std::vector<TilePos>();

	for (int i = 0; i < this->GP.SNAKE_DEFAULT_LENGTH; i++)
	{
		this->tiles.push_back({ initialSpawnPos.row, initialSpawnPos.col + this->GP.SNAKE_DEFAULT_LENGTH - 1 - i });
	}

	this->tiles.push_back(this->tiles.back());

	this->curDirection = MoveDir::RIGHT;
}

Snake::Snake(const GlobalParams& globalParams)
	:Snake(globalParams, this->GP.SNAKE_DEFAULT_SPAWN)
{
}

TilePos Snake::getHead()
{
	return this->tiles.front();
}

TilePos Snake::getTail()
{
	return this->tiles[this->tiles.size() - 2];
}
