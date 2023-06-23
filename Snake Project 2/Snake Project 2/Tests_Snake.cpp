#include "doctest.h"
#include <iostream>
#include <vector>
#include "Snake.h"
#include "Test_StubUtil.h"

TEST_CASE("Test Snake constructor with all parameters")
{
	GlobalParams globalTestParams = getTestGlobalParams();
	Snake snake = Snake(globalTestParams, { 3, 1 });

	CHECK_EQ(globalTestParams, snake.GP);
	CHECK_EQ(snake.curDirection, MoveDir::RIGHT);
	CHECK_EQ(snake.tiles, std::vector<TilePos>
	{ 
		{ 3, 3 },
		{ 3, 2 },
		{ 3, 1 },
		{ 3, 1 }
	});
}

TEST_CASE("Test Snake constructor with default spawn pos")
{
	GlobalParams globalTestParams = getTestGlobalParams();
	Snake snake = Snake(globalTestParams);

	CHECK_EQ(globalTestParams, snake.GP);
	CHECK_EQ(snake.curDirection, MoveDir::RIGHT);
	CHECK_EQ(snake.tiles, std::vector<TilePos>
	{
		{ 0, 2 },
		{ 0, 1 },
		{ 0, 0 },
		{ 0, 0 }
	});
}

TEST_CASE("Test Snake get tail and get head functions")
{
	GlobalParams globalTestParams = getTestGlobalParams();
	Snake snake = Snake(globalTestParams, { 3, 1 });

	CHECK_EQ(snake.getTail(), TilePos { 3, 1 });
	CHECK_EQ(snake.getHead(), TilePos{ 3, 3 });
}