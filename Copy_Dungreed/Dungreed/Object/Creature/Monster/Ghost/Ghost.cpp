#include "framework.h"
#include "Ghost.h"

Ghost::Ghost(int level, int num)
	: Monster(level,num)
{
	_status.SetMaxHp(15);
	_status._atk = 20;
	_status._speed = 300.0f;
	_gravityRatio = 0.0f;
}

void Ghost::Update()
{
	Monster::Update();
}

void Ghost::CollisionEvent()
{
}

void Ghost::AI()
{
	if (_attack)
	{
		_anim->ChangeAnimation(Creature::ATTACK);

		_movement += _attackDirection * _attackSpeed;
		Attack();

		_attackRunTime += DELTA_TIME;
		if (_attackRunTime >= _attackDelay)
		{
			_attackRunTime = 0.0f;
			_attack = false;
		}
	}
	else
	{
		_anim->ChangeAnimation(Creature::IDLE);

		float length = abs(_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x - _texture->GetTransform()->GetPos().x);
		if (length >= _targetDistance)
		{
			if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x && _reversed == true)
				ReverseTexture();
			else if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x < _texture->GetTransform()->GetPos().x && _reversed == false)
				ReverseTexture();

			MoveTo(_target.lock());
		}

		if (_targetAttackDistance <= length)
		{
			_attackWatitTime += DELTA_TIME;
			if (_attackWatitTime >= _attackWaitDelay)
			{
				_attackWatitTime = 0.0f;
				_attackDirection = _target.lock()->GetPos() - this->GetPos();
				_attackDirection.Normalize();
				_attack = true;
				_giveDamage = false;
			}
		}
	}
}

void Ghost::MoveTo(shared_ptr<Object> object)
{
	_attackDirection = object->GetPos() - this->GetPos();
	_attackDirection.Normalize();

	_movement += _attackDirection * _status._speed;
}

void Ghost::Attack()
{
	if (_giveDamage == false && _collider->IsCollision(_target.lock()->GetCollider()))
	{
		_giveDamage = true;
		GiveDamage(_target.lock());
	}
}
