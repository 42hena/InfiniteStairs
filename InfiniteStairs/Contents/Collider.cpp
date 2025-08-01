#include "Collider.h"

//Collider::Collider(const Vector2& rPosition, const Vector2& rPhysicPosition, int width, int height)
//	: _position(rPosition), _physicPosition(rPhysicPosition), _width(width), _height(height)
//{
//
//}
Collider::Collider(const Vector2& rPhysicPosition, int width, int height)
	: _physicPosition(rPhysicPosition), _width(width), _height(height)
{

}

//
//bool Collider::IsColliding(const Collider& other)
//{
//	bool flag = false;
//
//	int myMinX = _position._x + _physicPosition._x;
//	int myMaxX = myMinX + _width;
//
//	int otherMinX = other._position._x + other._physicPosition._x;
//	int otherMaxX = otherMinX + other._width;
//
//	
//
//	int myMinY = _position._y + _physicPosition._y;
//	int myMaxY = myMinY + _height;
//
//	int otherMinY = other._position._y + other._physicPosition._y;
//	int otherMaxY = otherMinY + other._height;
//		/*if (myMaxX <= otherMinX || myMinX >= otherMinX)
//			flag = false;
//	if (myMaxY <= otherMinY || myMinY >= otherMaxY)
//		flag = false;*/
//	if (myMaxX > otherMinX && otherMaxX > myMinX &&
//		myMaxY > otherMinY && otherMaxY > myMinY)
//		flag = true;
//	if (flag == true)
//		int a = 0;
//
//	return flag;
//}
#include "Actor/Actor.h"
//bool Collider::IsColiiding(const Actor& other)
//{
//	bool flag = false;
//	other.Position();
//
//	Actor* pActor = GetOwner();
//
//	Vector2 position = pActor->Position();
//	int myMinX = position._x + _physicPosition._x;
//	int myMaxX = myMinX + _width;
//
//	int otherMinX = other.Position()._x + other._physicPosition._x;
//	int otherMaxX = otherMinX + other.Width();
//
//
//
//	int myMinY = _position._y + _physicPosition._y;
//	int myMaxY = myMinY + _height;
//
//	int otherMinY = other._position._y + other._physicPosition._y;
//	int otherMaxY = otherMinY + other._height;
//	/*if (myMaxX <= otherMinX || myMinX >= otherMinX)
//		flag = false;
//if (myMaxY <= otherMinY || myMinY >= otherMaxY)
//	flag = false;*/
//	if (myMaxX > otherMinX && otherMaxX > myMinX &&
//		myMaxY > otherMinY && otherMaxY > myMinY)
//		flag = true;
//	if (flag == true)
//		int a = 0;
//
//	return flag;
//}

bool Collider::IsColliding(const Collider& other)
{
	bool flag = false;


	Actor* pActor = GetOwner();
	Actor* pOther = other.GetOwner();

	Vector2 myPosition = pActor->Position();
	Vector2 otherPosition = pOther->Position();


	int myMinX = myPosition._x + _physicPosition._x;
	int myMaxX = myMinX + _width;

	int otherMinX = otherPosition._x + other._physicPosition._x;
	int otherMaxX = otherMinX + other._width;



	int myMinY = myPosition._y + _physicPosition._y;
	int myMaxY = myMinY + _height;

	int otherMinY = otherPosition._y + other._physicPosition._y;
	int otherMaxY = otherMinY + other._height;
	/*if (myMaxX <= otherMinX || myMinX >= otherMinX)
		flag = false;
if (myMaxY <= otherMinY || myMinY >= otherMaxY)
	flag = false;*/
	if (myMaxX > otherMinX && otherMaxX > myMinX &&
		myMaxY > otherMinY && otherMaxY > myMinY)
		flag = true;
	if (flag == true)
		int a = 0;

	return flag;
}