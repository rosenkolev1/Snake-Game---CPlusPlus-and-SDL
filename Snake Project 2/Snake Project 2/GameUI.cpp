#include "GameUI.h"

const char GameUI::GAME_TILESET_PATH[100] = "./Images/snake_graphics_tileset.png";
const char GameUI::GAME_WINDOW_TITLE[100] = "Snake Game";

GameUI::GameUI() 
{
    this->sdlSystem = new sdl2::sdlsystem_ptr_t(sdl2::make_sdlsystem(SDL_INIT_EVERYTHING));
    if (!*this->sdlSystem) 
    {
        cerr << "Error creating SDL2 system: " << SDL_GetError() << endl;
        return;
    }

    this->sdlWindow = new sdl2::window_ptr_t(
        sdl2::makeWindow(GAME_WINDOW_TITLE, GAME_WINDOW_X, GAME_WINDOW_Y, GAME_WINDOW_W, GAME_WINDOW_H,
        SDL_WINDOW_SHOWN));

    if (!*this->sdlWindow) 
    {
        cerr << "Error creating window: " << SDL_GetError() << endl;
        return;
    }

    this->sdlRenderer = new sdl2::renderer_ptr_t(
        sdl2::makeRenderer(this->sdlWindow->get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if (!*this->sdlRenderer) 
    {
        cerr << "Error creating renderer: " << SDL_GetError() << endl;
        return;
    }

    /**this->sdlSurface = sdl2::make_png(GAME_TILESET_PATH);

    if (!*this->sdlSurface) {
        cerr << "Error creating surface: " << SDL_GetError() << endl;
        return;
    }*/

    this->sdlSurface = new sdl2::surf_ptr_t(sdl2::makePng(this->GAME_TILESET_PATH));
    if (!*this->sdlSurface) 
    {
        cerr << "Error creating the game tileset surface: " << SDL_GetError() << endl;
        return;
    }

    this->sdlTexture = new sdl2::texture_ptr_t(sdl2::makeTexture(this->sdlRenderer->get(), this->sdlSurface->get()));
    if (!*this->sdlTexture) 
    {
        cerr << "Error creating texture: " << SDL_GetError() << endl;
        return;
    }

    if (!loadGameTextures()) 
    {
        cerr << "Error creating the game tileset surface: " << SDL_GetError() << endl;
        return;
    }

    //this->snakeBodyHorizontal = sdl2::createTextureNew(this->sdlRenderer->get(),
    //    SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, GAME_TILE_W, GAME_TILE_H);

    //// Set target render to the needed texture
    //SDL_SetRenderTarget(this->sdlRenderer->get(), this->snakeBodyHorizontal->get());

    //SDL_Rect srcRect;
    //srcRect.x = 64;
    //srcRect.y = 0;
    //srcRect.w = GAME_TILESET_TILE_W;
    //srcRect.h = GAME_TILESET_TILE_H;

    //// Draw ontop of the current target texture
    //SDL_RenderCopy(this->sdlRenderer->get(), this->sdlTexture->get(), &srcRect, NULL);

    //SDL_SetRenderTarget(this->sdlRenderer->get(), NULL);

    //SDL_RenderClear(this->sdlRenderer->get());

    //validState = true;
}

bool GameUI::loadTexture(sdl2::texture_ptr_t*& targetTexture, int x, int y) {

    targetTexture = sdl2::createTextureNew(this->sdlRenderer->get(),
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, GAME_TILE_W, GAME_TILE_H);

    // Set target render to the needed texture
    SDL_SetRenderTarget(this->sdlRenderer->get(), targetTexture->get());

    SDL_Rect srcRect;
    srcRect.x = x * GAME_TILESET_TILE_W;
    srcRect.y = y * GAME_TILESET_TILE_H;
    srcRect.w = GAME_TILESET_TILE_W;
    srcRect.h = GAME_TILESET_TILE_H;

    // Draw on top of the current target texture
    SDL_RenderCopy(this->sdlRenderer->get(), this->sdlTexture->get(), &srcRect, NULL);

    SDL_SetRenderTarget(this->sdlRenderer->get(), NULL);

    SDL_RenderClear(this->sdlRenderer->get());

    return true;
}

bool GameUI::loadGameTextures() {
    for (int x = 0; x < 5; x++) 
    {
        for (int y = 0; y < 4; y++) 
        {
            bool valid = false;

            if (x == 0 && y == 0) 
            {
                valid = loadTexture(this->snakeTurn1, x, y);
            }

            if (!valid)
            {
                return false;
            }
        }
    }

    return true;
}

void GameUI::startGameRender() 
{
    for (int i = 0; i < 20; i++) 
    {
        SDL_RenderClear(this->sdlRenderer->get());

        SDL_Rect dstRect;
        dstRect.x = 0 + i * 10;
        dstRect.y = 300;
        dstRect.w = 10;
        dstRect.h = 10;

        SDL_RenderCopy(this->sdlRenderer->get(), this->snakeTurn1->get(), NULL, &dstRect);
        SDL_RenderPresent(this->sdlRenderer->get());
        SDL_Delay(1000);
    }
}