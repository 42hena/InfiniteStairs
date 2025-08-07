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
				// 노란색 배경 (빨강 + 초록)
				color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
			}
			else if (ch == L';'){
				// 빨간색 배경
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

	// case 1. 버튼이 눌렸다. or 눌린 상태 -> 버튼 들어간 느낌을 출력

	// case 2. 버튼이 때졌다. -> 기본 상태 출력
}
