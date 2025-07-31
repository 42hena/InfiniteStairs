#include "StairGenerator.h"
#include "Actor/Stair.h"

#include "Engine.h"



StairGenerator::StairGenerator(int width, int height)
	:_width(width),
	_height(height)
{
	_lastStairPos._x = Engine::GetInstance().Width() / 2;
	_lastStairPos._y = Engine::GetInstance().Height() / 2;
}

StairGenerator::~StairGenerator()
{
}

Stair* StairGenerator::InitGenerate()
{
	// ¿À¸¥ÂÊ
		Stair * newStair = new Stair("===", _lastStairPos);
		_lastStairPos._x = _lastStairPos._x + _width;
		_lastStairPos._y = _lastStairPos._y - 1;
		return newStair;
	if (rand() & 1) {
		;
	}
	else
	{
		Stair* newStair = new Stair("===", _lastStairPos);
		_lastStairPos._x = _lastStairPos._x - _width;
		_lastStairPos._y = _lastStairPos._y - 1;
		return newStair;
	}
}

void StairGenerator::MoveLastStair(int x, int y)
{
	_lastStairPos._x += x;
	_lastStairPos._y += y;
}
