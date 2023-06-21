#include "TilePos.h"
#include "Tile.h"

Tile::Tile()
{
	this->tilePos = TilePos(0, 0);
	this->isEmpty = true;
	this->containsApple = false;
}

Tile::Tile(TilePos tilePos, bool isEmpty, bool containsApple)
{
	this->tilePos = tilePos;
	this->isEmpty = isEmpty;
	this->containsApple = containsApple;
}

TilePos Tile::getPos()
{
	return this->tilePos;
}


