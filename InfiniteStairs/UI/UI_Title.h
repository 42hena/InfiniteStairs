#pragma once
#include "Actor/Actor.h"
#include "Math/Vector2.h"
#include "UI_Canvas.h"

class Title : public Canvas
{
public:
	Actor* Owner()		const { return _owner; }
	Vector2 Position()	const { return _position; }
	Vector2 WorldPosition() const {
		return _owner->Position() + _position;
	}

private:
	Vector2 _position;

	Actor* _owner;
};
