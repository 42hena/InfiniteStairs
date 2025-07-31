#pragma once

#include "Math/Vector2.h"

class StairGenerator
{
public:
	StairGenerator(int width, int height);
	~StairGenerator();

public:
	class Stair* InitGenerate();
	//class Stair* Generate();

	void MoveLastStair(int x, int y);

private:
	int		_stairCount = 0;
	Vector2 _lastStairPos;
	int _width = 3;
	int _height = 1;
};