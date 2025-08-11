#ifndef __INFINITE_STAIRS_H__
#define __INFINITE_STAIRS_H__

#include "Engine.h"
#include <vector>
#include "Level/Level.h"

enum Scene
{
	Scene_Title,
	Scene_InGame,
	Scene_Menu,
	Scene_Count
};

class InfiniteStairs : public Engine
{

public:
	InfiniteStairs();
	~InfiniteStairs();

	InfiniteStairs(const InfiniteStairs& rhs)				= delete;
	InfiniteStairs(InfiniteStairs&& rhs)					= delete;
	InfiniteStairs& operator=(const InfiniteStairs& rhs)	= delete;
	InfiniteStairs& operator=(InfiniteStairs&& rhs)			= delete;

public:
	static InfiniteStairs& GetInstance() { return *_static_instance; }

public:
	void RegisterLevel(Level* pLevel);
	void ChangeLevel(Scene sceneNum);

	virtual void CleanUp() override;

private:
	static InfiniteStairs*		_static_instance;

private:
	std::vector<class Level*>	_levels;
	Scene						_levelIndex = Scene_Title;
};

extern int global_score;

#endif
