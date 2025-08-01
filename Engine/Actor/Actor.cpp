#include "Engine.h"
#include "Actor.h"

#include "Utils/Utils.h"

#include "Level/Level.h"

#include <iostream>
#include <string>
#include <Windows.h>

/*
*		Ư�� �ɹ� �Լ�
*/

Actor::Actor(const char* pImage, Color color, const Vector2& position)
	: _hasBeginPlay(false),
	_color(color),
	_position(position),
	_sortingOrder(0)
{
	_width = static_cast<int>(strlen(pImage));

	// �޸� �Ҵ�
	_pImage = new char[_width + 1];

	strcpy_s(_pImage, _width + 1, pImage);
}

Actor::~Actor()
{
	// std::cout << "Actor �Ҹ� �׽�Ʈ:\n";
	SafeDeleteArray(_pImage);
}

/*
*		�̺�Ʈ �Լ�
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
	if (_isActive == false || _isExpired == true) {
		return;
	}
	// Ŀ�� ��ġ �� ����
	// COORD coord;

	// coord.X = static_cast<short>(_position._x);
	// coord.Y = static_cast<short>(_position._y);
	
	// Ŀ�� �̵�
	// Utils::SetConsolePosition(coord);
	Utils::SetConsolePosition(_position);

	// ���� ����
	Utils::SetConsoleTextColor(static_cast<WORD>(_color));

	// console â ����Ͽ� �׸���
	std::cout << _pImage;
}

void Actor::SetPosition(const Vector2& newPosition)
{
	if (_position == newPosition)
		return;
	
	// ���� ó��
	if (newPosition._y < 0 || newPosition._y + 1 > Engine::GetInstance().Height()) {
		Utils::SetConsolePosition(_position);
		std::string s = "";
		for (int i = 0; i < _width; ++i)
			s.push_back(' ');
		std::cout << s;
		Destroy();
		_isActive = false;
		_position = newPosition;
		return;
	}
	// �¡��� ó��
	if (newPosition._x < 0 || newPosition._x + _width > Engine::GetInstance().Width()){
		Utils::SetConsolePosition(_position);
		std::string s = "";
		for (int i = 0; i < _width; ++i)
			s.push_back(' ');
		std::cout << s;
		_isActive = false;
		_position = newPosition;
		return;
	}
	_isActive = true;
	Utils::SetConsolePosition(_position);
	Vector2 direction = newPosition - _position;
	/*_position._x += direction._x >= 0 ? _position._x : _position._x + _width;
	_position._y--;*/

	// console â ����Ͽ� �׸���

	std::string s = "";
	for (int i = 0; i < _width; ++i)
		s.push_back(' ');
	std::cout << s;

	// �̵��Ϸ��� ��ġ�� ����
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
	_isExpired = true;

	// ���� ��û
	_owner->DestroyActor(this);
}
