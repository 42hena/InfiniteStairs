#pragma once

#include "Engine.h"

#include "Contents/InfiniteStairs.h"

class IFunctor {
public:

	virtual void Excute() ABSTRACT;
	void operator()()
	{
		Excute();
	}
};

class ChangeLevelFunctor : public IFunctor {
public:
	ChangeLevelFunctor(Scene sceneNum)
		:_sceneNum(sceneNum)
	{
	}
	virtual void Excute()override {
		InfiniteStairs::GetInstance().ChangeLevel(_sceneNum);
	}

private:
	Scene _sceneNum;
};

class ExitFunctor : public IFunctor {
public:
	ExitFunctor()
	{
	}
	virtual void Excute()override {
		Engine::GetInstance().Quit();
	}
};