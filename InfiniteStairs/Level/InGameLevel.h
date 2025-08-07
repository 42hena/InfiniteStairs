#pragma once

#include "Level/Level.h"
#include "Contents/StairGenerator.h"

class Player;
class InGameLevel : public Level
{
	RTTI_DECLARATIONS(InGameLevel, Level)

public:
	InGameLevel();
	~InGameLevel();

public:
	virtual void Tick(float deltaTime)	override;
	virtual void Clear()				override;
	virtual void Reset()				override;

	void OnMovedStairs(int x, int y);
	void OnCreateStairs(int x, int y);
	void OnPressDown() { _keyPressFlag = true; }
	void OnResetTimer();

	bool IsColliding(Player *pPlayer);

	bool _keyPressFlag = false;
	StairGenerator _generator;
};
