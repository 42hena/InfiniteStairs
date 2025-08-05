#include "Stair.h"
#include "Contents/Character.h"
#include "Contents/Collider.h"
#include "Utils/Utils.h"

#include "Engine.h"

#include <iostream>

Stair::Stair(Character* pImage, Collider* col, const Vector2& rPosition)
	: Actor(L"", Color::Color_White, rPosition)
{
	_pStairImage = std::move(pImage);
	SetWidth(pImage->Width());
	SetHeight(pImage->Height());
	_imageWidth = pImage->Width();
	_imageHeight = pImage->Height();

	//Vector2 phyPos = Vector2(0, 1);
	//_pCollider = new Collider(phyPos, 3, 2); // TODO 콜라이더
	//Vector2 phyPos = Vector2(0, 1);
	_pCollider = col; // TODO 콜라이더

	// 콜라이더 컴포넌트 주인 설정
	_pCollider->SetOwner(this);
}

Stair::Stair(const wchar_t* pImage, const Vector2& rPosition)
	: Actor(pImage, Color::Color_White, rPosition)
{
	DebugBreak();
	Vector2 phyPos(0, 0);
	_pCollider = new Collider(phyPos, 3, 1); // TODO: 콜라이더...
	_pCollider->SetOwner(this);
}

Stair::~Stair()
{
	SafeDelete(_pCollider);
}

void Stair::BeginPlay()
{
	Vector2 position = Position();// 이거 필요
	if (position._x < 0 || position._x + Width() >= Engine::GetInstance().Width())
		SetActive(false);
	if (position._y < 0 || position._y + Height()/*1*/ >= Engine::GetInstance().Height())
		SetActive(false);
}

void Stair::Tick(float deltaTime)
{
	// 일단 필요하지 않아보임...
}

void Stair::Render()
{
	if (Active() == false || Expired() == true) {
		return;
	}

	Vector2 pos = Position();
	wchar_t** ppCharacter = _pStairImage->GetCharacterPtr();
	for (int i = 0; i < _imageHeight; ++i)
	{
		// Utils::SetConsolePosition(pos);
		Engine::GetInstance().Draw(ppCharacter[i], pos);
		//std::wcout << ppCharacter[i];
		/*if (_dir == Direction_Left)
			std::wcout << *_ppImage[0];
		else
			std::wcout << *(_ppImage[1]);*/
		pos._y = pos._y + 1;
	}
}

bool Stair::IsColliding(Collider* pOther) const
{
	return _pCollider->IsColliding(*pOther);;
}
