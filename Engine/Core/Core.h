#ifndef __CORE_H__
#define __CORE_H__

#pragma warning(disable: 4251)	// dll 외부로 템플릿 내보낼 때 발생함
#pragma warning(disable: 4172)	// 함수 지역 static 변수를 주소로 사용 시 발생

#ifdef BUILD_ENGINE_DLL
#define ENGINE_API __declspec(dllexport)

#else
#define ENGINE_API __declspec(dllimport)

#endif

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define IN
#define OUT
#define INOUT
#define ABSTRACT = 0;

// 메모리 정리 함수
template <typename T>
void SafeDelete(T*& target)
{
	if (target)
	{
		delete target;
		target = nullptr;
	}
}

// 메모리 정리 함수
template <typename T>
void SafeDeleteArray(T*& target)
{
	if (target)
	{
		delete[] target;
		target = nullptr;
	}
}

#endif
