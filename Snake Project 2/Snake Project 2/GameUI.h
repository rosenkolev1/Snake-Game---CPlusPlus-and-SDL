#pragma once
#include <iostream>

#include "SDL.h"
#include <memory>
#include "SDL_image.h"
#include "sdl2.h"
#include <vector>
#include <map>
#include "TilePos.h"
#include "ScreenPos.h"
#include "Tile.h"
#include "SDL_ttf.h"
#include "GameState.h"
#include "GlobalParams.h"

using std::cerr;
using std::endl;

class GameUI
{

private:

    GlobalParams GP;

    bool validState = false;

    std::unique_ptr<sdl2::sdlsystem_ptr_t> sdlSystem = nullptr;
    std::unique_ptr<sdl2::window_ptr_t> sdlWindow = nullptr;
    std::unique_ptr<sdl2::renderer_ptr_t> sdlRenderer = nullptr;

    std::unique_ptr<sdl2::surf_ptr_t> sdlSurface = nullptr;
    std::unique_ptr<sdl2::texture_ptr_t> sdlTexture = nullptr;

    std::unique_ptr<sdl2::texture_ptr_t> snakeHeadUp = nullptr;
    std::unique_ptr<sdl2::texture_ptr_t> snakeHeadLeft = nullptr;
    std::unique_ptr<sdl2::texture_ptr_t> snakeHeadRight = nullptr;
    std::unique_ptr<sdl2::texture_ptr_t> snakeHeadDown = nullptr;

    std::unique_ptr<sdl2::texture_ptr_t> snakeBodyHorizontal = nullptr;
    std::unique_ptr<sdl2::texture_ptr_t> snakeBodyVertical = nullptr;

    std::unique_ptr<sdl2::texture_ptr_t> snakeTurn1 = nullptr;
    std::unique_ptr<sdl2::texture_ptr_t> snakeTurn2 = nullptr;
    std::unique_ptr<sdl2::texture_ptr_t> snakeTurn3 = nullptr;
    std::unique_ptr<sdl2::texture_ptr_t> snakeTurn4 = nullptr;

    std::unique_ptr<sdl2::texture_ptr_t> snakeTailUp = nullptr;
    std::unique_ptr<sdl2::texture_ptr_t> snakeTailLeft = nullptr;
    std::unique_ptr<sdl2::texture_ptr_t> snakeTailRight = nullptr;
    std::unique_ptr<sdl2::texture_ptr_t> snakeTailDown = nullptr;

    std::unique_ptr<sdl2::texture_ptr_t> apple = nullptr;

    std::unique_ptr<sdl2::texture_ptr_t> emptyTile = nullptr;

    std::unique_ptr<sdl2::font_ptr_t> textFont = nullptr;

    std::unique_ptr<sdl2::texture_ptr_t> timeElapsedTxt = nullptr;
    std::unique_ptr<sdl2::texture_ptr_t> collectedApplesTxt = nullptr;

    std::unique_ptr<sdl2::texture_ptr_t> gameOverTxt = nullptr;
    std::unique_ptr<sdl2::texture_ptr_t> gameWonTxt = nullptr;

    //Mapping the tiles of the tileset (the .png file) to their coordinates, so we can iterate through the coordinates and 
    //load all the textures one by one
    const std::map<TilePos, std::unique_ptr<sdl2::texture_ptr_t>&> TILESET_TILE_TO_TEXTURE_MAP = 
    {
        { TilePos(0, 0), this->snakeTurn1 },
        { TilePos(0, 1), this->snakeBodyHorizontal },
        { TilePos(0, 2), this->snakeTurn2 },
        { TilePos(0, 3), this->snakeHeadUp },
        { TilePos(0, 4), this->snakeHeadRight },

        { TilePos(1, 0), this->snakeTurn3 },
        { TilePos(1, 2), this->snakeBodyVertical },
        { TilePos(1, 3), this->snakeHeadLeft },
        { TilePos(1, 4), this->snakeHeadDown },

        { TilePos(2, 2), this->snakeTurn4 },
        { TilePos(2, 3), this->snakeTailDown },
        { TilePos(2, 4), this->snakeTailLeft },

        { TilePos(3, 0), this->apple },
        { TilePos(3, 3), this->snakeTailRight },
        { TilePos(3, 4), this->snakeTailUp },
    };

    //Mapping all of the possible snake sprite flags to the snake's textures
    std::map<SnakeSprite, sdl2::texture_ptr_t*> SNAKE_SPRITE_TO_TEXTURE_MAP;
    
    bool setTextFont();
    bool loadEmptyTile();
    bool loadTileTexture(std::unique_ptr<sdl2::texture_ptr_t>& targetTexture, TilePos pos);
    bool loadTilesetTextures();

    bool loadText(std::unique_ptr<sdl2::texture_ptr_t>& targetTexture, std::string text, TTF_Font* font);
    bool loadTimeElapsedTexture(long curTime);
    bool loadCollectedApplesTexture(long collectedApples);
    bool loadGameOverTexture();
    bool loadGameWonTexture();

    void renderEmptyTileOnCurrentRenderer();

    void renderGridTile(const Tile& tile);
    void renderGrid(const std::vector<std::vector<Tile>>& grid);
    void renderTextUI(const GameState& state);

public:
    GameUI(const GlobalParams& globalParams);

    void renderTick(const GameState& gameState);
    bool isValid();
    ScreenPos getScreenPosForTile(const TilePos& pos);
};

