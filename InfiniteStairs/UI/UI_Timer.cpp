#include "UI_Timer.h"

#include "Engine.h"

#include "Utils/Utils.h"

#include "Level/InGameLevel.h"

#include <iostream>
#include "Contents/Character.h"
#include "Contents/InfiniteStairs.h"


ClimbTimer::ClimbTimer(const Vector2& rPosition)
	:Actor(L"", Color::Color_Red, rPosition),
	_remainGauge(10.0f)
{
}

ClimbTimer::ClimbTimer(Character* pImage, const Vector2& rPosition)
	:Actor(L"", Color::Color_Red, rPosition),
	_remainGauge(10.0f),
	_pImage(std::move(pImage))
{
}

ClimbTimer::~ClimbTimer()
{
	if (_pImage != nullptr) {
		SafeDelete(_pImage);
	}
}

void ClimbTimer::Tick(float deltaTime)
{
	if (Flag() == false)
		return;
	_remainGauge.ReduceTime(deltaTime);


	// Game이 끝나야 정상...
	if (_remainGauge.IsTimerExpired() == true)
	{
		// TODO: 게임 끝나는 로직 추가.
		int a = 0;
		/*Level* pLevel = GetOwner();

		InGameLevel* pRealLevel = dynamic_cast<InGameLevel*>(pLevel);
		pRealLevel->ChangeLevel(Scene_Title);*/
		InfiniteStairs::GetInstance().ChangeLevel(Scene_Title);
	}
}

void ClimbTimer::Render()
{
	// super::Render();
	Vector2 Test(40, 0);
	wchar_t** ppImage = _pImage->GetCharacterPtr();
	for (int i = 0; i < _pImage->Height(); ++i)
	{
		Engine::GetInstance().Draw(ppImage[i], Test);
		Test._y = Test._y + 1;
	}
	int gauge = static_cast<int>(_remainGauge.RemainTime() * 4);
	std::wstring str;
	for (int i = 0; i < gauge; ++i)
		str += L"▓";
	Test._x += 1;
	Test._y = Test._y - _pImage->Height() + 1;
	for (int h = 0; h < _pImage->Height() - 2; ++h)
	{
		Engine::GetInstance().Draw(str.data(), Test);
		Test._y = Test._y + 1;
	}

	wchar_t buff[200];
	GetRemainGaugeStr(buff, 200);
	Engine::GetInstance().DrawDefault((const wchar_t*)& buff, Position(), Color::Color_Green);
}

void ClimbTimer::Reset()
{
	SetFlag(false);	// TODO : 마음에 안들음.
	ClearTimer();
}

void ClimbTimer::ClearTimer()
{
	_remainGauge.ResetTimer();
}

wchar_t* ClimbTimer::GetRemainGaugeStr(wchar_t* buff, size_t size)
{
	int tt = swprintf_s(buff, size, L"remain Time : %f", _remainGauge.RemainTime());
	buff[tt] = 0;
	return buff;
}
