#include "GameUI.h"
#include "GlobalConstants.h"

GameUI::GameUI() 
{
    this->sdlSystem = std::make_unique<sdl2::sdlsystem_ptr_t>(sdl2::makeSdlSystem(SDL_INIT_EVERYTHING));
    if (!*this->sdlSystem) 
    {
        cerr << "Error creating SDL2 system: " << SDL_GetError() << endl;
        return;
    }

    this->sdlWindow = std::make_unique<sdl2::window_ptr_t>(sdl2::window_ptr_t(
        sdl2::makeWindow(GC::GAME_WINDOW_TITLE, GC::GAME_WINDOW_X, GC::GAME_WINDOW_Y, GC::GAME_WINDOW_W, GC::GAME_WINDOW_H,
        SDL_WINDOW_SHOWN)));

    if (!*this->sdlWindow) 
    {
        cerr << "Error creating window: " << SDL_GetError() << endl;
        return;
    }

    this->sdlRenderer = std::make_unique<sdl2::renderer_ptr_t>(sdl2::renderer_ptr_t(
        sdl2::makeRenderer(this->sdlWindow->get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)));
    if (!*this->sdlRenderer) 
    {
        cerr << "Error creating renderer: " << SDL_GetError() << endl;
        return;
    }

    this->sdlSurface = std::make_unique<sdl2::surf_ptr_t>(sdl2::surf_ptr_t(sdl2::makePng(GC::GAME_TILESET_PATH)));
    if (!*this->sdlSurface) 
    {
        cerr << "Error creating the game tileset surface: " << SDL_GetError() << endl;
        return;
    }

    this->sdlTexture = std::make_unique<sdl2::texture_ptr_t>(
        sdl2::texture_ptr_t(sdl2::makeTexture(this->sdlRenderer->get(), this->sdlSurface->get())));
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

    this->validState = true;
}

bool GameUI::loadTexture(std::unique_ptr<sdl2::texture_ptr_t>& targetTexture, TilePos pos) {

    targetTexture = std::make_unique<sdl2::texture_ptr_t>(sdl2::createTexture(this->sdlRenderer->get(),
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, GC::GAME_TILE_W, GC::GAME_TILE_H));

    // Set target render to the needed texture
    SDL_SetRenderTarget(this->sdlRenderer->get(), targetTexture->get());

    SDL_Rect srcRect;
    srcRect.x = pos.col * GC::GAME_TILESET_TILE_W;
    srcRect.y = pos.row * GC::GAME_TILESET_TILE_H;
    srcRect.w = GC::GAME_TILESET_TILE_W;
    srcRect.h = GC::GAME_TILESET_TILE_H;

    // Draw on top of the current target texture
    SDL_RenderCopy(this->sdlRenderer->get(), this->sdlTexture->get(), &srcRect, NULL);

    SDL_SetRenderTarget(this->sdlRenderer->get(), NULL);

    SDL_RenderClear(this->sdlRenderer->get());

    return true;
}

bool GameUI::loadGameTextures() {
    for (int row = 0; row < GC::GAME_TILESET_ROWS_COUNT; row++)
    {
        for (int col = 0; col < GC::GAME_TILESET_COLUMNS_COUNT; col++)
        {
            TilePos curTilePos = TilePos(row, col);
            auto targetTextureIt = this->TILESET_TILE_TO_TEXTURE_MAP.find(curTilePos);

            if (targetTextureIt != this->TILESET_TILE_TO_TEXTURE_MAP.end()) {
                bool valid = loadTexture(targetTextureIt->second, curTilePos);

                if (!valid)
                {
                    return false;
                }
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

        SDL_RenderCopy(this->sdlRenderer->get(), this->snakeHeadRight->get(), NULL, &dstRect);
        SDL_RenderPresent(this->sdlRenderer->get());
        SDL_Delay(1000);
    }
}

bool GameUI::isValid()
{
    return this->validState;
}
