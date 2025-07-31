#include "InfiniteStairs.h"



#include "Level/TitleLevel.h"
#include "Level/InGameLevel.h"
#include "../../Engine/Level/Level.h"

InfiniteStairs::InfiniteStairs()
{
	// Ÿ��Ʋ ����
	RegisterLevel(new TitleLevel());
	RegisterLevel(new InGameLevel());

	// Engine�� main �� ����
	AddLevel(_levels[Scene_InGame]);
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
