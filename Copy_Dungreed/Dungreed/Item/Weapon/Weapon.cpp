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

	SetWeapon();

	Item::Update();
}

void Weapon::Attack()
{
}

void Weapon::Skill()
{
}

void Weapon::Damaged(const Status& status)
{
}

void Weapon::AttackEffect()
{
}

void Weapon::SetWeapon()
{
}

void Weapon::SetOwner(shared_ptr<Player> owner)
{
	Item::SetOwner(owner);

	_springArm = make_shared<Transform>();
	_attackArm = make_shared<Transform>();
	_ownerFollower = make_shared<Transform>();

	_ownerFollower->SetParent(_owner.lock()->GetTexture()->GetTransform());
	_attackArm->SetParent(_ownerFollower);
	_texture->GetTransform()->SetParent(_springArm);

	_weaponLength = _texture->GetHalfSize().y;
}
