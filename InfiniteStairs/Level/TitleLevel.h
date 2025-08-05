#pragma once

#ifndef __TITLE_LEVEL_H__
#define __TITLE_LEVEL_H__

#include "Level/Level.h"

#pragma once

#include "Level/Level.h"

#include "Actor/Actor.h"

#include <vector>

class TitleLevel : public Level
{
	RTTI_DECLARATIONS(TitleLevel, Level)

public:
	TitleLevel();
	~TitleLevel();
public:
	virtual void Tick(float deltaTime)	override;
	virtual void Render()				override;


private:
	int _currentIndex = 0;

	Color _selectedColor = Color::Color_Green;
	Color _unSelectedColor = Color::Color_White;


	int _titleItemLength = 0;
};

#endif
