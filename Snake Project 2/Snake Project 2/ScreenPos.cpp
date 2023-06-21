#include "ScreenPos.h"

ScreenPos::ScreenPos()
{
	this->x = 0;
	this->y = 0;
}

ScreenPos::ScreenPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool ScreenPos::operator< (const ScreenPos& other) const
{
	return this->x != other.x ? this->x < other.x : this->y < other.y;
}
