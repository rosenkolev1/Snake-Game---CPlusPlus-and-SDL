#pragma once
#include <vector>
#include "TilePos.h"
#include "Tile.h"
#include "GlobalConstants.h"

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
	MoveDir curDirection;

	std::vector<TilePos> tiles;

	Snake(TilePos initialSpawnPos);

	Snake();
};

