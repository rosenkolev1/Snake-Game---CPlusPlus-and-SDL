#pragma once
#include "GameState.h"

class IGameUI
{
public:
	virtual ~IGameUI() = default;

	virtual void renderTick(const GameState& gameState) = 0;

	bool isValid();

protected:

	bool validState = false;
};

