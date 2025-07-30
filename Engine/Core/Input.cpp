#include "Input.h"

#include <Windows.h>

/*
*		static 변수 초기화
*/
Input* Input::_static_instance = nullptr;

/*
*		특수 멤버 함수
*/

Input::Input()
{
	_static_instance = this;
}

/*
*		static 함수
*/

Input& Input::GetInstance()
{
	return *_static_instance; 
}

/*
*		공개 함수
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
*		내부 함수 (예외 Engine)
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
