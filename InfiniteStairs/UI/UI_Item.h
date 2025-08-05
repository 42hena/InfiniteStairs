#pragma once

#include "Actor/Actor.h"

#include "Contents/IFunctor.h"
#include <vector>

class Character;
struct Item
{
	//template<typename ...Ts>
	using FpOnSelected = void(*)( );

public:
	Item(Character* pUnSelectedImage, Character* pSelectedImage, IFunctor* onSelected, const Vector2& rPosition);
	~Item();

	void OnSelected() { _selected = true; }
	void OnUnSelected() { _selected = false; }

	// 메뉴 Text
	Character* _pImage[2] = { nullptr };

	// 메뉴 선택 시 실행할 동작
	//FpOnSelected	_fpOnSelected = nullptr;
	IFunctor*		_fpFunctor;
	Vector2			_position;
	bool			_selected = false;
};

class NavigationItems : public Actor
{
	RTTI_DECLARATIONS(NavigationItems, Actor)

public:
	NavigationItems();
	~NavigationItems();

public:
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

public:
	void AddToNavigation(Item* newItem);
public:
	
private:
	std::vector<Item*>	_items;
	int					_selectedItemIndex = 0;


};