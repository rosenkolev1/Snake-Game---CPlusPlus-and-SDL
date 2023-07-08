#pragma once

#include "GlobalParams.h"

GlobalParams::GlobalParams()
{
    //Default speed of a tick, after which the game moves the snake, updating its position
    this->DEFAULT_TICK_SPEED = 200;
    //How fast the speed of the snake decreases when eating apples
    this->TICK_SPEED_DECREASE = 15;
    //What is the maximum speed of the snake
    this->TICK_SPEED_CAP = 50;

    this->FONT_PATH = "./Fonts/OpenSans_VariableFont.ttf";
    this->FONT_SIZE = 20;

    this->GAME_OVER_FONT_SIZE = 64;
    this->GAME_WON_FONT_SIZE = 72;

    //Default color for all text in the game
    this->TEXT_COLOR = Color
    ({
        .r = 255,
        .g = 255,
        .b = 255,
        .a = 100
    });

    //What key is used to restart the game
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

    //The dimensions of the .png tileset file, from which the game gets its texture. You probably should not touch these
    this->GAME_TILESET_W = 320;
    this->GAME_TILESET_H = 256;

    //The dimensions of a single tile as measuer in pixel on the .png tileset file (not the size of the tiles in the game grid!)
    //Probably should not change these
    this->GAME_TILESET_TILE_W = 64;
    this->GAME_TILESET_TILE_H = 64;

    //The numbers of rows and columns of tiles in the .png tileset file
    //You probably should not change these
    this->GAME_TILESET_ROWS_COUNT = GAME_TILESET_H / GAME_TILESET_TILE_H;
    this->GAME_TILESET_COLUMNS_COUNT = GAME_TILESET_W / GAME_TILESET_TILE_W;

    //The title of the game window
    this->GAME_WINDOW_TITLE = "Snake Game";

    //The number of rows and cols of the grid
    this->GAME_GRID_ROWS_COUNT = 20;
    this->GAME_GRID_COLS_COUNT = 20;

    //The coordinates of the top-left position of the game screen
    //The GAME_WINDOW_X and GAME_WINDOW_Y seem to be applied twice for some reason.
    //In other words, if GAME_WINDOW_X = 180, then the screen appears 360 pixels away from the left edge of the computer screen
    //Hence why, if you are playing at a resolution at 1920x1080, then GAME_WINDOW_X = 180 with GAME_WINDOW_W makes the game screen
    //spawn in the middle of the computer screen horizontally
    this->GAME_WINDOW_X = 180;
    this->GAME_WINDOW_Y = 95;

    //The width and height of the screen
    this->GAME_WINDOW_W = 1200;
    this->GAME_WINDOW_H = 700;

    //The Offset of the in-game grid borders to the edges of the render screen
    this->GAME_GRID_OFFSET_LEFT = 350;
    this->GAME_GRID_OFFSET_RIGHT = 350;
    this->GAME_GRID_OFFSET_UP = 100;
    this->GAME_GRID_OFFSET_DOWN = 100;

    //The borders coordinates (in a single value x or y, where x is a horizontal line and y is a vertical line) of the in-game grid.
    //These are calculated automatically based on the grid offsets. You probably should not change these (although it will still work)
    this->GAME_GRID_LEFT_BORDER = GAME_GRID_OFFSET_LEFT;
    this->GAME_GRID_RIGHT_BORDER = GAME_WINDOW_W - GAME_GRID_OFFSET_RIGHT;
    this->GAME_GRID_UPPER_BORDER = GAME_GRID_OFFSET_UP;
    this->GAME_GRID_BOTTOM_BORDER = GAME_WINDOW_H - GAME_GRID_OFFSET_DOWN;

    //The in-game grid width and height. These are calculated automatically based on the grid borders. 
    //You probably should not change these.
    this->GAME_GRID_W = GAME_GRID_RIGHT_BORDER - GAME_GRID_LEFT_BORDER;
    this->GAME_GRID_H = GAME_GRID_BOTTOM_BORDER - GAME_GRID_UPPER_BORDER;

    //The dimensions of the grid tiles. These are calculated automatically based on the grid dimensions and count of rows and cols
    //The grid can be with however many rows and cols and with whatever absolute width and height 
    //and the game tiles will adjust accordingly. You probably should not change these.
    this->GAME_TILE_W = GAME_GRID_W / GAME_GRID_COLS_COUNT;
    this->GAME_TILE_H = GAME_GRID_H / GAME_GRID_ROWS_COUNT;

    //The color of an empty tile
    this->EMPTY_TILE_COLOR = Color
    ({
        .r = 81,
        .g = 53,
        .b = 97,
        .a = 100
    });

    //The text box of the Time Elapsed UI text
    this->TIME_ELAPSED_RECT = Rect
    ({
        .x = GAME_GRID_LEFT_BORDER - 100,
        .y = GAME_GRID_UPPER_BORDER - 100,
        .w = 200,
        .h = 50,
    });

    //The text box of the Collected Apples UI text
    this->COLLECTED_APPLES_RECT = Rect 
    ({
        .x = GAME_GRID_RIGHT_BORDER - 100,
        .y = GAME_GRID_UPPER_BORDER - 100,
        .w = 200,
        .h = 50,
    });

    //The text box of the Game Over text
    this->GAME_OVER_RECT = Rect
    ({
        .x = (GAME_WINDOW_W - 600) / 2,
        .y = (GAME_WINDOW_H - 200) / 2,
        .w = 600,
        .h = 200,
    });

    //The text box of the Game Won text
    this->GAME_WON_RECT = Rect
    ({
        .x = (GAME_WINDOW_W - 600) / 2,
        .y = (GAME_WINDOW_H - 200) / 2,
        .w = 600,
        .h = 200,
    });

    //Default spawn coordinates of the snake
    //DEFAULT SPAWN is measured from the tail and the default direction for the snake is facing towards the right
    //For example, a default spawn with x = 0 and y = 0 and snake length = 3 means that the coordinates of the snake are:
    //(0, 0) -> tail
    //(0, 1) -> body
    //(0, 2) -> head
    this->SNAKE_DEFAULT_SPAWN = { 0, 0 };

    //The spawn length of the snake. The length should be at least 3, otherwise it looks weird (but still functional).
    //The spawn length should also make it so that, in combination with the snake default spawn, the snake fits in the boundaries
    //of the grid. Otherwise, you will get a vector out of range exception probably.
    this->SNAKE_DEFAULT_LENGTH = 3;

    //The default spawn coordinates for the apple. Like the snake spawn coordinates, these should be withing the grid boundaries.
    this->APPLE_DEFAULT_SPAWN = { GAME_GRID_ROWS_COUNT - 1, GAME_GRID_COLS_COUNT - 1 };

    // Maps the keyboard keys to the direction in which they make you go and also the opposite of that direction.
    // In the move dir vector, the first element shows what direction the button attempts to point us at (for example, <--A, D-->).
    // The second move dir tells us what is the opposite direction of that. It is needed so that we can check if we are trying to 
    // Do a 180 degree turn (for example, the snake is moving left and we try turning right by pressing D)
    // You probably should not change these. Or at the very least, you should not change the MoveDir pairs
    // You can change the keybinsd. Just do not bind 2 things to the same button.
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

    //Determines whether or not the game auto plays itself with the snake following a Hamiltonian Cycle depending on the graph.
    // If the graph has odd rows and odd cols then auto play will throw an error if enabled, because there is no Hamiltonian Cycle;
    // If the game is auto playing, then the speed increase after each devoured apple is negated. 
    // The snake moves with DEFAULT_TICK_SPEED for the whole rest of the game.
    // Once the snake wins the game, you can restart with the r button, which will auto play the game once again. To disable autoplay,
    // You have to quit the game entrirely and disable auto play before starting again.
    // If you enable this, then you might want to change the DEFAULT_TICK_SPEED to 0, so the snake can move as fast as possible, 
    // because otherwise, even for small grids, it takes long before the snake can collect all the apples.
    this->AUTO_PLAY_ENABLED = false;
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

GlobalParams& GlobalParams::setTextColor(Color color)
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

GlobalParams& GlobalParams::setEmptyTileColor(Color color)
{
    this->EMPTY_TILE_COLOR = color;
    return *this;
}

GlobalParams& GlobalParams::setTimeElapsedRect(Rect rect)
{
    this->TIME_ELAPSED_RECT = rect;
    return *this;
}

GlobalParams& GlobalParams::setCollectedApplesRect(Rect rect)
{
    this->COLLECTED_APPLES_RECT = rect;
    return *this;
}

GlobalParams& GlobalParams::setGameOverRect(Rect rect)
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