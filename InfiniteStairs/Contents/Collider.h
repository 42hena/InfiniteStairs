#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "Math/Vector2.h"

class Actor;
class Collider {
	
public:
	//Collider(const Vector2& rPosition, const Vector2& rPhysicPosition, int width, int height);
	Collider(const Vector2& rPhysicPosition, int width, int height);

public:
	bool IsColliding(const Collider& other);
	//bool IsColiiding(const Actor& other);

	Actor* GetOwner() const {	return _pOwner;	}
	void SetOwner(Actor* pActor) { _pOwner = pActor; }

private:

	Actor* _pOwner = nullptr;

	//Vector2 _position;
	Vector2 _physicPosition;
	int _width;
	int _height;
};

#endif