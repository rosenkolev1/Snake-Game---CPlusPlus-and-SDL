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

public:

	GameApp();

	Tile& getTile(TilePos pos);

	void startGameLoop();

	MoveDir determineDirection(TilePos from, TilePos to);
	SnakeSprite getSnakeHeadSprite(MoveDir to);
	SnakeSprite getSnakeTailSprite(MoveDir to);
	SnakeSprite getSnakeSprite(MoveDir from, MoveDir to);

	bool moveSnake();
	bool isOutOfBounds(TilePos pos);

	void replaceRandomApple();
};

