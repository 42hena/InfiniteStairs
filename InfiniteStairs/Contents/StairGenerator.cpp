#include "StairGenerator.h"
#include "Actor/Stair.h"
#include "Contents/Character.h"
#include "Engine.h"

#include <memory>

StairGenerator::StairGenerator(int width, int height)
	:_width(width),
	_height(height)
{
	// 전체 사이즈의 1/2에서 width를 1/2해야할듯?
	int newWidth = (Engine::GetInstance().Width() - width) / 2.0f;
	_lastStairPos._x = newWidth;
	_lastStairPos._y = 24;
	_initStairPos = _lastStairPos;
}

StairGenerator::~StairGenerator()
{
	if (_pStairImage != nullptr) {
		SafeDelete(_pStairImage);
	}
}

Stair* StairGenerator::InitGenerate()
{
	// case 홀수: 마지막 계단 기준으로 오른쪽 설치
	if (rand() & 1) {
		//Stair * newStair = new Stair(L"===", _lastStairPos);
		Vector2 colliderPos(0, 0);
		Collider* col = new Collider(colliderPos, _width, _height);
		Stair* newStair = new Stair(_pStairImage, col, _lastStairPos);
		_lastStairPos._x = _lastStairPos._x + _width;
		_lastStairPos._y = _lastStairPos._y - _height - 1; // TODO :변경중
		return newStair;
	}
	// case 짝수: 마지막 계단 기준으로 왼쪽 설치
	else
	{

		Vector2 colliderPos(0, 0);
		Collider* col = new Collider(colliderPos, _width, _height);
		Stair* newStair = new Stair(_pStairImage, col, _lastStairPos);
		_lastStairPos._x = _lastStairPos._x - _width;
		_lastStairPos._y = _lastStairPos._y - _height - 1;// TODO :변경중
		return newStair;
	}
}

void StairGenerator::MoveLastStair(int x, int y)
{
	_lastStairPos._x += x;
	_lastStairPos._y += y;
}

void StairGenerator::SetStairImage(Character* pImage)
{
	if (_pStairImage != nullptr) {
		delete _pStairImage;
		_pStairImage = nullptr;
	}
	_pStairImage = std::move(pImage);
	_width = pImage->Width();
	_height = pImage->Height();
}

void StairGenerator::Reset()
{
	_lastStairPos = _initStairPos;
}
