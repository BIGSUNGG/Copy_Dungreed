#include "framework.h"
#include "Weapon.h"

Weapon::Weapon(int level, int num)
	: Item(level, num)
{
	_itemType = WEAPON;
}

void Weapon::Update()
{
	_skillRuntime += DELTA_TIME;
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
		_anim->ChangeAnimation(Creature::Creature_State::IDLE);
}

void Weapon::Attack()
{
	_attacked = true;
	_giveDamageDelayRunTime = 0.0f;

	if (_anim != nullptr)
		_anim->ChangeAnimation(Creature::Creature_State::ATTACK);

	SOUND->Play(_attackSound);
}

void Weapon::CheckAttack()
{
}

void Weapon::Skill()
{
	if (_skillRuntime < _skillDelay  || _skill == nullptr)
		return;

	_skillRuntime = 0.f;

	_skill();

	if (_anim != nullptr)
		_anim->ChangeAnimation(Item::Item_State::SKILL);
}

void Weapon::Damaged(const Creature_Status& status)
{
}

float Weapon::GetSkillCoolTimeRatio()
{
	float ratio = _skillRuntime / _skillDelay;
	if (ratio > 1)
		ratio = 1;

	return ratio;
}

void Weapon::AttackEffect()
{
}

void Weapon::AddOffsetIndex(const int& num)
{
	_offsetIndex += num;

	if (_offsetIndex >= _appendAngle.size())
		_offsetIndex -= _appendAngle.size();
}

void Weapon::SetWeapon()
{
}

void Weapon::SetAttackDelay(float delay)
{
	_attackDelay = delay;
	_attackDelayTime = delay;
}

void Weapon::SetOwner(shared_ptr<Creature> owner)
{
	Item::SetOwner(owner);

	_springArm = make_shared<Transform>();
	_attackOfsset = make_shared<Transform>();
	_ownerFollower = make_shared<Transform>();

	_ownerFollower->SetParent(_owner.lock()->GetObjectTexture()->GetTransform());
	_attackOfsset->SetParent(_ownerFollower);
	_texture->GetTransform()->SetParent(_springArm);

	_weaponLength = _texture->GetHalfSize().y;
}

void Weapon::SetSkill(function<void()> skill, const wstring& image)
{
	_skill = skill;
	_skillHudTexture = make_shared<Quad>(image);
}

void Weapon::SetSkillDelay(const float& delay)
{
	_skillDelay = delay;
	_skillRuntime = delay;
}
