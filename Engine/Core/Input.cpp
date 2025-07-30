#include "Input.h"

#include <Windows.h>

/*
*		static ���� �ʱ�ȭ
*/
Input* Input::_static_instance = nullptr;

/*
*		Ư�� ��� �Լ�
*/

Input::Input()
{
	_static_instance = this;
}

/*
*		static �Լ�
*/

Input& Input::GetInstance()
{
	return *_static_instance; 
}

/*
*		���� �Լ�
*/

bool Input::GetKey(int keyCode)
{
	return _keyStates[keyCode]._isKeyDown;
}

bool Input::GetKeyDown(int keyCode)
{
	return !_keyStates[keyCode]._previousKeyDown && _keyStates[keyCode]._isKeyDown;
}

bool Input::GetKeyUp(int keyCode)
{
	return _keyStates[keyCode]._previousKeyDown && !_keyStates[keyCode]._isKeyDown;
}

/*
*		���� �Լ� (���� Engine)
*/

void Input::ProcessInput()
{
	for (int i = 0; i < 255; ++i)
	{
		_keyStates[i]._isKeyDown = GetAsyncKeyState(i) & 0x8000;
	}

	/*if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		Quit();
	}*/
}

void Input::SavePreviousKeyStates()
{
	for (int i = 0; i < 256; ++i)
	{
		_keyStates[i]._previousKeyDown = _keyStates[i]._isKeyDown;
	}
}
