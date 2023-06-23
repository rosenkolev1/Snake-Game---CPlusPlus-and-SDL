#include "GameState.h"

GameState::GameState()
{
    this->curTimeElapsed = 0;
    this->lastGameOverTime = 0;
    this->gameWon = false;
    this->gameOver = false;
    this->processTick = true;
    this->snake = Snake(GC::SNAKE_DEFAULT_SPAWN);
    this->tickSpeed = GC::DEFAULT_TICK_SPEED;

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

    //Set the tile flags for the snake and for the apple
    this->applePosition = TilePos(GC::APPLE_DEFAULT_SPAWN);
    Tile& appleTile = this->grid[this->applePosition.row][this->applePosition.col];
    appleTile.isApple = true;

    for (int i = 0; i < snake.tiles.size() - 1; i++)
    {
        auto pos = snake.tiles[i];
        Tile& tile = this->grid[pos.row][pos.col];
        tile.isSnake = true;
        
        if (i == 0)
        {
            tile.snakeSprite = SnakeSprite::HEAD_RIGHT;
        }
        else if (i == GC::SNAKE_DEFAULT_LENGTH - 1)
        {
            tile.snakeSprite = SnakeSprite::TAIL_LEFT;
        }
        else tile.snakeSprite = SnakeSprite::BODY_HOR;
    }

    /*for (int col )*/

    /*Tile& snakeHeadTile = this->grid[this->snake.tiles[0].row][this->snake.tiles[0].col];
    Tile& snakeBodyTile = this->grid[this->snake.tiles[1].row][this->snake.tiles[1].col];
    Tile& snakeTailTile = this->grid[this->snake.tiles[2].row][this->snake.tiles[2].col];*/

    /*snakeHeadTile.isSnake = true;
    snakeBodyTile.isSnake = true;
    snakeTailTile.isSnake = true;

    snakeHeadTile.snakeSprite = SnakeSprite::HEAD_RIGHT;
    snakeBodyTile.snakeSprite = SnakeSprite::BODY_HOR;
    snakeTailTile.snakeSprite = SnakeSprite::TAIL_LEFT;*/
}
