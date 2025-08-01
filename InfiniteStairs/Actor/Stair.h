#pragma once

#include "Actor/Actor.h"
#include "Contents/Collider.h"

//void SetPosition(Actor* pActor, int x, int y);

class Stair : public Actor
{
	RTTI_DECLARATIONS(Stair, Actor)
public:
	Stair(const char* pImage, const Vector2& rPosition);
	~Stair();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

public:
	Collider* GetCollider() const { return _pCollider; }
	bool IsColliding(Collider* pOther) const;

public:
	Collider* _pCollider = nullptr;
};