#include "InGameLevel.h"
#include "Engine.h"
#include "Actor/Player.h"
#include "Actor/Stair.h"
InGameLevel::InGameLevel()
	:_generator(3, 1)
{
	const char* player[] = {
	"###",
	"###",
	"###",
	"###",
	"###",
	nullptr
	};

	const char* stair = "===";

	Vector2 i(Engine::GetInstance().Width() / 2, Engine::GetInstance().Height() / 2);
	AddActor(new Player(player,Direction_Left));
	for (int i = 0; i < 1; ++i)
	{
		Stair* pNewStair = _generator.InitGenerate();
		AddActor(pNewStair);
	}
}

InGameLevel::~InGameLevel()
{
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
