#include "InfiniteStairs.h"



#include "Level/TitleLevel.h"
#include "Level/InGameLevel.h"

InfiniteStairs::InfiniteStairs()
{
	// Ÿ��Ʋ ����
	RegisterLevel(new TitleLevel());
	RegisterLevel(new InGameLevel());

	// Engine�� main �� ����
	AddLevel(_levels[Scene_Title]);
}

InfiniteStairs::~InfiniteStairs()
{
	// TODO: Level ���� �ʿ�
}

/*
*	
*/

void InfiniteStairs::RegisterLevel(Level* pLevel)
{
	_levels.push_back(pLevel);
}
