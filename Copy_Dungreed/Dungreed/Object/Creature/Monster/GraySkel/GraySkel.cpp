#include "framework.h"
#include "GraySkel.h"

GraySkel::GraySkel(int level, int num)
	: Monster(level, num)
{
	_status.SetMaxHp(80);
	_status._atk = 40;
}

void GraySkel::AI()
{
	if (_target.lock() == nullptr || _weaponSlot[_curWeaponSlot]->GetAnimation()->GetCurAnim() == Creature::State::ATTACK)
		return;

	float length = abs(_target.lock()->GetTexture()->GetTransform()->GetPos().x - _texture->GetTransform()->GetPos().x);
	if (length >= _targetDistanceGround)
	{
		if (_target.lock()->GetTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x)
			_movement.x += _speed;
		else
			_movement.x -= _speed;
	}
	else if (_texture->Top() < _target.lock()->GetTexture()->GetTransform()->GetPos().y && _target.lock()->GetIsFalling() == false)
	{
		if (length >= _targetDistanceJumping)
		{
			if (_target.lock()->GetTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x)
				_movement.x += _speed;
			else
				_movement.x -= _speed;
		}

		Jump();
	}
	else if (_texture->Bottom() > _target.lock()->GetTexture()->Top())
	{
		_passFloor = true;
	}
	else
	{
		if (_target.lock()->GetTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x && _reversed == true)
			ReverseTexture();
		else if (_target.lock()->GetTexture()->GetTransform()->GetPos().x < _texture->GetTransform()->GetPos().x && _reversed == false)
			ReverseTexture();

		Attack();
	}
}
