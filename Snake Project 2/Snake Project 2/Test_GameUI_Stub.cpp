#include "Test_GameUI_Stub.h"

void Test_GameUI_Stub::renderTick(const GameState& gameState)
{
	//The GameUI stub does nothing when it has to render stuff
	return;
}

Test_GameUI_Stub::Test_GameUI_Stub()
{
	this->validState = true;
}
