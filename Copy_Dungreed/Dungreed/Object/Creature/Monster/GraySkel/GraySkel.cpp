#include "framework.h"
#include "GraySkel.h"

GraySkel::GraySkel(int level, int num)
	: Monster(level, num)
{
	_status.SetMaxHp(80);
	_status._atk = 25;
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
	if (_target.lock() == nullptr || _weaponSlot[_curWeaponSlot]->GetAnimation()->GetCurAnim() == Creature::State::ATTACK)
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

		Attack();
	}
}

void GraySkel::Attack()
{
	if (_reversed)
	{
		_weaponSlot[_curWeaponSlot]->GetAnimation()->SetBeforeChangeFunc([=](shared_ptr<Quad> quad) {
			quad->GetTransform()->GetPos() = Vector2(quad->Right(),quad->Bottom()); 
			});

		_weaponSlot[_curWeaponSlot]->GetAnimation()->SetAfterChangeFunc([=](shared_ptr<Quad> quad) {
			quad->SetRight(quad->GetTransform()->GetPos().x);
			quad->SetBottom(quad->GetTransform()->GetPos().y); 
			});
	}
	else
	{
		_weaponSlot[_curWeaponSlot]->GetAnimation()->SetBeforeChangeFunc([=](shared_ptr<Quad> quad) {
			quad->GetTransform()->GetPos() = Vector2(quad->Left(), quad->Bottom());
			});

		_weaponSlot[_curWeaponSlot]->GetAnimation()->SetAfterChangeFunc([=](shared_ptr<Quad> quad) {
			quad->SetLeft(quad->GetTransform()->GetPos().x);
			quad->SetBottom(quad->GetTransform()->GetPos().y);
			});
	}
	Monster::Attack();
}
