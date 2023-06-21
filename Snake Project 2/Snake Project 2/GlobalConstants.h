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

    static const int GAME_GRID_X = 30;
    static const int GAME_GRID_Y = 30;

    static const int GAME_WINDOW_X = 100;
    static const int GAME_WINDOW_Y = 100;
    static const int GAME_WINDOW_W = 1000;
    static const int GAME_WINDOW_H = 700;
    
    static const int GAME_GRID_OFFSET_LEFT = 100;
    static const int GAME_GRID_OFFSET_RIGHT = 100;
    static const int GAME_GRID_OFFSET_UP = 100;
    static const int GAME_GRID_OFFSET_DOWN = 100;

    static const int GAME_TILE_W = (GAME_WINDOW_W - (GAME_GRID_OFFSET_LEFT + GAME_GRID_OFFSET_RIGHT)) / GAME_GRID_X;
    static const int GAME_TILE_H = (GAME_WINDOW_H - (GAME_GRID_OFFSET_UP + GAME_GRID_OFFSET_DOWN)) / GAME_GRID_Y;
};

using GC = GlobalConstants;
