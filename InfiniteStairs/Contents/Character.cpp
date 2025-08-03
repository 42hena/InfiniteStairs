#include "Character.h"

#include <string>
#include <Windows.h>

Character::Character(const wchar_t* str)
{
	_width = GetInputWidget(str);
	_height = 1;
	_character = new wchar_t*[2];

	for (int i = 0; i < _height; ++i)
	{
		_character[i] = new wchar_t[_width + 1];
		wcscpy_s(_character[i], _width + 1, str);
	}
	_character[_height] = nullptr;
}

Character::Character(const wchar_t** str)
{
	_height = GetInputHeight(str);
	_character = new wchar_t*[_height + 1];

	for (int i = 0; i < _height; ++i)
	{
		_width = GetInputWidget(str[i]);
		_character[i] = new wchar_t[_width + 1];
		wcscpy_s(_character[i], _width + 1, str[i]);
	}
	_character[_height] = nullptr;
}

Character::~Character()
{
	for (int i = 0; i < _height + 1; ++i){
		delete _character[i];
	}
	delete _character;
}

/*
*		내부 함수
*/

int Character::GetInputWidget(const wchar_t* str)
{
	return wcslen(str);
}

int Character::GetInputHeight(const wchar_t** str)
{
	int height = 0;
	while (*str != nullptr) {
		++height;
		++str;
	}
	return height;
}
