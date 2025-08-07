#include "ScreenBuffer.h"

#include "Math/Vector2.h"

#include <iostream>

/*
*		특수 멤버 함수
*/

ScreenBuffer::ScreenBuffer(HANDLE hConsole)
{
	_hConsole = hConsole;

	// width, height 설정
	UpdateScreenBuffer();

	// Cursor 설정
	CONSOLE_CURSOR_INFO cursorInfo{ 1, FALSE };
	SetConsoleCursorInfo(_hConsole, &cursorInfo);

	_pConsoleBuffer = new CHAR_INFO[_screenWidth * _screenHeight];
	_pSortOrder = new CHAR[_screenWidth * _screenHeight];

	memset(_pConsoleBuffer, 0, sizeof(CHAR_INFO)*_screenWidth * _screenHeight);
	memset(_pSortOrder, 0, _screenWidth * _screenHeight);
}

ScreenBuffer::~ScreenBuffer()
{
	if (_pConsoleBuffer != nullptr)
		SafeDeleteArray(_pConsoleBuffer);
	if (_pSortOrder != nullptr)
		SafeDeleteArray(_pSortOrder);

	// mainConsoleHandle을 삭제 시 조금 애매해질 수 있음.
	CloseHandle(_hConsole);
}

/*
*		
*/

HANDLE ScreenBuffer::CreateConsoleBuffer()
{
	HANDLE hConsoleBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	return hConsoleBuffer;
}

/*
* 
*/

void ScreenBuffer::UpdateScreenBuffer()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(_hConsole, &csbi);
	
	_screenWidth = csbi.dwSize.X;
	_screenHeight = csbi.dwSize.Y;
}

void ScreenBuffer::DrawBuffer(const wchar_t* str, const Vector2& rPosition)
{
	int index = rPosition._y * _screenWidth + rPosition._x;
	int strLen = static_cast<int>(wcslen(str));
	for (int i = 0; i < strLen; ++i) {
		_pConsoleBuffer[index + i].Char.UnicodeChar = str[i];
		// _pConsoleBuffer[index + i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		if (i & 1)
			_pConsoleBuffer[index + i].Attributes = FOREGROUND_RED;
		else
			_pConsoleBuffer[index + i].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;

	}
}

void ScreenBuffer::DrawBufferDefault(const wchar_t ch, const Vector2& rPosition, Color color)
{
	int index = rPosition._y * _screenWidth + rPosition._x;
	_pConsoleBuffer[index].Char.UnicodeChar = ch;
	_pConsoleBuffer[index].Attributes = static_cast<WORD>(color);
}


void ScreenBuffer::DrawBufferDefault(const wchar_t* str, const Vector2& rPosition, Color color)
{
	int index = rPosition._y * _screenWidth + rPosition._x;
	int strLen = static_cast<int>(wcslen(str));
	for (int i = 0; i < strLen; ++i) {
		_pConsoleBuffer[index + i].Char.UnicodeChar = str[i];
		_pConsoleBuffer[index + i].Attributes = static_cast<WORD>(color);
	}
}

void ScreenBuffer::Render()
{
	COORD coord{ _screenWidth , _screenHeight };
	SMALL_RECT smallRect{ 0, 0, coord.X - 1, coord.Y - 1 };
	WriteConsoleOutputW(_hConsole, _pConsoleBuffer, coord, { 0, 0 }, &smallRect);
}

void ScreenBuffer::Render(PCHAR_INFO consoleBuffer)
{
	DebugBreak();
	COORD coord{ _screenWidth , _screenHeight };
	SMALL_RECT smallRect{ 0, 0, coord.X - 1, coord.Y - 1 };
	WriteConsoleOutputW(_hConsole, consoleBuffer, coord, { 0, 0 }, &smallRect);
}


