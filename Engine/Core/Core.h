#ifndef __CORE_H__
#define __CORE_H__

#pragma warning(disable: 4251)	// dll �ܺη� ���ø� ������ �� �߻���
#pragma warning(disable: 4172)	// �Լ� ���� static ������ �ּҷ� ��� �� �߻�

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

// �޸� ���� �Լ�
template <typename T>
void SafeDelete(T*& target)
{
	if (target)
	{
		delete target;
		target = nullptr;
	}
}

// �޸� ���� �Լ�
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
