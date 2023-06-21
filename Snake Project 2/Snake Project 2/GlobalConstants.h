#pragma once

class GlobalConstants
{
public:

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
};

using GC = GlobalConstants;
