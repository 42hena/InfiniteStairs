#pragma once

#include "Actor/Actor.h"
#include "Math/Vector2.h"
#include "Contents/Timer.h"

class Character;
class ClimbTimer : public Actor
{
	RTTI_DECLARATIONS(ClimbTimer, Actor)

#pragma region Ư�� ��� �Լ�
public:
	ClimbTimer(const Vector2& rPosition);
	ClimbTimer(Character* pImage, const Vector2& rPosition);
	virtual ~ClimbTimer()						override;

	ClimbTimer(const ClimbTimer&)				= default;
	ClimbTimer(ClimbTimer&&)					= default;
	ClimbTimer& operator=(const ClimbTimer&)	= default;
	ClimbTimer& operator=(ClimbTimer&&)			= default;
#pragma endregion

#pragma region ���� �Լ�
public:	/* �̺�Ʈ �Լ� */
	virtual void Tick(float deltaTime)	override;
	virtual void Render()				override;


	virtual void Reset()				override;


public:	
	/* �ʱ�ȭ �Լ� */
	void		ClearTimer();
	void		Destroy();

	/* Getter */
	wchar_t*	GetRemainGaugeStr(wchar_t* buff, size_t len);

public:	/* Call back �Լ� */
	void OnBeginTime() { _isRunningFlag = true;}
#pragma endregion

private:
	inline bool Flag()				const	{ return _isRunningFlag; }
	inline void SetFlag(bool flag)			{ _isRunningFlag = flag; }

#pragma region ��� ����
private:
	Character*	_pImage = nullptr;
	bool		_isRunningFlag = false;
	FadeGauge	_remainGauge;
#pragma endregion
};
