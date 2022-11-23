#include "framework.h"
#include "Effect.h"

Effect::Effect(int level, int num)
	: Object(level, num)
{
	_renderOrder = 6.f;
	_objectType = Object::EFFECT;
}

void Effect::Update()
{
	Object::Update();

	if (_anim->GetIsPlaying() == false)
		_isActive = false;
}
