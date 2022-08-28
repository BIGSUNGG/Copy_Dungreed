#include "framework.h"
#include "Monster.h"

Monster::Monster(int level, int num)
	:Creature(level, num)
{
	_creatureType = Creature_Type::ENEMY;
	_targetDistance = (MathUtility::RandomFloat(_targetDistanceMin, _targetDistanceMax)) * _targetDistanceRatio;
	_speed = 300.0f;
}

void Monster::Update()
{
	if (GAME->GetObjectUpdate())
	{
		MovementEvent();

		SearchTarget();

		AI();
	}

	Creature::Update();
}

void Monster::SearchTarget()
{
	auto collisions =GAME->GetCollisions(_collider, Object::Object_Type::CREATURE);
	
	float length = (_texture->GetTransform()->GetPos() - GAME->GetPlayer()->GetTexture()->GetTransform()->GetPos()).Length();

	if (length <= _searchLength)
		_target = GAME->GetPlayer();
}

void Monster::AI()
{
	if (_target.lock() == nullptr)
		return;

	float length = abs(_target.lock()->GetTexture()->GetTransform()->GetPos().x - _texture->GetTransform()->GetPos().x);
	if (length >= _targetDistance)
	{
		if (_target.lock()->GetTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x)
			_movement.x += _speed;
		else
			_movement.x -= _speed;
	}
	else if (_texture->Top() < _target.lock()->GetTexture()->GetTransform()->GetPos().y)
	{
		Jump();
	}
	else if (_texture->Bottom() > _target.lock()->GetTexture()->Top())
	{
		_passFloor = true;
	}
	else
	{
		Attack();
	}
}

void Monster::Jump()
{
	if (_isFalling == false)
	{
		_jumpPower = _jumpPowerMax;
	}
}

void Monster::Attack()
{
	_anim->ChangeAnimation(State::ATTACK);
}

void Monster::MovementEvent()
{
	if (_velocity.x != 0)
	{
		_anim->ChangeAnimation(State::RUN);

		if (_velocity.x > 0 && _reversed == true)
			ReverseTexture();
		else if (_velocity.x < 0 && _reversed == false)
			ReverseTexture();
	}
	else
	{
		_anim->ChangeAnimation(State::IDLE);
	}

	if (_velocity.y != 0)
	{
		_anim->ChangeAnimation(State::JUMP);

		_isFalling = true;
	}
	else
	{
		_isFalling = false;
		_jumpPower = 0.0f;
	}
}
