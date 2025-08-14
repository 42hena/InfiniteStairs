#include "UI_MaxScore.h"

#include "Engine.h"
#include "Utils/Utils.h"

#include <iostream>

MaxScore::MaxScore(const Vector2& rPosition)
	:Actor(L"", Color::Color_White, rPosition)
{
	fopen_s(&_fp, "Score.txt", "r+");
	if (_fp == nullptr)
	{
		return;
		DebugBreak();
	}
	fscanf_s(_fp, "%d", &global_score);
}

MaxScore::~MaxScore()
{
	fseek(_fp, 0, SEEK_SET);
	fprintf_s(_fp, "%d", global_score);
}

void MaxScore::Tick(float deltaTime)
{
}

void MaxScore::Render()
{
	wchar_t buff[200];
	GetScoreStr(buff, 200);
	Engine::GetInstance().DrawDefault((const wchar_t*)&buff, Position(), Color::Color_Green);
}

wchar_t* MaxScore::GetScoreStr(wchar_t* buff, size_t size)
{
	int tt = swprintf_s(buff, size, L"Score : %d", global_score);
	buff[tt] = 0;
	return buff;
}
