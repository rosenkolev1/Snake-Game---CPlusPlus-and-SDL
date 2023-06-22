#include "TilePos.h"
#include "Tile.h"

Tile::Tile()
	:Tile({0, 0})
{
}

Tile::Tile(TilePos tilePos)
	:Tile(tilePos, false, false, SnakeSprite::NONE)
{
}

Tile::Tile(TilePos tilePos, bool isSnake, bool isApple, SnakeSprite snakeSprite)
{
	this->tilePos = tilePos;
	this->isSnake = isSnake;
	this->isApple = isApple;
	this->snakeSprite = snakeSprite;
}


