#pragma once

#include "SDL.h"
#include "TilePos.h"
#include <string>
#include "MoveDir.h"
#include <map>
#include <vector>

class GlobalConstants
{
public:

    static const int DEFAULT_TICK_SPEED = 0;
    static const int TICK_SPEED_DECREASE = 15;
    static const int TICK_SPEED_CAP = 50;

    static const inline char FONT_PATH[] = "./Fonts/OpenSans_VariableFont.ttf";
    static const inline int FONT_SIZE = 20;
    static const inline int GAME_OVER_FONT_SIZE = 64;
    static const inline int GAME_WON_FONT_SIZE = 72;
    static const inline SDL_Color TEXT_COLOR = 
    { 
        .r = 255, 
        .g = 255,
        .b = 255,
        .a = 100
    };

    static const inline SDL_Keycode RESTART_KEY = SDLK_r;

    static const inline std::string TIME_ELAPSED_TXT = "Time Elapsed: ";
    static const inline std::string COLLECTED_APPLES_TXT = "Apples Collected: ";

    static const inline std::string PRESS_KEY_TO_RESTART_TXT = 
        std::string("Press " + std::string(1, (char)RESTART_KEY)) + std::string(" to restart the game!!!");

    static const inline std::string GAME_OVER_TXT = std::string("           Game Over :(\n") + PRESS_KEY_TO_RESTART_TXT;

    static const inline std::string GAME_WON_TXT = 
        std::string("YOU HAVE WON THE GAME !!!\n") + 
        std::string("                     :)\n") + PRESS_KEY_TO_RESTART_TXT;

    static const inline char GAME_TILESET_PATH[] = "./Images/snake_graphics_tileset.png";

    static const int GAME_TILESET_W = 320;
    static const int GAME_TILESET_H = 256;

    static const int GAME_TILESET_TILE_W = 64;
    static const int GAME_TILESET_TILE_H = 64;

    static const int GAME_TILESET_ROWS_COUNT = GAME_TILESET_H / GAME_TILESET_TILE_H;
    static const int GAME_TILESET_COLUMNS_COUNT = GAME_TILESET_W / GAME_TILESET_TILE_W;

    static const inline char GAME_WINDOW_TITLE[] = "Snake Game";

    static const int GAME_GRID_ROWS_COUNT = 30;
    static const int GAME_GRID_COLS_COUNT = 30;

    //The GAME_WINDOW_X and GAME_WINDOW_Y are applied from both sides (left and right for X and up and down for Y)
    static const int GAME_WINDOW_X = 180;
    static const int GAME_WINDOW_Y = 95;
    static const int GAME_WINDOW_W = 1200;
    static const int GAME_WINDOW_H = 700;

    static const int GAME_GRID_OFFSET_LEFT = 350;
    static const int GAME_GRID_OFFSET_RIGHT = 350;
    static const int GAME_GRID_OFFSET_UP = 100;
    static const int GAME_GRID_OFFSET_DOWN = 100;

    static const int GAME_GRID_LEFT_BORDER = GAME_GRID_OFFSET_LEFT;
    static const int GAME_GRID_RIGHT_BORDER = GAME_WINDOW_W - GAME_GRID_OFFSET_RIGHT;
    static const int GAME_GRID_UPPER_BORDER = GAME_GRID_OFFSET_UP;
    static const int GAME_GRID_BOTTOM_BORDER = GAME_WINDOW_H - GAME_GRID_OFFSET_DOWN;

    static const int GAME_GRID_W = GAME_GRID_RIGHT_BORDER - GAME_GRID_LEFT_BORDER;
    static const int GAME_GRID_H = GAME_GRID_BOTTOM_BORDER - GAME_GRID_UPPER_BORDER;

    static const int GAME_TILE_W = GAME_GRID_W / GAME_GRID_COLS_COUNT;
    static const int GAME_TILE_H = GAME_GRID_H / GAME_GRID_ROWS_COUNT;

    static const inline SDL_Color EMPTY_TILE_COLOR =
    {
        .r = 81,
        .g = 53,
        .b = 97,
        .a = 100
    };

    static const inline SDL_Rect TIME_ELAPSED_RECT = 
    {
        .x = GAME_GRID_LEFT_BORDER - 100,
        .y = GAME_GRID_UPPER_BORDER - 100,
        .w = 200,
        .h = 50,
    };

    static const inline SDL_Rect COLLECTED_APPLES_RECT =
    {
        .x = GAME_GRID_RIGHT_BORDER - 100,
        .y = GAME_GRID_UPPER_BORDER - 100,
        .w = 200,
        .h = 50,
    };

    static const inline SDL_Rect GAME_OVER_RECT =
    {
        .x = (GAME_WINDOW_W - 600) / 2,
        .y = (GAME_WINDOW_H - 200) / 2,
        .w = 600,
        .h = 200,
    };

    static const inline SDL_Rect GAME_WON_RECT =
    {
        .x = (GAME_WINDOW_W - 600) / 2,
        .y = (GAME_WINDOW_H - 200) / 2,
        .w = 600,
        .h = 200,
    };

    //DEFAULT SPAWN is measured from the tail and the default direction for the snake is facing towards the right
    static const inline TilePos SNAKE_DEFAULT_SPAWN = { 0, 0 };
    static const inline int SNAKE_DEFAULT_LENGTH = 6;

    static const inline TilePos APPLE_DEFAULT_SPAWN = { GAME_GRID_ROWS_COUNT - 1, GAME_GRID_COLS_COUNT - 1 };

    // In the move dir vector, the first element shows what direction the button attempts to point us at
    // The second move dir tells us what is the opposite direction of that (i.e. we cannot do a 180 degree turn)
    static const inline std::map<SDL_Keycode, std::vector<MoveDir>> KEY_TO_MOVE_MAP =
    {
        { SDLK_a, { MoveDir::Left, MoveDir::Right } },
        { SDLK_LEFT, { MoveDir::Left, MoveDir::Right } },
        { SDLK_d, { MoveDir::Right, MoveDir::Left } },
        { SDLK_RIGHT, { MoveDir::Right, MoveDir::Left } },
        { SDLK_w, { MoveDir::Up, MoveDir::Down } },
        { SDLK_UP, { MoveDir::Up, MoveDir::Down } },
        { SDLK_s, { MoveDir::Down, MoveDir::Up } },
        { SDLK_DOWN, {  MoveDir::Down, MoveDir::Up } },
    };
};

using GC = GlobalConstants;
