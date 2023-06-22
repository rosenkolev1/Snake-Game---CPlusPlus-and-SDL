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
            this->grid[row].push_back(Tile(TilePos(row, col), false, false, SnakeSprite::NONE));
        }
    }

    this->collectedApples = 0;

    //TODO: Set the apple position randomly, as long as it is not on top of the snake tiles
    this->applePosition = TilePos(GC::APPLE_DEFAULT_SPAWN);

    //Set the tile flags for the snake and for the apple
    Tile& appleTile = this->grid[this->applePosition.row][this->applePosition.col];
    Tile& snakeTile = this->grid[this->snake.tiles[0].row][this->snake.tiles[0].col];

    appleTile.isApple = true;
    snakeTile.isSnake = true;
    snakeTile.snakeSprite = SnakeSprite::HEAD_RIGHT;
}
