#include "framework.h"
#include "Gun.h"

Gun::Gun(int level, int num)
	:Weapon(level,num)
{
	_weaponType = GUN;
	_offset = { 40,-20 };
}

Gun::~Gun()
{
}

void Gun::Attack()
{
	if (_attackDelayTime < _attackDelay)
		return;

	_attackDelayTime = 0.0f;

	++_offsetIndex;

	if (_offsetIndex >= _appendAngle.size())
		_offsetIndex = 0;

	shared_ptr<Bullet> _bullet = MAKE_BULLET(_weaponType, 0);
	_bullet->GetObjectTexture()->GetTransform()->GetPos() = _springArm->GetWorldPos();
	_bullet->GetObjectTexture()->GetTransform()->GetAngle() = _showDirection - (0.5f * PI);
	
	float angle = _showDirection / PI;
	Vector2 direction = { 1.0f,tan(_showDirection) };

	if (angle > 0.5f || angle < -0.5f)
		direction *= -1;

	direction.Normalize();

	_bullet->SetDirection(direction);
	_bullet->SetSpeed(_bulletSpeed);
	_bullet->SetOwner(dynamic_pointer_cast<Gun>(shared_from_this()));

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
			angle = _showDirection + (_appendAngle[_offsetIndex] * PI);
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
			angle = _showDirection - (_appendAngle[_offsetIndex] * PI);
			_springArm->GetAngle() = angle;
		}

		_springArm->UpdateWorld();
		_ownerFollower->UpdateWorld();
		_attackOfsset->UpdateWorld();
	}
}
