#ifndef __UI_SCORE_H__
#define __UI_SCORE_H__

#include "Actor/Actor.h"
#include "Math/Vector2.h"

class Score : public Actor
{
	RTTI_DECLARATIONS(Score, Actor)
public:
	Score(const Vector2& rPosition);
public:

	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

	void OnEarnScore()
	{
		_score += 1;
	}

	void Clear() {
		_score = 0;
	}

	void GameStart() {
		Clear();
	}
	wchar_t* GetScoreStr(wchar_t* buff, size_t len);
	
	void OnEarnScore(int score) { _score += 1; }

private:
	int		_score = 0;
};

#endif