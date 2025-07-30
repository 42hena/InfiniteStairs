#pragma once

#include "Level/Level.h"

class InGameLevel : public Level
{
	RTTI_DECLARATIONS(InGameLevel, Level)

public:
	InGameLevel();
	~InGameLevel();
};