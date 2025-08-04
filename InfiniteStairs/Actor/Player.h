#pragma once

#include "Actor/Actor.h"
#include "Contents/Collider.h"

enum Direction
{
	Direction_Left = -1,
	Direction_None,
	Direction_Right
};

class Character;
class Collider;
class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)

public:
	Player(Character* left, Character* right, const Vector2& rPosition, Collider* col, Direction dir = Direction_Left);
	Player(const wchar_t** ppImage[], Direction dir = Direction::Direction_Left);
	~Player();

public:
	inline int ImageWidth() { return _imageWidth; }
	inline int ImageHeight() { return _imageHeight; }


	virtual void Tick(float deltaTime = 0) override;
	virtual void Render() override;

	class Level* CurLevel() const { return pLevel; }

	Collider* GetCollider() const { return _pCollider; }
	bool IsColliding(Collider* pOther) const;
private:
	Level* pLevel =  nullptr;

	Character*	_image[2];
	int			_imageLength = 1;

	wchar_t** _ppImage[2] = { nullptr, nullptr };
	int _imageWidth = 3;
	int _imageHeight = 5;
	Direction _dir;
	int _sortOrder = 10;

	Collider* _pCollider = nullptr;
};