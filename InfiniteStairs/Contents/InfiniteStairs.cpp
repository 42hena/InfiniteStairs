#include "InfiniteStairs.h"



#include "Level/TitleLevel.h"
#include "Level/InGameLevel.h"

InfiniteStairs::InfiniteStairs()
{
	// 타이틀 레벨
	RegisterLevel(new TitleLevel());
	RegisterLevel(new InGameLevel());

	// Engine의 main 씬 지정
	AddLevel(_levels[Scene_Title]);
}

InfiniteStairs::~InfiniteStairs()
{
	// TODO: Level 제거 필요
}

/*
*	
*/

void InfiniteStairs::RegisterLevel(Level* pLevel)
{
	_levels.push_back(pLevel);
}
