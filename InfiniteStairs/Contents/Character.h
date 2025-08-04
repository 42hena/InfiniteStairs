#pragma once


class Character
{
public:
	Character(const wchar_t* str);
	Character(const wchar_t** str);
	Character(const Character& rhs);
	Character(Character&& rhs) noexcept;
	Character& operator=(const Character& rhs);
	Character& operator=(Character&& rhs);
	~Character();

public:
	inline int Width() { return _width; }
	inline int Height() { return _height; }
	inline wchar_t** GetCharacterPtr() { return _character; }


private:
	void Clear();
	int GetInputWidget(const wchar_t* str);
	int GetInputHeight(const wchar_t** str);

private:
	int _width;
	int _height;

	wchar_t** _character;
};