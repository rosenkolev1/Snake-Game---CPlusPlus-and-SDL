#pragma once
#include <vector>
#include "TilePos.h"
#include "Tile.h"
#include "GlobalParams.h"
#include <map>
#include "MoveDir.h"

class Snake
{
public:
	GlobalParams GP;

	static const inline std::map<MoveDir, TilePos> MOVE_OFFSET_MAP =
	{
		{ MoveDir::UP, { -1, 0 } },
		{ MoveDir::RIGHT, { 0, 1 } },
		{ MoveDir::DOWN, { 1, 0 } },
		{ MoveDir::LEFT, { 0, -1 } },
	};

	MoveDir curDirection;

	std::vector<TilePos> tiles;

	Snake(const GlobalParams& globalParams, TilePos initialSpawnPos);
	Snake(const GlobalParams& globalParams);

	TilePos getHead();
	TilePos getTail();

	bool operator== (const Snake& other) const = default;
};

