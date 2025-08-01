#include "InGameLevel.h"
#include "Engine.h"
#include "Actor/Player.h"
#include "Actor/Stair.h"
InGameLevel::InGameLevel()
	:_generator(3, 1)
{
	const char* l[] = {"<##", nullptr};
	const char* r[] = {"##>", nullptr};
	const char** player[2] = {
		l,r
	};

	const char* stair = "===";

	Vector2 i(Engine::GetInstance().Width() / 2, Engine::GetInstance().Height() / 2);
	AddActor(new Player(player,Direction_Left));
	for (int i = 0; i < 10; ++i)
	{
		Stair* pNewStair = _generator.InitGenerate();
		AddActor(pNewStair);
	}
}

InGameLevel::~InGameLevel()
{
}

void InGameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);


	if (_gameFlag)
	{
		// 충돌 확인
		Player* pPlayer = nullptr;
		for (Actor* pActor : _actors)
		{
			pPlayer = pActor->As<Player>();
			if (pPlayer != nullptr)
			{
				break;
			}
		}
		// if ()
		// TODO: 키 입력 시에만 확인
		bool flag = false;
		for (Actor* pActor : _actors)
		{
			if (pPlayer == pActor) {
				continue;
			}

			if (pActor->As<Stair>() == nullptr) {
				DebugBreak();
			}

			// 여기서 충돌 확인
			Stair* pStair = static_cast<Stair*>(pActor);
			flag = pPlayer->IsColliding(pStair->GetCollider());
			if (flag == true)
				break;
		}

		if (flag == false)
		{
			DebugBreak();
		}


		_gameFlag = false;
	}
}

void InGameLevel::OnMovedStairs(int x, int y)
{
	for (Actor* pActor : _actors)
	{
		if (pActor->As<Player>()) {
			continue;
		}

		Vector2 position(pActor->Position());


		Vector2 newPosition(position._x - x *  pActor->Width(), position._y - y);
		pActor->SetPosition(newPosition);
	}
	/*Vector2 newPosition(position._x + w, position._y + h);
	pActor->SetPosition(newPosition);*/
}

void InGameLevel::OnCreateStairs(int x, int y)
{
	_generator.MoveLastStair(-x * 3, -y);
	Stair* pStair = _generator.InitGenerate();
	AddActor(pStair);
}

/*
*	
*/

//void InGameLevel::ChangePosition(int x, int y)
//{
//	for (Actor* pActor : _actors)
//	{
//		if (pActor->As<Player>()) {
//			continue;
//		}
//
//		Vector2 position(pActor->Position());
//		int w = pActor->Width();
//		int h = pActor->Height();
//		Vector2 newPosition(position._x + x, position._y + 1);
//		pActor->SetPosition(newPosition);
//	}
//
//	/*Vector2 newPosition(position._x + w, position._y + h);
//	pActor->SetPosition(newPosition);*/
//}
