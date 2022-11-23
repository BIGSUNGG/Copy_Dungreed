#include "framework.h"
#include "GraySkel.h"

GraySkel::GraySkel(int level, int num)
	: Monster(level, num)
{
	_status.SetMaxHp(80);
	_status._atk = 25;
	_status._speed = 300.0f;

	_dropGold = true;
}

void GraySkel::Update()
{
	if (_weaponSlot[_curWeaponSlot] != nullptr)
	{
		float angle;

		if (_reversed)
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

	float length = abs(_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x - _texture->GetTransform()->GetPos().x);
	if (length >= _targetDistanceGround)
	{
		if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x)
			MoveRight();
		else
			MoveLeft();
	}
	else if (_texture->Top() < _target.lock()->GetObjectTexture()->GetTransform()->GetPos().y && _target.lock()->IsFalling() == false)
	{
		if (length >= _targetDistanceJumping)
		{
			if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x)
				MoveRight();
			else
				MoveLeft();
		}

		Jump();
	}
	else if (_texture->Bottom() > _target.lock()->GetObjectTexture()->Top())
	{
		_movement->SetPassFloor(true);
	}
	else
	{
		if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x && _reversed == true)
			ReverseTexture();
		else if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x < _texture->GetTransform()->GetPos().x && _reversed == false)
			ReverseTexture();
		float t = _target.lock()->GetCollider()->Bottom();
		if(_collider->Bottom() >= _target.lock()->GetCollider()->Bottom())
			Attack();
	}
}

void GraySkel::Attack()
{
	_weaponSlot[_curWeaponSlot]->GetAnimation()->SetBeforeChangeFunc([=](pair<int,int> pair) {
		_weaponSlot[_curWeaponSlot]->GetObjectTexture()->GetTransform()->GetPos() = 
			Vector2(_weaponSlot[_curWeaponSlot]->GetObjectTexture()->Left(), _weaponSlot[_curWeaponSlot]->GetObjectTexture()->Bottom());
		});
	
	_weaponSlot[_curWeaponSlot]->GetAnimation()->SetAfterChangeFunc([=](pair<int, int> pair) {
		_weaponSlot[_curWeaponSlot]->GetObjectTexture()->SetLeft(_weaponSlot[_curWeaponSlot]->GetObjectTexture()->GetTransform()->GetPos().x);
		_weaponSlot[_curWeaponSlot]->GetObjectTexture()->SetBottom(_weaponSlot[_curWeaponSlot]->GetObjectTexture()->GetTransform()->GetPos().y);
		});

	Monster::Attack();
}

void GraySkel::MovementEvent()
{
	if (_movement->GetVelocity().x != 0)
	{
		_anim->ChangeAnimation(Creature_State::RUN);

		if (_movement->GetVelocity().x > 0 && _reversed == true && _movement->IsFalling() == false)
			ReverseTexture();
		else if (_movement->GetVelocity().x < 0 && _reversed == false && _movement->IsFalling() == false)
			ReverseTexture();
	}
	else
	{
		_anim->ChangeAnimation(Creature_State::IDLE);
	}

	if (_movement->GetVelocity().y != 0)
	{
		_anim->ChangeAnimation(Creature_State::JUMP);
	}
}
