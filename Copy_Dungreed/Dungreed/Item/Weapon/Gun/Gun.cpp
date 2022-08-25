#include "framework.h"
#include "Gun.h"

Gun::Gun(int level, int num)
	: Weapon(level,num)
{
	_weaponType = GUN;
	_offset = { 40,-10 };

	_bullets.reserve(10);
}

Gun::~Gun()
{
}

void Gun::Update()
{
	Weapon::Update();

	for (auto& bullet : _bullets)
	{
		if (bullet == nullptr)
			continue;

		if (bullet->GetIsActive() == false)
		{
			bullet = nullptr;
			continue;
		}

		bullet->Update();
	}
}

void Gun::Render()
{
	for (auto& bullet : _bullets)
	{
		if (bullet == nullptr)
			continue;

		bullet->Render();
	}

	Weapon::Render();
}

void Gun::Attack()
{
	shared_ptr<Bullet> _bullet = MAKE_PLAYER_BULLET(_weaponType, _num);
	_bullet->GetTexture()->GetTransform()->GetPos() = _texture->GetTransform()->GetWorldPos();
	_bullet->GetTexture()->GetTransform()->GetAngle() = (MOUSE_WORLD_POS - _owner.lock()->GetTexture()->GetTransform()->GetPos()).Angle() - (0.5f * PI);

	Vector2 direction = MOUSE_WORLD_POS - _owner.lock()->GetTexture()->GetTransform()->GetPos();
	direction.Normalize();

	_bullet->SetDirection(direction);
	_bullet->SetSpeed(_bulletSpeed);
	_bullet->SetOwner(_owner.lock());

	bool addBullet = false;

	for (auto& bullet : _bullets)
	{
		if (bullet != nullptr)
			continue;

		bullet = _bullet;
		addBullet = true;
		break;
	}

	if (addBullet == false)
		_bullets.emplace_back(_bullet);
}

void Gun::AttackEffect()
{
}

void Gun::SetWeapon()
{
	if (_owner.lock() != nullptr)
	{
		_springArm->GetPos() = _offset + _owner.lock()->GetTexture()->GetTransform()->GetPos();
		_ownerFollower->GetAngle() = (MOUSE_WORLD_POS - _owner.lock()->GetTexture()->GetTransform()->GetPos()).Angle();
		_attackArm->GetPos().x = _weaponLength;
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
			angle = (MOUSE_WORLD_POS - _owner.lock()->GetTexture()->GetTransform()->GetPos()).Angle() + (_appendAngle[_angleIndex] * PI);
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
			angle = (MOUSE_WORLD_POS - _owner.lock()->GetTexture()->GetTransform()->GetPos()).Angle() - (_appendAngle[_angleIndex] * PI);
			_springArm->GetAngle() = angle;
		}

		_springArm->UpdateWorld();
		_ownerFollower->UpdateWorld();
		_attackArm->UpdateWorld();
	}
}
