#include "Contents/InfiniteStairs.h"

#include <Windows.h>
#include <iostream>

#include "Utils/Utils.h"
#include <fcntl.h>
#include <io.h>

#include "Contents/Character.h"

#include "Contents/Animator.h"
#include "ScreenBuffer.h"



void Init()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(482);

	char buf[200];
	sprintf_s(buf, 200, "mode con cols=%d lines=%d", 121, 50);
	system(buf);
	int charMode = _setmode(_fileno(stdout), _O_U16TEXT);
}



int main()
{
	Init();

	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE) {
		std::wcerr << L"GetStdHandle failed\n";
		return 1;
	}

	// 콘솔 모드 설정 (마우스 입력, 입력 버퍼에서 이벤트 읽기)
	DWORD prev_mode;
	if (!GetConsoleMode(hStdin, &prev_mode)) {
		std::wcerr << L"GetConsoleMode failed\n";
		return 1;
	}

	DWORD new_mode = prev_mode;
	new_mode &= ~ENABLE_QUICK_EDIT_MODE;      // Quick Edit 모드 OFF
	new_mode |= ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
//
	if (!SetConsoleMode(hStdin, new_mode)) {
		std::wcerr << L"SetConsoleMode failed\n";
		return 1;
	}

	InfiniteStairs game;
	game.Run();
}
