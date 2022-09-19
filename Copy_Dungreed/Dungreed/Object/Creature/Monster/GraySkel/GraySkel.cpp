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
			MoveRight();
		else
			MoveLeft();
	}
	else if (_texture->Top() < _target.lock()->GetTexture()->GetTransform()->GetPos().y && _target.lock()->GetIsFalling() == false)
	{
		if (length >= _targetDistanceJumping)
		{
			if (_target.lock()->GetTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x)
				MoveRight();
			else
				MoveLeft();
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

void GraySkel::TileBlockCollision(shared_ptr<Tile> tile)
{
	Monster::TileBlockCollision(tile);
	
	//if (_beforeMove.x - (_texture->GetHalfSize().x * _texture->GetTransform()->GetScale().x) <= tile->GetPos().y)
	Jump();
}
