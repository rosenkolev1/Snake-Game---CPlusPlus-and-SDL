#pragma once
#include <vector>
#include "Tile.h"
#include "Snake.h"
#include "GlobalParams.h"

class GameState
{
public:

	GlobalParams GP;

	std::vector<std::vector<Tile>> grid;

	int tickSpeed;

	bool processTick;

	int collectedApples;

	TilePos applePosition;

	Snake snake;

	bool gameOver;
	bool gameWon;

	long lastGameOverTime;
	long curTimeElapsed;

	GameState(const GlobalParams& globalParams);
};

