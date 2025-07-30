#pragma once

#ifndef __TITLE_LEVEL_H__
#define __TITLE_LEVEL_H__

#include "Level/Level.h"

#pragma once

#include "Level/Level.h"

#include "Actor/Actor.h"

#include <vector>

struct TitleItem
{
	using OnSelected = void(*)();

	TitleItem(const char* text, OnSelected onSelected)
		: _fOnSelected(onSelected)
	{
		size_t length = strlen(text) + 1;
		_titleText = new char[length];
		strcpy_s(_titleText, length, text);
	}

	~TitleItem()
	{
		SafeDeleteArray(_titleText);
	}

	// 메뉴 Text
	char* _titleText = nullptr;

	// 메뉴 선택 시 실행할 동작
	OnSelected _fOnSelected = nullptr;
};

class TitleLevel : public Level
{
	RTTI_DECLARATIONS(TitleLevel, Level)

public:
	TitleLevel();
	~TitleLevel();
public:
	virtual void Tick(float deltaTime)	override;
	virtual void Render()				override;


private:
	int _currentIndex = 0;

	Color _selectedColor = Color::Color_Green;
	Color _unSelectedColor = Color::Color_White;


	int _titleItemLength = 0;

private:
		const char* _pTitle =
		" ______             ______   __            __    __                       ______    __                __                           \n"
		"/      |           /      \\ /  |          /  |  /  |                     /      \\  /  |              /  |                        \n"
		"$$$$$$/  _______  /$$$$$$  |$$/  _______  $$/  _$$ |_     ______        /$$$$$$  |_$$ |_     ______  $$/   ______    _______       \n"
		"  $$ |  /       \\ $$ |_ $$/ /  |/       \\ /  |/ $$   |   /      \\       $$ \\__$$// $$   |   /      \\ /  | /      \\  /      | \n"
		"  $$ |  $$$$$$$  |$$   |    $$ |$$$$$$$  |$$ |$$$$$$/   /$$$$$$  |      $$      \\$$$$$$/    $$$$$$  |$$ |/$$$$$$  |/$$$$$$$/      \n"
		"  $$ |  $$ |  $$ |$$$$/     $$ |$$ |  $$ |$$ |  $$ | __ $$    $$ |       $$$$$$  | $$ | __  /    $$ |$$ |$$ |  $$/ $$      \\      \n"
		" _$$ |_ $$ |  $$ |$$ |      $$ |$$ |  $$ |$$ |  $$ |/  |$$$$$$$$/       /  \\__$$ | $$ |/  |/$$$$$$$ |$$ |$$ |       $$$$$$  |     \n"
		"/ $$   |$$ |  $$ |$$ |      $$ |$$ |  $$ |$$ |  $$  $$/ $$       |      $$    $$/  $$  $$/ $$    $$ |$$ |$$ |      /     $$/       \n"
		"$$$$$$/ $$/   $$/ $$/       $$/ $$/   $$/ $$/    $$$$/   $$$$$$$/        $$$$$$/    $$$$/   $$$$$$$/ $$/ $$/       $$$$$$$/        \n";

		
		std::vector<TitleItem*> _items;
};

#endif
