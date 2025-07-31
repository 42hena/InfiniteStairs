#pragma once

#include "Actor/Actor.h"

//void SetPosition(Actor* pActor, int x, int y);

class Stair : public Actor
{
	RTTI_DECLARATIONS(Stair, Actor)
public:
	Stair(const char* pImage, const Vector2& rPosition);
	~Stair();

public:
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;


	void OnMoved();

public:
	
};