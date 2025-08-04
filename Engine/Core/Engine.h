#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "Core.h"
#include "Input.h"
#include <Windows.h>

struct EngineSettings
{
	// �ܼ� ����
	int width = 0;

	// �ܼ� ����
	int height = 0;

	// Ÿ�� ������
	float frameRate = 0.0f;
};

class Vector2;
class Level;
class ScreenBuffer;
class ENGINE_API Engine
{
	enum Limit
	{
		Limit_ScreenCount = 2,
	};
#pragma region Ư�� �ɹ� �Լ�
public:
	Engine();
	virtual ~Engine();

public:
	Engine(const Engine&)				= delete;
	Engine& operator=(const Engine&)	= delete;
	Engine(Engine&&)					= delete;
	Engine& operator=(Engine&&)			= delete;
#pragma endregion
	
#pragma region Ŭ���� ���� static �Լ�
public:
	static Engine& GetInstance();
#pragma endregion

#pragma region ���� �Լ�
public:
	/* Engine ���� �Լ� */
	void Run();
	virtual void CleanUp();
	void Quit();

	/* Level ���� �Լ�*/
	void AddLevel(Level* newLevel);

	int Width() const;
	int Height() const;
	void Draw(const wchar_t* str, const Vector2& rPosition);

#pragma endregion

#pragma region ���� �Լ�
private:
	/* �̺�Ʈ �Լ� */
	void BeginPlay();
	void Tick(float deltaTime = 0.0f);

	/* Draw �Լ� */
	void Render();
	void ClearBoard();

	/* ���� ���� ���� �Լ� */
	void LoadEngineSettings();
#pragma endregion

#pragma region static ����
private:
	static Engine* _static_instance;
#pragma endregion

#pragma region �ɹ� ����
protected:
	bool isQuit = false;
	Level* _mainLevel = nullptr;
	Input _input;
	EngineSettings _settings;

	ScreenBuffer*	_pScreenBuffers[Limit_ScreenCount];
	bool			_screenOrder = false;
#pragma endregion
};

#endif
