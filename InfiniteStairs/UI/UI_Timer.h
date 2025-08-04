#pragma once

#include "Actor/Actor.h"
#include "Math/Vector2.h"
#include "Contents/Timer.h"

class ClimbTimer : public Actor
{
	RTTI_DECLARATIONS(ClimbTimer, Actor)
public:
	ClimbTimer();
	~ClimbTimer();


public:
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;
	void ClearTimer()
	{
		_remainGauge.ResetTimer();
	}
	wchar_t* GetRemainGaugeStr(wchar_t* buff, size_t len);
	

	void OnBeginTime() { _flag = true;}

private:
	bool		_flag = false;
	Vector2		_position;
	FadeGauge	_remainGauge;
};
