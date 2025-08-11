#ifndef __UI_MAX_SCORE_H__
#define __UI_MAX_SCORE_H__

#include "Actor/Actor.h"
#include "Math/Vector2.h"
#include "Contents/InfiniteStairs.h"

class MaxScore : public Actor
{
	RTTI_DECLARATIONS(MaxScore, Actor)
public:
	MaxScore(const Vector2& rPosition);
	~MaxScore();

public:

	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

	wchar_t* GetScoreStr(wchar_t* buff, size_t len);

	void OnEarnScore(int score) {
		_score += 1;
		if (global_score < _score)
			global_score = _score;
	}

private:
	int		_score = 0;
	FILE* _fp;
};

#endif