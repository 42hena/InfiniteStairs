#include "Engine.h"
#include "Input.h"

#include "Level/Level.h"

#include "Utils/Utils.h"

#include "Math/Vector2.h"

#include "Render/ScreenBuffer.h"

#include <iostream>
#include <Windows.h>

/*
*		static 변수 초기화
*/

Engine* Engine::_static_instance = nullptr;

BOOL /*WINAPI*/ ConsoleMessageProcedure(DWORD ctrlType)
{
	switch (ctrlType)
	{
	case CTRL_CLOSE_EVENT:
		Engine::GetInstance().CleanUp();
		return false;
	default:
		break;
	}
	return false;
}

/*
*		특수 맴버 함수
*/

Engine::Engine()
{
	_static_instance = this;

	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;// 찾아보기

	// 콘솔 커서 끄기
	
	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info
	);

	SetConsoleCtrlHandler(ConsoleMessageProcedure, true);
	// 모든 텍스트 색상이 변경.
	/*SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_GREEN
	);*/

	// 더블 버퍼링 용 버퍼 2개 생성.
	for (int i = 0; i < Limit_ScreenCount; ++i) {
		_pScreenBuffers[i] = new ScreenBuffer(ScreenBuffer::CreateConsoleBuffer());
	}

	LoadEngineSettings();
}

Engine::~Engine()
{
	if (false)
		CleanUp();
}

/*
*		클래스 내부 static 함수
*/

Engine& Engine::GetInstance()
{
	return *_static_instance;
}

/*
*		공개 함수
*/

void Engine::Run()
{
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;
	//printf("%lld %lld\n", currentTime.QuadPart, frequency.QuadPart);

	float targetFrameRate = 120.0f;
	float oneFrameTime = 1.0f / targetFrameRate;

	long long times;
	while (!isQuit)
	{
		QueryPerformanceCounter(&currentTime);
		times = currentTime.QuadPart - previousTime.QuadPart;
		float deltaTime = times / (float)frequency.QuadPart;

		_input.ProcessInput();
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();
		
			wchar_t title[50] = {};
			swprintf_s(title, 50, L"FPS: %f", (1.0f) / deltaTime);
			//wsprintf_s()
			SetConsoleTitleW(title);

			// 시간 업데이트
			previousTime = currentTime;

			// 현재 프레임의 입력을 기록
			_input.SavePreviousKeyStates();

			// 이전 프레임에 추가 및 삭제 요청된 액터 처리
			if (_mainLevel != nullptr) {
				_mainLevel->ProcessAddAndDestroyActors();
				_mainLevel->ProcessUIAddAndDestroyActors();
			}
		}
	}

	// Console 출력 색 원래대로 변경
	Utils::SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Engine::CleanUp()
{
	SafeDelete(_mainLevel);
	std::wcout << "Engine 삭제\n";
}

void Engine::Quit()
{
	// 종료 플레그 설정
	isQuit = true;
}

void Engine::AddLevel(Level* newLevel)
{
	if (_mainLevel != nullptr)
	{
		delete _mainLevel;
		_mainLevel = nullptr;
	}
	_mainLevel = newLevel;
}

int Engine::Width() const
{
	return _settings.width;
}

int Engine::Height() const
{
	return _settings.height;
}

/*
*		Engine의 내부 함수
*/

void Engine::BeginPlay()
{
	if (_mainLevel != nullptr) {
		_mainLevel->BeginPlay();
	}
}

void Engine::Tick(float deltaTime)
{
	if (_mainLevel != nullptr) {
		_mainLevel->Tick(deltaTime);
	}
}

void Engine::Render()
{
	// Console 출력 색 변경
	Utils::SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	if (_mainLevel != nullptr)
	{
		ClearBoard();
		
		// 스크린 버퍼에 쓰기.
		_mainLevel->Render();

		// 버퍼 출력
		_pScreenBuffers[_screenOrder]->Render();
		
		SetConsoleActiveScreenBuffer(_pScreenBuffers[_screenOrder]->ConsoleHandle());
		
		// 더블 버퍼 순서 변경.
		_screenOrder = !_screenOrder;
	}
}

void Engine::ClearBoard()
{
	int order = _screenOrder;
	CHAR_INFO* pSB = _pScreenBuffers[order]->GetScreenBuffer();
	void* pSS = _pScreenBuffers[order]->GetSortBuffer();
	int width = _pScreenBuffers[order]->ScreenWidth();
	int height = _pScreenBuffers[order]->ScreenHeight();
	/*Utils::SetConsoleTextColor(_pScreenBuffers[order]->ConsoleHandle(), Color::Color_None);

	COORD coord{ width, height };
	SMALL_RECT rect{ 0, 0, width - 1, height - 1 };
	WriteConsoleOutputW(_pScreenBuffers[order]->ConsoleHandle(), pSB, coord, { 0, 0 }, &rect);*/

	memset(pSB, 0, width * height * sizeof(CHAR_INFO));
	memset(pSS, 0, width * height);

	_pScreenBuffers[order]->Render();
}

void Engine::LoadEngineSettings()
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, "../Settings/EngineSetting.txt", "rt");
	if (pFile == nullptr)
	{
		std::cout << "Failed to load enigine settings.\n";
		return;
	}
	
	// 파일 로드
	fseek(pFile, 0, SEEK_END);

	size_t fileSize = ftell(pFile);

	rewind(pFile);

	char* pBuffer = new char[fileSize + 1];
	pBuffer[0] = 0;

	size_t readSize = fread(pBuffer, sizeof(char), fileSize, pFile);
	pBuffer[readSize] = 0;

	char* context = nullptr;
	char* token = nullptr;
	token = strtok_s(pBuffer, "\n", &context);

	while (token != nullptr)
	{
		// 키/값 분리.
		char header[10] = { };

		// 아래 구문이 제대로 동작하려면 키와 값 사이의 빈칸이 있어야 함.
		sscanf_s(token, "%s", header, 10);

		// 헤더 문자열 비교.
		if (strcmp(header, "framerate") == 0)
		{
			sscanf_s(token, "framerate = %f", &_settings.frameRate);
		}
		else if (strcmp(header, "width") == 0)
		{
			sscanf_s(token, "width = %d", &_settings.width);
		}
		else if (strcmp(header, "height") == 0)
		{
			sscanf_s(token, "height = %d", &_settings.height);
		}

		// 그 다음줄 분리.
		token = strtok_s(nullptr, "\n", &context);
	}

	SafeDeleteArray(pBuffer);

	fclose(pFile);
}

void Engine::Draw(const wchar_t* str, const Vector2& rPosition)
{
	_pScreenBuffers[_screenOrder]->DrawBuffer(str, rPosition);
}

void Engine::DrawDefault(const wchar_t* str, const Vector2& rPosition, Color color)
{
	_pScreenBuffers[_screenOrder]->DrawBufferDefault(str, rPosition, color);
}
