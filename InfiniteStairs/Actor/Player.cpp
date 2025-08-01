#include "Player.h"
#include "Input.h"
#include "Level/Level.h"
#include "Level/InGameLevel.h"
#include "Engine.h"
#include "Utils/Utils.h"
#include <iostream>
// 왜 const 안됌?
//Player::Player(const char ** ppImage, Direction dir)
//	:_dir(dir)
//	,Actor("###", Color::Color_Blue, Vector2(18, 9))
//{
//
//	char** first = const_cast<char**>(ppImage);
//	int row = 0;
//	int col = 3;
//
//	while (*first != nullptr)
//	{
//		++row;
//		first++;
//	}
//	_ppImage = new char* [row + 1];
//	_ppImage[row] = nullptr;
//	for (int i = 0; i < row; ++i)
//	{
//		size_t strLen = strlen(ppImage[i]);
//		_ppImage[i] = new char[strLen + 1];
//		strcpy_s(_ppImage[i], strLen + 1, ppImage[i]);
//		_height = strLen;
//	}
//	_height = row;
//
//	Vector2 phyPos = Vector2(0, 1);
//	_pCollider = new Collider(phyPos, 3, 1);
//	_pCollider->SetOwner(this);
//}

Player::Player(const char** ppImage[], Direction dir)
	:_dir(dir)
	, Actor("###", Color::Color_Blue, Vector2(18, 9))
{

	char** first = const_cast<char**>(ppImage[0]);
	int row = 0;
	int col = 3;

	while (*first != nullptr)
	{
		++row;
		first++;
	}
	_ppImage[0] = new char* [row + 1];
	_ppImage[0][row] = nullptr;
	for (int i = 0; i < row; ++i)
	{
		size_t strLen = strlen(ppImage[0][i]);
		_ppImage[0][i] = new char[strLen + 1];
		strcpy_s(_ppImage[0][i], strLen + 1, ppImage[0][i]);
		_height = strLen;
	}
	_height = row;

	first = const_cast<char**>(ppImage[1]);
	row = 0;

	while (*first != nullptr)
	{
		++row;
		first++;
	}
	_ppImage[1] = new char* [row + 1];
	_ppImage[1][row] = nullptr;
	for (int i = 0; i < row; ++i)
	{
		size_t strLen = strlen(ppImage[1][i]);
		_ppImage[1][i] = new char[strLen + 1];
		strcpy_s(_ppImage[1][i], strLen + 1, ppImage[1][i]);
		_height = strLen;
	}
	_height = row;

	Vector2 phyPos = Vector2(0, 1);
	_pCollider = new Collider(phyPos, 3, 1);
	_pCollider->SetOwner(this);
}

Player::~Player()
{
	SafeDelete(_pCollider);
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 키 입력 q(방향전환 및 직진) w(직진)
	// Q를 눌렀다?

	// Key Press (Q)
	if (Input::GetInstance().GetKeyDown(0x51))
	{
		_dir = _dir == Direction_Left ? Direction_Right : Direction_Left;

		{
			Vector2 newPosition(_dir, - 1);
			Level* owner = GetOwner();

			InGameLevel* ll = dynamic_cast<InGameLevel*>(owner);
			if (ll == nullptr)
				DebugBreak();
			ll->OnPressDown();
			ll->OnMovedStairs(newPosition._x, newPosition._y);
			ll->OnCreateStairs(newPosition._x, newPosition._y);
		}
	}
	// Key Press (W)
	else if (Input::GetInstance().GetKeyDown(0x57))
	{
		{
			Vector2 newPosition(_dir, -1);
			Level* owner = GetOwner();

			InGameLevel*  ll = dynamic_cast<InGameLevel*>(owner);
			if (ll == nullptr)
				DebugBreak();
			ll->OnPressDown();
			ll->OnMovedStairs(newPosition._x, newPosition._y);
			ll->OnCreateStairs(newPosition._x, newPosition._y);
		}
	}
}

void Player::Render()
{
	if (Active() == false || Expired() == true) {
		return;
	}
	// 커서 위치 값 생성
	// COORD coord;

	// coord.X = static_cast<short>(_position._x);
	// coord.Y = static_cast<short>(_position._y);

	// 커서 이동
	// Utils::SetConsolePosition(coord);
	Utils::SetConsolePosition(Position());

	// 색상 변경
	//Utils::SetConsoleTextColor(static_cast<WORD>(_color));

	// console 창 출력하여 그리기
	if (_dir == Direction_Left)
		std::cout << *_ppImage[0];
	else
		std::cout << *(_ppImage[1]);

}

bool Player::IsColliding(Collider* pOther) const
{
	return _pCollider->IsColliding(*pOther);;
}