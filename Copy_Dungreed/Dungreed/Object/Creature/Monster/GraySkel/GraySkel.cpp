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
	if (_weaponSlot[_curWeaponSlot] != nullptr)
	{
		float angle;

		if (_reverseTexture)
			angle = 1 * PI;
		else
			angle = 0;

		_weaponSlot[_curWeaponSlot]->SetShowTo(angle);
	}
	Monster::Update();
}

void GraySkel::AI()
{
	if (_weaponSlot[_curWeaponSlot]->GetAnimation()->GetCurAnim() == Creature::Creature_State::ATTACK && 
		_weaponSlot[_curWeaponSlot]->GetAnimation()->IsPlaying() == true)
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
		_movement->SetPassFloor(true);
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
	_weaponSlot[_curWeaponSlot]->GetAnimation()->SetBeforeChangeFunc([=](std::pair<int,int> value) 
		{
			_weaponSlot[_curWeaponSlot]->GetObjectTexture()->GetTransform()->GetPos() = 
			Vector2(_weaponSlot[_curWeaponSlot]->GetObjectTexture()->Left(), _weaponSlot[_curWeaponSlot]->GetObjectTexture()->Bottom());
		});
	
	_weaponSlot[_curWeaponSlot]->GetAnimation()->SetAfterChangeFunc([=](std::pair<int, int> value) 
		{
			_weaponSlot[_curWeaponSlot]->GetObjectTexture()->SetLeft(_weaponSlot[_curWeaponSlot]->GetObjectTexture()->GetTransform()->GetPos().x);
			_weaponSlot[_curWeaponSlot]->GetObjectTexture()->SetBottom(_weaponSlot[_curWeaponSlot]->GetObjectTexture()->GetTransform()->GetPos().y);
		});

	Monster::Attack();
}

void GraySkel::MovementEvent()
{
	// 좌우로 이동 중이라면
	if (_movement->GetVelocity().x != 0)
	{
		_anim->ChangeAnimation(Creature_State::RUN);

		// 오른쪽으로 이동 중이라면
		if (_movement->GetVelocity().x > 0 && _reverseTexture == true && _movement->IsFalling() == false)
			ReverseTexture();
		// 왼쪽으로 이동 중이라면
		else if (_movement->GetVelocity().x < 0 && _reverseTexture == false && _movement->IsFalling() == false)
			ReverseTexture();
	}
	else // 가만히 있다면
	{
		_anim->ChangeAnimation(Creature_State::IDLE);
	}

	// 위 아래로 움직이는 중이라면
	if (_movement->GetVelocity().y != 0)
	{
		_anim->ChangeAnimation(Creature_State::JUMP);
	}
}
