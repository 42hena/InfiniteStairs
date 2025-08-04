#include "Player.h"
#include "Input.h"
#include "Level/Level.h"
#include "Level/InGameLevel.h"
#include "Engine.h"
#include "Utils/Utils.h"
#include "Contents/Character.h"
#include <iostream>
// 왜 const 안됌?(const char ** ppImage

Player::Player(Character* left, Character* right, const Vector2& rPosition, Collider* col, Direction dir)
	:Actor(L"###", Color::Color_Blue, rPosition),
	_dir(dir),
	_imageLength(1)
{
	_image[0] = std::move(left);
	_image[1] = std::move(right);
	_imageWidth = left->Width();
	_imageHeight = left->Height();

	_pCollider = col;

	// 콜라이더 컴포넌트 주인 설정
	_pCollider->SetOwner(this);
}

Player::Player(const wchar_t** ppImage[], Direction dir)
	:_dir(dir)
	, Actor(L"###", Color::Color_Blue, Vector2(18, 9))
{
	DebugBreak();
	wchar_t** first = const_cast<wchar_t**>(ppImage[0]);
	int row = 0;

	while (*first != nullptr)
	{
		++row;
		first++;
	}
	_ppImage[0] = new wchar_t* [row + 1];
	_ppImage[0][row] = nullptr;
	for (int i = 0; i < row; ++i)
	{
		size_t strLen = wcslen(ppImage[0][i]);
		_ppImage[0][i] = new wchar_t[strLen + 1];
		wcscpy_s(_ppImage[0][i], strLen + 1, ppImage[0][i]);
		_imageHeight = strLen;
	}
	_imageHeight = row;

	first = const_cast<wchar_t**>(ppImage[1]);
	row = 0;

	while (*first != nullptr)
	{
		++row;
		first++;
	}
	_ppImage[1] = new wchar_t* [row + 1];
	_ppImage[1][row] = nullptr;
	for (int i = 0; i < row; ++i)
	{
		size_t strLen = wcslen(ppImage[1][i]);
		_ppImage[1][i] = new wchar_t[strLen + 1];
		wcscpy_s(_ppImage[1][i], strLen + 1, ppImage[1][i]);
		_imageHeight = strLen;
	}
	_imageHeight = row;

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
	// super::Tick(deltaTime);

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

	Vector2 playerPosition = Position();
	

	if (_dir == Direction::Direction_Left)
	{
		wchar_t** ppCharacter = _image[0]->GetCharacterPtr();
		for (int i = 0; i < _imageHeight; ++i)
		{
			Engine::GetInstance().Draw(ppCharacter[i], playerPosition);
			// 콘솔의 다음 위치로 이동
			playerPosition._y = playerPosition._y + 1;
		}
	}
	else if (_dir == Direction::Direction_Right)
	{
		wchar_t** ppCharacter = _image[1]->GetCharacterPtr();
		for (int i = 0; i < _imageHeight; ++i)
		{
			Engine::GetInstance().Draw(ppCharacter[i], playerPosition);
			// 콘솔의 다음 위치로 이동
			playerPosition._y = playerPosition._y + 1;
		}
	}
	/*if (_dir == Direction_Left)
		std::wcout << *_ppImage[0];
	else
		std::wcout << *(_ppImage[1]);*/
}

bool Player::IsColliding(Collider* pOther) const
{
	return _pCollider->IsColliding(*pOther);
}