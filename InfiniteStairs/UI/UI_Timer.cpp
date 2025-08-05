#include "UI_Timer.h"

#include "Engine.h"

#include "Utils/Utils.h"

#include <iostream>

ClimbTimer::ClimbTimer(const Vector2& rPosition)
	:Actor(L"", Color::Color_Red, rPosition),
	_remainGauge(10.0f)
{
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

	wchar_t buff[200];
	GetRemainGaugeStr(buff, 200);
	Engine::GetInstance().DrawDefault((const wchar_t*)& buff, Position(), Color::Color_Green);
}

wchar_t* ClimbTimer::GetRemainGaugeStr(wchar_t* buff, size_t size)
{
	int tt = swprintf_s(buff, size, L"remain Time : %f", _remainGauge.RemainTime());
	buff[tt] = 0;
	return buff;
}
