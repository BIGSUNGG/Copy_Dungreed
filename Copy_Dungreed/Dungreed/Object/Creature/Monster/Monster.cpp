#include "framework.h"
#include "Monster.h"

Monster::Monster(int level, int num)
	:Creature(level, num)
{
	_creatureType = Creature_Type::ENEMY;
	_speed = 300.0f;
}

void Monster::Update()
{
	if (GAME->GetObjectUpdate())
	{
		MovementEvent();

		SearchTarget();

		if (_spawn == true)
			AI();

		if (_weaponSlot[_curWeaponSlot] != nullptr)
		{
			float angle;

			if (_reversed)
				angle = 0;
			else
				angle =  1 * PI;

			_weaponSlot[_curWeaponSlot]->SetShowTo(angle);
		}

		if (_spawn == false && _target.lock() != nullptr)
		{
			_spawnDelay -= DELTA_TIME;
			if (_spawnDelay <= 0)		
				_spawn = true;
		}
	}

	if (_spawn == true)
		Creature::Update();
	else
		Object::Update();
}

void Monster::Render()
{
	if (_spawn || GAME->GetObjectUpdate() == false || GAME->GetPlayer() == nullptr)
		Creature::Render();
}

void Monster::SearchTarget()
{
	if (_target.lock() != nullptr)
		return;

	auto collisions = GAME->GetCollisions(_collider, Object::Object_Type::CREATURE);

	float length = (_texture->GetTransform()->GetPos() - GAME->GetPlayer()->GetTexture()->GetTransform()->GetPos()).Length();

	if (length <= _searchLength)
	{
		SetTarget(GAME->GetPlayer());
		MAP_MANAGER->SetTarget(GAME->GetPlayer());
	}
}

void Monster::AI()
{
}

void Monster::SetTarget(shared_ptr<Creature> target)
{
	_target = target;
	SpawnEffect();
}

bool Monster::GetDamage(Status status)
{
	if(_spawn == false)
		return false;

	return Creature::GetDamage(status);
}

void Monster::SpawnEffect()
{
	shared_ptr<Effect> spawn = MAKE_CREATURE_EFFECT(Map::Level::PUBLIC, 1);
	spawn->GetTexture()->GetTransform()->GetPos() = _texture->GetTransform()->GetPos();

	if (_reversed)
		spawn->GetTexture()->ReverseToX();

	GAME->AddEffect(spawn);
}

void Monster::MovementEvent()
{
	if (_velocity.x != 0)
	{
		_anim->ChangeAnimation(State::RUN);

		if (_velocity.x > 0 && _reversed == true && _isFalling == false)
			ReverseTexture();
		else if (_velocity.x < 0 && _reversed == false && _isFalling == false)
			ReverseTexture();
	}
	else
	{
		_anim->ChangeAnimation(State::IDLE);
	}

	if (_velocity.y != 0)
	{
		_anim->ChangeAnimation(State::JUMP);

		_isFalling = true;
	}
	else
	{
		_isFalling = false;
		_jumpPower = 0.0f;
	}
}
