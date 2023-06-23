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
		{ MoveDir::Up, { -1, 0 } },
		{ MoveDir::Right, { 0, 1 } },
		{ MoveDir::Down, { 1, 0 } },
		{ MoveDir::Left, { 0, -1 } },
	};

	MoveDir curDirection;

	std::vector<TilePos> tiles;

	Snake(TilePos initialSpawnPos);

	Snake();
};

