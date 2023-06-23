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

TEST_CASE("Test TilePos operator == and !=")
{
	TilePos pos1 = { 10, 20 };
	TilePos pos2 = { 10, 20 };

	CHECK_EQ(pos1, pos2);

	pos2 = { 15, -33 };

	CHECK_NE(pos1, pos2);

	pos2 = { 15, 20 };

	CHECK_NE(pos1, pos2);

	pos2 = { 10, 19 };

	CHECK_NE(pos1, pos2);
}

TEST_CASE("Test TilePos operator <")
{
	TilePos pos1 = { 10, 20 };
	TilePos pos2 = { 0, 5 };

	CHECK_LT(pos2, pos1);

	pos2 = { 0, 100 };

	CHECK_LT(pos2, pos1);

	pos2 = { 10, -32 };

	CHECK_LT(pos2, pos1);

	pos2 = { 10, 20 };

	CHECK_FALSE(pos1 < pos2);
}

TEST_CASE("Test TilePos operator *")
{
	TilePos pos1 = { 10, 20 };

	CHECK_EQ(pos1 * 2, TilePos(20, 40));

	CHECK_EQ(pos1 * 0, TilePos(0, 0));
}