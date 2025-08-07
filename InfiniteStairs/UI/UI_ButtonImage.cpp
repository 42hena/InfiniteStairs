#include "UI_ButtonImage.h"
#include "Contents/Character.h"
#include <utility>
#include "Engine.h"

ButtonImage::ButtonImage(Character* pUnClickedImage, Character* pClickedImage, const Vector2& rPosition)
	: Actor(L"", Color::Color_None, rPosition)
{
	_pImage = std::move(pUnClickedImage);
	_width = pUnClickedImage->Width();
	_height = pUnClickedImage->Height();
}

ButtonImage::~ButtonImage()
{
	SafeDelete(_pImage);
}

void ButtonImage::Render()
{
	// super::Render();

	wchar_t** ppImage = _pImage->GetCharacterPtr();
	Vector2 pos = Position();
	for (int i = 0; i < _height; ++i)
	{
		for (int j = 0; j < _width; ++j)
		{
			wchar_t ch = ppImage[i][j];
			DWORD color = 0;
			if (ch == L'-') {
				// ����� ��� (���� + �ʷ�)
				color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
			}
			else if (ch == L';'){
				// ������ ���
				color = BACKGROUND_RED | BACKGROUND_INTENSITY;
			}
			else
			{
				color = FOREGROUND_GREEN;
			}
			pos._x = pos._x + 1;
			Engine::GetInstance().DrawDefault(ch, pos, static_cast<Color>(color));
		}
		pos._x = Position()._x;
		pos._y = pos._y + 1;
	}

	// case 1. ��ư�� ���ȴ�. or ���� ���� -> ��ư �� ������ ���

	// case 2. ��ư�� ������. -> �⺻ ���� ���
}
