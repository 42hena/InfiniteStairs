#include "Animator.h"
#include <iostream>
#include "Utils/Utils.h"
Animator::Animator()
{
}

Animator::~Animator()
{
	for (auto* pImage : _anims) {
		SafeDelete(pImage);
	}
	_anims.clear();
}

void Animator::AddAnim(Character* pImage)
{
	_anims.push_back(std::move(pImage));
}
