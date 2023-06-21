#include "TilePos.h"

TilePos::TilePos()
{
	this->row = 0;
	this->col = 0;
}

TilePos::TilePos(int x, int y)
{
	this->row = x;
	this->col = y;
}

bool TilePos::operator< (const TilePos& other) const {
	return this->row != other.row ? this->row < other.row : this->col < other.col;
}
