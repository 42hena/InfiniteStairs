#pragma once

#include "Actor/Actor.h"

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
	Player(const char** ppImage, Direction dir = Direction::Direction_Left);
	~Player();

public:
	inline int Width() { return _width; }
	inline int Height() { return _height; }


	virtual void Tick(float deltaTime = 0) override;

	class Level* CurLevel() const { return pLevel; }
private:
	Level* pLevel =  nullptr;

	char** _ppImage;
	int _width = 3;
	int _height = 5;
	Direction _dir;
	int _sortOrder = 10;
};