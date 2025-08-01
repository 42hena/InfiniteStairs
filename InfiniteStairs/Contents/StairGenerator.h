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

	inline int StairWidth() const { return _width; }
	void SetStairWidth(int width) { _width = width; }
	
	inline int StairHeight() const { return _height; }
	void SetStairHeight(int height) { _height = height; }

private:
	int		_stairCount = 0;
	Vector2 _lastStairPos;
	int _width = 3;
	int _height = 1;
};