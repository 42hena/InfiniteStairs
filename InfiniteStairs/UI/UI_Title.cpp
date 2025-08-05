#include "UI_Title.h"

#include "Engine.h"

#include <utility>

/*
*		Ư�� ��� �Լ�
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
*		�̺�Ʈ �Լ�
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
		// �ܼ��� ���� ��ġ�� �̵�
		titlePosition._y = titlePosition._y + 1;
	}
}

