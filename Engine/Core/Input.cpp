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

bool Input::GetKey(int keyCode) const
{
    return _keyStates[keyCode]._isKeyDown;
}

bool Input::GetKeyDown(int keyCode) const
{
    return !_keyStates[keyCode]._previousKeyDown && _keyStates[keyCode]._isKeyDown;
}

bool Input::GetKeyPressed(int keyCode) const
{
    return _keyStates[keyCode]._previousKeyDown && _keyStates[keyCode]._isKeyDown;
}

bool Input::GetKeyUp(int keyCode) const
{
    return _keyStates[keyCode]._previousKeyDown && !_keyStates[keyCode]._isKeyDown;
}

/* 마우스 왼쪽 버튼 관련 함수 */

bool Input::GetMouseLeftClickDown() const
{
    return GetKeyDown(VK_LBUTTON);
}

bool Input::GetMouseLeftClickUp() const
{
    return GetKeyUp(VK_LBUTTON);
}

bool Input::GetMouseLeftClickPressed() const
{
    return GetKeyPressed(VK_LBUTTON);
}

/* 마우스 오른쪽 버튼 관련 함수 */

bool Input::GetMouseRightClickDown() const
{
    return GetKeyDown(VK_RBUTTON);
}

bool Input::GetMouseRightClickUp() const
{
    return GetKeyUp(VK_RBUTTON);
}

bool Input::GetMouseRightClickPressed() const
{
    return GetKeyPressed(VK_RBUTTON);
}

/* 마우스 중앙 버튼 관련 함수 */

bool Input::GetMouseMiddleClickDown() const
{
    return GetKeyDown(VK_MBUTTON);
}

bool Input::GetMouseMiddleClickUp() const
{
    return GetKeyUp(VK_MBUTTON);
}

bool Input::GetMouseMiddleClickPressed() const
{
    return GetKeyPressed(VK_MBUTTON);
}

/* 마우스 위치 관련 함수 */

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
