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

Player::~Player()
{
	SafeDelete(_pCollider);
	for (int i = 0; i < 2; ++i)
	{
		SafeDelete(_image[i]);
		SafeDelete(_pAnim[i]);
	}
}

void Player::Tick(float deltaTime)
{
	// super::Tick(deltaTime);
	_pAnim[0]->CalculateTime(deltaTime);
	_pAnim[1]->CalculateTime(deltaTime);
	// Key Press (Q)
	if (Input::GetInstance().GetKeyDown(0x51))
	{
		_previousDir = _dir;
		_dir = _dir == Direction_Left ? Direction_Right : Direction_Left;

		{
			Vector2 newPosition(_dir, - 1);
			Level* owner = GetOwner();

			InGameLevel* ll = dynamic_cast<InGameLevel*>(owner);
			if (ll == nullptr)
				DebugBreak();
			ll->OnPressDown();
			ll->OnMovedStairs(newPosition._x, newPosition._y);	// TODO: 문제
			//ll->OnCreateStairs(newPosition._x, newPosition._y);	// TODO: 문제
		}
	}
	// Key Press (W)
	else if (Input::GetInstance().GetKeyDown(0x57))
	{
		{
			_previousDir = _dir;
			Vector2 newPosition(_dir, -1);
			Level* owner = GetOwner();

			InGameLevel*  ll = dynamic_cast<InGameLevel*>(owner);
			if (ll == nullptr)
				DebugBreak();
			ll->OnPressDown();
			ll->OnMovedStairs(newPosition._x, newPosition._y);	// TODO: 문제
			//ll->OnCreateStairs(newPosition._x, newPosition._y);	// TODO: 문제
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
		Character* pImage = _pAnim[0]->GetCurrentImagePtr();

		
		wchar_t** ppCharacter = pImage->GetCharacterPtr();
		for (int i = 0; i < pImage->Height(); ++i)
		{
			Engine::GetInstance().DrawDefault(ppCharacter[i], playerPosition, Color::Color_White);
			// 콘솔의 다음 위치로 이동
			playerPosition._y = playerPosition._y + 1;
		}
	}
	else if (_dir == Direction::Direction_Right)
	{
		Character* pImage = _pAnim[1]->GetCurrentImagePtr();


		wchar_t** ppCharacter = pImage->GetCharacterPtr();
		for (int i = 0; i < pImage->Height(); ++i)
		{
			Engine::GetInstance().DrawDefault(ppCharacter[i], playerPosition, Color::Color_White);
			// 콘솔의 다음 위치로 이동
			playerPosition._y = playerPosition._y + 1;
		}
	}
	/*if (_dir == Direction_Left)
		std::wcout << *_ppImage[0];
	else
		std::wcout << *(_ppImage[1]);*/
}

void Player::Reset()
{
	// 방향 처음으로.
	_dir = Direction_Left;
	/*for (int i = 0 ; i < 2 ; ++i)
		_pAnim[i].Reset();*/
}

bool Player::IsColliding(Collider* pOther) const
{
	return _pCollider->IsColliding(*pOther);
}
