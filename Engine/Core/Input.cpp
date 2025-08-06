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

bool Input::GetMouseRightClick()
{
	return _mouseStates[RIGHTMOST_BUTTON_PRESSED]._isClick;
}

COORD Input::GetMouseLeftPosition()
{
	return _mouseStates[FROM_LEFT_1ST_BUTTON_PRESSED]._mousePosition;
}

/*
*		내부 함수 (예외 Engine)
*/

void Input::ProcessInput()
{
	for (int i = 0; i < 256; ++i) {
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

	/*if (fontSize.X == 0) fontSize.X = 8;
	if (fontSize.Y == 0) fontSize.Y = 12;
	p.x / fontSize.X;
	p.y / fontSize.Y;*/

	//bool nowLeft = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
	//bool nowRight = (GetAsyncKeyState(VK_RBUTTON) & 0x8000);

	_mouseStates[VK_LBUTTON]._mousePosition.X = p.x / fontSize.X;
	_mouseStates[VK_LBUTTON]._mousePosition.Y = p.y / fontSize.Y;
	/*mouseState.leftPressed = (!mouseState.prevLeftDown && nowLeft);
	mouseState.rightPressed = (!mouseState.prevRightDown && nowRight);

	mouseState.leftDown = nowLeft;
	mouseState.rightDown = nowRight;*/


	//// TODO: 마우스 이벤트를 받아야 함.
	//INPUT_RECORD inputRecord;
	//DWORD events;
	//if (PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &inputRecord, 1, &events) > 0) {
	//	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &inputRecord, 1, &events);
	//	if (inputRecord.EventType == MOUSE_EVENT) {
	//		MOUSE_EVENT_RECORD mouseEvent = inputRecord.Event.MouseEvent;
	//		if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
	//			_mouseStates[FROM_LEFT_1ST_BUTTON_PRESSED]._mousePosition = mouseEvent.dwMousePosition;
	//	}
	//}

	/*const int recordCount = 256;
	INPUT_RECORD records[recordCount] = {};
	DWORD eventReadCount = 0;

	if (PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE), records, recordCount, &eventReadCount) && eventReadCount > 0)
	{
		if (ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), records, recordCount, &eventReadCount))
		{
			if (eventReadCount > 2)
			{
				int b = 0;
			}
			for (int ix = 0; ix < (int)eventReadCount; ++ix)
			{
				int mouseCnt = 0;
				int mouseMoveCnt = 0;
				int mouseDoubleClickCnt = 0;
				int mouseWheelCnt = 0;
				int mouseLCnt = 0;
				int mouseRCnt = 0;
				int TestCCC = 0;
				INPUT_RECORD& record = records[ix];
				if (record.EventType == MOUSE_EVENT){
					mouseCnt++;
					if (record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						mouseRCnt++;
						TestCCC |= 1;
					}
					if (record.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED)
					{
						mouseLCnt++;
						TestCCC |= 1;
					}

					if (record.Event.MouseEvent.dwEventFlags & MOUSE_MOVED)
					{
						mouseMoveCnt++;
						TestCCC |= 2;
					}
					if (record.Event.MouseEvent.dwEventFlags & DOUBLE_CLICK)
					{
						mouseDoubleClickCnt++;
						TestCCC |= 2;
					}
					if (record.Event.MouseEvent.dwEventFlags & MOUSE_WHEELED)
					{
						mouseWheelCnt++;
						TestCCC |= 2;
					}
				}
				if (TestCCC == 3)
					int d = 0;
				if (mouseCnt != mouseMoveCnt)
					int c = 0;
			}

			for (int ix = 0; ix < (int)eventReadCount; ++ix)
			{
				
INPUT_RECORD& record = records[ix];
				switch (record.EventType)
				{
				case KEY_EVENT:
				{
					if (record.Event.KeyEvent.bKeyDown)
					{
						_keyStates[record.Event.KeyEvent.wVirtualKeyCode]._isKeyDown = true;
					}
					else
					{
						_keyStates[record.Event.KeyEvent.wVirtualKeyCode]._isKeyDown = false;
					}
				}
				break;

				case MOUSE_EVENT:
				{
					_mouseStates[VK_LBUTTON]._mousePosition = record.Event.MouseEvent.dwMousePosition;
					_keyStates[VK_LBUTTON]._isKeyDown
						|= (record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) != 0;
					_keyStates[VK_RBUTTON]._isKeyDown
						|= (record.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) != 0;
					if (_keyStates[VK_LBUTTON]._isKeyDown || _keyStates[VK_RBUTTON]._isKeyDown)
						int a = 0;
				}
				break;
				}
			}
		}
	}*/
}

void Input::SavePreviousKeyStates()
{
	for (int i = 0; i < 256; ++i) {
		_keyStates[i]._previousKeyDown = _keyStates[i]._isKeyDown;
	}
	/*for (int i = 0; i < 2; ++i) {
		_keyStates[i]._isKeyDown = 0;
	}*/
}
