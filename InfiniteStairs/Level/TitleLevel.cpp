#include "TitleLevel.h"
#include "Input.h"

#include "Engine.h"
#include "UI/UI_Title.h"
#include "Utils/Utils.h"
#include "Contents/Character.h"

#include "Resources/Resources.h"

#include "UI/UI_Item.h"
#include "UI/UI_MaxScore.h"

#include <iostream>

TitleLevel::TitleLevel()
{
	Character* pImage = new Character(pTitleImage);
	Vector2 titlePosition(0, 5);
	_UIActors.push_back(new Title(pImage, titlePosition));
	_UIActors.push_back(new NavigationItems());

	Vector2 scorePos = { 55, 20 };
	_UIActors.push_back(new MaxScore(scorePos));
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 입력 처리
	if (Input::GetInstance().GetKeyDown(VK_ESCAPE))
	{
		Engine::GetInstance().Quit();
	}
	//if (Input::GetInstance().GetKeyDown(VK_DOWN))
	//{
	//	_currentIndex = (_currentIndex + 1) % _titleItemLength;
	//}
	//if (Input::GetInstance().GetKeyDown(VK_RETURN))
	//{
	//	//_items[_currentIndex]->_fOnSelected();
	//}
}

void TitleLevel::Render()
{
	super::Render();
}
