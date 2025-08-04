#include "Timer.h"

/*
*		
*/

Timer::Timer(float initialTime)
	: _initialTime(initialTime),
	_remainTime(initialTime)
{

}

Timer::~Timer()
{

}

/*
*		
*/

bool Timer::IsTimerExpired()
{
	if (_remainTime <= 0.0f) {
		return true;
	}
	return false;
}

void Timer::ResetTimer()
{
	_remainTime = _initialTime;
}

void Timer::ReduceTime(float deltaTime)
{
	_remainTime -= deltaTime;
}

void Timer::SetInitialTime(float initialTime)
{
	_initialTime = initialTime;
	ResetTimer();
}

FadeGauge::FadeGauge(float initialTime, float gaugeSpeed)
	: Timer(initialTime),
	_gaugeSpeed(gaugeSpeed)
{
}

FadeGauge::~FadeGauge()
{
}

void FadeGauge::ReduceTime(float deltaTime)
{
	_remainTime -= deltaTime * _gaugeSpeed;
}

void FadeGauge::SpeedUp(float speed)
{
	_gaugeSpeed += speed;
}

void FadeGauge::SpeedDown(float speed)
{
	_gaugeSpeed -= speed;
}
