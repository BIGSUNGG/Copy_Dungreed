#include "framework.h"
#include "Weapon.h"

Weapon::Weapon(int level, int num)
	: Item(level,num)
{
	_itemType = WEAPON;
}

void Weapon::Update()
{
	_attackedTime += DELTA_TIME;

	if (_owner != nullptr)
	{
		_springArm->GetPos() = _owner->GetHandPos() + _owner->GetTexture()->GetTransform()->GetPos();
		_ownerFollower->GetAngle() = (MOUSE_WORLD_POS - _owner->GetTexture()->GetTransform()->GetPos()).Angle();
		_swingArm->GetPos().x = _weaponLength;

		float angle;

		if (_owner->GetReversed())
		{
			if (_reversed == false)
			{
				_texture->ReverseToY();
				_texture->ReverseToX();
				_reversed = true;
			}
			_texture->GetTransform()->GetPos().y = -_weaponLength;
			angle = (MOUSE_WORLD_POS - _owner->GetTexture()->GetTransform()->GetPos()).Angle() + (_appendAngle[_angleIndex] * PI);
			_springArm->GetAngle() = angle;
		}
		else
		{
			if (_reversed == true)
			{
				_texture->ReverseToY();
				_texture->ReverseToX();
				_reversed = false;
			}
			_texture->GetTransform()->GetPos().y = _weaponLength;
			angle = (MOUSE_WORLD_POS - _owner->GetTexture()->GetTransform()->GetPos()).Angle() - (_appendAngle[_angleIndex] * PI);
			_springArm->GetAngle() = angle;
		}

		_springArm->UpdateWorld();
		_ownerFollower->UpdateWorld();
		_swingArm->UpdateWorld();
	}

	Item::Update();
}

void Weapon::Attack()
{
	if (_attackedTime < _attackDelay)
		return;
	
	_attackedTime = 0.0f;

	++_angleIndex;

	if (_angleIndex >= _appendAngle.size())
		_angleIndex = 0;

	SwingEffect();

	shared_ptr<Collider> _attack = make_shared<RectCollider>(_attackRange);
	_attack->GetTransform()->GetPos() = _swingArm->GetWorldPos();
	_attack->GetAngle() = (MOUSE_WORLD_POS - _owner->GetTexture()->GetTransform()->GetPos()).Angle() - (0.5f * PI);
	_attack->Update();

	GAME->AddTempCollider(_attack);
	vector<shared_ptr<Object>> _collisions = GAME->GetCollisions(_attack, Object::Object_Type::CREATURE);
	for (auto& enemy : _collisions)
	{
		if (enemy != _owner)
		{
			shared_ptr<Creature> creature = dynamic_pointer_cast<Creature>(enemy);
			creature->Damaged(_status);
		}
	}

}

void Weapon::Skill()
{
}

void Weapon::Damaged(const Status& status)
{
}

void Weapon::SwingEffect()
{
	shared_ptr<Effect> swing = MAKE_ITEM_EFFECT(1, 0);
	swing->GetTexture()->GetTransform()->GetPos() = _swingArm->GetWorldPos();
	swing->GetTexture()->GetTransform()->GetAngle() = (MOUSE_WORLD_POS - _owner->GetTexture()->GetTransform()->GetPos()).Angle() - (0.5f * PI);

	_attackRange = swing->GetTexture()->GetHalfSize();

	if (_reversed)
		swing->GetTexture()->ReverseToX();

	GAME->AddEffect(swing);
}

void Weapon::SetOwner(shared_ptr<Player> owner)
{
	Item::SetOwner(owner);

	_springArm = make_shared<Transform>();
	_swingArm = make_shared<Transform>();
	_ownerFollower = make_shared<Transform>();

	_ownerFollower->SetParent(_owner->GetTexture()->GetTransform());
	_swingArm->SetParent(_ownerFollower);
	_texture->GetTransform()->SetParent(_springArm);

	_weaponLength = _texture->GetHalfSize().y;
}
