#pragma once

#include "SDL.h"
#include "TilePos.h"
#include <string>
#include "MoveDir.h"
#include <map>
#include <vector>
#include "Color.h"
#include "Rect.h"

class GlobalParams
{
public:
    int DEFAULT_TICK_SPEED;
    int TICK_SPEED_DECREASE;
    int TICK_SPEED_CAP;

    std::string FONT_PATH;
    int FONT_SIZE;
    int GAME_OVER_FONT_SIZE;
    int GAME_WON_FONT_SIZE;
    Color TEXT_COLOR;

    SDL_Keycode RESTART_KEY;

    std::string TIME_ELAPSED_TXT;
    std::string COLLECTED_APPLES_TXT;

    std::string PRESS_KEY_TO_RESTART_TXT;

    std::string GAME_OVER_TXT;

    std::string GAME_WON_TXT;

    std::string GAME_TILESET_PATH;

    int GAME_TILESET_W;
    int GAME_TILESET_H;

    int GAME_TILESET_TILE_W;
    int GAME_TILESET_TILE_H;

    int GAME_TILESET_ROWS_COUNT;
    int GAME_TILESET_COLUMNS_COUNT;

    std::string GAME_WINDOW_TITLE;

    int GAME_GRID_ROWS_COUNT;
    int GAME_GRID_COLS_COUNT;

    //The GAME_WINDOW_X and GAME_WINDOW_Y are applied from both sides (left and right for X and up and down for Y)
    int GAME_WINDOW_X;
    int GAME_WINDOW_Y;
    int GAME_WINDOW_W;
    int GAME_WINDOW_H;

    int GAME_GRID_OFFSET_LEFT;
    int GAME_GRID_OFFSET_RIGHT;
    int GAME_GRID_OFFSET_UP;
    int GAME_GRID_OFFSET_DOWN;

    int GAME_GRID_LEFT_BORDER;
    int GAME_GRID_RIGHT_BORDER;
    int GAME_GRID_UPPER_BORDER;
    int GAME_GRID_BOTTOM_BORDER;

    int GAME_GRID_W;
    int GAME_GRID_H;

    int GAME_TILE_W;
    int GAME_TILE_H;

    Color EMPTY_TILE_COLOR;

    Rect TIME_ELAPSED_RECT;

    Rect COLLECTED_APPLES_RECT;

    Rect GAME_OVER_RECT;

    Rect GAME_WON_RECT;

    //DEFAULT SPAWN is measured from the tail and the default direction for the snake is facing towards the right
    TilePos SNAKE_DEFAULT_SPAWN;
    int SNAKE_DEFAULT_LENGTH;

    TilePos APPLE_DEFAULT_SPAWN;

    // In the move dir vector, the first element shows what direction the button attempts to point us at
    // The second move dir tells us what is the opposite direction of that (i.e. we cannot do a 180 degree turn)
    std::map<SDL_Keycode, std::vector<MoveDir>> KEY_TO_MOVE_MAP;

    bool AUTO_PLAY_ENABLED;

    GlobalParams();

    bool operator==(const GlobalParams & other) const = default;

    GlobalParams& setDefaultTickSpeed(int val);
    GlobalParams& setTickSpeedDecrease(int val);
    GlobalParams& setTickSpeedCap(int val);
    GlobalParams& setFontPath(std::string path);
    GlobalParams& setFontSize(int size);
    GlobalParams& setGameOverFontSize(int size);
    GlobalParams& setGameWonFontSize(int size);
    GlobalParams& setTextColor(Color color);
    GlobalParams& setRestartKey(SDL_Keycode keycode);
    GlobalParams& setTimeElapsedTxt(std::string text);
    GlobalParams& setCollectedApplesTxt(std::string text);
    GlobalParams& setPressKeyToRestartTxt(std::string text);
    GlobalParams& setGameOverTxt(std::string text);
    GlobalParams& setGameWonTxt(std::string text);
    GlobalParams& setGameTilesetPath(std::string text);
    GlobalParams& setGameTilesetWidth(int width);
    GlobalParams& setGameTilesetHeight(int height);
    GlobalParams& setGameTilesetTileWidth(int width);
    GlobalParams& setGameTilesetTileHeight(int height);
    GlobalParams& setGameTilesetRowsCount(int count);
    GlobalParams& setGameTilesetColumnsCount(int count);
    GlobalParams& setGameWindowTitle(std::string title);
    GlobalParams& setGameGridRowsCount(int count);
    GlobalParams& setGameGridColumnsCount(int count);
    GlobalParams& setGameWindowX(int x);
    GlobalParams& setGameWindowY(int y);
    GlobalParams& setGameWindowWidth(int width);
    GlobalParams& setGameWindowHeight(int height);
    GlobalParams& setGameGridOffsetLeft(int offset);
    GlobalParams& setGameGridOffsetRight(int offset);
    GlobalParams& setGameGridOffsetUp(int offset);
    GlobalParams& setGameGridOffsetDown(int offset);

    GlobalParams& setGameGridLeftBorder(int x);
    GlobalParams& setGameGridRightBorder(int x);
    GlobalParams& setGameGridUpperBorder(int y);
    GlobalParams& setGameGridBottomBorder(int y);
    GlobalParams& setGameGridWidth(int width);
    GlobalParams& setGameGridHeight(int height);
    GlobalParams& setGameTileWidth(int width);
    GlobalParams& setGameTileHeight(int height);

    GlobalParams& setEmptyTileColor(Color color);

    GlobalParams& setTimeElapsedRect(Rect rect);
    GlobalParams& setCollectedApplesRect(Rect rect);
    GlobalParams& setGameOverRect(Rect rect);

    GlobalParams& setSnakeDefaultSpawnPos(TilePos pos);
    GlobalParams& setSnakeDefaultLength(int length);
    GlobalParams& setAppleDefaultSpawnPos(TilePos pos);
    GlobalParams& setKeyToMoveMap(std::map<SDL_Keycode, std::vector<MoveDir>> map);

    GlobalParams& enableAutoPlay();
    GlobalParams& disableAutoPlay();
};

//using GP = GlobalParams;
