#include "framework.h"
#include "Melee.h"

Melee::Melee(int level, int num)
	: Weapon(level,num)
{
	_weaponType = MELEE;
	_appendAngle = { -0.1f,0.7f };
	_offset = { 45,-25 };
}

Melee::~Melee()
{
}

void Melee::Attack()
{
	if (_attackedTime < _attackDelay)
		return;

	_attackedTime = 0.0f;

	++_angleIndex;

	if (_angleIndex >= _appendAngle.size())
		_angleIndex = 0;

	AttackEffect();

	shared_ptr<Collider> _attack = make_shared<RectCollider>(_attackRange);
	_attack->GetTransform()->GetPos() = _attackArm->GetWorldPos();
	_attack->GetAngle() = (MOUSE_WORLD_POS - _owner.lock()->GetTexture()->GetTransform()->GetPos()).Angle() - (0.5f * PI);
	_attack->Update();

	vector<shared_ptr<Object>> _collisions = GAME->GetCollisions(_attack, Object::Object_Type::CREATURE);
	for (auto& enemy : _collisions)
	{
		if (enemy != _owner.lock())
		{
			shared_ptr<Creature> creature = dynamic_pointer_cast<Creature>(enemy);
			creature->Damaged(_status);
		}
	}
}

void Melee::AttackEffect()
{
	shared_ptr<Effect> swing = MAKE_WEAPON_EFFECT(_weaponType, _num);
	swing->GetTexture()->GetTransform()->GetPos() = _attackArm->GetWorldPos();
	swing->GetTexture()->GetTransform()->GetAngle() = (MOUSE_WORLD_POS - _owner.lock()->GetTexture()->GetTransform()->GetPos()).Angle() - (0.5f * PI);

	_attackRange = swing->GetTexture()->GetHalfSize();

	if (_reversed)
		swing->GetTexture()->ReverseToX();

	GAME->AddEffect(swing);
}

void Melee::SetWeapon()
{
	if (_owner.lock() != nullptr)
	{
		_springArm->GetPos() = _offset + _owner.lock()->GetTexture()->GetTransform()->GetPos();
		_ownerFollower->GetAngle() = (MOUSE_WORLD_POS - _owner.lock()->GetTexture()->GetTransform()->GetPos()).Angle();
		_attackArm->GetPos().x = _weaponLength;

		float angle;

		if (_owner.lock()->GetReversed())
		{
			if (_reversed == false)
			{
				_texture->ReverseToY();
				_offset.x *= -1;
				_reversed = true;
			}
			_texture->GetTransform()->GetPos().y = -_weaponLength;
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
			_texture->GetTransform()->GetPos().y = _weaponLength;
			angle = (MOUSE_WORLD_POS - _owner.lock()->GetTexture()->GetTransform()->GetPos()).Angle() - (_appendAngle[_angleIndex] * PI);
			_springArm->GetAngle() = angle;
		}

		_springArm->UpdateWorld();
		_ownerFollower->UpdateWorld();
		_attackArm->UpdateWorld();
	}
}
