#include "framework.h"
#include "Creature.h"

Creature::Creature(int level, int num)
	: Object(level, num)
{
	_objectType = Object::Object_Type::CREATURE;
}

void Creature::Update()
{
	_movementPos = _texture->GetTransform()->GetPos() - _movedPos;
	_movedPos = _texture->GetTransform()->GetPos();

	Object::Update();
}
