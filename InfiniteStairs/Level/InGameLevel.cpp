#include "InGameLevel.h"
#include "Engine.h"
#include "Actor/Player.h"
#include "Actor/Stair.h"


#include "UI/UI_Score.h"
#include "UI/UI_GameHUD.h"
#include "UI/UI_Timer.h"

#include "Contents/Character.h"

InGameLevel::InGameLevel()
	:_generator(11, 2)
{	
	//const wchar_t* wp[] = { L"<###>", L"<===>", nullptr};

	const wchar_t* wlp[] = { L"  ∧＿∧ =-   ", L"(´･ω･`)`つ=-", L"　`つ \ =-    ",L" 　\,⌒＼\,,,_=-", nullptr };
	const wchar_t* wrp[] = { L"　-= ∧＿∧    ", L"-=と(´･ω･`) ", L"　-=/　と_ノ   ",L"-=_/／⌒ｿ    ", nullptr };

	Character *playerL = new Character(wlp);
	Character *playerR = new Character(wrp);

	// const char* stair = "===";
	
	const wchar_t* stair[] = { L"╔═════════╗",L"╚═════════╝", nullptr};
	Character* pStair = new Character(stair);
	_generator.SetStairImage(pStair);
	int stairWidth = 11;
	int stairHeight = 2;

	Vector2 playerPos(66, 22);
	Vector2 playerColliderPos(0, 3);
	Collider* pPlayerCollider = new Collider(playerColliderPos, stairWidth, 2);
	 AddActor(new Player(playerL, playerR, playerPos, pPlayerCollider, Direction_Left));

	// 계단 생성

	_generator.SetStairWidth(stairWidth);
	_generator.SetStairHeight(stairHeight);
	for (int i = 0; i < 2; ++i)
	{
		Stair* pNewStair = _generator.InitGenerate();
		AddActor(pNewStair);
	}

	// Game UI 설정
	//Vector2 rr(51, 10);
	//AddUIActor(new Score(rr));
	//rr._x = 0;
	//rr._y = 0;
	//// AddUIActor(new GameHUD(rr, 41, 21));

	//AddUIActor(new ClimbTimer());
}

InGameLevel::~InGameLevel()
{
}

void InGameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	/* 키 입력 시 로직 */
	if (_keyPressFlag)
	{
		Player* pPlayer = nullptr;
		for (Actor* pActor : _actors)
		{
			pPlayer = pActor->As<Player>();
			if (pPlayer != nullptr) {
				break;
			}
		}
		
		bool collisionFlag = false;
		for (Actor* pActor : _actors)
		{
			if (pPlayer == pActor) {
				continue;
			}
			if (pActor->As<Stair>() == nullptr) {
				continue;
			}

			// 여기서 충돌 확인
			Stair* pStair = static_cast<Stair*>(pActor);
			collisionFlag = pPlayer->IsColliding(pStair->GetCollider());
			if (collisionFlag == true)
			{
				Actor* pUIActor = nullptr;
				for (Actor* pActor : _UIActors)
				{
					pUIActor = pActor;
					if (pUIActor->As<Score>() != nullptr) {
						static_cast<Score*>(pUIActor)->OnEarnScore();
					}
					else if (pUIActor->As<ClimbTimer>() != nullptr) {
						static_cast<ClimbTimer*>(pUIActor)->OnBeginTime();
					}
				}
				OnResetTimer();
				break;
			}
		}

		if (collisionFlag == false)
		{
			// TODO: 게임 다시하기 및 이런거 로직.
			DebugBreak();
		}


		_keyPressFlag = false;
	}
}

void InGameLevel::OnMovedStairs(int x, int y)
{
	for (Actor* pActor : _actors) {
		if (pActor->As<Player>()) {
			continue;
		}

		Vector2 position(pActor->Position());
		Vector2 newPosition(position._x - x *  pActor->Width(), position._y - y * pActor->Height());
		pActor->SetPosition(newPosition);
	}
}

void InGameLevel::OnCreateStairs(int x, int y)
{
	_generator.MoveLastStair(-x * 11, -y * 2);	// TODO 이거 꽤 문제네.
	Stair* pStair = _generator.InitGenerate();
	AddActor(pStair);
}

void InGameLevel::OnResetTimer()
{
	for (Actor* pActor : _UIActors)
	{
		if (pActor->As<ClimbTimer>() == nullptr) {
			continue;
		}

		static_cast<ClimbTimer*>(pActor)->ClearTimer();
	}
}

bool InGameLevel::IsColliding(Player* pPlayer)
{
	bool flag = false;
	for (Actor* pActor : _actors)
	{
		if (pPlayer == pActor) {
			continue;
		}

		// 현재는 계단만 있음.
		if (pActor->As<Stair>() == nullptr) {
			continue;
		}

		// 여기서 충돌 확인
		Stair* pStair = static_cast<Stair*>(pActor);
		flag = pPlayer->IsColliding(pStair->GetCollider());
		if (flag == true) {
			return flag;
		}
	}
	return flag;
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
