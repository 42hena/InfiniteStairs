#ifndef __UTILS_H__
#define __UTILS_H__

#include "Math/Vector2.h"
#include "Math/Color.h"

#include <Windows.h>

namespace Utils
{
	// 두 값을 서로 바꿀 때 사용하는 함수
	template <typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	// 콘솔 출력 핸들 가져오는 함수
	inline HANDLE GetConsoleHandle()
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}

	// 콘솔 커서 위치 이동 함수
	inline void SetConsolePosition(COORD coord)
	{
		SetConsoleCursorPosition(GetConsoleHandle(), coord);
	}

	inline void SetConsolePosition(const Vector2& rPosition)
	{
		SetConsolePosition(static_cast<COORD>(rPosition));
	}

	// 콘솔 텍스트 색상 설정 함수
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
