#pragma once
class ScreenPos
{
public:

	int x;
	int y;

	ScreenPos();
	ScreenPos(int x, int y);

	bool operator< (const ScreenPos& other) const;
};

