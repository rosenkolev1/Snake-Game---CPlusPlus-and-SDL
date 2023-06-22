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

	Tile getTile(TilePos pos);

	void startGameLoop();
};

