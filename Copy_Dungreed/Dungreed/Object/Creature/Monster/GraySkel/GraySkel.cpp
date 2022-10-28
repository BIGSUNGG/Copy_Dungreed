#include "framework.h"
#include "GraySkel.h"

GraySkel::GraySkel(int level, int num)
	: Monster(level, num)
{
	_status.SetMaxHp(80);
	_status._atk = 25;
	_status._speed = 300.0f;
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
		_weaponSlot[_curWeaponSlot]->GetAnimation()->GetIsPlaying() == true)
		return;

	float length = abs(_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x - _texture->GetTransform()->GetPos().x);
	if (length >= _targetDistanceGround)
	{
		if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x)
			MoveRight();
		else
			MoveLeft();
	}
	else if (_texture->Top() < _target.lock()->GetObjectTexture()->GetTransform()->GetPos().y && _target.lock()->GetIsFalling() == false)
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
		_passFloor = true;
	}
	else
	{
		if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x && _reversed == true)
			ReverseTexture();
		else if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x < _texture->GetTransform()->GetPos().x && _reversed == false)
			ReverseTexture();

		if(_target.lock()->GetIsFalling() == false)
			Attack();
	}
}

void GraySkel::Attack()
{
	_weaponSlot[_curWeaponSlot]->GetAnimation()->SetBeforeChangeFunc([=](shared_ptr<Quad> quad) {
		quad->GetTransform()->GetPos() = Vector2(quad->Left(), quad->Top());
		});

	_weaponSlot[_curWeaponSlot]->GetAnimation()->SetAfterChangeFunc([=](shared_ptr<Quad> quad) {
		quad->SetLeft(quad->GetTransform()->GetPos().x);
		quad->SetTop(quad->GetTransform()->GetPos().y);
		});
	Monster::Attack();
}

void GraySkel::MovementEvent()
{
	if (_velocity.x != 0)
	{
		_anim->ChangeAnimation(Creature_State::RUN);

		if (_velocity.x > 0 && _reversed == true && _isFalling == false)
			ReverseTexture();
		else if (_velocity.x < 0 && _reversed == false && _isFalling == false)
			ReverseTexture();
	}
	else
	{
		_anim->ChangeAnimation(Creature_State::IDLE);
	}

	if (_velocity.y != 0)
	{
		_anim->ChangeAnimation(Creature_State::JUMP);

		_isFalling = true;
	}
	else
	{
		FallingEnd();
		_jumpPower = 0.0f;
	}
}
