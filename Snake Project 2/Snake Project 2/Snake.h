#pragma once
#include <vector>
#include "TilePos.h"
#include "Tile.h"
#include "GlobalConstants.h"
#include <map>
#include "MoveDir.h"

class Snake
{
public:
	static const inline std::map<MoveDir, TilePos> MOVE_OFFSET_MAP =
	{
		{ MoveDir::UP, { -1, 0 } },
		{ MoveDir::RIGHT, { 0, 1 } },
		{ MoveDir::DOWN, { 1, 0 } },
		{ MoveDir::LEFT, { 0, -1 } },
	};

	MoveDir curDirection;

	std::vector<TilePos> tiles;

	Snake(TilePos initialSpawnPos);
	Snake();

	TilePos getHead();
	TilePos getTail();
};

