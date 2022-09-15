#include "framework.h"
#include "Weapon.h"

Weapon::Weapon()
{
	_itemType = WEAPON;
}

void Weapon::Update()
{
	_attackDelayTime += DELTA_TIME;
	if (_attacked)
	{
		_giveDamageDelayRunTime += DELTA_TIME;
		if (_giveDamageDelayRunTime >= _giveDamageDelay)
		{
			CheckAttack();
			_attacked = false;
		}
	}

	SetWeapon();

	Item::Update();

	if(_anim != nullptr && _anim->GetIsPlaying() == false)
		_anim->ChangeAnimation(Creature::State::IDLE);
}

void Weapon::Attack()
{
	_attacked = true;
	_giveDamageDelayRunTime = 0.0f;

	if (_anim != nullptr)
		_anim->ChangeAnimation(Creature::State::ATTACK);
}

void Weapon::CheckAttack()
{
}

void Weapon::Skill()
{
}

void Weapon::GiveDamage(shared_ptr<Creature> enemy)
{
	enemy->Damaged(_status);
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

void Weapon::SetOwner(shared_ptr<Creature> owner)
{
	Item::SetOwner(owner);

	_springArm = make_shared<Transform>();
	_attackOfsset = make_shared<Transform>();
	_ownerFollower = make_shared<Transform>();

	_ownerFollower->SetParent(_owner.lock()->GetTexture()->GetTransform());
	_attackOfsset->SetParent(_ownerFollower);
	_texture->GetTransform()->SetParent(_springArm);

	_weaponLength = _texture->GetHalfSize().y;
}
