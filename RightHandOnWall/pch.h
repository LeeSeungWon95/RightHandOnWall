#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include "Types.h"
#include <stack>
#include <queue>
#include <map>

using namespace std;

struct Pos
{
	bool operator==(Pos& pos)
	{
		return x == pos.x && y == pos.y;
	}
	bool operator!=(Pos& pos)
	{
		return !(*this == pos);
	}
	bool operator<(const Pos& other) const
	{
		if (y != other.y)
		{
			return y < other.y;
		}
		return x < other.x;
	}
	Pos operator+(Pos& pos)
	{
		Pos ret;
		ret.x = x + pos.x;
		ret.y = y + pos.y;
		return ret;
	}
	Pos operator-(Pos& pos)
	{
		Pos ret;
		ret.x = x - pos.x;
		ret.y = y - pos.y;
		return ret;
	}
	Pos& operator+=(Pos& pos)
	{
		x += pos.x;
		y += pos.y;
		return *this;
	}
	Pos& operator-=(Pos& pos)
	{
		x -= pos.x;
		y -= pos.y;
		return *this;
	}
	int32 x = 0;
	int32 y = 0;
};

enum Dir
{
	DIR_UP = 0,
	DIR_LEFT = 1,
	DIR_DOWN = 2,
	DIR_RIGHT = 3,

	DIR_COUNT = 4
};

