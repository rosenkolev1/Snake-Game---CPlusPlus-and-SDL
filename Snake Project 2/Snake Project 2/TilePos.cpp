#include "TilePos.h"
#include <iostream>

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

bool TilePos::operator==(const TilePos& other) const
{
	return this->row == other.row && this->col == other.col;
}

bool TilePos::operator< (const TilePos& other) const
{
	return this->row != other.row ? this->row < other.row : this->col < other.col;
}

TilePos TilePos::operator+(const TilePos& other) const
{
	return TilePos(this->row + other.row, this->col + other.col);
}

TilePos TilePos::operator*(int num) const
{
	return TilePos(this->row * num, this->col * num);
}
