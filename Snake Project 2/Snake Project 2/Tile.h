#pragma once
#include "TilePos.h"

class Tile
{
private:

	bool isEmpty;
	bool containsApple;

	TilePos tilePos;

public:

	Tile();
	Tile(TilePos tilePos, bool isEmpty, bool containsApple);

	TilePos getPos();
};

