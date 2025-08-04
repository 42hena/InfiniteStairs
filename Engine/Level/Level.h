#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "Core.h"
#include <vector>
#include "RTTI.h"

class Actor;
class ENGINE_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)

#pragma region Ư�� �ɹ� �Լ�
public:
	Level();
	virtual ~Level();
#pragma endregion

#pragma region ���� �Լ�
public:
	/*
	*		�̺�Ʈ �Լ�
	*/
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

	/*
	*		��ü ���� �Լ�
	*/
	void AddActor(Actor* newActor);	// Level���� ���ƴٴ� ��ü ���� �Լ�
	void DestroyActor(Actor* destroyedActor);
	void ProcessAddAndDestroyActors();
	
	
	void AddUIActor(Actor* newActor);	// Level���� ���ƴٴ� ��ü ���� �Լ�
	void DestroyUIActor(Actor* destroyedActor);
	void ProcessUIAddAndDestroyActors();

#pragma endregion

#pragma region ���� �Լ�
private:
	void SortActorsBySortingOrder();
#pragma endregion

#pragma region ��� ����
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
