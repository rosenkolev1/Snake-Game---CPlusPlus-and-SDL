#include "GameApp.h"
#include <stack>
#include <random>

GameApp::GameApp(const GlobalParams& globalParams)
    :GP(globalParams),
    state(this->GP)
{
    //Memory leak test
    /*for (int i = 0; i < 1000; i++) {
        GameUI gameUI = GameUI();
    }*/

    this->gameUI = std::make_unique<GameUI>(GameUI(this->GP));

    if (!gameUI->isValid())
    {
        cerr << "Error initialising the game UI: " << SDL_GetError() << endl;
        exit(2);
    }

    //this->state = GameState(this->GP);

    this->resetGameState();

    this->hamiltonianCounter = 0;

    if (this->GP.AUTO_PLAY_ENABLED && this->hamiltonianCycle.empty())
    {
        if (this->GP.GAME_GRID_ROWS_COUNT % 2 == 0)
        {
            this->hamiltonianCycle = this->getHamiltonianCycleForEvenRows();
        }
        else if (this->GP.GAME_GRID_ROWS_COUNT % 2 == 1 && this->GP.GAME_GRID_COLS_COUNT % 2 == 0)
        {
            this->hamiltonianCycle = this->getHamiltonianCycleForEvenCols();
        }
        else
        {
            cerr << "Error! The graphs rows and columns are both uneven, there is no Hamilton Cycle!\n" << 
                "Disable autoplay or change grid dimensions!: " << endl;
            exit(2);
        }
    }
}

Tile& GameApp::getTile(TilePos pos)
{
    return this->state.grid[pos.row][pos.col];
}

void GameApp::startGameLoop()
{
    while (true)
    {
        bool previouslyGameOver = this->state.gameOver;
        bool previouslyGameWon = this->state.gameWon;

        long currentTime = SDL_GetTicks64();

        this->state.processTick = currentTime - this->lastTickEnd >= this->state.tickSpeed;

        if (this->state.processTick && !this->state.gameOver && !this->state.gameWon) 
        {
            SDL_Event keyboardEvent;

            MoveDir snakeNewDir = this->state.snake.curDirection;

            while (SDL_PollEvent(&keyboardEvent))
            {
                if (keyboardEvent.type == SDL_KEYDOWN)
                {
                    auto keyIt = this->GP.KEY_TO_MOVE_MAP.find(keyboardEvent.key.keysym.sym); 

                    if (keyIt != this->GP.KEY_TO_MOVE_MAP.end())
                    {
                        if (std::count(keyIt->second.begin(), keyIt->second.end(), this->state.snake.curDirection) == 0)
                        {
                            snakeNewDir = keyIt->second[0];
                        }
                    }                    
                }
            }

            this->state.snake.curDirection = snakeNewDir;

            if (this->GP.AUTO_PLAY_ENABLED)
            {
                auto nextTile = this->hamiltonianCycle[this->hamiltonianCounter++];
                this->hamiltonianCounter %= this->hamiltonianCycle.size();
                this->state.snake.curDirection = this->determineDirection(this->state.snake.getHead(), nextTile);
            }

            this->moveSnake();
        }
        else if (this->state.gameOver || this->state.gameWon)
        {
            SDL_Event keyboardEvent;

            while (SDL_PollEvent(&keyboardEvent))
            {
                if (keyboardEvent.type == SDL_KEYDOWN && keyboardEvent.key.keysym.sym == this->GP.RESTART_KEY)
                {
                    this->resetGameState();
                }
            }
        }

        if (!previouslyGameOver && this->state.gameOver || 
            !previouslyGameWon  && this->state.gameWon)
        {
            this->state.lastGameOverTime = SDL_GetTicks64() - this->state.lastGameOverTime;
        }

        this->state.curTimeElapsed = !(state.gameOver || state.gameWon) 
            ? SDL_GetTicks64() - state.lastGameOverTime : state.lastGameOverTime;

        gameUI->renderTick(this->state);

        //Exit the game after 5 seconds of death screen
        if ((this->state.gameOver || this->state.gameWon) && currentTime - this->lastTickEnd > 5000)
        {
            exit(0);
        }

        if (this->state.processTick && !(this->state.gameOver || this->state.gameWon))
        {
            this->state.processTick = false;
            this->lastTickEnd = SDL_GetTicks64();
        }
    }
}

bool GameApp::isOutOfBounds(TilePos pos)
{
    return pos.row < 0 || pos.row >= this->state.grid.size() || 
           pos.col < 0 || pos.col >= this->state.grid[0].size();
}

void GameApp::resetGameState()
{
    this->lastTickEnd = 0;

    this->state = GameState(this->GP);

    //Spawn the apple randomly
    this->replaceRandomApple();

    this->state.lastGameOverTime = SDL_GetTicks64();

    this->hamiltonianCounter = 0;
}

std::vector<TilePos> GameApp::getHamiltonianCycleForEvenCols()
{
    std::vector<TilePos> optimalMoves = std::vector<TilePos>();

    //First row except the first couple of tiles
    for (int col = this->GP.SNAKE_DEFAULT_LENGTH; col < this->GP.GAME_GRID_COLS_COUNT; col++)
    {
        optimalMoves.push_back({ 0, col });
    }

    //Almost everything else
    for (int col = this->GP.GAME_GRID_COLS_COUNT - 1; col >= 0; col--)
    {
        if (col % 2 == 0)
        {
            for (int row = this->GP.GAME_GRID_ROWS_COUNT - 1; row >= 1; row--)
            {
                optimalMoves.push_back({ row, col });
            }
        }
        else
        {
            for (int row = 1; row < this->GP.GAME_GRID_ROWS_COUNT; row++)
            {
                optimalMoves.push_back({ row, col });
            }
        }
    }

    //First couple of tiles on the first row
    for (int col = 0; col < this->GP.SNAKE_DEFAULT_LENGTH; col++)
    {
        optimalMoves.push_back({ 0, col });
    }

    return optimalMoves;
}

std::vector<TilePos> GameApp::getHamiltonianCycleForEvenRows()
{
    std::vector<TilePos> optimalMoves = std::vector<TilePos>();

    //First row except the first couple of tiles
    for (int col = this->GP.SNAKE_DEFAULT_LENGTH; col < this->GP.GAME_GRID_COLS_COUNT; col++)
    {
        optimalMoves.push_back({ 0, col });
    }

    //Last col
    for (int row = 1; row < this->GP.GAME_GRID_ROWS_COUNT; row++)
    {
        optimalMoves.push_back({ row, this->GP.GAME_GRID_COLS_COUNT - 1 });
    }

    //Almost everything else
    for (int row = this->GP.GAME_GRID_ROWS_COUNT - 1; row >= 1; row--)
    {
        if (row % 2 == 0)
        {
            for (int col = 0; col < this->GP.GAME_GRID_COLS_COUNT - 1; col++)
            {
                optimalMoves.push_back({ row, col });
            }
        }
        else
        {
            for (int col = this->GP.GAME_GRID_COLS_COUNT - 2; col >= 0; col--)
            {
                optimalMoves.push_back({ row, col });
            }
        }
    }

    //First couple tiles on the first row
    for (int col = 0; col < this->GP.SNAKE_DEFAULT_LENGTH; col++)
    {
        optimalMoves.push_back({ 0, col });
    }

    return optimalMoves;
}

void GameApp::replaceRandomApple()
{
    this->getTile(this->state.applePosition).isApple = false;

    Snake& snake = this->state.snake;
    std::vector<TilePos> possibleTiles = std::vector<TilePos>();

    TilePos inFrontOfHead = snake.getHead() + Snake::MOVE_OFFSET_MAP.at(snake.curDirection);

    for (int row = 0; row < this->state.grid.size(); row++)
    {
        for (int col = 0; col < this->state.grid[0].size(); col++)
        {
            TilePos cur = { row, col };

            if (std::count(snake.tiles.begin(), snake.tiles.end() - 1, cur) == 0 &&
                inFrontOfHead != cur)
            {
                possibleTiles.push_back(cur);
            }
        }
    }

    //In this case, the snake takes up all but one of the tiles, that being the tile right in front of its head,
    //So the player is about to beat the game and the last apple has to spawn in front of the head
    if (possibleTiles.size() == 0)
    {
        this->state.applePosition = inFrontOfHead;
        return;
    }

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, possibleTiles.size() - 1); // define the range

    int randomIndex = distr(gen);

    this->state.applePosition = possibleTiles[randomIndex];
    this->getTile(this->state.applePosition).isApple = true;
}

void GameApp::decreaseTickSpeed()
{
    if (!this->GP.AUTO_PLAY_ENABLED)
    {
        this->state.tickSpeed -= this->GP.TICK_SPEED_DECREASE;

        if (this->state.tickSpeed < this->GP.TICK_SPEED_CAP) this->state.tickSpeed = this->GP.TICK_SPEED_CAP;
    }
}

bool GameApp::moveSnake()
{
    Snake& snake = this->state.snake;

    TilePos newHeadPos = snake.tiles.front() + Snake::MOVE_OFFSET_MAP.at(snake.curDirection);

    //If the snake tries to go out of bounds, kill it
    if (this->isOutOfBounds(newHeadPos))
    {
        this->state.gameOver = true;
        return false;
    }

    Tile& newSnakeHead = this->getTile(newHeadPos);

    bool devouredApple = newHeadPos == this->state.applePosition;

    if (devouredApple)
    {
        this->state.collectedApples++;

        //In this case, the player has won the game and collected all apples
        if (this->state.collectedApples + this->GP.SNAKE_DEFAULT_LENGTH == this->GP.GAME_GRID_ROWS_COUNT * this->GP.GAME_GRID_COLS_COUNT)
        {
            this->state.gameWon = true;
        }
        else
        {
            //Spawn a new apple at random position
            this->replaceRandomApple();
        }

        //Change the tick speed
        this->decreaseTickSpeed();

        auto& newTail = this->getTile(snake.tiles.back());
        auto& oldTail = this->getTile(snake.getTail());

        newTail.isSnake = true;

        //Add a new 'invisible training tile'
        snake.tiles.push_back(snake.tiles.back());
    }

    //Check if the snake hits itself.
    if (std::count(snake.tiles.begin(), snake.tiles.end() - 1, newHeadPos) > 0)
    {
        if (!(snake.tiles.back() == newHeadPos && devouredApple) &&
            !(snake.getTail() == newHeadPos && !devouredApple))
        {
            this->state.gameOver = true;
            return false;
        }
    }

    this->getTile(snake.getTail()).isSnake = false;
    
    newSnakeHead.isSnake = true;
    newSnakeHead.isApple = false;

    //Change all the tile positions from the tail to the head
    for (int i = snake.tiles.size() - 1; i >= 1; i--)
    {
        snake.tiles[i] = snake.tiles[i - 1];
    }

    //Set proper head pos
    snake.tiles[0] = newHeadPos;

    //Determine head sprite
    newSnakeHead.snakeSprite = this->getSnakeHeadSprite(snake.curDirection);

    MoveDir toDir = snake.curDirection;

    //Determine all the other sprites
    for (int i = 1; i < snake.tiles.size() - 2; i++)
    {
        MoveDir fromDir = this->determineDirection(snake.tiles[i + 1], snake.tiles[i]);
        auto newSnakeSprite = this->getSnakeSprite(fromDir, toDir);
        this->getTile(snake.tiles[i]).snakeSprite = newSnakeSprite;

        toDir = fromDir;
    }

    //Determine tail sprite
    if (newHeadPos != snake.getTail())
    {
        this->getTile(snake.getTail()).snakeSprite = this->getSnakeTailSprite(toDir);
    }
    else 
    {
        this->getTile(snake.getTail()).snakeSprite = this->getSnakeTailSprite(toDir);
    }

    return true;
}

MoveDir GameApp::determineDirection(TilePos from, TilePos to)
{
    if (to.col < from.col) return MoveDir::LEFT;
    else if (to.col > from.col) return MoveDir::RIGHT;
    else if (to.row < from.row) return MoveDir::UP;
    else return MoveDir::DOWN;
}

SnakeSprite GameApp::getSnakeHeadSprite(MoveDir to)
{
    return (SnakeSprite)(to + 1);
}

SnakeSprite GameApp::getSnakeTailSprite(MoveDir to)
{
    if (to == MoveDir::UP)  return SnakeSprite::TAIL_DOWN;
    else if (to == MoveDir::DOWN) return SnakeSprite::TAIL_UP;
    else if (to == MoveDir::RIGHT) return SnakeSprite::TAIL_LEFT;
    else return SnakeSprite::TAIL_RIGHT;
}

SnakeSprite GameApp::getSnakeSprite(MoveDir from, MoveDir to)
{
    //Determine neck sprite
    if (to == MoveDir::RIGHT && from == MoveDir::UP ||
        to == MoveDir::DOWN && from == MoveDir::LEFT)
    {
        return SnakeSprite::TURN_1;
    }
    else if (to == MoveDir::DOWN && from == MoveDir::RIGHT ||
        to == MoveDir::LEFT && from == MoveDir::UP)
    {
        return SnakeSprite::TURN_2;
    }
    else if (to == MoveDir::RIGHT && from == MoveDir::DOWN ||
        to == MoveDir::UP && from == MoveDir::LEFT)
    {
        return SnakeSprite::TURN_3;
    }
    else if (to == MoveDir::UP && from == MoveDir::RIGHT ||
        to == MoveDir::LEFT && from == MoveDir::DOWN)
    {
        return SnakeSprite::TURN_4;
    }
    else if (to == MoveDir::LEFT && from == MoveDir::LEFT ||
        to == MoveDir::RIGHT && from == MoveDir::RIGHT)
    {
        return SnakeSprite::BODY_HOR;
    }
    else
    {
        return SnakeSprite::BODY_VER;
    }
}
    
