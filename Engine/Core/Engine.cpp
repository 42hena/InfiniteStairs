#include "Engine.h"
#include "Input.h"

#include "Level/Level.h"

#include "Utils/Utils.h"

#include "Math/Vector2.h"

#include "Render/ScreenBuffer.h"

#include <iostream>
#include <Windows.h>

/*
*		static ���� �ʱ�ȭ
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
*		Ư�� �ɹ� �Լ�
*/

Engine::Engine()
{
	_static_instance = this;

	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;// ã�ƺ���

	// �ܼ� Ŀ�� ����
	
	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info
	);

	SetConsoleCtrlHandler(ConsoleMessageProcedure, true);
	// ��� �ؽ�Ʈ ������ ����.
	/*SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_GREEN
	);*/

	// ���� ���۸� �� ���� 2�� ����.
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
*		Ŭ���� ���� static �Լ�
*/

Engine& Engine::GetInstance()
{
	return *_static_instance;
}

/*
*		���� �Լ�
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

			// �ð� ������Ʈ
			previousTime = currentTime;

			// ���� �������� �Է��� ���
			_input.SavePreviousKeyStates();

			// ���� �����ӿ� �߰� �� ���� ��û�� ���� ó��
			if (_mainLevel != nullptr) {
				_mainLevel->ProcessAddAndDestroyActors();
				_mainLevel->ProcessUIAddAndDestroyActors();
			}
		}
	}

	// Console ��� �� ������� ����
	Utils::SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Engine::CleanUp()
{
	SafeDelete(_mainLevel);
	std::wcout << "Engine ����\n";
}

void Engine::Quit()
{
	// ���� �÷��� ����
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
*		Engine�� ���� �Լ�
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
	// Console ��� �� ����
	Utils::SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	if (_mainLevel != nullptr)
	{
		ClearBoard();
		
		// ��ũ�� ���ۿ� ����.
		_mainLevel->Render();

		// ���� ���
		_pScreenBuffers[_screenOrder]->Render();
		
		SetConsoleActiveScreenBuffer(_pScreenBuffers[_screenOrder]->ConsoleHandle());
		
		// ���� ���� ���� ����.
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
	
	// ���� �ε�
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
		// Ű/�� �и�.
		char header[10] = { };

		// �Ʒ� ������ ����� �����Ϸ��� Ű�� �� ������ ��ĭ�� �־�� ��.
		sscanf_s(token, "%s", header, 10);

		// ��� ���ڿ� ��.
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

		// �� ������ �и�.
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
