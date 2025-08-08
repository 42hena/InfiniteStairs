#include "Engine.h"
#include "Actor.h"

#include "Utils/Utils.h"

#include "Level/Level.h"

#include <iostream>
#include <string>
#include <Windows.h>

/*
*		특수 맴버 함수
*/

Actor::Actor(const wchar_t* pImage, Color color, const Vector2& position)
	: _hasBeginPlay(false),
	_color(color),
	_position(position),
	_sortingOrder(0)
{
	_width = static_cast<int>(wcslen(pImage));

	// 메모리 할당
	_pImage = new wchar_t[_width + 1];

	wcscpy_s(_pImage, _width + 1, pImage);
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
	// 딱히 내용 없음.
}

void Actor::Render()
{
	if (Active() == false || Expired() == true) {
		return;
	}

	Utils::SetConsolePosition(_position);

	// 색상 변경
	Utils::SetConsoleTextColor(static_cast<WORD>(_color));

	// console 창 출력하여 그리기
	std::wcout << _pImage;
}

void Actor::SetPosition(const Vector2& newPosition)
{
	if (_position == newPosition)
		return;
	
	std::wstring emptyLine = L"";
	for (int i = 0; i < _width; ++i)
		emptyLine.push_back(' ');

	// 상·하 처리
	if (newPosition._y + _height >= Engine::GetInstance().Height()) {		
		Destroy();
		SetActive(false);
		_position = newPosition;
		return;
	}
	// 좌·우 처리
	if (newPosition._y < 0 || newPosition._x < 0 || newPosition._x >= Engine::GetInstance().Width()){
		for (int i = 0; i < _height; ++i) {
			++_position._y;
		}
		SetActive(false);
		_position = newPosition;
		return;
	}
	SetActive(true);
	
	Vector2 direction = newPosition - _position;
	/*_position._x += direction._x >= 0 ? _position._x : _position._x + _width;
	_position._y--;*/

	// console 창 출력하여 그리기

	for (int i = 0; i < _height; ++i)
	{
		Utils::SetConsolePosition(_position);
		std::wcout << emptyLine;
		++_position._y;
	}

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

Level* Actor::GetOwner() const
{
	return _owner;
}

void Actor::QuitGame()
{
	Engine::GetInstance().Quit();
}

void Actor::Destroy()
{
	if (Expired() == false)	{
		return;
	}

	// 만료 플레그
	_isExpired = true;

	// 삭제 요청
	_owner->DestroyActor(this);
}
