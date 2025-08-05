#pragma once

#include <vector>

#include "Contents/Character.h"

class Animator {
	enum Anim {
		Anim_Frame = 12
	};
public:
	Animator();
	~Animator();

public:
	void AddAnim(Character* pImage);
	void CalculateTime(float deltaTime)
	{
		_elapsedTime += deltaTime;
		if (_elapsedTime >= _targetTime)
		{
			_frameIndex = (_frameIndex + 1) % (_anims.size());
			_elapsedTime -= _targetTime;
		}
	}

	Character* GetCurrentImagePtr() {	return _anims[_frameIndex];	}

private:
	std::vector<Character*> _anims;
	int			_frameIndex = 0;
	int			_frameSize = 0;
	int			_capacity = 0;
	int			_size = 0;
	float		_targetTime = 1.0f / Anim_Frame;
	float		_elapsedTime = 0.0;
};