#include "framework.h"
#include "Monster.h"

Monster::Monster(int level, int num)
	:Creature(level, num)
{
	_creatureType = Creature_Type::ENEMY;
}

void Monster::Update()
{
	MovementEvent();

	Creature::Update();
}

void Monster::MovementEvent()
{
	if (_velocity.x != 0)
	{
		//_anim->ChangeAnimation(State::MOVE);
	}
	else
	{
		//_anim->ChangeAnimation(State::IDLE);
	}

	if (_velocity.y != 0)
	{
		//_anim->ChangeAnimation(State::JUMP);
		_isFalling = true;
	}
	else
	{
		_isFalling = false;
		_jumpPower = 0.0f;
	}
}
