#include "Stair.h"

Stair::Stair(const char* pImage, const Vector2& rPosition)
	: Actor(pImage, Color::Color_White, rPosition)
{
}

Stair::~Stair()
{
}

void Stair::Tick(float deltaTime)
{

}

void Stair::Render()
{
	super::Render();
}

//void Stair::SetPosition(int x, int y)
//{
//	
//}

