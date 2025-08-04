#pragma once

#include "Engine.h"
#include <Windows.h>

class Vector2;
class ENGINE_API ScreenBuffer {
public:
	ScreenBuffer(HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE));
	~ScreenBuffer();

public:
	static HANDLE CreateConsoleBuffer();
public:
	void UpdateScreenBuffer();

	void DrawBuffer(const wchar_t* str, const Vector2& rPosition);

	HANDLE ConsoleHandle() const { return _hConsole; }

	void Render();
	void Render(PCHAR_INFO consoleBuffer);

public:

	inline short ScreenWidth() {	return _screenWidth;	}
	inline short ScreenHeight() {	return _screenHeight;	}
	inline CHAR_INFO* GetScreenBuffer() const {return _pConsoleBuffer;}
	inline CHAR* GetSortBuffer() const {return _pSortOrder;}

private:
	HANDLE		_hConsole;
	CHAR_INFO*	_pConsoleBuffer = nullptr;
	CHAR*		_pSortOrder = nullptr;
	short			_screenWidth;
	short			_screenHeight;
};