#include "GameApp.h"
#include <stack>

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

    //Setup the Sdl event handling


    this->lastTickEnd = 0;

    this->state = GameState();
}

Tile& GameApp::getTile(TilePos pos)
{
    return this->state.grid[pos.row][pos.col];
}

void GameApp::startGameLoop()
{
    //int debugAlternateCounter = 1;

    while (true)
    {
        long currentTime = SDL_GetTicks64();

        this->state.processTick = currentTime - this->lastTickEnd >= this->state.tickSpeed;

        if (this->state.processTick) 
        {
            SDL_Event keyboardEvent;

            MoveDir snakeNewDir = this->state.snake.curDirection;

            //TODO: Move snake based on keys pressed by the user
            while (SDL_PollEvent(&keyboardEvent))
            {
                if (keyboardEvent.type == SDL_KEYDOWN)
                {
                    auto keyIt = GC::KEY_TO_MOVE_MAP.find(keyboardEvent.key.keysym.sym); 

                    if (keyIt != GC::KEY_TO_MOVE_MAP.end())
                    {
                        if (std::count(keyIt->second.begin(), keyIt->second.end(), this->state.snake.curDirection) == 0)
                        {
                            snakeNewDir = keyIt->second[0];
                        }
                    }                    
                }
            }

            this->state.snake.curDirection = snakeNewDir;
            
            //this->state.snake.curDirection = (MoveDir)debugAlternateCounter;
            this->moveSnake(MoveDir::Left);
            /*debugAlternateCounter += 1;
            debugAlternateCounter %= 4;*/

            if (this->state.gameOver)
            {
                //TODO: Add game over screen or winning screen if the player has collected all apples
                exit(0);
            }
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

bool GameApp::isOutOfBounds(TilePos pos)
{
    return pos.row < 0 || pos.row >= this->state.grid.size() || 
           pos.col < 0 || pos.col >= this->state.grid[0].size();
}

bool GameApp::moveSnake(MoveDir oldDirection)
{
    TilePos originalTailPos = this->state.snake.tiles[this->state.snake.tiles.size() - 2];

    Snake& snake = this->state.snake;

    TilePos newHeadPos = snake.tiles.front() + Snake::MOVE_OFFSET_MAP.at(snake.curDirection);

    //If the snake tries to go out of bound, kill it
    if (this->isOutOfBounds(newHeadPos))
    {
        this->state.gameOver = true;
        return false;
    }

    Tile& snakeHead = this->getTile(newHeadPos);

    bool devouredApple = newHeadPos == this->state.applePosition;

    snakeHead.isSnake = true;
    snakeHead.isApple = false;

    if (devouredApple)
    {
        this->state.collectedApples += 1;

        auto& newTail = this->getTile(snake.tiles.back());
        auto& oldTail = this->getTile(originalTailPos);

        newTail.isSnake = true;

        newTail.snakeSprite = this->getTile(originalTailPos).snakeSprite;

        //Change old tail sprite
        MoveDir toDir = this->determineDirection(oldTail.tilePos, newTail.tilePos);
        MoveDir fromDir = this->determineDirection(snake.tiles[snake.tiles.size() - 3], oldTail.tilePos);

        oldTail.snakeSprite = this->getSnakeSprite(fromDir, toDir);

        //Add a new 'invisible training tile'
        snake.tiles.push_back(snake.tiles.back());
    }

    //Check if the snake hits itself.
    if (std::count(snake.tiles.begin(), snake.tiles.end() - 1, newHeadPos) > 0)
    {
        if (!(snake.tiles.back() == newHeadPos && devouredApple))
        {
            this->state.gameOver = true;
            return false;
        }
    }

    SnakeSprite prevSprite = SnakeSprite::NONE;

    //Change all the positions and sprites from the tail to the head
    for (int i = snake.tiles.size() - 1; i >= 1; i--)
    {
        SnakeSprite tileCurSprite = prevSprite;

        auto tilePosNext = snake.tiles[i - 1];
        auto& tileNext = this->getTile(snake.tiles[i - 1]);

        snake.tiles[i] = snake.tiles[i - 1];
        prevSprite = tileNext.snakeSprite;
        tileNext.snakeSprite = tileCurSprite;
    }

    //Set proper head pos
    snake.tiles[0] = newHeadPos;

    //Determine head sprite
    snakeHead.snakeSprite = (SnakeSprite)(snake.curDirection + 1);

    //Get neck tile
    TilePos neckPos = snake.tiles[1];

    //Get tile after neck
    TilePos afterNeckPos = snake.tiles[2];

    MoveDir neckIncomingDir = this->determineDirection(afterNeckPos, neckPos);

    //Determine neck sprite
    this->getTile(neckPos).snakeSprite = this->getSnakeSprite(neckIncomingDir, snake.curDirection);

    //Determine tail sprite
    MoveDir tailToDir = this->determineDirection(snake.tiles[snake.tiles.size() - 2], snake.tiles[snake.tiles.size() - 3]);

    //If the current tail is not also the head
    if (newHeadPos != snake.tiles[snake.tiles.size() - 2])
    {
        this->getTile(snake.tiles[snake.tiles.size() - 2]).snakeSprite = this->getSnakeTailSprite(tailToDir);
    }

    //If an apple was not eaten and the previous tail is not a head now, then clear the previous tail
    /*if (!devouredApple && originalTailPos != newHeadPos)
    {
        Tile& previousTail = this->getTile(originalTailPos);
        previousTail.isSnake = false;
        previousTail.snakeSprite = SnakeSprite::NONE;
    }*/

    return true;
}

MoveDir GameApp::determineDirection(TilePos from, TilePos to)
{
    if (to.col < from.col) return MoveDir::Left;
    else if (to.col > from.col) return MoveDir::Right;
    else if (to.row < from.row) return MoveDir::Up;
    else return MoveDir::Down;
}

SnakeSprite GameApp::getSnakeTailSprite(MoveDir to)
{
    if (to == MoveDir::Up)  return SnakeSprite::TAIL_DOWN;
    else if (to == MoveDir::Down) return SnakeSprite::TAIL_UP;
    else if (to == MoveDir::Right) return SnakeSprite::TAIL_LEFT;
    else return SnakeSprite::TAIL_RIGHT;
}

SnakeSprite GameApp::getSnakeSprite(MoveDir from, MoveDir to)
{
    //Determine neck sprite
    if (to == MoveDir::Right && from == MoveDir::Up ||
        to == MoveDir::Down && from == MoveDir::Left)
    {
        return SnakeSprite::TURN_1;
    }
    else if (to == MoveDir::Down && from == MoveDir::Right ||
        to == MoveDir::Left && from == MoveDir::Up)
    {
        return SnakeSprite::TURN_2;
    }
    else if (to == MoveDir::Right && from == MoveDir::Down ||
        to == MoveDir::Up && from == MoveDir::Left)
    {
        return SnakeSprite::TURN_3;
    }
    else if (to == MoveDir::Up && from == MoveDir::Right ||
        to == MoveDir::Left && from == MoveDir::Down)
    {
        return SnakeSprite::TURN_4;
    }
    else if (to == MoveDir::Left && from == MoveDir::Left ||
        to == MoveDir::Right && from == MoveDir::Right)
    {
        return SnakeSprite::BODY_HOR;
    }
    else if (to == MoveDir::Down && from == MoveDir::Down ||
        to == MoveDir::Up && from == MoveDir::Up)
    {
        return SnakeSprite::BODY_VER;
    }
}
    
