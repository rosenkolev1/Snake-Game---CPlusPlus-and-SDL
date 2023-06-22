#include "GameState.h"

GameState::GameState()
{
    this->processTick = true;
    this->snake = Snake(GC::SNAKE_DEFAULT_SPAWN);
    this->tickSpeed = 1000;

    //Initialize the grid
    for (int row = 0; row < GC::GAME_GRID_ROWS_COUNT; row++)
    {
        this->grid.push_back(std::vector<Tile>());

        for (int col = 0; col < GC::GAME_GRID_COLS_COUNT; col++)
        {
            this->grid[row].push_back(Tile(TilePos(row, col), true, false));
        }
    }

    this->collectedApples = 0;

    //TODO: Set the apple position randomly
    this->applePosition = TilePos(GC::APPLE_DEFAULT_SPAWN);
}
