#include "Player.h"
#include "Input.h"
#include "Level/Level.h"
#include "Level/InGameLevel.h"

#include <iostream>
// �� const �ȉ�?
Player::Player(const char ** ppImage, Direction dir)
	:_dir(dir)
{

	char** first = const_cast<char**>(ppImage);
	int row = 0;
	int col = 0;

	while (*first != nullptr)
	{
		++row;
		first++;
	}
	_ppImage = new char* [row + 1];
	_ppImage[row] = nullptr;
	for (int i = 0; i < row; ++i)
	{
		size_t strLen = strlen(ppImage[i]);
		_ppImage[i] = new char[strLen + 1];
		strcpy_s(_ppImage[i], strLen + 1, ppImage[i]);
		_height = strLen;
	}
	for (int i = 0; i < row; ++i)
	{
		std::cout << _ppImage[i] << "\n";
	}
	_width = row;
}

Player::~Player()
{
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// Ű �Է� q(������ȯ �� ����) w(����)
	// Q�� ������?

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
			ll->OnMovedStairs(newPosition._x, newPosition._y);
			ll->OnCreateStairs(newPosition._x, newPosition._y);
		}
	}
}
