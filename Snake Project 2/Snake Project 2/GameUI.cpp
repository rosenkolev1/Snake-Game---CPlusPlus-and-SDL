#include "GameUI.h"
#include "GlobalConstants.h"

GameUI::GameUI() 
{
    this->sdlSystem = std::make_unique<sdl2::sdlsystem_ptr_t>(sdl2::createSdlSystem(SDL_INIT_EVERYTHING));
    if (!*this->sdlSystem) 
    {
        cerr << "Error creating SDL2 system: " << SDL_GetError() << endl;
        return;
    }

    this->sdlWindow = std::make_unique<sdl2::window_ptr_t>(sdl2::window_ptr_t(
        sdl2::createWindow(GC::GAME_WINDOW_TITLE, GC::GAME_WINDOW_X, GC::GAME_WINDOW_Y, GC::GAME_WINDOW_W, GC::GAME_WINDOW_H,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)));

    if (!*this->sdlWindow) 
    {
        cerr << "Error creating window: " << SDL_GetError() << endl;
        return;
    }

    this->sdlRenderer = std::make_unique<sdl2::renderer_ptr_t>(sdl2::renderer_ptr_t(
        sdl2::createRenderer(this->sdlWindow->get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)));
    if (!*this->sdlRenderer) 
    {
        cerr << "Error creating renderer: " << SDL_GetError() << endl;
        return;
    }

    this->sdlSurface = std::make_unique<sdl2::surf_ptr_t>(sdl2::surf_ptr_t(sdl2::createPng(GC::GAME_TILESET_PATH)));
    if (!*this->sdlSurface) 
    {
        cerr << "Error creating the game tileset surface: " << SDL_GetError() << endl;
        return;
    }

    this->sdlTexture = std::make_unique<sdl2::texture_ptr_t>(
        sdl2::texture_ptr_t(sdl2::createTextureFromSurface(this->sdlRenderer->get(), this->sdlSurface->get())));
    if (!*this->sdlTexture) 
    {
        cerr << "Error loading the texture tileset: " << SDL_GetError() << endl;
        return;
    }

    if (!loadTilesetTextures()) 
    {
        cerr << "Error loading the game textures: " << SDL_GetError() << endl;
        return;
    }

    if (!loadEmptyTile()) 
    {
        cerr << "Error loading the empty tile texture: " << SDL_GetError() << endl;
        return;
    }

    //Initialize ttf library
    if (TTF_Init())
    {
        cerr << "Error initalizing the library: " << SDL_GetError() << endl;
        return;
    }

    if (!setTextFont())
    {
        cerr << "Error setting the text font: " << SDL_GetError() << endl;
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

    //Reset the draw color
    SDL_SetRenderDrawColor(this->sdlRenderer->get(), 0, 0, 0, 100);

    SDL_RenderClear(this->sdlRenderer->get());

    return true;
}

bool GameUI::loadTileTexture(std::unique_ptr<sdl2::texture_ptr_t>& targetTexture, TilePos pos) 
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

bool GameUI::loadTilesetTextures() 
{
    for (int row = 0; row < GC::GAME_TILESET_ROWS_COUNT; row++)
    {
        for (int col = 0; col < GC::GAME_TILESET_COLUMNS_COUNT; col++)
        {
            TilePos curTilePos = TilePos(row, col);
            auto targetTextureIt = this->TILESET_TILE_TO_TEXTURE_MAP.find(curTilePos);

            if (targetTextureIt != this->TILESET_TILE_TO_TEXTURE_MAP.end()) {
                bool valid = loadTileTexture(targetTextureIt->second, curTilePos);

                if (!valid)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool GameUI::setTextFont()
{
    this->textFont = std::make_unique<sdl2::font_ptr_t>(sdl2::createFont(GC::FONT_PATH, GC::FONT_SIZE));

    //Check for validity
    if (!textFont->get()) 
    {
        return false;
    }

    return true;
}

bool GameUI::loadTimeElapsedTexture(long curTime)
{
    //TODO: Add logic for parsing the time from miliseconds to a hh:mm::ss format
    sdl2::surf_ptr_t textSurface = sdl2::createText(this->textFont->get(), (GC::TIME_ELAPSED_TXT + "2").c_str(), GC::TEXT_COLOR);

    if (!textSurface.get())
    {
        return false;
    }

    this->timeElapsedTxt = std::make_unique<sdl2::texture_ptr_t>(
        sdl2::createTextureFromSurface(this->sdlRenderer->get(), textSurface.get()));

    if (!this->timeElapsedTxt->get())
    {
        return false;
    }

    return true;
}

void GameUI::renderGrid(const std::vector<std::vector<Tile>>& grid)
{
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
}

void GameUI::renderTextUI(int collectedApples)
{
    if (!this->loadTimeElapsedTexture(SDL_GetTicks64()))
    {
        cerr << "Error loading the time elapsed texture: " << SDL_GetError() << endl;
        return;
    }

    SDL_RenderCopy(this->sdlRenderer->get(), this->timeElapsedTxt->get(), NULL, &GC::TIME_ELAPSED_RECT);
}

void GameUI::renderTick(const std::vector<std::vector<Tile>>& grid, int collectedApples)
{
    SDL_RenderClear(this->sdlRenderer->get());

    //Render the grid
    this->renderGrid(grid);

    //Render the text UI
    this->renderTextUI(collectedApples);

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
