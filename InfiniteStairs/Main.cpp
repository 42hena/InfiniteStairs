#include "Contents/InfiniteStairs.h"

#include <Windows.h>
#include <iostream>

#include "Utils/Utils.h"
#include <fcntl.h>
#include <io.h>

#include "Contents/Character.h"

#include "Contents/Animator.h"

void Init()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(482);

	char buf[200];
	sprintf_s(buf, 200, "mode con cols=%d lines=%d", 121, 50);
	system(buf);
	int charMode = _setmode(_fileno(stdout), _O_U16TEXT);
}

#include <windows.h>
#include <iostream>
#include <vector>
#include "ScreenBuffer.h"
//int main() {
//    Init();
//
//	
//	//ScreenBuffer screenBuff;
//    // 콘솔 화면 크기 얻기
//   // CONSOLE_SCREEN_BUFFER_INFO csbi;
//   // GetConsoleScreenBufferInfo(hConsole, &csbi);
//   // int width = csbi.dwSize.X;
//   // int height = csbi.dwSize.Y;
//
//   // int b = 0;
//
//   // GetConsoleScreenBufferInfo(hConsole, &csbi);
//   // width = csbi.dwSize.X;
//   // height = csbi.dwSize.Y;
//   // wprintf(L"%d %d\n", width, height);
//
//
//   // // 내 버퍼를 CHAR_INFO 배열로 만듦 (가로*세로 크기)
//   // std::vector<CHAR_INFO> buffer(width * height);
//
//   // const wchar_t* f[4] = {L"　-=∧ ＿ ∧   ", L"-=と(´･ω･`)", L"　-=/　と_ノ  ", L"-=_/／⌒ｿ   "};
//   // //const wchar_t* f[4] = {L"∧＿∧   ", L"-=と(´･ω･`)", L"　-=/　と_ノ  ", L"-=_/／⌒ｿ   "};
//   // const wchar_t* ff =  L"∧＿∧   ";
//   // for (int i = 0; i < 4; ++i)
//   // {
//   //     for (int j = 0; j < wcslen(f[i]); ++j)
//   //     {
//   //         buffer[i* width + j].Char.UnicodeChar = f[i][j];
//   //         buffer[i * width + j].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
//   //     }
//   // }
//   // 
//   // //std::wcout << L"と";
//   // //_write(_fileno(stdout), L"#と", sizeof(L"#と"));
//
//   // // 버퍼 초기화 (배경색 흰색, 문자 공백)
//   // 
//   // //auto size1 = sizeof(L'#');
//   // //auto size2 = sizeof(L'と');
//   // //
//   // /*buffer[0].Char.UnicodeChar = L'と';
//   // buffer[0].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;*/
//   // //buffer[2].Char.UnicodeChar = L'と';
//   // //buffer[2].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
//   // ////
//
//   // //////// 내 버퍼의 (0,0)에 'H', (1,0)에 'i' 넣기
//   // //////buffer[0].Char.UnicodeChar = L'と';
//   // //////buffer[0].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//
//   // //////buffer[1].Char.UnicodeChar = L'と';
//   // //////buffer[1].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//
//   // ////// 실제 콘솔 버퍼에 내 버퍼 복사
//   // COORD bufferSize = { (SHORT)width, (SHORT)height };
//   // COORD bufferCoord = { 0, 0 };
//   // SMALL_RECT writeRegion = { 0, 0, (SHORT)(width - 1), (SHORT)(height - 1) };
//
//   // //_write(_fileno(stdout), buffer.data(), bufferSize.X * bufferSize.Y);
//
//   // BOOL success = WriteConsoleOutputW(
//   //     hConsole,
//   //     buffer.data(),
//   //     bufferSize,
//   //     bufferCoord,
//   //     &writeRegion
//   // );
//
//   // /*SMALL_RECT readRegion = { 0, 0, csbi.dwSize.X - 1, csbi.dwSize.Y - 1 };
//   // 
//   // if (!ReadConsoleOutputW(hConsole, buffer.data(), bufferSize, bufferCoord, &readRegion)) {
//   //     std::cerr << "ReadConsoleOutput failed\n";
//   //     return 1;
//   // }*/
//
//   // /*if (!success) {
//   //     std::cerr << "WriteConsoleOutput 실패: " << GetLastError() << "\n";
//   //     return 1;
//   // }*/
//
//   // int a = 0;
//
//   //Vector2 posss(0, 10);
//   // Utils::SetConsolePosition(posss);
//   // //// 종료 전 대기
//   // ////system("pause");
//   // //std::cin.get();
//   // //return 0;
//}

#include <windows.h>
#include <iostream>
//
//int main() {
//    // 표준 출력 콘솔 핸들
//    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
//
//    // 새 화면 버퍼 생성 (읽기/쓰기 가능)
//    HANDLE hNewBuffer = CreateConsoleScreenBuffer(
//        GENERIC_READ | GENERIC_WRITE,
//        0,
//        NULL,
//        CONSOLE_TEXTMODE_BUFFER,
//        NULL);
//
//    if (hNewBuffer == INVALID_HANDLE_VALUE) {
//        std::cerr << "새 콘솔 버퍼 생성 실패\n";
//        return 1;
//    }
//
//    // 새 버퍼에 문자 출력
//    const wchar_t* msg = L"とello, New Console Buffer!";
//    const wchar_t* msgPrev = L"Hello, Prev Console Buffer!";
//    DWORD written;
//    int ret1 =WriteConsoleOutputCharacterW(hNewBuffer, msg, wcslen(msg), { 0,0 }, &written);
//    int ret2=WriteConsoleOutputCharacterW(hStdout, msgPrev, wcslen(msgPrev), { 0, 0 }, &written);
//    // 새 버퍼를 활성 화면으로 설정
//    SetConsoleActiveScreenBuffer(hNewBuffer);
//
//    //std::cout << "\n새 버퍼가 활성화 되었습니다. 아무 키나 누르면 복귀합니다...\n";
//    std::cin.get();
//
//    // 기존 버퍼를 다시 활성화
//    SetConsoleActiveScreenBuffer(hStdout);
//    for (int i = 0; i < 100; ++i)
//    {
//        SetConsoleActiveScreenBuffer(hStdout);
//        SetConsoleActiveScreenBuffer(hNewBuffer);
//    }
//    std::cin.get();
//    // 새 버퍼 핸들 닫기
//    SetConsoleActiveScreenBuffer(hStdout);
//    //CloseHandle(hNewBuffer);
//    Vector2 pos(0, 1);
//    Utils::SetConsolePosition(pos);
//    
//    return 0;
//}

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
	new_mode |= ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS;
	//new_mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT); // 라인 입력, 에코 해제
//
	if (!SetConsoleMode(hStdin, new_mode)) {
		std::wcerr << L"SetConsoleMode failed\n";
		return 1;
	}

//	//std::wcout << L"마우스 이벤트 테스트 (ESC 누르면 종료)\n";
//
//	//INPUT_RECORD inputRecord;
//	//DWORD events;
//
//	//while (true) {
//	//	// 입력 이벤트 대기 및 읽기
//	//	/*if (!ReadConsoleInput(hStdin, &inputRecord, 1, &events)) {
//	//		std::wcerr << L"ReadConsoleInput failed\n";
//	//		break;
//	//	}*/
//
//	//	if (PeekConsoleInput(hStdin, &inputRecord, 1, &events))
//	//	{
//	//		/*if (ReadConsoleInput(hStdin, &inputRecord, 1, &events))
//	//		{*/
//	//			if (inputRecord.EventType == MOUSE_EVENT) {
//	//				MOUSE_EVENT_RECORD mouseEvent = inputRecord.Event.MouseEvent;
//	//				COORD pos = mouseEvent.dwMousePosition;
//
//	//				std::wcout << L"마우스 위치: (" << pos.X << ", " << pos.Y << ") ";
//
//	//				if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
//	//					std::wcout << L"왼쪽 버튼 클릭 ";
//	//				}
//	//				if (mouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) {
//	//					std::wcout << L"오른쪽 버튼 클릭 ";
//	//				}
//
//	//				if (mouseEvent.dwEventFlags & MOUSE_MOVED) {
//	//					std::wcout << L"마우스 이동 ";
//	//				}
//
//	//				std::wcout << std::endl;
//	//			}
//	//			else if (inputRecord.EventType == KEY_EVENT) {
//	//				KEY_EVENT_RECORD keyEvent = inputRecord.Event.KeyEvent;
//	//				if (keyEvent.bKeyDown && keyEvent.wVirtualKeyCode == VK_ESCAPE) {
//	//					std::wcout << L"ESC 누름, 종료합니다.\n";
//	//					break;
//	//				}
//	//			}
//	//		//}
//	//	}
//	//}
//	CONSOLE_FONT_INFOEX fontInfo;
//	fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
//	GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
//	
//
//	// 원하는 글꼴 크기로 변경 (예: 폰트 크기 16)
//	//fontInfo.dwFontSize.Y = 5;
//
//	//SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
//

//	
//
//
//	/*std::wcout <<
//	L"          █████   █    ██  ██▓▄▄▄█████▓        "        ;
//	L"        ▒██▓  ██▒ ██  ▓██▒▓██▒▓  ██▒ ▓▒                "
//	L"        ▒██▒  ██░▓██  ▒██░▒██▒▒ ▓██░ ▒░                "
//	L"        ░██  █▀ ░▓▓█  ░██░░██░░ ▓██▓ ░                 "
//	L"        ░▒███▒█▄ ▒▒█████▓ ░██░  ▒██▒ ░                 "
//	L"        ░░ ▒▒░ ▒ ░▒▓▒ ▒ ▒ ░▓    ▒ ░░                   "
//	L"         ░ ▒░  ░ ░░▒░ ░ ░  ▒ ░    ░                    "
//	L"           ░   ░  ░░░ ░ ░  ▒ ░  ░                      "
//	L"            ░       ░      ░                           "
//		;*/
//	/*std::wcout <<
//		L"    ██████ ▄▄▄█████▓ ▄▄▄       ██▀███  ▄▄▄█████▓       ";
//		L"  ▒██    ▒ ▓  ██▒ ▓▒▒████▄    ▓██ ▒ ██▒▓  ██▒ ▓▒       ";
//		L"  ░ ▓██▄   ▒ ▓██░ ▒░▒██  ▀█▄  ▓██ ░▄█ ▒▒ ▓██░ ▒░       ";
//		L"    ▒   ██▒░ ▓██▓ ░ ░██▄▄▄▄██ ▒██▀▀█▄  ░ ▓██▓ ░        ";
//		L"  ▒██████▒▒  ▒██▒ ░  ▓█   ▓██▒░██▓ ▒██▒  ▒██▒ ░        ";
//		L"  ▒ ▒▓▒ ▒ ░  ▒ ░░    ▒▒   ▓▒█░░ ▒▓ ░▒▓░  ▒ ░░          ";
//		L"  ░ ░▒  ░ ░    ░      ▒   ▒▒ ░  ░▒ ░ ▒░    ░           ";
//		L"  ░  ░  ░    ░        ░   ▒     ░░   ░   ░             ";*/
//	
//
//
//
//
//
//     
//
//	/*std::wcout <<
//		L"▄████  ▄▄▄       ███▄ ▄███▓▓█████      ██████ ▄▄▄█████▓ ▄▄▄       ██▀███  ▄▄▄█████▓";
//		██▒ ▀█▒▒████▄    ▓██▒▀█▀ ██▒▓█   ▀    ▒██    ▒ ▓  ██▒ ▓▒▒████▄    ▓██ ▒ ██▒▓  ██▒ ▓▒
//		▒██░▄▄▄░▒██  ▀█▄  ▓██    ▓██░▒███      ░ ▓██▄   ▒ ▓██░ ▒░▒██  ▀█▄  ▓██ ░▄█ ▒▒ ▓██░ ▒░
//		░▓█  ██▓░██▄▄▄▄██ ▒██    ▒██ ▒▓█  ▄      ▒   ██▒░ ▓██▓ ░ ░██▄▄▄▄██ ▒██▀▀█▄  ░ ▓██▓ ░
//		░▒▓███▀▒ ▓█   ▓██▒▒██▒   ░██▒░▒████▒   ▒██████▒▒  ▒██▒ ░  ▓█   ▓██▒░██▓ ▒██▒  ▒██▒ ░
//		░▒   ▒  ▒▒   ▓▒█░░ ▒░   ░  ░░░ ▒░ ░   ▒ ▒▓▒ ▒ ░  ▒ ░░    ▒▒   ▓▒█░░ ▒▓ ░▒▓░  ▒ ░░
//		░   ░   ▒   ▒▒ ░░  ░      ░ ░ ░  ░   ░ ░▒  ░ ░    ░      ▒   ▒▒ ░  ░▒ ░ ▒░    ░
//		░ ░   ░   ░   ▒   ░      ░      ░      ░  ░  ░    ░        ░   ▒     ░░   ░   ░
//		░       ░  ░       ░      ░  ░         ░                 ░  ░   ░*/
//
//	/*std::wcout <<
//		L"      ██▓ ███▄    █   █████▒██▓ ███▄    █  ██▓▄▄██████▓▓█████      ██████ ▄▄▄█████▓ ▄▄▄       ██▓ ██▀███    ██████       "
//		L"     ▓██▒ ██ ▀█   █ ▓██   ▒▓██▒ ██ ▀█   █ ▓██▒▓  ██▒ ▓▒▓█   ▀    ▒██    ▒ ▓  ██▒ ▓▒▒████▄    ▓██▒▓██ ▒ ██▒▒██    ▒       "
//		L"     ▒██▒▓██  ▀█ ██▒▒████ ░▒██▒▓██  ▀█ ██▒▒██▒▒ ▓██░ ▒░▒███      ░ ▓██▄   ▒ ▓██░ ▒░▒██  ▀█▄  ▒██▒▓██ ░▄█ ▒░ ▓██▄         "
//		L"     ░██░▓██▒  ▐▌██▒░▓█▒  ░░██░▓██▒  ▐▌██▒░██░░ ▓██▓ ░ ▒▓█  ▄      ▒   ██▒░ ▓██▓ ░ ░██▄▄▄▄██ ░██░▒██▀▀█▄    ▒   ██▒      "
//		L"     ░██░▒██░   ▓██░░▒█░   ░██░▒██░   ▓██░░██░  ▒██▒ ░ ░▒████▒   ▒██████▒▒  ▒██▒ ░  ▓█   ▓██▒░██░░██▓ ▒██▒▒██████▒▒      "
//		L"     ░▓  ░ ▒░   ▒ ▒  ▒ ░   ░▓  ░ ▒░   ▒ ▒ ░▓    ▒ ░░   ░░ ▒░ ░   ▒ ▒▓▒ ▒ ░  ▒ ░░    ▒▒   ▓▒█░░▓  ░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░      "
//		L"     ▒ ░░ ░░   ░ ▒░ ░      ▒ ░░ ░░   ░ ▒░ ▒ ░    ░     ░ ░  ░   ░ ░▒  ░ ░    ░      ▒   ▒▒ ░ ▒ ░  ░▒ ░ ▒░░ ░▒  ░ ░       "
//		L"     ▒ ░   ░   ░ ░  ░ ░    ▒ ░   ░   ░ ░  ▒ ░  ░         ░      ░  ░  ░    ░        ░   ▒    ▒ ░  ░░   ░ ░  ░  ░         "
//		L"     ░           ░         ░           ░  ░              ░  ░         ░                 ░  ░ ░     ░           ░         ";*/
//	// TODO 124 - 1(nullptr)으로 바꿔야 할듯?

	InfiniteStairs game;
	game.Run();
}
