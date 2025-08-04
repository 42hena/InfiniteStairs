#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "Core.h"
#include <vector>
#include "RTTI.h"

class Actor;
class ENGINE_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)

#pragma region 특수 맴버 함수
public:
	Level();
	virtual ~Level();
#pragma endregion

#pragma region 공개 함수
public:
	/*
	*		이벤트 함수
	*/
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

	/*
	*		객체 관리 함수
	*/
	void AddActor(Actor* newActor);	// Level에서 돌아다닐 객체 생성 함수
	void DestroyActor(Actor* destroyedActor);
	void ProcessAddAndDestroyActors();
	
	
	void AddUIActor(Actor* newActor);	// Level에서 돌아다닐 객체 생성 함수
	void DestroyUIActor(Actor* destroyedActor);
	void ProcessUIAddAndDestroyActors();

#pragma endregion

#pragma region 내부 함수
private:
	void SortActorsBySortingOrder();
#pragma endregion

#pragma region 멤버 변수
protected:
	std::vector<Actor*> _actors;
	std::vector<Actor*> _addRequestActors;
	std::vector<Actor*> _destroyRequestActors;

	std::vector<Actor*> _UIActors;
	std::vector<Actor*> _addRequestUIActors;
	std::vector<Actor*> _destroyRequestUIActors;
#pragma endregion
};

#endif
