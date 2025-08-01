#pragma once

#include "Level/Level.h"
#include "Contents/StairGenerator.h"

class InGameLevel : public Level
{
	RTTI_DECLARATIONS(InGameLevel, Level)

public:
	InGameLevel();
	~InGameLevel();

public:
	virtual void Tick(float deltaTime)override;

	void OnMovedStairs(int x, int y);
	void OnCreateStairs(int x, int y);
	void OnPressDown() { _gameFlag = true; }
	//void ChangePosition(int x, int y);
	bool _gameFlag = false;
	StairGenerator _generator;
};
