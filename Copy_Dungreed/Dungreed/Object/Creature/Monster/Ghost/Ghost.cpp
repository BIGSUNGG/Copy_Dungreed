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
	// 공격 중이라면
	if (_attack)
	{
		_anim->ChangeAnimation(Creature::ATTACK);

		// 공격 방향으로 돌진
		_movement->GetMoveDir() += _attackDirection * _attackSpeed;
		Attack();

		// 현재 공격 지속 시간 확인
		_attackTime += DELTA_TIME;
		if (_attackTime >= _attackDuration) // 현재 공격 지속 시간이 공격 지속 시간을 넘었다면
		{
			// 공격 중지
			_attackTime = 0.0f;
			_attack = false;
		}
	}
	// 공격 중이 아니라면
	else
	{
		_anim->ChangeAnimation(Creature::IDLE);

		// 타겟이 오른쪽에 있다면
		if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x && _reverseTexture == true)
			ReverseTexture();
		// 타겟이 왼쪽에 있다면
		else if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x < _texture->GetTransform()->GetPos().x && _reverseTexture == false)
			ReverseTexture();

		// 타겟이 멀리 있다면
		float length = abs((_target.lock()->GetObjectTexture()->GetTransform()->GetPos() - _texture->GetTransform()->GetPos()).Length());
		if (length >= _targetDistance)
		{
			MoveTo(_target.lock());
		}

		// 타겟이 공격 범위 안에 있다면
		if (_targetAttackDistance >= length)
		{			
			_attackWatitTime += DELTA_TIME;
			if (_attackWatitTime >= _attackWaitDelay)
			{
				// 공격 시작
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
	// object 방향으로 이동
	_attackDirection = object->GetPos() - this->GetPos();
	_attackDirection.Normalize();

	_movement->GetMoveDir() += _attackDirection * _status._speed;
}

void Ghost::Attack()
{
	// 타겟과 부딪혔다면
	if (_giveDamage == false && _collider->IsCollision(_target.lock()->GetCollider()))
	{
		// 데미지 주기
		_giveDamage = true;
		GiveDamage(_attackDamage, _target.lock());
	}
}
