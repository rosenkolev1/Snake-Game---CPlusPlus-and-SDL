#pragma once
#include "GameUI.h"
#include "Tile.h"
#include "GlobalParams.h"
#include "GameState.h"
#include "MoveDir.h"
#include <map>
#include "IGameUI.h"

class GameApp
{
	//TODO: Maybe implement a builder pattern way of constructing game app with variable GlobalConstants parameters

private:

	std::unique_ptr<IGameUI> gameUI = nullptr;

	GlobalParams GP;
	GameState state;

	long lastTickEnd;

	std::vector<TilePos> hamiltonianCycle;
	int hamiltonianCounter = 0;

public:

	//Used for unit tests only
	GameApp(const GlobalParams& globalParams, IGameUI* gameUI);

	GameApp(const GlobalParams& globalParams);

	void finishConstructor();

	Tile& getTile(TilePos pos);

	void startGameLoop();

	MoveDir determineDirection(TilePos from, TilePos to);
	SnakeSprite getSnakeHeadSprite(MoveDir to);
	SnakeSprite getSnakeTailSprite(MoveDir to);
	SnakeSprite getSnakeBodySprite(MoveDir from, MoveDir to);

	bool moveSnake(MoveDir direction);
	bool isOutOfBounds(TilePos pos);

	std::vector<TilePos> getHamiltonianCycleForEvenRows();
	std::vector<TilePos> getHamiltonianCycleForEvenCols();
	void resetGameState();
	void replaceRandomApple();
	void decreaseTickSpeed();

	const GameState& getState() const;
	long getLastTickEnd() const;
	int getHamiltonianCounter() const;
};

