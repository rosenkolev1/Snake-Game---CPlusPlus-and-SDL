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
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)));

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
        cerr << "Error loading the texture tileset: " << SDL_GetError() << endl;
        return;
    }

    if (!loadGameTextures()) 
    {
        cerr << "Error loading the game textures: " << SDL_GetError() << endl;
        return;
    }

    if (!loadEmptyTile()) 
    {
        cerr << "Error loading the empty tile texture: " << SDL_GetError() << endl;
        return;
    }

    this->validState = true;
}

bool GameUI::loadEmptyTile()
{
    this->emptyTile = std::make_unique<sdl2::texture_ptr_t>(sdl2::createTexture(this->sdlRenderer->get(),
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, GC::GAME_TILE_W, GC::GAME_TILE_H));

    // Set target render to the needed texture
    SDL_SetRenderTarget(this->sdlRenderer->get(), this->emptyTile->get());

    //Set the draw color
    SDL_SetRenderDrawColor(this->sdlRenderer->get(), 81, 53, 97, 100);

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = GC::GAME_TILE_W;
    rect.h = GC::GAME_TILE_H;

    // Draw on top of the current target texture
    //SDL_RenderDrawRect(this->sdlRenderer->get(), &rect);

    SDL_RenderFillRect(this->sdlRenderer->get(), NULL);

    //Reset the renderer back to the screen
    SDL_SetRenderTarget(this->sdlRenderer->get(), NULL);

    //Set the draw color
    SDL_SetRenderDrawColor(this->sdlRenderer->get(), 0, 0, 0, 100);

    SDL_RenderClear(this->sdlRenderer->get());

    return true;
}

bool GameUI::loadTexture(std::unique_ptr<sdl2::texture_ptr_t>& targetTexture, TilePos pos) 
{
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

bool GameUI::loadGameTextures() 
{
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

void GameUI::renderTick(const std::vector<std::vector<Tile>>& grid)
{
    SDL_RenderClear(this->sdlRenderer->get());

    for (auto tilesRow : grid) 
    {
        for (auto tile : tilesRow) 
        {
            ScreenPos screenPos = getScreenPosForTile(tile.getPos());

            SDL_Rect dstRect;
            dstRect.x = screenPos.x;
            dstRect.y = screenPos.y;
            dstRect.w = GC::GAME_TILE_W;
            dstRect.h = GC::GAME_TILE_H;

            SDL_RenderCopy(this->sdlRenderer->get(), this->emptyTile->get(), NULL, &dstRect);
        }
    }

    SDL_RenderPresent(this->sdlRenderer->get());
}

bool GameUI::isValid()
{
    return this->validState;
}

ScreenPos GameUI::getScreenPosForTile(TilePos pos)
{
    return ScreenPos(GC::GAME_GRID_LEFT_BORDER + GC::GAME_TILE_W * pos.col, GC::GAME_GRID_UPPER_BORDER + GC::GAME_TILE_H * pos.row);
}
