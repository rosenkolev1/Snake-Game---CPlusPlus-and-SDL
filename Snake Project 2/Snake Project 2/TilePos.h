#pragma once
class TilePos
{
public:
	int row;
	int col;

	TilePos();
	TilePos(int row, int col);


	bool operator== (const TilePos& other) const;
	bool operator< (const TilePos& other) const;

	TilePos operator+ (const TilePos& other) const;

	TilePos operator* (int num) const;
};

