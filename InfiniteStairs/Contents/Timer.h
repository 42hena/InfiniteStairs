#ifndef __TIMER_H__
#define __TIMER_H__

class Timer
{
public:
	Timer(float initialTime = 10.0f);
	virtual ~Timer();

public:
	bool IsTimerExpired();
	void ResetTimer();

	float RemainTime() const {	return _remainTime;	}

	virtual void EarnTime(float deltaTime);
	virtual void ReduceTime(float deltaTime);

	void SetInitialTime(float initialTime);

protected:
	float _initialTime = 10.0f;
	float _remainTime = 10.0f;
};

class FadeGauge : public Timer
{
public:
	FadeGauge(float initialTime, float gaugeSpeed = 1.0f);
	virtual ~FadeGauge() override;

public:
	virtual void ReduceTime(float deltaTime) override;
	void SpeedUp(float speed);
	void SpeedDown(float speed);

private:
	float _gaugeSpeed;
};

#endif
