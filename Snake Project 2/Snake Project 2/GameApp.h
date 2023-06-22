#pragma once
#include "GameUI.h"
#include "Tile.h"
#include "GlobalConstants.h"

class GameApp
{
private:

	std::unique_ptr<GameUI> gameUI = nullptr;

	std::vector<std::vector<Tile>> grid;

	int tickSpeed;

	long lastTickEnd;

	int collectedApples;

public:

	GameApp();
};

