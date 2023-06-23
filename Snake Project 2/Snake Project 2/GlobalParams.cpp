#pragma once

#include "GlobalParams.h"

GlobalParams::GlobalParams()
{
    this->DEFAULT_TICK_SPEED = 0;
    this->TICK_SPEED_DECREASE = 15;
    this->TICK_SPEED_CAP = 50;

    this->FONT_PATH = "./Fonts/OpenSans_VariableFont.ttf";
    this->FONT_SIZE = 20;
    this->GAME_OVER_FONT_SIZE = 64;
    this->GAME_WON_FONT_SIZE = 72;
    this->TEXT_COLOR =
    {
        .r = 255,
        .g = 255,
        .b = 255,
        .a = 100
    };

    this->RESTART_KEY = SDLK_r;

    this->TIME_ELAPSED_TXT = "Time Elapsed: ";
    this->COLLECTED_APPLES_TXT = "Apples Collected: ";

    this->PRESS_KEY_TO_RESTART_TXT =
        std::string("Press " + std::string(1, (char)RESTART_KEY)) + std::string(" to restart the game!!!");

    this->GAME_OVER_TXT = std::string("           Game Over :(\n") + PRESS_KEY_TO_RESTART_TXT;

    this->GAME_WON_TXT =
        std::string("YOU HAVE WON THE GAME !!!\n") +
        std::string("                     :)\n") + PRESS_KEY_TO_RESTART_TXT;

    this->GAME_TILESET_PATH = "./Images/snake_graphics_tileset.png";

    this->GAME_TILESET_W = 320;
    this->GAME_TILESET_H = 256;

    this->GAME_TILESET_TILE_W = 64;
    this->GAME_TILESET_TILE_H = 64;

    this->GAME_TILESET_ROWS_COUNT = GAME_TILESET_H / GAME_TILESET_TILE_H;
    this->GAME_TILESET_COLUMNS_COUNT = GAME_TILESET_W / GAME_TILESET_TILE_W;

    this->GAME_WINDOW_TITLE = "Snake Game";

    this->GAME_GRID_ROWS_COUNT = 8;
    this->GAME_GRID_COLS_COUNT = 8;

    //The GAME_WINDOW_X and GAME_WINDOW_Y are applied from both sides (left and right for X and up and down for Y)
    this->GAME_WINDOW_X = 180;
    this->GAME_WINDOW_Y = 95;
    this->GAME_WINDOW_W = 1200;
    this->GAME_WINDOW_H = 700;

    this->GAME_GRID_OFFSET_LEFT = 350;
    this->GAME_GRID_OFFSET_RIGHT = 350;
    this->GAME_GRID_OFFSET_UP = 100;
    this->GAME_GRID_OFFSET_DOWN = 100;

    this->GAME_GRID_LEFT_BORDER = GAME_GRID_OFFSET_LEFT;
    this->GAME_GRID_RIGHT_BORDER = GAME_WINDOW_W - GAME_GRID_OFFSET_RIGHT;
    this->GAME_GRID_UPPER_BORDER = GAME_GRID_OFFSET_UP;
    this->GAME_GRID_BOTTOM_BORDER = GAME_WINDOW_H - GAME_GRID_OFFSET_DOWN;

    this->GAME_GRID_W = GAME_GRID_RIGHT_BORDER - GAME_GRID_LEFT_BORDER;
    this->GAME_GRID_H = GAME_GRID_BOTTOM_BORDER - GAME_GRID_UPPER_BORDER;

    this->GAME_TILE_W = GAME_GRID_W / GAME_GRID_COLS_COUNT;
    this->GAME_TILE_H = GAME_GRID_H / GAME_GRID_ROWS_COUNT;

    this->EMPTY_TILE_COLOR =
    {
        .r = 81,
        .g = 53,
        .b = 97,
        .a = 100
    };

    this->TIME_ELAPSED_RECT =
    {
        .x = GAME_GRID_LEFT_BORDER - 100,
        .y = GAME_GRID_UPPER_BORDER - 100,
        .w = 200,
        .h = 50,
    };

    this->COLLECTED_APPLES_RECT =
    {
        .x = GAME_GRID_RIGHT_BORDER - 100,
        .y = GAME_GRID_UPPER_BORDER - 100,
        .w = 200,
        .h = 50,
    };

    this->GAME_OVER_RECT =
    {
        .x = (GAME_WINDOW_W - 600) / 2,
        .y = (GAME_WINDOW_H - 200) / 2,
        .w = 600,
        .h = 200,
    };

    this->GAME_WON_RECT =
    {
        .x = (GAME_WINDOW_W - 600) / 2,
        .y = (GAME_WINDOW_H - 200) / 2,
        .w = 600,
        .h = 200,
    };

    //DEFAULT SPAWN is measured from the tail and the default direction for the snake is facing towards the right
    this->SNAKE_DEFAULT_SPAWN = { 0, 0 };
    this->SNAKE_DEFAULT_LENGTH = 3;

    this->APPLE_DEFAULT_SPAWN = { GAME_GRID_ROWS_COUNT - 1, GAME_GRID_COLS_COUNT - 1 };

    // In the move dir vector, the first element shows what direction the button attempts to point us at
    // The second move dir tells us what is the opposite direction of that (i.e. we cannot do a 180 degree turn)
    this->KEY_TO_MOVE_MAP =
    {
        { SDLK_a, { MoveDir::LEFT, MoveDir::RIGHT } },
        { SDLK_LEFT, { MoveDir::LEFT, MoveDir::RIGHT } },
        { SDLK_d, { MoveDir::RIGHT, MoveDir::LEFT } },
        { SDLK_RIGHT, { MoveDir::RIGHT, MoveDir::LEFT } },
        { SDLK_w, { MoveDir::UP, MoveDir::DOWN } },
        { SDLK_UP, { MoveDir::UP, MoveDir::DOWN } },
        { SDLK_s, { MoveDir::DOWN, MoveDir::UP } },
        { SDLK_DOWN, {  MoveDir::DOWN, MoveDir::UP } },
    };

    this->AUTO_PLAY_ENABLED = true;
}

#pragma region OptionSetters

GlobalParams& GlobalParams::setDefaultTickSpeed(int val)
{
    this->DEFAULT_TICK_SPEED = val;
    return *this;
}

GlobalParams& GlobalParams::setTickSpeedDecrease(int val)
{
    this->TICK_SPEED_DECREASE = val;
    return *this;
}
GlobalParams& GlobalParams::setTickSpeedCap(int val)
{
    this->TICK_SPEED_CAP = val;
    return *this;
}

GlobalParams& GlobalParams::setFontPath(std::string path)
{
    this->FONT_PATH = path;
    return *this;
}

GlobalParams& GlobalParams::setFontSize(int size)
{
    this->FONT_SIZE = size;
    return *this;
}

GlobalParams& GlobalParams::setGameOverFontSize(int size)
{
    this->GAME_OVER_FONT_SIZE = size;
    return *this;
}

GlobalParams& GlobalParams::setGameWonFontSize(int size)
{
    this->GAME_WON_FONT_SIZE = size;
    return *this;
}

GlobalParams& GlobalParams::setTextColor(SDL_Color color)
{
    this->TEXT_COLOR = color;
    return *this;
}

GlobalParams& GlobalParams::setRestartKey(SDL_Keycode keycode)
{
    this->RESTART_KEY = keycode;
    return *this;
}

GlobalParams& GlobalParams::setTimeElapsedTxt(std::string text)
{
    this->TIME_ELAPSED_TXT = text;
    return *this;
}

GlobalParams& GlobalParams::setCollectedApplesTxt(std::string text)
{
    this->COLLECTED_APPLES_TXT = text;
    return *this;
}

GlobalParams& GlobalParams::setPressKeyToRestartTxt(std::string text)
{
    this->PRESS_KEY_TO_RESTART_TXT = text;
    return *this;
}

GlobalParams& GlobalParams::setGameOverTxt(std::string text)
{
    this->GAME_OVER_TXT = text;
    return *this;
}

GlobalParams& GlobalParams::setGameWonTxt(std::string text)
{
    this->GAME_WON_TXT = text;
    return *this;
}

GlobalParams& GlobalParams::setGameTilesetPath(std::string text)
{
    this->GAME_TILESET_PATH = text;
    return *this;
}

GlobalParams& GlobalParams::setGameTilesetWidth(int width)
{
    this->GAME_TILESET_W = width;
    return *this;
}

GlobalParams& GlobalParams::setGameTilesetHeight(int height)
{
    this->GAME_TILESET_H = height;
    return *this;
}

GlobalParams& GlobalParams::setGameTilesetTileWidth(int width)
{
    this->GAME_TILESET_TILE_W = width;
    return *this;
}

GlobalParams& GlobalParams::setGameTilesetTileHeight(int height)
{
    this->GAME_TILESET_TILE_H = height;
    return *this;
}

GlobalParams& GlobalParams::setGameTilesetRowsCount(int count)
{
    this->GAME_TILESET_ROWS_COUNT = count;
    return *this;
}

GlobalParams& GlobalParams::setGameTilesetColumnsCount(int count)
{
    this->GAME_TILESET_COLUMNS_COUNT = count;
    return *this;
}

GlobalParams& GlobalParams::setGameWindowTitle(std::string title)
{
    this->GAME_WINDOW_TITLE = title;
    return *this;
}

GlobalParams& GlobalParams::setGameGridRowsCount(int count)
{
    this->GAME_GRID_ROWS_COUNT = count;
    return *this;
}

GlobalParams& GlobalParams::setGameGridColumnsCount(int count)
{
    this->GAME_GRID_COLS_COUNT = count;
    return *this;
}

GlobalParams& GlobalParams::setGameWindowX(int x)
{
    this->GAME_WINDOW_X = x;
    return *this;
}

GlobalParams& GlobalParams::setGameWindowY(int y)
{
    this->GAME_WINDOW_Y = y;
    return *this;
}

GlobalParams& GlobalParams::setGameWindowWidth(int width)
{
    this->GAME_WINDOW_W = width;
    return *this;
}

GlobalParams& GlobalParams::setGameWindowHeight(int height)
{
    this->GAME_WINDOW_H = height;
    return *this;
}

GlobalParams& GlobalParams::setGameGridOffsetLeft(int offset)
{
    this->GAME_GRID_OFFSET_LEFT = offset;
    return *this;
}

GlobalParams& GlobalParams::setGameGridOffsetRight(int offset)
{
    this->GAME_GRID_OFFSET_RIGHT = offset;
    return *this;
}

GlobalParams& GlobalParams::setGameGridOffsetUp(int offset)
{
    this->GAME_GRID_OFFSET_UP = offset;
    return *this;
}

GlobalParams& GlobalParams::setGameGridOffsetDown(int offset)
{
    this->GAME_GRID_OFFSET_DOWN = offset;
    return *this;
}

GlobalParams& GlobalParams::setGameGridLeftBorder(int x)
{
    this->GAME_GRID_LEFT_BORDER = x;
    return *this;
}

GlobalParams& GlobalParams::setGameGridRightBorder(int x)
{
    this->GAME_GRID_RIGHT_BORDER = x;
    return *this;
}

GlobalParams& GlobalParams::setGameGridUpperBorder(int y)
{
    this->GAME_GRID_UPPER_BORDER = y;
    return *this;
}

GlobalParams& GlobalParams::setGameGridBottomBorder(int y)
{
    this->GAME_GRID_BOTTOM_BORDER = y;
    return *this;
}

GlobalParams& GlobalParams::setGameGridWidth(int width)
{
    this->GAME_GRID_W = width;
    return *this;
}

GlobalParams& GlobalParams::setGameGridHeight(int height)
{
    this->GAME_GRID_H = height;
    return *this;
}

GlobalParams& GlobalParams::setGameTileWidth(int width)
{
    this->GAME_TILE_W = width;
    return *this;
}

GlobalParams& GlobalParams::setGameTileHeight(int height)
{
    this->GAME_TILE_H = height;
    return *this;
}

GlobalParams& GlobalParams::setEmptyTileColor(SDL_Color color)
{
    this->EMPTY_TILE_COLOR = color;
    return *this;
}

GlobalParams& GlobalParams::setTimeElapsedRect(SDL_Rect rect)
{
    this->TIME_ELAPSED_RECT = rect;
    return *this;
}

GlobalParams& GlobalParams::setCollectedApplesRect(SDL_Rect rect)
{
    this->COLLECTED_APPLES_RECT = rect;
    return *this;
}

GlobalParams& GlobalParams::setGameOverRect(SDL_Rect rect)
{
    this->GAME_OVER_RECT = rect;
    return *this;
}

GlobalParams& GlobalParams::setSnakeDefaultSpawnPos(TilePos pos)
{
    this->SNAKE_DEFAULT_SPAWN = pos;
    return *this;
}

GlobalParams& GlobalParams::setSnakeDefaultLength(int length)
{
    this->SNAKE_DEFAULT_LENGTH = length;
    return *this;
}

GlobalParams& GlobalParams::setAppleDefaultSpawnPos(TilePos pos)
{
    this->APPLE_DEFAULT_SPAWN = pos;
    return *this;
}

GlobalParams& GlobalParams::setKeyToMoveMap(std::map<SDL_Keycode, std::vector<MoveDir>> map)
{
    this->KEY_TO_MOVE_MAP = map;
    return *this;
}

GlobalParams& GlobalParams::enableAutoPlay()
{
    this->AUTO_PLAY_ENABLED = true;
    return *this;
}

GlobalParams& GlobalParams::disableAutoPlay()
{
    this->AUTO_PLAY_ENABLED = false;
    return *this;
}

#pragma endregion