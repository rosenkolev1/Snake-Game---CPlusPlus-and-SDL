#include "GameUI.h"
#include "GlobalConstants.h"
#include <sstream>

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

    if (!loadEmptyTile())
    {
        cerr << "Error loading the empty tile texture: " << SDL_GetError() << endl;
        return;
    }

    if (!loadTilesetTextures()) 
    {
        cerr << "Error loading the game textures: " << SDL_GetError() << endl;
        return;
    }

    //Initialize ttf library
    if (TTF_Init())
    {
        cerr << "Error initalizing the library: " << SDL_GetError() << endl;
        return;
    }

    //Set the font for the UI text
    if (!setTextFont())
    {
        cerr << "Error setting the text font: " << SDL_GetError() << endl;
        return;
    }

    //Initialize the snake sprites mape here
    this->SNAKE_SPRITE_TO_TEXTURE_MAP =
    {
        { SnakeSprite::NONE, this->emptyTile.get()},
        { SnakeSprite::HEAD_UP, this->snakeHeadUp.get() },
        { SnakeSprite::HEAD_RIGHT, this->snakeHeadRight.get() },
        { SnakeSprite::HEAD_DOWN, this->snakeHeadDown.get() },
        { SnakeSprite::HEAD_LEFT, this->snakeHeadLeft.get() },
        { SnakeSprite::BODY_HOR, this->snakeBodyHorizontal.get() },
        { SnakeSprite::BODY_VER, this->snakeBodyVertical.get() },
        { SnakeSprite::TAIL_UP, this->snakeTailUp.get() },
        { SnakeSprite::TAIL_RIGHT, this->snakeTailRight.get() },
        { SnakeSprite::TAIL_DOWN, this->snakeTailDown.get() },
        { SnakeSprite::TAIL_LEFT, this->snakeTailLeft.get() },
        { SnakeSprite::TURN_1, this->snakeTurn1.get() },
        { SnakeSprite::TURN_2, this->snakeTurn2.get() },
        { SnakeSprite::TURN_3, this->snakeTurn3.get() },
        { SnakeSprite::TURN_4, this->snakeTurn4.get() }
    };

    this->validState = true;
}

bool GameUI::loadEmptyTile()
{
    this->emptyTile = std::make_unique<sdl2::texture_ptr_t>(sdl2::createTexture(this->sdlRenderer->get(),
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, GC::GAME_TILE_W, GC::GAME_TILE_H));

    // Set target render to the needed texture
    SDL_SetRenderTarget(this->sdlRenderer->get(), this->emptyTile->get());

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = GC::GAME_TILE_W;
    rect.h = GC::GAME_TILE_H;

    this->renderEmptyTileOnCurrentRenderer();

    //Reset the renderer back to the screen
    SDL_SetRenderTarget(this->sdlRenderer->get(), NULL);

    SDL_RenderClear(this->sdlRenderer->get());

    return true;
}

bool GameUI::loadTileTexture(std::unique_ptr<sdl2::texture_ptr_t>& targetTexture, TilePos pos) 
{
    targetTexture = std::make_unique<sdl2::texture_ptr_t>(sdl2::createTexture(this->sdlRenderer->get(),
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, GC::GAME_TILE_W, GC::GAME_TILE_H));

    // Set target render to the needed texture
    SDL_SetRenderTarget(this->sdlRenderer->get(), targetTexture->get());

    //Add empty tile as background to the texture
    this->renderEmptyTileOnCurrentRenderer();

    SDL_Rect srcRect;
    srcRect.x = pos.col * GC::GAME_TILESET_TILE_W;
    srcRect.y = pos.row * GC::GAME_TILESET_TILE_H;
    srcRect.w = GC::GAME_TILESET_TILE_W;
    srcRect.h = GC::GAME_TILESET_TILE_H;

    //Draw on top of the current target texture, which should be an empty file
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

bool GameUI::loadText(std::unique_ptr<sdl2::texture_ptr_t>& targetTexture, std::string text, TTF_Font* font)
{
    sdl2::surf_ptr_t textSurface = sdl2::createText(font,
        text.c_str(), GC::TEXT_COLOR);

    if (!textSurface.get())
    {
        return false;
    }

    targetTexture = std::make_unique<sdl2::texture_ptr_t>(
        sdl2::createTextureFromSurface(this->sdlRenderer->get(), textSurface.get()));

    if (!targetTexture->get())
    {
        return false;
    }

    return true;
}

bool GameUI::loadTimeElapsedTexture(long curTime)
{
    long totalSeconds = curTime / 1000;
    long leftoverSeconds = totalSeconds % 60;
    long totalMinutes = (totalSeconds - leftoverSeconds) / 60;
    long leftoverMinutes = totalMinutes % 60;
    long leftoverHours = (totalMinutes - leftoverMinutes) / 60;

    std::string secondsString = leftoverSeconds < 10 ? "0" + std::to_string(leftoverSeconds) : std::to_string(leftoverSeconds);
    std::string minutesString = leftoverMinutes < 10 ? "0" + std::to_string(leftoverMinutes) : std::to_string(leftoverMinutes);

    std::stringstream stringStream;
    stringStream << leftoverHours << ':' << minutesString << ':' << secondsString;

    std::string timeStr = stringStream.str();

    sdl2::surf_ptr_t textSurface = sdl2::createText(this->textFont->get(), (GC::TIME_ELAPSED_TXT + timeStr).c_str(), GC::TEXT_COLOR);

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

bool GameUI::loadCollectedApplesTexture(long collectedApples)
{
    return this->loadText(this->collectedApplesTxt, GC::COLLECTED_APPLES_TXT + std::to_string(collectedApples), 
        this->textFont->get());
}

bool GameUI::loadGameOverTexture()
{
    auto fontPtr = sdl2::createFont(GC::FONT_PATH, GC::GAME_OVER_FONT_SIZE);

    return this->loadText(this->gameOverTxt, GC::GAME_OVER_TXT, fontPtr.get());
}

void GameUI::renderEmptyTileOnCurrentRenderer()
{
    //Add empty tile as background to the texture
    SDL_SetRenderDrawColor(this->sdlRenderer->get(),
        GC::EMPTY_TILE_COLOR.r,
        GC::EMPTY_TILE_COLOR.g,
        GC::EMPTY_TILE_COLOR.b,
        GC::EMPTY_TILE_COLOR.a);
    SDL_RenderFillRect(this->sdlRenderer->get(), NULL);
    SDL_SetRenderDrawColor(this->sdlRenderer->get(), 0, 0, 0, 100);
}

void GameUI::renderGridTile(const Tile& tile)
{
    ScreenPos screenPos = getScreenPosForTile(tile.tilePos);

    SDL_Rect dstRect;
    dstRect.x = screenPos.x;
    dstRect.y = screenPos.y;
    dstRect.w = GC::GAME_TILE_W;
    dstRect.h = GC::GAME_TILE_H;

    SDL_Texture* tileTexture = nullptr;

    if (tile.isApple)
    {
        tileTexture = this->apple->get();
    }
    else if (!tile.isSnake)
    {
        tileTexture = this->emptyTile->get();
    }
    else
    {
        tileTexture = this->SNAKE_SPRITE_TO_TEXTURE_MAP.find(tile.snakeSprite)->second->get();
    }

    SDL_RenderCopy(this->sdlRenderer->get(), tileTexture, NULL, &dstRect);
}

void GameUI::renderGrid(const std::vector<std::vector<Tile>>& grid)
{
    for (auto tilesRow : grid)
    {
        for (auto tile : tilesRow)
        {
            renderGridTile(tile);
        }
    }
}

void GameUI::renderTextUI(const GameState& state)
{
    //Load time elapsed texture
    if (!this->loadTimeElapsedTexture(SDL_GetTicks64()))
    {
        cerr << "Error loading the time elapsed texture: " << SDL_GetError() << endl;
        return;
    }

    SDL_RenderCopy(this->sdlRenderer->get(), this->timeElapsedTxt->get(), NULL, &GC::TIME_ELAPSED_RECT);

    //Load apples collected
    if (!this->loadCollectedApplesTexture(state.collectedApples))
    {
        cerr << "Error loading the collected apples texture: " << SDL_GetError() << endl;
        return;
    }

    SDL_RenderCopy(this->sdlRenderer->get(), this->collectedApplesTxt->get(), NULL, &GC::COLLECTED_APPLES_RECT);

    //Render game over text if game is over
    if (state.gameOver)
    {
        if (!this->loadGameOverTexture())
        {
            cerr << "Error loading the game over texture: " << SDL_GetError() << endl;
            return;
        }

        SDL_RenderCopy(this->sdlRenderer->get(), this->gameOverTxt->get(), NULL, &GC::GAME_OVER_RECT);
    }
}

void GameUI::renderTick(const GameState& gameState)
{
    SDL_RenderClear(this->sdlRenderer->get());

    //Render the grid
    this->renderGrid(gameState.grid);

    //Render the text UI
    this->renderTextUI(gameState);

    SDL_RenderPresent(this->sdlRenderer->get());
}

bool GameUI::isValid()
{
    return this->validState;
}

ScreenPos GameUI::getScreenPosForTile(const TilePos& pos)
{
    return ScreenPos(GC::GAME_GRID_LEFT_BORDER + GC::GAME_TILE_W * pos.col, GC::GAME_GRID_UPPER_BORDER + GC::GAME_TILE_H * pos.row);
}
