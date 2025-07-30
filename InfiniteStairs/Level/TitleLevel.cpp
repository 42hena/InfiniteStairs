#include "TitleLevel.h"
#include "Input.h"

#include "Engine.h"
#include "Utils/Utils.h"

#include <iostream>

TitleLevel::TitleLevel()
{
	_items.emplace_back(new TitleItem(
		"  ____                        ____  _             _    \n"
		"/ ___ | __ _ _ __ ___   ___  / ___|| |_ __ _ _ __| |_  \n"
		"| |  _ / _` | '_ ` _ \\ / _ \\ \\___ \\| __/ _` | '__ | __|\n"
		"| |_| | (_| | | | | | |  __ / ___) | || (_| | |  | |_  \n"
		"\\____ |\\__,_|_| |_| |_|\\___| |____ /\\__\\__,_|_|  \\__ | \n",
		[]() {

		}
	));
	_items.emplace_back(new TitleItem(
		"      _                 \n"
		"  ___| |_ ___  _ __ ___ \n"
		" / __| __/ _ \\| '__/ _ \\\n"
		" \\__ \\ || (_) | | |  __/\n"
		" |___/\\__\\___/|_|  \\___|\n",
		[]() {

		}
	));
	_items.emplace_back(new TitleItem(
		"   ___        _ _   \n"
		"  / _ \\ _   _(_) |_ \n"
		" | | | | | | | | __|\n"
		" | |_| | |_| | | |_ \n"
		"  \\__\\_\\\\__,_|_|\\__|\n",
		[]() {
			Engine::GetInstance().Quit();
		}
	));

	// 아이템 수 미리 저장
	_titleItemLength = static_cast<int>(_items.size());	// size_t -> int
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 입력 처리
	if (Input::GetInstance().GetKeyDown(VK_UP))
	{
		_currentIndex = (_currentIndex - 1 + _titleItemLength) % _titleItemLength;
	}
	if (Input::GetInstance().GetKeyDown(VK_DOWN))
	{
		_currentIndex = (_currentIndex + 1) % _titleItemLength;
	}
	if (Input::GetInstance().GetKeyDown(VK_RETURN))
	{
		_items[_currentIndex]->_fOnSelected();
	}
}

void TitleLevel::Render()
{
	super::Render();

	std::cout << _pTitle;
	
	Utils::SetConsolePosition(COORD{ 0, 10 });
	Utils::SetConsoleTextColor(static_cast<WORD>(_unSelectedColor));

	for (int idx = 0; idx < _titleItemLength; ++idx)
	{
		Color textColor = (idx == _currentIndex) ? _selectedColor : _unSelectedColor;
	 
		Utils::SetConsoleTextColor(static_cast<WORD>(textColor));

		std::cout << _items[idx]->_titleText << "\n";
	}
}
