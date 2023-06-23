#pragma once
#include "TilePos.h"
#include "SnakeSprite.h"

class Tile
{
public:

	bool isSnake;
	bool isApple;

	SnakeSprite snakeSprite;
	TilePos tilePos;

	Tile();
	Tile(TilePos tilePos);
	Tile(TilePos tilePos, bool isSnake, bool isApple, SnakeSprite snakeSprite);

	bool operator== (const Tile& other) const = default;
};

