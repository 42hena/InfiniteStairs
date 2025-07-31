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
	void OnMovedStairs(int x, int y);
	void OnCreateStairs(int x, int y);
	//void ChangePosition(int x, int y);

	StairGenerator _generator;
};
