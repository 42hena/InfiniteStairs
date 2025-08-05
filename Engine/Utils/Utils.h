#ifndef __UTILS_H__
#define __UTILS_H__

#include "Math/Vector2.h"
#include "Math/Color.h"

#include <Windows.h>

namespace Utils
{
	// �� ���� ���� �ٲ� �� ����ϴ� �Լ�
	template <typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	// �ܼ� ��� �ڵ� �������� �Լ�
	inline HANDLE GetConsoleHandle()
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}

	// �ܼ� Ŀ�� ��ġ �̵� �Լ�
	inline void SetConsolePosition(COORD coord)
	{
		SetConsoleCursorPosition(GetConsoleHandle(), coord);
	}

	inline void SetConsolePosition(const Vector2& rPosition)
	{
		SetConsolePosition(static_cast<COORD>(rPosition));
	}

	// �ܼ� �ؽ�Ʈ ���� ���� �Լ�
	inline void SetConsoleTextColor(WORD color)
	{
		SetConsoleTextAttribute(GetConsoleHandle(), color);
	}

	inline void SetConsoleTextColor(HANDLE handle, Color color)
	{
		SetConsoleTextAttribute(handle, static_cast<WORD>(color));
	}

	inline void SetConsoleTextColor(Color color)
	{
		SetConsoleTextColor(static_cast<WORD>(color));
	}
}

#endif
