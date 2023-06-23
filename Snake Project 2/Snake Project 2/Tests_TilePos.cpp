#include "doctest.h"
#include <iostream>
#include <vector>
#include "TilePos.h"

TEST_CASE("Test TilePos operator +")
{
	TilePos pos1 = { 10, 20 };
	TilePos pos2 = { 15, -33 };

	TilePos actualPos = pos1 + pos2;
	TilePos expectedPos = { 25, -13 };

	CHECK_EQ(expectedPos, actualPos);
}