#include "framework.h"
#include "Gun.h"

Gun::Gun(int level, int num)
	:Weapon(level,num)
{
	_weaponType = GUN;
	_offset = { 40,-10 };
}

Gun::~Gun()
{
}

void Gun::Attack()
{
	if (_attackDelayTime < _attackDelay)
		return;

	_attackDelayTime = 0.0f;

	++_index;

	if (_index >= _appendAngle.size())
		_index = 0;

	shared_ptr<Bullet> _bullet = MAKE_PLAYER_BULLET(_weaponType, 0);
	_bullet->GetObjectTexture()->GetTransform()->GetPos() = _springArm->GetWorldPos();
	_bullet->GetObjectTexture()->GetTransform()->GetAngle() = _showDirection - (0.5f * PI);

	Vector2 direction = { 1.0f,tan(_showDirection) };

	direction.Normalize();
	if (_reversed)
		direction *= -1;

	_bullet->SetDirection(direction);
	_bullet->SetSpeed(_bulletSpeed);
	_bullet->SetOwner(shared_from_this());

	bool addBullet = false;

	GAME->AddEctObject(_bullet);

	Weapon::Attack();
}

void Gun::AttackEffect()
{
}

void Gun::SetWeapon()
{
	if (_owner.lock() != nullptr)
	{
		_springArm->GetPos() = _offset + _owner.lock()->GetObjectTexture()->GetTransform()->GetPos();
		_ownerFollower->GetAngle() = _showDirection;
		_attackOfsset->GetPos().x = _weaponLength;
		_texture->GetTransform()->GetPos().x = _weaponLength;

		float angle;

		if (_owner.lock()->GetReversed())
		{
			if (_reversed == false)
			{
				_texture->ReverseToY();
				_offset.x *= -1;
				_reversed = true;
			}
			angle = _showDirection + (_appendAngle[_index] * PI);
			_springArm->GetAngle() = angle;
		}
		else
		{
			if (_reversed == true)
			{
				_texture->ReverseToY();
				_offset.x *= -1;
				_reversed = false;
			}
			angle = _showDirection - (_appendAngle[_index] * PI);
			_springArm->GetAngle() = angle;
		}

		_springArm->UpdateWorld();
		_ownerFollower->UpdateWorld();
		_attackOfsset->UpdateWorld();
	}
}
