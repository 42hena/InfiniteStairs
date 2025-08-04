#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "Core.h"
#include "Input.h"
#include <Windows.h>

struct EngineSettings
{
	// 콘솔 가로
	int width = 0;

	// 콘솔 세로
	int height = 0;

	// 타겟 프레임
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
#pragma region 특수 맴버 함수
public:
	Engine();
	virtual ~Engine();

public:
	Engine(const Engine&)				= delete;
	Engine& operator=(const Engine&)	= delete;
	Engine(Engine&&)					= delete;
	Engine& operator=(Engine&&)			= delete;
#pragma endregion
	
#pragma region 클래스 내부 static 함수
public:
	static Engine& GetInstance();
#pragma endregion

#pragma region 공개 함수
public:
	/* Engine 관련 함수 */
	void Run();
	virtual void CleanUp();
	void Quit();

	/* Level 관련 함수*/
	void AddLevel(Level* newLevel);

	int Width() const;
	int Height() const;
	void Draw(const wchar_t* str, const Vector2& rPosition);

#pragma endregion

#pragma region 내부 함수
private:
	/* 이벤트 함수 */
	void BeginPlay();
	void Tick(float deltaTime = 0.0f);

	/* Draw 함수 */
	void Render();
	void ClearBoard();

	/* 엔진 설정 파일 함수 */
	void LoadEngineSettings();
#pragma endregion

#pragma region static 변수
private:
	static Engine* _static_instance;
#pragma endregion

#pragma region 맴버 변수
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
