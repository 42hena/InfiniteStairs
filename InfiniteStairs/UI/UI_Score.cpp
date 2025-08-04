#include "UI_Score.h"

#include "Utils/Utils.h"

#include <iostream>

Score::Score(const Vector2& rPosition)
	:Actor(L"", Color::Color_White, rPosition)
{
}

void Score::Tick(float deltaTime)
{
}

void Score::Render()
{
	// ºÎ¸ð Æ½ ¹«½Ã.
	Utils::SetConsolePosition(Position());

	Utils::SetConsoleTextColor(Color::Color_Blue);
	wchar_t buff[200];
	std::wcout << GetScoreStr(buff, 200);
}

wchar_t* Score::GetScoreStr(wchar_t* buff, size_t size)
{
	int tt = swprintf_s(buff, size, L"Score : %d", _score);
	buff[tt] = 0;
	return buff;
}
