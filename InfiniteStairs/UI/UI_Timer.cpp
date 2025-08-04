#include "UI_Timer.h"

#include "Utils/Utils.h"

#include <iostream>

ClimbTimer::ClimbTimer()
	:Actor(L"", Color::Color_Red),
	_remainGauge(10.0f)
{
	Vector2 pos = Position();
	pos._x = 15;
	pos._y = 0;
	SetPosition(pos);
}

ClimbTimer::~ClimbTimer()
{
}

void ClimbTimer::Tick(float deltaTime)
{
	if (_flag == false)
		return;
	_remainGauge.ReduceTime(deltaTime);
	if (_remainGauge.IsTimerExpired() == true)
	{
		int a = 0;
	}

}

void ClimbTimer::Render()
{
	// super::Render();

	Utils::SetConsolePosition(Position());

	Utils::SetConsoleTextColor(Color::Color_Blue);
	wchar_t buff[200];
	std::wcout << GetRemainGaugeStr(buff, 200);
}

wchar_t* ClimbTimer::GetRemainGaugeStr(wchar_t* buff, size_t size)
{
	int tt = swprintf_s(buff, size, L"remain Time : %f", _remainGauge.RemainTime());
	buff[tt] = 0;
	return buff;
}
