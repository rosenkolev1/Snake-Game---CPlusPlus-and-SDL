#include "GlobalParams.h"

GlobalParams getTestGlobalParams()
{
	GlobalParams params = GlobalParams();

	params
		.setDefaultTickSpeed(0)
		.setTickSpeedDecrease(15)
		.setTickSpeedCap(50)
		.setFontPath("./Fonts/OpenSans_VariableFont.ttf")
		.setFontSize(20)
		.setGameOverFontSize(64)
		.setGameWonFontSize(72)
		.setTextColor({ .r = 255, .g = 255, .b = 255, .a = 100 })
		.setRestartKey(SDLK_r)
		.setTimeElapsedTxt("Time Elapsed: ")
		.setCollectedApplesTxt("Apples Collected: ")
		.setPressKeyToRestartTxt("Press r to restart the game!!!")
		.setGameWonTxt("YOU HAVE WON THE GAME!!!\n                     :)\n")
		.setGameTilesetPath("./Images/snake_graphics_tileset.png")
		.setGameTilesetWidth(320)
		.setGameTilesetHeight(256)
		.setGameTilesetTileWidth(64)
		.setGameTilesetTileHeight(64)
		.setGameTilesetRowsCount(params.GAME_TILESET_H / params.GAME_TILESET_TILE_H)
		.setGameTilesetColumnsCount(params.GAME_TILESET_W / params.GAME_TILESET_TILE_W)
		.setGameWindowTitle("Snake Game")
		.setGameGridRowsCount(4)
		.setGameGridColumnsCount(4)
		.setGameWindowX(180)
		.setGameWindowY(95)
		.setGameWindowWidth(1200)
		.setGameWindowHeight(700)
		.setGameGridOffsetLeft(350)
		.setGameGridOffsetRight(350)
		.setGameGridOffsetUp(100)
		.setGameGridOffsetDown(100)
		.setGameGridLeftBorder(params.GAME_GRID_OFFSET_LEFT)
		.setGameGridRightBorder(params.GAME_WINDOW_W - params.GAME_GRID_OFFSET_RIGHT)
		.setGameGridUpperBorder(params.GAME_GRID_OFFSET_UP)
		.setGameGridBottomBorder(params.GAME_WINDOW_H - params.GAME_GRID_OFFSET_DOWN)
		.setGameGridWidth(params.GAME_GRID_RIGHT_BORDER - params.GAME_GRID_LEFT_BORDER)
		.setGameGridHeight(params.GAME_GRID_BOTTOM_BORDER - params.GAME_GRID_UPPER_BORDER)
		.setGameTileWidth(params.GAME_GRID_W / params.GAME_GRID_COLS_COUNT)
		.setGameTileHeight(params.GAME_GRID_H / params.GAME_GRID_ROWS_COUNT)
		.setEmptyTileColor({ .r = 81, .g = 53, .b = 97, .a = 100 })
		.setTimeElapsedRect({ .x = params.GAME_GRID_LEFT_BORDER - 100, .y = params.GAME_GRID_UPPER_BORDER - 100, .w = 200, .h = 50 })
		.setCollectedApplesRect({ .x = params.GAME_GRID_RIGHT_BORDER - 100, .y = params.GAME_GRID_UPPER_BORDER - 100, .w = 200, .h = 50 })
		.setGameOverRect({ .x = (params.GAME_WINDOW_W - 600) / 2, .y = (params.GAME_WINDOW_H - 200) / 2, .w = 600, .h = 200 })
		.setSnakeDefaultSpawnPos({ 0, 0 })
		.setSnakeDefaultLength(3)
		.setAppleDefaultSpawnPos({ params.GAME_GRID_ROWS_COUNT - 1, params.GAME_GRID_COLS_COUNT - 1 })
		.setKeyToMoveMap(
			{
				{ SDLK_a, { MoveDir::LEFT, MoveDir::RIGHT } },
				{ SDLK_LEFT, { MoveDir::LEFT, MoveDir::RIGHT } },
				{ SDLK_d, { MoveDir::RIGHT, MoveDir::LEFT } },
				{ SDLK_RIGHT, { MoveDir::RIGHT, MoveDir::LEFT } },
				{ SDLK_w, { MoveDir::UP, MoveDir::DOWN } },
				{ SDLK_UP, { MoveDir::UP, MoveDir::DOWN } },
				{ SDLK_s, { MoveDir::DOWN, MoveDir::UP } },
				{ SDLK_DOWN, {  MoveDir::DOWN, MoveDir::UP } },
			}
			)
		.disableAutoPlay();

	return params;
}

