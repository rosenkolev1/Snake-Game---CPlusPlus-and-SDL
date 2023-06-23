#pragma once
#include <vector>
#include "TilePos.h"
#include "Tile.h"
#include "GlobalConstants.h"
#include <map>

enum MoveDir
{
	Up = 0,
	Right = 1,
	Down = 2,
	Left = 3
};

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

