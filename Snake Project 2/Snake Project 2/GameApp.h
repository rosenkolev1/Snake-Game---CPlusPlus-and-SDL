#pragma once
#include "GameUI.h"
#include "Tile.h"
#include "GlobalConstants.h"
#include "GameState.h"

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
	SnakeSprite getSnakeTailSprite(MoveDir to);
	SnakeSprite getSnakeSprite(MoveDir from, MoveDir to);

	//TODO: remove old dir
	bool moveSnake(MoveDir oldDirection);
	bool isOutOfBounds(TilePos pos);
};

