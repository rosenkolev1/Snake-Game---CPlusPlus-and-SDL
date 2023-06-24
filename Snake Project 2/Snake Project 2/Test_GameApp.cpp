#include "doctest.h"
#include "GlobalParams.h"
#include "Test_Util.h"
#include "GameApp.h"
#include "Test_GameUI_Stub.h"
#include "TilePos.h"
#include "MoveDir.h"
#include "SnakeSprite.h"

TEST_CASE("Test getHamiltonianCycleForEvenRows of GameApp for even rows of the grid")
{
	GlobalParams globalTestParams = getTestGlobalParams();
	Test_GameUI_Stub* stubGameUI = new Test_GameUI_Stub();
	GameApp app = GameApp(globalTestParams, stubGameUI);

	std::vector<TilePos> expectedHamiltonianCycle =
	{
		{ 0, 3 },
		{ 1, 3 },
		{ 2, 3 },
		{ 3, 3 },
		{ 3, 2 },
		{ 3, 1 },
		{ 3, 0 },
		{ 2, 0 },
		{ 2, 1 },
		{ 2, 2 },
		{ 1, 2 },
		{ 1, 1 },
		{ 1, 0 },
		{ 0, 0 },
		{ 0, 1 },
		{ 0, 2 },
	};

	CHECK_EQ(app.getHamiltonianCycleForEvenRows(), expectedHamiltonianCycle);
}

TEST_CASE("Test getHamiltonianCycleForEvenCols of GameApp for uneven rows and even cols of the grid")
{
	GlobalParams globalTestParams = getTestGlobalParams();
	globalTestParams.setGameGridRowsCount(5);

	Test_GameUI_Stub* stubGameUI = new Test_GameUI_Stub();
	GameApp app = GameApp(globalTestParams, stubGameUI);

	std::vector<TilePos> expectedHamiltonianCycle =
	{
		{ 0, 3 },
		{ 1, 3 },
		{ 2, 3 },
		{ 3, 3 },
		{ 4, 3 },

		{ 4, 2 },
		{ 3, 2 },
		{ 2, 2 },
		{ 1, 2 },

		{ 1, 1 },
		{ 2, 1 },
		{ 3, 1 },
		{ 4, 1 },

		{ 4, 0 },
		{ 3, 0 },
		{ 2, 0 },
		{ 1, 0 },

		{ 0, 0 },
		{ 0, 1 },
		{ 0, 2 },
	};

	CHECK_EQ(app.getHamiltonianCycleForEvenCols(), expectedHamiltonianCycle);
}

TEST_CASE("Test isOutOfBounds of GameApp")
{
	GlobalParams globalTestParams = getTestGlobalParams();
	globalTestParams.setGameGridRowsCount(5);

	Test_GameUI_Stub* stubGameUI = new Test_GameUI_Stub();
	GameApp app = GameApp(globalTestParams, stubGameUI);

	CHECK(app.isOutOfBounds({ -1, 2 }));
	CHECK(app.isOutOfBounds({ 1, -2 }));
	CHECK(app.isOutOfBounds({ 5, -2 }));
	CHECK(app.isOutOfBounds({ 1, 4 }));
}

TEST_CASE("Test determineDirection of GameApp")
{
	GlobalParams globalTestParams = getTestGlobalParams();

	Test_GameUI_Stub* stubGameUI = new Test_GameUI_Stub();
	GameApp app = GameApp(globalTestParams, stubGameUI);

	CHECK_EQ(app.determineDirection({ 0, 0 }, { 0, 1 }), MoveDir::RIGHT);
	CHECK_EQ(app.determineDirection({ 0, 1 }, { 0, 0 }), MoveDir::LEFT);
	CHECK_EQ(app.determineDirection({ 0, 0 }, { 1, 0 }), MoveDir::DOWN);
	CHECK_EQ(app.determineDirection({ 1, 0 }, { 0, 0 }), MoveDir::UP);
}

TEST_CASE("Test getSnakeHeadSprite of GameApp")
{
	GlobalParams globalTestParams = getTestGlobalParams();

	Test_GameUI_Stub* stubGameUI = new Test_GameUI_Stub();
	GameApp app = GameApp(globalTestParams, stubGameUI);

	CHECK_EQ(app.getSnakeHeadSprite(MoveDir::LEFT), SnakeSprite::HEAD_LEFT);
	CHECK_EQ(app.getSnakeHeadSprite(MoveDir::RIGHT), SnakeSprite::HEAD_RIGHT);
	CHECK_EQ(app.getSnakeHeadSprite(MoveDir::UP), SnakeSprite::HEAD_UP);
	CHECK_EQ(app.getSnakeHeadSprite(MoveDir::DOWN), SnakeSprite::HEAD_DOWN);
}

TEST_CASE("Test getSnakeTailSprite of GameApp")
{
	GlobalParams globalTestParams = getTestGlobalParams();

	Test_GameUI_Stub* stubGameUI = new Test_GameUI_Stub();
	GameApp app = GameApp(globalTestParams, stubGameUI);

	CHECK_EQ(app.getSnakeTailSprite(MoveDir::LEFT), SnakeSprite::TAIL_RIGHT);
	CHECK_EQ(app.getSnakeTailSprite(MoveDir::RIGHT), SnakeSprite::TAIL_LEFT);
	CHECK_EQ(app.getSnakeTailSprite(MoveDir::UP), SnakeSprite::TAIL_DOWN);
	CHECK_EQ(app.getSnakeTailSprite(MoveDir::DOWN), SnakeSprite::TAIL_UP);
}

TEST_CASE("Test getSnakeBodySprite of GameApp")
{
	GlobalParams globalTestParams = getTestGlobalParams();

	Test_GameUI_Stub* stubGameUI = new Test_GameUI_Stub();
	GameApp app = GameApp(globalTestParams, stubGameUI);

	CHECK_EQ(app.getSnakeBodySprite(MoveDir::LEFT, MoveDir::LEFT), SnakeSprite::BODY_HOR);
	CHECK_EQ(app.getSnakeBodySprite(MoveDir::RIGHT, MoveDir::RIGHT), SnakeSprite::BODY_HOR);
	CHECK_EQ(app.getSnakeBodySprite(MoveDir::UP, MoveDir::UP), SnakeSprite::BODY_VER);
	CHECK_EQ(app.getSnakeBodySprite(MoveDir::DOWN, MoveDir::DOWN), SnakeSprite::BODY_VER);

	CHECK_EQ(app.getSnakeBodySprite(MoveDir::LEFT, MoveDir::UP), SnakeSprite::TURN_3);
	CHECK_EQ(app.getSnakeBodySprite(MoveDir::LEFT, MoveDir::DOWN), SnakeSprite::TURN_1);

	CHECK_EQ(app.getSnakeBodySprite(MoveDir::RIGHT, MoveDir::UP), SnakeSprite::TURN_4);
	CHECK_EQ(app.getSnakeBodySprite(MoveDir::RIGHT, MoveDir::DOWN), SnakeSprite::TURN_2);

	CHECK_EQ(app.getSnakeBodySprite(MoveDir::UP, MoveDir::RIGHT), SnakeSprite::TURN_1);
	CHECK_EQ(app.getSnakeBodySprite(MoveDir::UP, MoveDir::LEFT), SnakeSprite::TURN_2);

	CHECK_EQ(app.getSnakeBodySprite(MoveDir::DOWN, MoveDir::RIGHT), SnakeSprite::TURN_3);
	CHECK_EQ(app.getSnakeBodySprite(MoveDir::DOWN, MoveDir::LEFT), SnakeSprite::TURN_4);
}

TEST_CASE("Test decreaseTickSpeed of GameApp with disabled autoplay")
{
	GlobalParams globalTestParams = getTestGlobalParams();
	globalTestParams.setDefaultTickSpeed(100);
	globalTestParams.setTickSpeedDecrease(65);
	globalTestParams.setTickSpeedCap(30);
	globalTestParams.disableAutoPlay();

	Test_GameUI_Stub* stubGameUI = new Test_GameUI_Stub();
	GameApp app = GameApp(globalTestParams, stubGameUI);

	app.decreaseTickSpeed();

	CHECK_EQ(app.getState().tickSpeed, 35);

	app.decreaseTickSpeed();

	CHECK_EQ(app.getState().tickSpeed, 30);

	app.decreaseTickSpeed();

	CHECK_EQ(app.getState().tickSpeed, 30);
}

TEST_CASE("Test decreaseTickSpeed of GameApp with enabled autoplay")
{
	GlobalParams globalTestParams = getTestGlobalParams();
	globalTestParams.setDefaultTickSpeed(100);
	globalTestParams.setTickSpeedDecrease(65);
	globalTestParams.setTickSpeedCap(30);
	globalTestParams.enableAutoPlay();

	Test_GameUI_Stub* stubGameUI = new Test_GameUI_Stub();
	GameApp app = GameApp(globalTestParams, stubGameUI);

	app.decreaseTickSpeed();

	CHECK_EQ(app.getState().tickSpeed, 100);

	app.decreaseTickSpeed();

	CHECK_EQ(app.getState().tickSpeed, 100);
}

TEST_CASE("Test moveSnake of GameApp. No apple devoured")
{
	GlobalParams globalTestParams = getTestGlobalParams();
	globalTestParams.setSnakeDefaultLength(4);
	globalTestParams.setGameGridRowsCount(5);
	globalTestParams.setGameGridColumnsCount(5);
	globalTestParams.setAppleDefaultSpawnPos({ 4, 4 });

	Test_GameUI_Stub* stubGameUI = new Test_GameUI_Stub();
	GameApp app = GameApp(globalTestParams, stubGameUI);

	GameState& state = const_cast<GameState&>(app.getState());

	//Artificially move the apple from its random position for the sake of the unit test
	state.grid[state.applePosition.row][state.applePosition.col].isApple = false;
	state.grid[4][4].isApple = true;
	state.applePosition = TilePos{ 4, 4 };

	//Move the snake to the right
	app.moveSnake(MoveDir::RIGHT);

	std::vector<std::vector<Tile>> expectedGrid =
	{
		{
			Tile({ 0, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 0, 1 }, true, false, SnakeSprite::TAIL_LEFT),
			Tile({ 0, 2 }, true, false, SnakeSprite::BODY_HOR),
			Tile({ 0, 3 }, true, false, SnakeSprite::BODY_HOR),
			Tile({ 0, 4 }, true, false, SnakeSprite::HEAD_RIGHT)
		},
		{
			Tile({ 1, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 4 }, false, false, SnakeSprite::NONE)
		},
		{
			Tile({ 2, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 4 }, false, false, SnakeSprite::NONE)
		},
		{
			Tile({ 3, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 4 }, false, false, SnakeSprite::NONE)
		},
		{
			Tile({ 4, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 4 }, false, true, SnakeSprite::NONE)
		},
	};

	std::vector<TilePos> expectedSnakeTilesPos =
	{
		{ 0, 4 },
		{ 0, 3 },
		{ 0, 2 },
		{ 0, 1 },
		{ 0, 0 },
	};

	CHECK_EQ(state.grid, expectedGrid);
	CHECK_EQ(app.getState().snake.tiles, expectedSnakeTilesPos);

	//Move the snake down
	app.moveSnake(MoveDir::DOWN);

	expectedGrid =
	{
		{
			Tile({ 0, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 0, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 0, 2 }, true, false, SnakeSprite::TAIL_LEFT),
			Tile({ 0, 3 }, true, false, SnakeSprite::BODY_HOR),
			Tile({ 0, 4 }, true, false, SnakeSprite::TURN_2)
		},
		{
			Tile({ 1, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 4 }, true, false, SnakeSprite::HEAD_DOWN)
		},
		{
			Tile({ 2, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 4 }, false, false, SnakeSprite::NONE)
		},
		{
			Tile({ 3, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 4 }, false, false, SnakeSprite::NONE)
		},
		{
			Tile({ 4, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 4 }, false, true, SnakeSprite::NONE)
		},
	};

	expectedSnakeTilesPos =
	{
		{ 1, 4 },
		{ 0, 4 },
		{ 0, 3 },
		{ 0, 2 },
		{ 0, 1 },
	};

	CHECK_EQ(state.grid, expectedGrid);
	CHECK_EQ(app.getState().snake.tiles, expectedSnakeTilesPos);

	//Move the snake left
	app.moveSnake(MoveDir::LEFT);

	expectedGrid =
	{
		{
			Tile({ 0, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 0, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 0, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 0, 3 }, true, false, SnakeSprite::TAIL_LEFT),
			Tile({ 0, 4 }, true, false, SnakeSprite::TURN_2)
		},
		{
			Tile({ 1, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 3 }, true, false, SnakeSprite::HEAD_LEFT),
			Tile({ 1, 4 }, true, false, SnakeSprite::TURN_4)
		},
		{
			Tile({ 2, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 4 }, false, false, SnakeSprite::NONE)
		},
		{
			Tile({ 3, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 4 }, false, false, SnakeSprite::NONE)
		},
		{
			Tile({ 4, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 4 }, false, true, SnakeSprite::NONE)
		},
	};

	expectedSnakeTilesPos =
	{
		{ 1, 3 },
		{ 1, 4 },
		{ 0, 4 },
		{ 0, 3 },
		{ 0, 2 },
	};

	CHECK_EQ(state.grid, expectedGrid);
	CHECK_EQ(app.getState().snake.tiles, expectedSnakeTilesPos);

	//Move the snake right
	app.moveSnake(MoveDir::UP);

	expectedGrid =
	{
		{
			Tile({ 0, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 0, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 0, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 0, 3 }, true, false, SnakeSprite::HEAD_UP),
			Tile({ 0, 4 }, true, false, SnakeSprite::TAIL_UP)
		},
		{
			Tile({ 1, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 3 }, true, false, SnakeSprite::TURN_3),
			Tile({ 1, 4 }, true, false, SnakeSprite::TURN_4)
		},
		{
			Tile({ 2, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 4 }, false, false, SnakeSprite::NONE)
		},
		{
			Tile({ 3, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 4 }, false, false, SnakeSprite::NONE)
		},
		{
			Tile({ 4, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 4 }, false, true, SnakeSprite::NONE)
		},
	};

	expectedSnakeTilesPos =
	{
		{ 0, 3 },
		{ 1, 3 },
		{ 1, 4 },
		{ 0, 4 },
		{ 0, 3 },
	};

	CHECK_EQ(state.grid, expectedGrid);
	CHECK_EQ(app.getState().snake.tiles, expectedSnakeTilesPos);

	//Move the snake right again. The snake just moved right once and then run a circle around itself
	app.moveSnake(MoveDir::RIGHT);

	expectedGrid =
	{
		{
			Tile({ 0, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 0, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 0, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 0, 3 }, true, false, SnakeSprite::TURN_1),
			Tile({ 0, 4 }, true, false, SnakeSprite::HEAD_RIGHT)
		},
		{
			Tile({ 1, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 3 }, true, false, SnakeSprite::TURN_3),
			Tile({ 1, 4 }, true, false, SnakeSprite::TAIL_RIGHT)
		},
		{
			Tile({ 2, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 4 }, false, false, SnakeSprite::NONE)
		},
		{
			Tile({ 3, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 4 }, false, false, SnakeSprite::NONE)
		},
		{
			Tile({ 4, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 4 }, false, true, SnakeSprite::NONE)
		},
	};

	expectedSnakeTilesPos =
	{
		{ 0, 4 },
		{ 0, 3 },
		{ 1, 3 },
		{ 1, 4 },
		{ 0, 4 },
	};

	CHECK_EQ(state.grid, expectedGrid);
	CHECK_EQ(app.getState().snake.tiles, expectedSnakeTilesPos);
}

TEST_CASE("Test moveSnake of GameApp. Snake devours apple")
{
	GlobalParams globalTestParams = getTestGlobalParams();
	globalTestParams.setSnakeDefaultLength(4);
	globalTestParams.setGameGridRowsCount(5);
	globalTestParams.setGameGridColumnsCount(5);
	globalTestParams.setAppleDefaultSpawnPos({ 0, 4 });

	Test_GameUI_Stub* stubGameUI = new Test_GameUI_Stub();
	GameApp app = GameApp(globalTestParams, stubGameUI);

	GameState& state = const_cast<GameState&>(app.getState());

	//Artificially move the apple from its random position for the sake of the unit test
	state.grid[state.applePosition.row][state.applePosition.col].isApple = false;
	state.grid[0][4].isApple = true;
	state.applePosition = TilePos{ 0, 4 };

	//Move the snake to the right
	app.moveSnake(MoveDir::RIGHT);

	//Artificially move the apple from its random position for the sake of the unit test
	state.grid[state.applePosition.row][state.applePosition.col].isApple = false;
	state.grid[4][4].isApple = true;
	state.applePosition = TilePos{ 4, 4 };

	std::vector<std::vector<Tile>> expectedGrid =
	{
		{
			Tile({ 0, 0 }, true, false, SnakeSprite::TAIL_LEFT),
			Tile({ 0, 1 }, true, false, SnakeSprite::BODY_HOR),
			Tile({ 0, 2 }, true, false, SnakeSprite::BODY_HOR),
			Tile({ 0, 3 }, true, false, SnakeSprite::BODY_HOR),
			Tile({ 0, 4 }, true, false, SnakeSprite::HEAD_RIGHT)
		},
		{
			Tile({ 1, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 1, 4 }, false, false, SnakeSprite::NONE)
		},
		{
			Tile({ 2, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 2, 4 }, false, false, SnakeSprite::NONE)
		},
		{
			Tile({ 3, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 3, 4 }, false, false, SnakeSprite::NONE)
		},
		{
			Tile({ 4, 0 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 1 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 2 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 3 }, false, false, SnakeSprite::NONE),
			Tile({ 4, 4 }, false, true, SnakeSprite::NONE)
		},
	};

	std::vector<TilePos> expectedSnakeTilesPos =
	{
		{ 0, 4 },
		{ 0, 3 },
		{ 0, 2 },
		{ 0, 1 },
		{ 0, 0 },
		{ 0, 0 },
	};

	CHECK_EQ(state.collectedApples, 1);
	CHECK_EQ(state.grid, expectedGrid);
	CHECK_EQ(app.getState().snake.tiles, expectedSnakeTilesPos);
}

TEST_CASE("Test moveSnake of GameApp. Snake moves out of bounds!")
{
	GlobalParams globalTestParams = getTestGlobalParams();
	globalTestParams.setSnakeDefaultLength(4);
	globalTestParams.setGameGridRowsCount(4);
	globalTestParams.setGameGridColumnsCount(4);
	globalTestParams.setAppleDefaultSpawnPos({ 3, 3 });

	Test_GameUI_Stub* stubGameUI = new Test_GameUI_Stub();
	GameApp app = GameApp(globalTestParams, stubGameUI);

	GameState& state = const_cast<GameState&>(app.getState());

	//Move the snake to the right
	app.moveSnake(MoveDir::RIGHT);

	CHECK(state.gameOver);
}

TEST_CASE("Test moveSnake of GameApp. Snake hits itself!")
{
	GlobalParams globalTestParams = getTestGlobalParams();
	globalTestParams.setSnakeDefaultLength(5);
	globalTestParams.setGameGridRowsCount(5);
	globalTestParams.setGameGridColumnsCount(5);
	globalTestParams.setAppleDefaultSpawnPos({ 4, 4 });

	Test_GameUI_Stub* stubGameUI = new Test_GameUI_Stub();
	GameApp app = GameApp(globalTestParams, stubGameUI);

	GameState& state = const_cast<GameState&>(app.getState());

	//Artificially move the apple from its random position for the sake of the unit test
	state.grid[state.applePosition.row][state.applePosition.col].isApple = false;
	state.grid[4][4].isApple = true;
	state.applePosition = TilePos{ 4, 4 };

	//Move the snake down
	app.moveSnake(MoveDir::DOWN);

	//Move the snake left
	app.moveSnake(MoveDir::LEFT);

	//Move the snake up --> collision
	app.moveSnake(MoveDir::UP);

	CHECK(state.gameOver);
}

TEST_CASE("Test moveSnake of GameApp. Snake devours all apples and the game is won!")
{
	GlobalParams globalTestParams = getTestGlobalParams();
	globalTestParams.setSnakeDefaultLength(3);
	globalTestParams.setGameGridRowsCount(4);
	globalTestParams.setGameGridColumnsCount(4);
	globalTestParams.setAppleDefaultSpawnPos({ 0, 3 });

	Test_GameUI_Stub* stubGameUI = new Test_GameUI_Stub();
	GameApp app = GameApp(globalTestParams, stubGameUI);

	GameState& state = const_cast<GameState&>(app.getState());

	//Artificially move the apple from its random position for the sake of the unit test
	state.grid[state.applePosition.row][state.applePosition.col].isApple = false;
	state.grid[3][3].isApple = true;
	state.applePosition = TilePos{ 0, 3 };

	state.collectedApples = 12;

	app.moveSnake(MoveDir::RIGHT);

	CHECK(state.gameWon);
	CHECK_EQ(state.collectedApples, 13);
}