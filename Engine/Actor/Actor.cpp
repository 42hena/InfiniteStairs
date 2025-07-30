#include "Engine.h"
#include "Actor.h"

#include "Utils/Utils.h"

#include "Level/Level.h"

#include <iostream>
#include <Windows.h>

/*
*		특수 맴버 함수
*/

Actor::Actor(const char* pImage, Color color, const Vector2& position)
	: _hasBeginPlay(false),
	_color(color),
	_position(position),
	_sortingOrder(0)
{
	_width = static_cast<int>(strlen(pImage));

	// 메모리 할당
	_pImage = new char[_width + 1];

	strcpy_s(_pImage, _width + 1, pImage);
}

Actor::~Actor()
{
	// std::cout << "Actor 소멸 테스트:\n";
	SafeDeleteArray(_pImage);
}

/*
*		이벤트 함수
*/

void Actor::BeginPlay()
{
	_hasBeginPlay = true;
}

void Actor::Tick(float deltaTime)
{
}

void Actor::Render()
{
	// 커서 위치 값 생성
	// COORD coord;

	// coord.X = static_cast<short>(_position._x);
	// coord.Y = static_cast<short>(_position._y);
	
	// 커서 이동
	// Utils::SetConsolePosition(coord);
	Utils::SetConsolePosition(_position);

	// 색상 변경
	Utils::SetConsoleTextColor(static_cast<WORD>(_color));

	// console 창 출력하여 그리기
	std::cout << _pImage;
}

void Actor::SetPosition(const Vector2& newPosition)
{
	if (_position == newPosition)
		return;
	
	// 좌·우 처리
	if (newPosition._x < 0 || newPosition._x + _width > Engine::GetInstance().Widget()){
		return;
	}
	// 상·하 처리
	if (newPosition._y < 0 || newPosition._y - 1 > Engine::GetInstance().Height()) {
		return;
	}

	// 커서 위치 값 생성
	/*COORD coord;
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	coord.X = static_cast<short>(_position._x);
	coord.Y = static_cast<short>(_position._y);
	Utils::SetConsolePosition(_position);
	*/

	Vector2 direction = newPosition - _position;
	_position._x = direction._x >= 0 ? _position._x : _position._x + _width - 1;

	// 커서 이동
	Utils::SetConsolePosition(_position);

	// console 창 출력하여 그리기
	//for (int i = 0 ; i < _width ; ++i)
	std::cout << " ";
	
	// 이동하려는 위치로 변경
	_position = newPosition;
}

Vector2 Actor::Position() const
{
	return _position;
}

void Actor::SetSortingOrder(unsigned int sortingOrder)
{
	_sortingOrder = sortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
	_owner = newOwner;
}

Level* Actor::GetOwner()
{
	return _owner;
}

void Actor::QuitGame()
{
	Engine::GetInstance().Quit();
}

void Actor::Destroy()
{
	_isExpired = true;

	// 삭제 요청
	_owner->DestroyActor(this);
}
