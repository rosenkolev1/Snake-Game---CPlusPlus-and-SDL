#include "GameApp.h"

GameApp::GameApp()
{
    //Memory leak test
    /*for (int i = 0; i < 100; i++) {
        GameUI gameUI = GameUI();
    }*/

    this->gameUI = std::make_unique<GameUI>(GameUI());

    if (!gameUI->isValid())
    {
        cerr << "Error initialising the game UI: " << SDL_GetError() << endl;
        exit(2);
    }

    this->lastTickEnd = 0;

    this->state = GameState();
}

Tile GameApp::getTile(TilePos pos)
{
    return this->state.grid[pos.row][pos.col];
}

void GameApp::startGameLoop()
{
    while (true)
    {
        long currentTime = SDL_GetTicks64();

        this->state.processTick = currentTime - this->lastTickEnd >= this->state.tickSpeed;

        //TODO: Add functionality for moving snake
        if (this->state.processTick) {

        }

        gameUI->renderTick(this->state);

        if (this->state.processTick)
        {
            this->state.processTick = false;
            this->lastTickEnd = SDL_GetTicks64();
        }

        /*SDL_Delay(this->tickSpeed);*/
    }
}
    
