#include "UI_GameHUD.h"

#include "Utils/Utils.h"

#include <iostream>

GameHUD::GameHUD(const Vector2& rPosition, int width, int height)
	:_position(rPosition),
	_width(width),
	_height(height)
{
	_pOutline = new wchar_t[width + 1];
	for (int i = 0; i < width; ++i)
		_pOutline[i] = L'#';
	_pOutline[width] = L'\0';
}

GameHUD::~GameHUD()
{
	SafeDeleteArray(_pOutline);
}

void GameHUD::Render()
{
	for (int i = 0; i < _height; ++i) {
		if (i == 0 || i == _height - 1)
		{
			Vector2 pos(0, i);
			Utils::SetConsolePosition(pos);
			std::wcout << _pOutline;
			continue;
		}
		Vector2 pos(0, i);
		Utils::SetConsolePosition(pos);
		std::wcout << L"■";
		pos._x += (_width - 1);
		Utils::SetConsolePosition(pos);
		std::wcout << L"■";
	}
}
