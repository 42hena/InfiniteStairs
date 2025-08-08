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

Actor::Actor(const wchar_t* pImage, Color color, const Vector2& position)
	: _hasBeginPlay(false),
	_color(color),
	_position(position),
	_sortingOrder(0)
{
	_width = static_cast<int>(wcslen(pImage));

	// �޸� �Ҵ�
	_pImage = new wchar_t[_width + 1];

	wcscpy_s(_pImage, _width + 1, pImage);
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
	// ���� ���� ����.
}

void Actor::Render()
{
	if (Active() == false || Expired() == true) {
		return;
	}

	Utils::SetConsolePosition(_position);

	// ���� ����
	Utils::SetConsoleTextColor(static_cast<WORD>(_color));

	// console â ����Ͽ� �׸���
	std::wcout << _pImage;
}

void Actor::SetPosition(const Vector2& newPosition)
{
	if (_position == newPosition)
		return;
	
	std::wstring emptyLine = L"";
	for (int i = 0; i < _width; ++i)
		emptyLine.push_back(' ');

	// ���� ó��
	if (newPosition._y + _height >= Engine::GetInstance().Height()) {		
		Destroy();
		SetActive(false);
		_position = newPosition;
		return;
	}
	// �¡��� ó��
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

	// console â ����Ͽ� �׸���

	for (int i = 0; i < _height; ++i)
	{
		Utils::SetConsolePosition(_position);
		std::wcout << emptyLine;
		++_position._y;
	}

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
	if (Expired() == false)	{
		return;
	}

	// ���� �÷���
	_isExpired = true;

	// ���� ��û
	_owner->DestroyActor(this);
}
