#ifndef __UI_TITLE_H__
#define __UI_TITLE_H__

#include "Actor/Actor.h"
#include "Math/Vector2.h"

#include "Contents/Character.h"

class Title : public Actor
{
	RTTI_DECLARATIONS(Title, Actor)

public:
	Title(Character* pImage, const Vector2& rPosition);
	~Title();

public:
	Vector2 Position()	const { return _position; }

public:
	virtual void Tick(float deltaTime)	override;
	virtual void Render()				override;


private:
	Character*	_pImage;
	Vector2		_position;

	int			_imageWidth = 121;
	int			_imageHeight = 9;

private:	// 현재 미사용 변수
	int			_sortOrder = 10;
};

#endif
