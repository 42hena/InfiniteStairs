#include "Stair.h"


Stair::Stair(const char* pImage, const Vector2& rPosition)
	: Actor(pImage, Color::Color_White, rPosition)
{
	Vector2 phyPos(0, 0);
	_pCollider = new Collider(phyPos, 3, 1);
	_pCollider->SetOwner(this);
}

Stair::~Stair()
{
	SafeDelete(_pCollider);
}

void Stair::BeginPlay()
{
	Vector2 position = Position();// 이거 필요
	if (position._x < 0 || position._x + Width() > 39)
		SetActive(false);
	if (position._y < 0 || position._y + Height()/*1*/ > 20)
		SetActive(false);
}

void Stair::Tick(float deltaTime)
{
	
}

void Stair::Render()
{
	super::Render();
}

bool Stair::IsColliding(Collider* pOther) const
{
	return _pCollider->IsColliding(*pOther);;
}


//void Stair::SetPosition(int x, int y)
//{
//	
//}

