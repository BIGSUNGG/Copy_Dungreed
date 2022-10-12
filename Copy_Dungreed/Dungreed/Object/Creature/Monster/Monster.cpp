#include "framework.h"
#include "Monster.h"

Monster::Monster(int level, int num)
	:Creature(level, num)
{
	_creatureType = Creature_Type::ENEMY;
	_speed = 300.0f;
	_render = false;
	
	SOUND->Add("Hit_Monster", "Resource/Sound/Creature/Monster/Hit/Hit_Monster.wav");
	SOUND->Add("MonsterDie", "Resource/Sound/Creature/Monster/Die/MonsterDie.wav");
}

void Monster::Update()
{
	if (GAME->GetPlaying())
	{
		MovementEvent();

		SearchTarget();

		if (_spawn == true)
			AI();

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
	if (_spawn || GAME->GetPlaying() == false || GAME->GetPlayer() == nullptr)
		Creature::Render();
}

void Monster::SearchTarget()
{
	if (_target.lock() != nullptr)
		return;

	auto collisions = GAME->GetCollisions(_collider, Object::Object_Type::CREATURE);

	float length = (_texture->GetTransform()->GetPos() - GAME->GetPlayer()->GetObjectTexture()->GetTransform()->GetPos()).Length();

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
	_render = true;
	SpawnEffect();
}

bool Monster::GetDamage(shared_ptr<Creature> enemy, shared_ptr<Item> weapon)
{
	if(_spawn == false)
		return false;

	const bool& damaged = Creature::GetDamage(enemy, weapon);

	if (_status._hp > 0)
	{
		SOUND->Play("Hit_Monster");
		_buffer->_data.selected = 1;
		_buffer->_data.value1 = 1;
		_buffer->_data.value2 = 0;
		_buffer->_data.value3 = 0;
	}
	else
		SOUND->Play("MonsterDie");

	return damaged;
}

void Monster::SpawnEffect()
{
	shared_ptr<Effect> spawn = MAKE_CREATURE_EFFECT(Map::Level::PUBLIC, 1);
	spawn->GetObjectTexture()->GetTransform()->GetPos() = _texture->GetTransform()->GetPos();

	if (_reversed)
		spawn->GetObjectTexture()->ReverseToX();

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
