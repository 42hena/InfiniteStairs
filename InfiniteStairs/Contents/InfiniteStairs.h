#ifndef __INFINITE_STAIRS_H__
#define __INFINITE_STAIRS_H__

#include "Engine.h"
#include <vector>
#include "Level/Level.h"

class InfiniteStairs : public Engine
{
	enum Scene
	{
		Scene_Title,
		Scene_InGame,
		Scene_Menu,
	};

public:
	InfiniteStairs();
	~InfiniteStairs();

	InfiniteStairs(const InfiniteStairs& rhs)				= delete;
	InfiniteStairs(InfiniteStairs&& rhs)					= delete;
	InfiniteStairs& operator=(const InfiniteStairs& rhs)	= delete;
	InfiniteStairs& operator=(InfiniteStairs&& rhs)			= delete;

public:
	void RegisterLevel(Level* pLevel);

private:
	std::vector<class Level*> _levels;
};

#endif
