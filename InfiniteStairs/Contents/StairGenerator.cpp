#include "StairGenerator.h"
#include "Actor/Stair.h"

#include "Engine.h"



StairGenerator::StairGenerator(int width, int height)
	:_width(width),
	_height(height)
{
	_lastStairPos._x = 18;
	_lastStairPos._y = Engine::GetInstance().Height() / 2;
}

StairGenerator::~StairGenerator()
{
}

Stair* StairGenerator::InitGenerate()
{
	// ¿À¸¥ÂÊ
	if (rand() & 1) {
		_lastStairPos._x = _lastStairPos._x + _width;
		_lastStairPos._y = _lastStairPos._y - 1;
		Stair * newStair = new Stair("===", _lastStairPos);
		return newStair;
	}
	else
	{
		_lastStairPos._x = _lastStairPos._x - _width;
		_lastStairPos._y = _lastStairPos._y - 1;
		Stair* newStair = new Stair("===", _lastStairPos);
		return newStair;
	}
}

void StairGenerator::MoveLastStair(int x, int y)
{
	_lastStairPos._x += x;
	_lastStairPos._y += y;
}
