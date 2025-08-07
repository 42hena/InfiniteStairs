#include "UI_Item.h"

#include "Utils/Utils.h"

#include "Input.h"
#include "Engine.h"

#include "Contents/Character.h"

#include "Contents/InfiniteStairs.h"
#include "Contents/IFunctor.h"

#include <memory>

//Item::Item(Character* pUnSelectedImage, Character* pSelectedImage, FpOnSelected onSelected, const Vector2& rPosition)
//	: 
//	_fpOnSelected(onSelected),
//	_position(rPosition)
//{
//	_pImage[0] = std::move(pUnSelectedImage);
//	_pImage[1] = std::move(pSelectedImage);
//}

Item::Item(Character* pUnSelectedImage, Character* pSelectedImage, IFunctor *onSelected, const Vector2& rPosition)
	:
	_fpFunctor(onSelected),
	_position(rPosition)
{
	_pImage[0] = std::move(pUnSelectedImage);
	_pImage[1] = std::move(pSelectedImage);
}

Item::~Item()
{
	if (_pImage != nullptr) {
		SafeDelete(_pImage[0]);
		SafeDelete(_pImage[1]);
	}
	delete _fpFunctor;
}

/*
*		
*/

NavigationItems::NavigationItems()
{
	const wchar_t* itemUnSelectedGameImage[] = {
		L"    ███████╗████████╗ █████╗ ██████╗ ████████╗         ",
		L"    ██╔════╝╚══██╔══╝██╔══██╗██╔══██╗╚══██╔══╝         ",
		L"    ███████╗   ██║   ███████║██████╔╝   ██║            ",
		L"    ╚════██║   ██║   ██╔══██║██╔══██╗   ██║            ",
		L"    ███████║   ██║   ██║  ██║██║  ██║   ██║            ",
		L"    ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝            ",
	nullptr };
	const wchar_t* itemSelectedGameImage[] = { 
		
		L"    ██████ ▄▄▄█████▓ ▄▄▄       ██▀███  ▄▄▄█████▓       ",
		L"  ▒██    ▒ ▓  ██▒ ▓▒▒████▄    ▓██ ▒ ██▒▓  ██▒ ▓▒       ",
		L"  ░ ▓██▄   ▒ ▓██░ ▒░▒██  ▀█▄  ▓██ ░▄█ ▒▒ ▓██░ ▒░       ",
		L"    ▒   ██▒░ ▓██▓ ░ ░██▄▄▄▄██ ▒██▀▀█▄  ░ ▓██▓ ░        ",
		L"  ▒██████▒▒  ▒██▒ ░  ▓█   ▓██▒░██▓ ▒██▒  ▒██▒ ░        ",
		L"  ▒ ▒▓▒ ▒ ░  ▒ ░░    ▒▒   ▓▒█░░ ▒▓ ░▒▓░  ▒ ░░          ",
		L"  ░ ░▒  ░ ░    ░      ▒   ▒▒ ░  ░▒ ░ ▒░    ░           ",
		L"  ░  ░  ░    ░        ░   ▒     ░░   ░   ░             ",
		nullptr };
	const wchar_t* itemUnSelectedQuitImage[] = {
		L"           ██████╗ ██╗   ██╗██╗████████╗               ",
		L"          ██╔═══██╗██║   ██║██║╚══██╔══╝               ",
		L"          ██║   ██║██║   ██║██║   ██║               ",
		L"          ██║▄▄ ██║██║   ██║██║   ██║               ",
		L"          ╚██████╔╝╚██████╔╝██║   ██║               ",
		L"          ╚══▀▀═╝  ╚═════╝ ╚═╝   ╚═╝               ",
		nullptr };
	const wchar_t* itemSelectedQuit[] = { 
		/*L"   ___        _ _   ",
		L"  / _ \\ _   _(_) |_ ",
		L" | | | | | | | | __|",
		L" | |_| | |_| | | |_ "
		L"  \\__\\_\\\\__,_|_|\\__|",*/
		L"          █████   █    ██  ██▓▄▄▄█████▓                ",
		L"        ▒██▓  ██▒ ██  ▓██▒▓██▒▓  ██▒ ▓▒                ",
		L"        ▒██▒  ██░▓██  ▒██░▒██▒▒ ▓██░ ▒░                ",
		L"        ░██  █▀ ░▓▓█  ░██░░██░░ ▓██▓ ░                 ",
		L"        ░▒███▒█▄ ▒▒█████▓ ░██░  ▒██▒ ░                 ",
		L"        ░░ ▒▒░ ▒ ░▒▓▒ ▒ ▒ ░▓    ▒ ░░                   ",
		L"         ░ ▒░  ░ ░░▒░ ░ ░  ▒ ░    ░                    ",
		L"           ░   ░  ░░░ ░ ░  ▒ ░  ░                      ",
		L"            ░       ░      ░                           ",

		nullptr };
	Character* pImageGameStart1 = new Character(itemUnSelectedGameImage);
	Character* pImageGameStart2 = new Character(itemSelectedGameImage);
	Character* pImageQuit1 = new Character(itemUnSelectedQuitImage);
	Character* pImageQuit2 = new Character(itemSelectedQuit);

	Vector2 StartPosition(38, 25);
	IFunctor* changeLevelFunc = new ChangeLevelFunctor(Scene_InGame);
	_items.emplace_back(new Item(pImageGameStart1, pImageGameStart2,
		changeLevelFunc, StartPosition));


	IFunctor* exitFunc = new ExitFunctor();
	StartPosition._y += 10;
	_items.emplace_back(new Item(pImageQuit1, pImageQuit2,
		exitFunc, StartPosition
	));
}

NavigationItems::~NavigationItems()
{
	for (auto* pItem : _items) {
		SafeDelete(pItem);
	}
}

void NavigationItems::AddToNavigation(Item* newItem)
{
	_items.push_back(std::move(newItem));
}

void NavigationItems::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 입력 처리
	int length = _items.size();
	if (Input::GetInstance().GetKeyDown(VK_UP))	{
		_selectedItemIndex = (_selectedItemIndex - 1 + length) % length;
	}

	if (Input::GetInstance().GetKeyDown(VK_DOWN))	{
		_selectedItemIndex = (_selectedItemIndex + 1) % length;
	}

	if (Input::GetInstance().GetKeyDown(VK_RETURN))	{
		IFunctor* func  = _items[_selectedItemIndex]->_fpFunctor;
		(*func)();
	}
}


void NavigationItems::Render()
{
	if (Active() == false || Expired() == true) {
		return;
	}

	// super::Render();

	size_t itemLength = _items.size();
	for (int i = 0; i < static_cast<int>(itemLength); ++i) {
		if (i == _selectedItemIndex) {
			wchar_t** ppImage = _items[i]->_pImage[1]->GetCharacterPtr();
			int imageHeight = _items[i]->_pImage[1]->Height();
			Vector2 position = _items[i]->_position;
			for (int h = 0; h < imageHeight; ++h) {
				Engine::GetInstance().Draw(ppImage[h], position);
				position._y = position._y + 1;
			}
		}
		else {
			wchar_t** ppImage = _items[i]->_pImage[0]->GetCharacterPtr();
			int imageHeight = _items[i]->_pImage[0]->Height();
			Vector2 position = _items[i]->_position;
			for (int h = 0; h < imageHeight; ++h) {
				Engine::GetInstance().DrawDefault(ppImage[h], position, Color::Color_White);
				position._y = position._y + 1;
			}
		}
	}
}
