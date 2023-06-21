#pragma once
#include <iostream>

#include "SDL.h"
#include <memory>
#include "SDL_image.h"
#include "sdl2.h"
#include <vector>
#include <map>
#include "TilePos.h"

using std::cerr;
using std::endl;

//using namespace sdl2;

class GameUI
{

private:

    //= "./Images/snake_graphics_tileset.png"
    static const char GAME_TILESET_PATH[100];

    const int GAME_TILESET_TILE_W = 64;
    const int GAME_TILESET_TILE_H = 64;

    //"Snake Game"
    static const char GAME_WINDOW_TITLE[100];

    //TODO: Move GAME_GRID constants to another class
    static const int GAME_GRID_X = 30;
    static const int GAME_GRID_Y = 30;

    static const int GAME_WINDOW_X = 100;
    static const int GAME_WINDOW_Y = 100;
    static const int GAME_WINDOW_W = 1000;
    static const int GAME_WINDOW_H = 700;

    static const int GAME_TILE_W = (GAME_WINDOW_W * 7 / 8) / GAME_GRID_X;
    static const int GAME_TILE_H = (GAME_WINDOW_H * 7 / 8) / GAME_GRID_Y;

    bool validState = false;

    sdl2::sdlsystem_ptr_t* sdlSystem = nullptr;
    sdl2::window_ptr_t* sdlWindow = nullptr;
    sdl2::renderer_ptr_t* sdlRenderer = nullptr;

    sdl2::surf_ptr_t* sdlSurface = nullptr;
    sdl2::texture_ptr_t* sdlTexture = nullptr;

    sdl2::texture_ptr_t* snakeHeadUp = nullptr;
    sdl2::texture_ptr_t* snakeHeadLeft = nullptr;
    sdl2::texture_ptr_t* snakeHeadRight = nullptr;
    sdl2::texture_ptr_t* snakeHeadDown = nullptr;

    sdl2::texture_ptr_t* snakeBodyHorizontal = nullptr;
    sdl2::texture_ptr_t* snakeBodyVertical = nullptr;

    sdl2::texture_ptr_t* snakeTurn1 = nullptr;
    sdl2::texture_ptr_t* snakeTurn2 = nullptr;
    sdl2::texture_ptr_t* snakeTurn3 = nullptr;
    sdl2::texture_ptr_t* snakeTurn4 = nullptr;

    sdl2::texture_ptr_t* snakeTailUp = nullptr;
    sdl2::texture_ptr_t* snakeTailLeft = nullptr;
    sdl2::texture_ptr_t* snakeTailRight = nullptr;
    sdl2::texture_ptr_t* snakeTailDown = nullptr;

    sdl2::texture_ptr_t* apple = nullptr;

    sdl2::texture_ptr_t* emptyTile = nullptr;
    
    bool loadTexture(sdl2::texture_ptr_t*& targetTexture, int x, int y);
    bool loadGameTextures();

public:
    GameUI();

    void startGameRender();
};

