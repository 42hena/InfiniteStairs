#ifndef __UI_Button_IMAGE_H__
#define __UI_Button_IMAGE_H__

#include "Actor/Actor.h"
#include "Math/Vector2.h"

enum ButtonEvent {
	ButtonLButton,
	ButtonRButton,
};
class Character;
class ButtonImage : public Actor
{

	RTTI_DECLARATIONS(ButtonImage, Actor)
public:
	ButtonImage(Character* pUnClickedImage, Character* pClickedImage, const Vector2& rPosition);
	~ButtonImage();
public:
	int Width()			{ return _width; }
	int Height()		{ return _height; }
	ButtonEvent Type()	{ return _type; }

	void SetType(ButtonEvent type) { _type = type; }

	virtual void Render() override;

private:
	Vector2		_position = Vector2::Zero;
	int			_width;
	int			_height;
	Character*	_pImage;
	ButtonEvent _type;
};

#endif
