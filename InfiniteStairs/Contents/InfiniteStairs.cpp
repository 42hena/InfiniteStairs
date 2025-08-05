#include "InfiniteStairs.h"



#include "Level/TitleLevel.h"
#include "Level/InGameLevel.h"
#include "../../Engine/Level/Level.h"


InfiniteStairs* InfiniteStairs::_static_instance = nullptr;

InfiniteStairs::InfiniteStairs()
{
	_static_instance = this;

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

void InfiniteStairs::ChangeLevel(Scene sceneNum)
{
	if (_levelIndex == sceneNum || sceneNum >= Scene_Count) {
		DebugBreak();
		return;
	}

	_mainLevel = _levels[sceneNum];
}