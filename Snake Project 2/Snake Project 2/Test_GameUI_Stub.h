#pragma once
#include "IGameUI.h"

class Test_GameUI_Stub : public IGameUI
{
public:

	void renderTick(const GameState& gameState) override;

	Test_GameUI_Stub();
};

