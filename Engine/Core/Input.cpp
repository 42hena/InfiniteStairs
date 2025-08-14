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

bool Input::GetMouseLeftClick()
{
	return _keyStates[VK_LBUTTON]._isKeyDown && !_keyStates[VK_LBUTTON]._previousKeyDown;
}

COORD Input::GetMousePosition()
{
	return _mouseStates._mousePosition;
}

/*
*		내부 함수 (예외 Engine)
*/

void Input::ProcessInput()
{
	for (int i = 0; i < 255; ++i) {
		_keyStates[i]._isKeyDown = GetAsyncKeyState(i) & 0x8000;
	}

	POINT p;
	GetCursorPos(&p);
	HWND hwnd = GetConsoleWindow();
	ScreenToClient(hwnd, &p);

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFO fontInfo;
	GetCurrentConsoleFont(hOut, FALSE, &fontInfo);
	COORD fontSize = GetConsoleFontSize(hOut, fontInfo.nFont);
	if (fontSize.X == 0)
		fontSize.X = 8;
	if (fontSize.Y == 0)
		fontSize.Y = 16;

	_mouseStates._mousePosition.X = static_cast<SHORT>(p.x / fontSize.X);
	_mouseStates._mousePosition.Y = static_cast<SHORT>(p.y / fontSize.Y);
}

void Input::SavePreviousKeyStates()
{
	for (int i = 0; i < 255; ++i) {
		_keyStates[i]._previousKeyDown = _keyStates[i]._isKeyDown;
	}
}
