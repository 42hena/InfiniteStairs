#ifndef __INPUT_H__
#define __INPUT_H__

#include "Core.h"

#include <Windows.h>
class ENGINE_API Input
{
	friend class Engine;
#pragma region KeyState_Ű_Ȯ��_����ü
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
#pragma region MouseState_Ű_Ȯ��_����ü
	struct MouseState
	{
		enum CONST_MOUSESTATE
		{
			VK_MAX = 3
		};
		bool _isClick = false;
		COORD _mousePosition;
	};
#pragma endregion

#pragma region Ư�� ��� �Լ�
public:
	Input();
#pragma endregion

#pragma region static �Լ�
public:
	static Input& GetInstance();
#pragma endregion

#pragma region ���� �Լ�
	
	// Ű Ȯ�� �Լ�
	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);


	// ���콺 Ȯ�� �Լ�
	bool	GetMouseLeftClick();
	COORD	GetMousePosition();

#pragma endregion
private:
	void ProcessInput();
	void SavePreviousKeyStates();
#pragma region static ����
private:
	static Input*	_static_instance;
#pragma endregion

#pragma region ��� ����
private:
	KeyState	_keyStates[255] = {};
	MouseState	_mouseStates	= {};
#pragma endregion
};

#endif
