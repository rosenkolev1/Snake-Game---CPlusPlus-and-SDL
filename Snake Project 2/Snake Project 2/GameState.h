#pragma once
#include <vector>
#include "Tile.h"
#include "Snake.h"
#include "GlobalConstants.h"

class GameState
{
public:

	std::vector<std::vector<Tile>> grid;

	int tickSpeed;

	bool processTick;

	int collectedApples;

	TilePos applePosition;

	Snake snake;

	GameState();
};

