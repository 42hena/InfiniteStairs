#include "Level.h"

#include "Actor/Actor.h"

#include "Utils/Utils.h"

#include <iostream>

/*
*		특수 멤버 함수
*/

Level::Level()
{
	// std::cout << "Level: " << Level::TypeIdClass() << "\n";
}

Level::~Level()
{
	for (const Actor* actor : _actors)	{
		SafeDelete(actor);
	}
	_actors.clear();
}

/*
*		이벤트 함수
*/

void Level::BeginPlay()
{
	for (Actor* const actor : _actors)
	{
		// 액터 처리 여부 확인
		if (actor->_isActive == false || actor->_isExpired == true) {
			continue;
		}

		if (actor->HasBeginPlay() == true) { 
			continue; 
		}

		actor->BeginPlay();
	}
}

void Level::Tick(float deltaTime)
{
	for (Actor* const actor : _actors) {
		// 액터 처리 여부 확인
		if (actor->_isActive == false || actor->_isExpired == true) {
			continue;
		}
		actor->Tick(deltaTime);
	}

	for (Actor* const actor : _UIActors) {
		// 액터 처리 여부 확인
		if (actor->_isActive == false || actor->_isExpired == true) {
			continue;
		}
		actor->Tick(deltaTime);
	}
}

void Level::Render()
{
	// 정렬해서 재배치
	SortActorsBySortingOrder();

	// RenderPass
	for (Actor* const actor : _actors) {
		// 액터 처리 여부 확인
		if (actor->_isActive == false || actor->_isExpired == true) {
			continue;
		}
		actor->Render();
	}

	for (Actor* const actor : _UIActors) {
		if (actor->_isActive == false || actor->_isExpired == true) {
			continue;
		}
		actor->Render();
	}
}

/*
*		객체 관리 함수
*/

void Level::AddActor(Actor* newActor)
{
	// 객체 추가 요청
	_addRequestActors.emplace_back(newActor);
}

void Level::DestroyActor(Actor* destroyedActor)
{
	// 객체 추가 요청
	_destroyRequestActors.emplace_back(destroyedActor);
}

void Level::ProcessAddAndDestroyActors()
{
	for (auto iter = _actors.begin(); iter != _actors.end(); /* iter 증가 없음 */) {
		// case : 만료된 actor
		if ((*iter)->_isExpired)
		{
			iter = _actors.erase(iter);
			continue;
		}
		++iter;
	}

	for (auto*& pActor : _destroyRequestActors) {
		Utils::SetConsolePosition(pActor->Position());

		for (int i = 0 ; i < pActor->Width() ; ++i) { 
			std::wcout << " ";
		}
		SafeDelete(pActor);
	}
	_destroyRequestActors.clear();

	for (Actor* pActor : _addRequestActors)
	{
		pActor->SetOwner(this);
		_actors.emplace_back(pActor);
	}
	_addRequestActors.clear();
}

void Level::AddUIActor(Actor* newActor)
{
	// 객체 추가 요청
	_addRequestUIActors.emplace_back(newActor);
}

void Level::DestroyUIActor(Actor* destroyedActor)
{
	// 객체 추가 요청
	_destroyRequestUIActors.emplace_back(destroyedActor);
}

void Level::ProcessUIAddAndDestroyActors()
{
	for (auto iter = _UIActors.begin(); iter != _UIActors.end(); /* iter 증가 없음 */) {
		// case : 만료된 actor
		if ((*iter)->_isExpired)
		{
			iter = _UIActors.erase(iter);
			continue;
		}
		++iter;
	}

	for (auto*& pActor : _destroyRequestUIActors) {
		Utils::SetConsolePosition(pActor->Position());

		for (int i = 0; i < pActor->Width(); ++i) {
			std::cout << " ";
		}
		SafeDelete(pActor);
	}
	_destroyRequestUIActors.clear();

	for (Actor* pActor : _addRequestUIActors)
	{
		pActor->SetOwner(this);
		_UIActors.emplace_back(pActor);
	}
	_addRequestUIActors.clear();
}

/*
*		내부 함수
*/

void Level::SortActorsBySortingOrder()
{
	for (int idx = 0; idx < static_cast<int>(_actors.size()); ++idx)
	{
		for (int j = 0; j < static_cast<int>(_actors.size()) - 1 ; ++j)
		{
			if (_actors[j]->_sortingOrder > _actors[j + 1]->_sortingOrder)
			{
				std::swap(_actors[j], _actors[j + 1]);
			}
		}
	}
}
