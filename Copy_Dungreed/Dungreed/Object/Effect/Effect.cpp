#include "framework.h"
#include "Effect.h"

Effect::Effect(int level, int num)
	: Object(level, num)
{
	_objectType = Object::EFFECT;
}

void Effect::Update()
{
	Object::Update();

	if (_anim->GetIsPlaying() == false)
		_isActive = false;
}
