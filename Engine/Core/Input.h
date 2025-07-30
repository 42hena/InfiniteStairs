#ifndef __INPUT_H__
#define __INPUT_H__

#include "Core.h"

class ENGINE_API Input
{
	friend class Engine;
#pragma region KeyState_키_확인_구조체
	struct KeyState
	{
		enum CONST_KEYSTATE
		{
			VK_MAX = 255
		};
		bool _isKeyDown = false;
		bool _previousKeyDown = false;
	};
#pragma endregion

#pragma region 특수 멤버 함수
public:
	Input();
#pragma endregion

#pragma region static 함수
public:
	static Input& GetInstance();
#pragma endregion

#pragma region 공개 함수
	
	// 키 확인 함수
	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);
#pragma endregion
private:
	void ProcessInput();
	void SavePreviousKeyStates();
#pragma region static 변수
private:
	static Input*	_static_instance;
#pragma endregion

#pragma region 멤버 변수
private:
	KeyState _keyStates[256] = {};
#pragma endregion
};

#endif
