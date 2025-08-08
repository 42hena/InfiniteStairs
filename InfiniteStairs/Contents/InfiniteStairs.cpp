#include "InfiniteStairs.h"



#include "Level/TitleLevel.h"
#include "Level/InGameLevel.h"
#include "../../Engine/Level/Level.h"


InfiniteStairs* InfiniteStairs::_static_instance = nullptr;

InfiniteStairs::InfiniteStairs()
{
	_static_instance = this;

	// 타이틀 레벨
	RegisterLevel(new TitleLevel());
	RegisterLevel(new InGameLevel());

	// Engine의 main 씬 지정
	_levelIndex = Scene_Title;
	AddLevel(_levels[_levelIndex]);
}

InfiniteStairs::~InfiniteStairs()
{
	/*isQuit = true;
	_mainLevel = nullptr;*/
	for (auto* Level : _levels) {
		SafeDelete(Level);
	}
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

	_levelIndex = sceneNum;

	_mainLevel->Clear();
	_nextLevel = _levels[_levelIndex];
	_levelChangeFlag = true;
}

void InfiniteStairs::CleanUp()
{
	this->~InfiniteStairs();
}
