#include "InGameLevel.h"
#include "Engine.h"
#include "Actor/Player.h"
#include "Actor/Stair.h"


#include "UI/UI_Score.h"
#include "UI/UI_GameHUD.h"
#include "UI/UI_Timer.h"
#include "UI/UI_ButtonImage.h"

#include "Contents/Character.h"

#include "Resources/Resources.h"

#include "Contents/InfiniteStairs.h"

InGameLevel::InGameLevel()
	:_generator(11, 2)
{	
	const int cStairCount = 1;
	//const wchar_t* wp[] = { L"<###>", L"<===>", nullptr};

	const wchar_t* wlp[] = { 
		L"  ∧＿∧ =-   ", 
		L"(´･ω･`)`つ=-", 
		L"　`つ \ =-    ",
		L" 　\,⌒＼\,,,_=-", nullptr };




	const wchar_t* wrp[] = { 
		L"　-= ∧＿∧    ", 
		L"-=と(´･ω･`) ", 
		L"　-=/　と_ノ   ",
		L"-=_/／⌒ｿ    ", nullptr };

	Character *playerL = new Character(wlp);
	Character *playerR = new Character(wrp);

	// const char* stair = "===";
	
	const wchar_t* stair[] = { L"╔═════════╗",L"╚═════════╝", nullptr};
	Character* pStair = new Character(stair);
	_generator.SetStairImage(pStair);
	int stairWidth = 11;
	int stairHeight = 2;	// 얘는 잘못건들이면 안됌

	Vector2 playerPos(66, 23);	// TODO: 1칸 줄임.
	Vector2 playerColliderPos(0, 3);
	Collider* pPlayerCollider = new Collider(playerColliderPos, stairWidth, 2);


	Animator* animL = new Animator();
	for (int i = 0; i < 12; ++i)
	{
		animL->AddAnim(new Character(alp[i]));
	}
	Animator* animR = new Animator();
	for (int i = 0; i < 12; ++i)
	{
		animR->AddAnim(new Character(arp[i]));
	}

	Player* pPlayer = new Player(playerL, playerR, playerPos, pPlayerCollider, Direction_Left);
	pPlayer->SetAnim(animL);
	pPlayer->SetAnim(animR);
	AddActor(pPlayer);

	// 계단 생성
	_generator.SetStairWidth(stairWidth);
	_generator.SetStairHeight(stairHeight);
	/*for (int i = 0; i < cStairCount; ++i)
	{
		Stair* pNewStair = _generator.InitGenerate();
		AddActor(pNewStair);
	}*/

	const wchar_t* pTimer[] = {
		L"╭────────────────────────────────────────╮",
		L"|                                        |",
		L"|                                        |",
		L"╰────────────────────────────────────────╯",
		 nullptr };
	Character* pTimerr = new Character(pTimer);

	// Game UI 설정
	Vector2 rr(0, 0);
	AddUIActor(new Score(rr));
	rr._y = rr._y + 1;
	// AddUIActor(new GameHUD(rr, 41, 21));

	AddUIActor(new ClimbTimer(pTimerr, rr));


	Character* plButton = new Character(buttonL);
	Vector2 lButtonPos(0, 30);

	ButtonImage* pLButtonImage = new ButtonImage(plButton, nullptr, lButtonPos);
	pLButtonImage->SetType(ButtonLButton);
	AddUIActor(pLButtonImage);

	Character* prButton = new Character(buttonR);
	Vector2 rButtonPos(99, 30);
	ButtonImage* pRButtonImage = new ButtonImage(prButton, nullptr, rButtonPos);
	pRButtonImage->SetType(ButtonRButton);
	AddUIActor(pRButtonImage);
}

InGameLevel::~InGameLevel()
{
	/*for (auto pActor : _actors) {
		DestroyActor(pActor);
	}
	for (auto pActor : _UIActors) {
		DestroyUIActor(pActor);
	}*/
}

void InGameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	if (Input::GetInstance().GetKeyDown(VK_ESCAPE)) {
		Engine::GetInstance().Quit();
		return;
	}

	/* Time Over */

	/* 마우스 입력 */
	bool ret= Input::GetInstance().GetMouseLeftClick();
	if (ret)
	{
		COORD mousePosition = Input::GetInstance().GetMousePosition();

		wchar_t debug[50] = {};
		swprintf_s(debug, 50, L"posX: %d, posY: %d\n", mousePosition.X, mousePosition.Y);
		OutputDebugStringW(debug);

		ButtonImage* pButton = nullptr;
		for (Actor* pActor : _UIActors) {
			pButton = pActor->As<ButtonImage>();
			if (pButton == nullptr) {
				continue;
			}

			int w = pButton->Width();
			int h = pButton->Height();
			Vector2 pos = pButton->Position();
			int b = 0;
			if (mousePosition.X >= pos._x && mousePosition.X < pos._x + w &&
				mousePosition.Y >= pos._y && mousePosition.Y < pos._y + h
				)
			{
				if (pButton->Type() == ButtonLButton)
				{
					Player* pPlayer = static_cast<Player*>(_actors[0]);

					pPlayer->ChangeDir();
					//_dir = _dir == Direction_Left ? Direction_Right : Direction_Left;
					Vector2 newPosition(pPlayer->GetDir(), -1);
					OnPressDown();
					OnMovedStairs(newPosition._x, newPosition._y);
					//OnCreateStairs(newPosition._x, newPosition._y);
				}
				else if (pButton->Type() == ButtonRButton)
				{
					Player* pPlayer = static_cast<Player*>(_actors[0]);

					//_dir = _dir == Direction_Left ? Direction_Right : Direction_Left;
					Vector2 newPosition(pPlayer->GetDir(), -1);
					OnPressDown();
					OnMovedStairs(newPosition._x, newPosition._y);
					//OnCreateStairs(newPosition._x, newPosition._y);
				}
			}
		}
	}

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
				Vector2 newPosition(pPlayer->GetDir(), -1);
				OnCreateStairs(newPosition._x, newPosition._y);
				// 여기서 생성하는 쪽으로 가야할듯?


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

		_keyPressFlag = false;
		if (collisionFlag == false)
		{
			InfiniteStairs::GetInstance().ChangeLevel(Scene_Title);
		}
	}
}

void InGameLevel::Clear()
{
	for (auto* pActor : _actors) {
		Actor* temp = pActor->As<Player>();
		if (temp != nullptr) {
			static_cast<Actor*>(temp)->Reset();
			continue;
		}

		pActor->Destroy();
	}
}

void InGameLevel::Reset()
{
	_generator.Reset();

	for (auto* pActor : _UIActors) {
		pActor->Reset();
	}

	for (int i = 0; i < 5; ++i)
	{
		Stair* pNewStair = _generator.InitGenerate();
		AddActor(pNewStair);
	}
}

void InGameLevel::OnMovedStairs(int x, int y)
{
	for (Actor* pActor : _actors) {
		if (pActor->As<Player>()) {
			continue;
		}

		Vector2 position(pActor->Position());
		Vector2 newPosition(position._x - x *  pActor->Width(), position._y - y * pActor->Height() + 1);// TODO:......;
		pActor->SetPosition(newPosition);
	}
}

void InGameLevel::OnCreateStairs(int x, int y)
{
	_generator.MoveLastStair(-x * 11, -y * 3);	// TODO 이거 꽤 문제네.
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
