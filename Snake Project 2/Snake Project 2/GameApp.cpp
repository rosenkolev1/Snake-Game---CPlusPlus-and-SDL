#include "GameApp.h"

GameApp::GameApp()
{
    //Memory leak test
    /*for (int i = 0; i < 100; i++) {
        GameUI gameUI = GameUI();
    }*/

    this->tickSpeed = 1000;

    //Initialize the grid



    for(int row = 0; row < GC::GAME_GRID_ROWS_COUNT; row++) 
    {
        this->grid.push_back(std::vector<Tile>());

        for (int col = 0; col < GC::GAME_GRID_COLS_COUNT; col++) 
        {
            this->grid[row].push_back(Tile(TilePos(row, col), true, false));
        }
    }

    this->gameUI = std::make_unique<GameUI>(GameUI());

    if (!gameUI->isValid())
    {
        exit(2);
    }

    for (int i = 0; i < 30; i++) 
    {
        gameUI->renderTick(this->grid);
        SDL_Delay(this->tickSpeed);
    }
}
    
