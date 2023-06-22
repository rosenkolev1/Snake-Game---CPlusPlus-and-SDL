#pragma once
#include "TilePos.h"

class Tile
{
private:

	bool isEmpty;
	bool containsApple;

	TilePos tilePos;

	//TODO: Add information about the snake sprite that is rendered currently

public:

	Tile();
	Tile(TilePos tilePos, bool isEmpty, bool containsApple);

	TilePos getPos();
};

