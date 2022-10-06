#include "framework.h"
#include "Melee.h"

Melee::Melee(int level, int num)
	: Weapon(level,num)
{
	_weaponType = MELEE;
	_offset = { 45,-25 };
}

Melee::~Melee()
{
}

void Melee::Attack()
{
	if (_attackDelayTime < _attackDelay)
		return;

	_attackDelayTime = 0.0f;

	++_index;

	if (_index >= _appendAngle.size())
		_index = 0;

	Weapon::Attack();
}

void Melee::CheckAttack()
{
	AttackEffect();

	shared_ptr<Collider> _attack = make_shared<RectCollider>(_attackRange);
	_attack->GetTransform()->GetPos() = _springArm->GetWorldPos();
	_attack->GetTransform()->GetAngle() = _showDirection - (0.5f * PI);
	_attack->Update();

	vector<shared_ptr<Object>> _collisions = GAME->GetCollisions(_attack, Object::Object_Type::CREATURE);
	for (auto& enemy : _collisions)
	{
		if (enemy != _owner.lock())
		{
			shared_ptr<Creature> creature = dynamic_pointer_cast<Creature>(enemy);
			if (creature->GetCreatureType() != _owner.lock()->GetCreatureType())
				GiveDamage(creature); 
		}
	}
}

void Melee::AttackEffect()
{
	if (_attackEffect == nullptr)
		return;

	shared_ptr<Effect> effect = _attackEffect();
	effect->GetObjectTexture()->GetTransform()->GetPos() = _attackOfsset->GetWorldPos();
	effect->GetObjectTexture()->GetTransform()->GetAngle() = _showDirection - (0.5f * PI);

	if (_reversed)
		effect->GetObjectTexture()->ReverseToX();

	GAME->AddEffect(effect);
}

void Melee::SetWeapon()
{
	if (_owner.lock() != nullptr)
	{
		_springArm->GetPos() = _offset + _owner.lock()->GetObjectTexture()->GetTransform()->GetPos();
		_ownerFollower->GetAngle() = _showDirection;
		_attackOfsset->GetPos().x = _weaponLength;

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
			_texture->GetTransform()->GetPos().y = _weaponLength;
			angle = _showDirection - (_appendAngle[_index] * PI);
			_springArm->GetAngle() = angle;
		}

		_springArm->UpdateWorld();
		_ownerFollower->UpdateWorld();
		_attackOfsset->UpdateWorld();
	}
}
