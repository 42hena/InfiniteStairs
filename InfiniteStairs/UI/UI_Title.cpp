#include "UI_Title.h"

#include "Engine.h"

#include <utility>

/*
*		특수 멤버 함수
*/

Title::Title(Character* pImage, const Vector2& rPosition)
	: _position(rPosition)
{
	_pImage = std::move(pImage);
	_imageWidth = _pImage->Width();
	_imageHeight = _pImage->Height();
	SetWidth(_imageWidth);
	SetHeight(_imageHeight);
}

Title::~Title()
{
	if (_pImage != nullptr)	{
		SafeDelete(_pImage);
	}
}

/*
*		이벤트 함수
*/

void Title::Tick(float deltaTime)
{
	super::Tick(deltaTime);
}

void Title::Render()
{
	// super::Render();

	if (Active() == false || Expired() == true) {
		return;
	}

	Vector2 titlePosition = Position();


	wchar_t** ppTitle = _pImage->GetCharacterPtr();
	for (int i = 0; i < _imageHeight; ++i)
	{
		Engine::GetInstance().Draw(ppTitle[i], titlePosition);
		// 콘솔의 다음 위치로 이동
		titlePosition._y = titlePosition._y + 1;
	}
}

