#ifndef __UI_GAME_HUD_H__
#define __UI_GAME_HUD_H__

#include "Actor/Actor.h"
#include "Math/Vector2.h"

class GameHUD : public Actor
{
	RTTI_DECLARATIONS(GameHUD, Actor)
public:
	GameHUD(const Vector2& rPosition, int width, int height);
	~GameHUD();
public:
	int Width() { return _width; }
	int Height() { return _height; }

	virtual void Render() override;


private:
	Vector2		_position = Vector2::Zero;
	int			_width;
	int			_height;
	wchar_t*	_pOutline;
};

#endif
