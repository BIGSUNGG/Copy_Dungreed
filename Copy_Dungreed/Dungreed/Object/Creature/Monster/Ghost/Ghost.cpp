#include "framework.h"
#include "Ghost.h"

Ghost::Ghost(int level, int num)
	: Monster(level,num)
{
	_status.SetMaxHp(15);
	_status._speed = 300.0f;

	_movement->SetGravityRatio(0.0f);
	_movement->SetCollision(false);
	
}

void Ghost::Update()
{
	Monster::Update();
}

void Ghost::AI()
{
	// ���� ���̶��
	if (_attack)
	{
		_anim->ChangeAnimation(Creature::ATTACK);

		// ���� �������� ����
		_movement->GetMoveDir() += _attackDirection * _attackSpeed;
		Attack();

		// ���� ���� ���� �ð� Ȯ��
		_attackTime += DELTA_TIME;
		if (_attackTime >= _attackDuration) // ���� ���� ���� �ð��� ���� ���� �ð��� �Ѿ��ٸ�
		{
			// ���� ����
			_attackTime = 0.0f;
			_attack = false;
		}
	}
	// ���� ���� �ƴ϶��
	else
	{
		_anim->ChangeAnimation(Creature::IDLE);

		// Ÿ���� �����ʿ� �ִٸ�
		if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x && _reverseTexture == true)
			ReverseTexture();
		// Ÿ���� ���ʿ� �ִٸ�
		else if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x < _texture->GetTransform()->GetPos().x && _reverseTexture == false)
			ReverseTexture();

		// Ÿ���� �ָ� �ִٸ�
		float length = abs((_target.lock()->GetObjectTexture()->GetTransform()->GetPos() - _texture->GetTransform()->GetPos()).Length());
		if (length >= _targetDistance)
		{
			MoveTo(_target.lock());
		}

		// Ÿ���� ���� ���� �ȿ� �ִٸ�
		if (_targetAttackDistance >= length)
		{			
			_attackWatitTime += DELTA_TIME;
			if (_attackWatitTime >= _attackWaitDelay)
			{
				// ���� ����
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
	// object �������� �̵�
	_attackDirection = object->GetPos() - this->GetPos();
	_attackDirection.Normalize();

	_movement->GetMoveDir() += _attackDirection * _status._speed;
}

void Ghost::Attack()
{
	// Ÿ�ٰ� �ε����ٸ�
	if (_giveDamage == false && _collider->IsCollision(_target.lock()->GetCollider()))
	{
		// ������ �ֱ�
		_giveDamage = true;
		GiveDamage(_attackDamage, _target.lock());
	}
}
