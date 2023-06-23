#include "doctest.h"
#include "Test_StubUtil.h"
#include "GameState.h"
#include "SnakeSprite.h"

TEST_CASE("Test GameState constructor")
{
	GlobalParams globalTestParams = getTestGlobalParams();
	GameState state = GameState(globalTestParams);

	CHECK_EQ(state.GP, globalTestParams);
	CHECK_EQ(state.curTimeElapsed, 0);
	CHECK_EQ(state.applePosition, globalTestParams.APPLE_DEFAULT_SPAWN);
	CHECK_EQ(state.collectedApples, 0);
	CHECK_FALSE(state.gameOver);
	CHECK_FALSE(state.gameWon);
	CHECK(state.processTick);
	CHECK_EQ(state.lastGameOverTime, 0);
	CHECK_EQ(state.tickSpeed, globalTestParams.DEFAULT_TICK_SPEED);

	REQUIRE_EQ(state.snake, Snake(globalTestParams, globalTestParams.SNAKE_DEFAULT_SPAWN));

	std::vector<std::vector<Tile>> expectedGrid =
	{
		{
			Tile({ 0, 0 }, true, false, SnakeSprite::TAIL_LEFT),
			Tile({ 0, 1 }, true, false, SnakeSprite::BODY_HOR),
			Tile({ 0, 2 }, true, false, SnakeSprite::HEAD_RIGHT),
			Tile({ 0, 3 }, false, false, SnakeSprite::NONE),
		},
		{
			Tile({ 1, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 3 }, false, false, SnakeSprite::NONE),
		},
		{
			Tile({ 2, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 3 }, false, false, SnakeSprite::NONE),
		},
		{
			Tile({ 3, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 3 }, false, true, SnakeSprite::NONE),
		}
	};

	CHECK_EQ(state.grid, expectedGrid);
}