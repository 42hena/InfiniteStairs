#pragma once

#include "Actor/Actor.h"
#include "Contents/Collider.h"

enum Direction
{
	Direction_Left = -1,
	Direction_None,
	Direction_Right
};
class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)


public:
	Player(const char** ppImage[], Direction dir = Direction::Direction_Left);
	~Player();

public:
	inline int Width() { return _width; }
	inline int Height() { return _height; }


	virtual void Tick(float deltaTime = 0) override;
	virtual void Render() override;

	class Level* CurLevel() const { return pLevel; }

	Collider* GetCollider() const { return _pCollider; }
	bool IsColliding(Collider* pOther) const;
private:
	Level* pLevel =  nullptr;

	char** _ppImage[2];
	int _width = 3;
	int _height = 5;
	Direction _dir;
	int _sortOrder = 10;

	Collider* _pCollider = nullptr;
};