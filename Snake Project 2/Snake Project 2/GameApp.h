#pragma once
#include "GameUI.h"
#include "Tile.h"
#include "GlobalConstants.h"
#include "GameState.h"
#include "MoveDir.h"
#include <map>

class GameApp
{
private:

	std::unique_ptr<GameUI> gameUI = nullptr;

	GameState state;

	long lastTickEnd;

	bool autoPlay;
	std::vector<TilePos> hamiltonianCycle;
	int hamiltonianCounter = 0;

public:

	GameApp(bool autoPlay = false);

	Tile& getTile(TilePos pos);

	void startGameLoop();

	MoveDir determineDirection(TilePos from, TilePos to);
	SnakeSprite getSnakeHeadSprite(MoveDir to);
	SnakeSprite getSnakeTailSprite(MoveDir to);
	SnakeSprite getSnakeSprite(MoveDir from, MoveDir to);

	bool moveSnake();
	bool isOutOfBounds(TilePos pos);

	std::vector<TilePos> getHamiltonianCycleForEvenRows();
	std::vector<TilePos> getHamiltonianCycleForEvenCols();
	void resetGameState();
	void replaceRandomApple();
	void decreaseTickSpeed();
};

