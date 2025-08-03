#pragma once


class Character
{
public:
	Character(const wchar_t* str);
	Character(const wchar_t** str);
	~Character();

public:
	inline int Width() { return _width; }
	inline int Height() { return _height; }
	inline wchar_t** GetCharacterPtr() { return _character; }

private:
	int GetInputWidget(const wchar_t* str);
	int GetInputHeight(const wchar_t** str);

private:
	int _width;
	int _height;

	wchar_t** _character;
};