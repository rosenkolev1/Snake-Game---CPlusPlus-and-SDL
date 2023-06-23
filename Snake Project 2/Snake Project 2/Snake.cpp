#include "Snake.h"

Snake::Snake(TilePos initialSpawnPos)
{
	this->tiles = std::vector<TilePos>();

	for (int i = 0; i < 3; i++)
	{
		this->tiles.push_back({ initialSpawnPos.row, initialSpawnPos.col + 2 - i });
	}

	this->tiles.push_back(this->tiles.back());

	this->curDirection = MoveDir::Right;
}

Snake::Snake()
	:Snake(GC::SNAKE_DEFAULT_SPAWN)
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
