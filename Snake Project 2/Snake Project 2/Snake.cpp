#include "Snake.h"

Snake::Snake(TilePos initialSpawnPos)
{
	this->tiles = std::vector<TilePos>(1, initialSpawnPos);
	this->tiles.push_back({ -1, -1 });

	this->curDirection = MoveDir::Right;
}

Snake::Snake()
	:Snake(GC::SNAKE_DEFAULT_SPAWN)
{
}
