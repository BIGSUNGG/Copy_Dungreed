#include "framework.h"
#include "GraySkel.h"

GraySkel::GraySkel(int level, int num)
	: Monster(level, num)
{
	_status.SetMaxHp(80);
	_status._speed = 300.0f;

	_ableDropGold = true;
}

void GraySkel::Update()
{
	auto curWeapon = GetCurWeapon();
	if (curWeapon != nullptr)
	{
		float angle;

		if (_reverseTexture)
			angle = 1 * PI;
		else
			angle = 0;

		curWeapon->SetShowTo(angle);
	}
	Monster::Update();
}

void GraySkel::AI()
{
	auto curWeapon = GetCurWeapon();
	if (curWeapon->GetAnimation()->GetCurAnim() == Creature::Creature_State::ATTACK &&
		curWeapon->GetAnimation()->IsPlaying() == true)
		return;

	// 타겟이 공격할 수 있는 길이보다 멀리있다면
	float length = abs(_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x - _texture->GetTransform()->GetPos().x);
	if (length >= _targetAttackDistance)
	{		
		// 타겟이 오른쪽에 있다면
		if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x) 
			MoveRight();
		// 타겟이 왼쪽에 있다면
		else
			MoveLeft();
	}
	// 타겟이 공중에 있지않고 위에 있다면
	else if (_texture->Top() < _target.lock()->GetObjectTexture()->GetTransform()->GetPos().y && _target.lock()->IsFalling() == false)
	{
		// 타겟이 바로 위에 있지않다면
		if (length >= _targetJumpOrFallDistance)
		{						
			// 타겟이 오른쪽에 있다면
			if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x)
				MoveRight();
			// 타겟이 왼쪽에 있다면
			else 
				MoveLeft();
		}
		// 타겟이 바로 위에 있다면
		else 
			Jump();		
	}
	// 타겟이 아래에 있다면
	else if (_texture->Bottom() > _target.lock()->GetObjectTexture()->Top())
	{
		_movementComponent->SetPassFloor(true);
	}
	// 타겟이 공격 범위안에 있다면
	else
	{
		// 타겟이 오른쪽에 있고 왼쪽을 보고 있다면
		if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x && _reverseTexture == true)
			ReverseTexture();
		// 타겟이 왼쪽에 있고 오른쪽을 보고 있다면
		else if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x < _texture->GetTransform()->GetPos().x && _reverseTexture == false)
			ReverseTexture();
		
		// 타겟과 같은 높이에 있다면
		if (_collider->Bottom() >= _target.lock()->GetCollider()->Bottom())
			Attack();
	}
}

void GraySkel::Attack()
{
	auto curWeapon = GetCurWeapon();

	// 애니메이션 변경 시 오브젝트 위치 재조정
	curWeapon->GetAnimation()->SetBeforeChangeFunc([=](std::pair<int,int> value) 
		{
			curWeapon->GetObjectTexture()->GetTransform()->GetPos() = 
			Vector2(curWeapon->GetObjectTexture()->Left(), curWeapon->GetObjectTexture()->Bottom());
		});
	
	curWeapon->GetAnimation()->SetAfterChangeFunc([=](std::pair<int, int> value) 
		{
			curWeapon->GetObjectTexture()->SetLeft(curWeapon->GetObjectTexture()->GetTransform()->GetPos().x);
			curWeapon->GetObjectTexture()->SetBottom(curWeapon->GetObjectTexture()->GetTransform()->GetPos().y);
		});

	Monster::Attack();
}

void GraySkel::MovementEvent()
{
	// 좌우로 이동 중이라면
	if (_movementComponent->GetVelocity().x != 0)
	{
		_anim->ChangeAnimation(Creature_State::RUN);

		// 오른쪽으로 이동 중이라면
		if (_movementComponent->GetVelocity().x > 0 && _reverseTexture == true && _movementComponent->IsFalling() == false)
			ReverseTexture();
		// 왼쪽으로 이동 중이라면
		else if (_movementComponent->GetVelocity().x < 0 && _reverseTexture == false && _movementComponent->IsFalling() == false)
			ReverseTexture();
	}
	else // 가만히 있다면
	{
		_anim->ChangeAnimation(Creature_State::IDLE);
	}

	// 위 아래로 움직이는 중이라면
	if (_movementComponent->GetVelocity().y != 0)
	{
		_anim->ChangeAnimation(Creature_State::JUMP);
	}
}
