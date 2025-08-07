#pragma once

#include "Actor/Actor.h"
#include "Contents/Collider.h"

//void SetPosition(Actor* pActor, int x, int y);

class Character;
class Stair : public Actor
{
	RTTI_DECLARATIONS(Stair, Actor)
public:
	Stair(Character* pImage, Collider* col, const Vector2& rPosition);
	Stair(const wchar_t* pImage, const Vector2& rPosition);
	~Stair();

public:
	virtual void BeginPlay()			override;
	virtual void Tick(float deltaTime)	override;
	virtual void Render()				override;
	virtual void Reset()				override;

	virtual int	Width() { return _imageWidth; }
	virtual int	Height() { return _imageHeight; }

	inline int	ImageWidth() { return _imageWidth; }
	inline int	ImageHeight() { return _imageHeight; }

public:
	Collider* GetCollider() const { return _pCollider; }
	bool IsColliding(Collider* pOther) const;

public:
	Collider* _pCollider = nullptr;
	Character* _pStairImage = nullptr;
private:
	int _imageWidth;
	int _imageHeight;
};
