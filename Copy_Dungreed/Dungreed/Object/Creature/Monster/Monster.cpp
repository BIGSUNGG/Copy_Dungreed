#include "framework.h"
#include "Monster.h"

Monster::Monster(int level, int num)
	:Creature(level, num)
{
	_creatureType = Creature_Type::ENEMY;
	_targetDistanceGround = (MathUtility::RandomFloat(_targetDistanceMin, _targetDistanceMax)) * _targetDistanceRatio;
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

	Creature::Update();
}

void Monster::Render()
{
	if (_spawn || GAME->GetObjectUpdate() == false)
		Creature::Render();
}

void Monster::SearchTarget()
{
	if (_target.lock() != nullptr)
		return;

	auto collisions =GAME->GetCollisions(_collider, Object::Object_Type::CREATURE);
	
	float length = (_texture->GetTransform()->GetPos() - GAME->GetPlayer()->GetTexture()->GetTransform()->GetPos()).Length();

	if (length <= _searchLength)
	{
		_target = GAME->GetPlayer();
		SpawnEffect();
	}
}

void Monster::AI()
{
	if (_target.lock() == nullptr || _weaponSlot[_curWeaponSlot]->GetAnimation()->GetCurAnim() == Creature::State::ATTACK)
		return;

	float length = abs(_target.lock()->GetTexture()->GetTransform()->GetPos().x - _texture->GetTransform()->GetPos().x);
	if (length >= _targetDistanceGround)
	{
		if (_target.lock()->GetTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x)
			_movement.x += _speed;
		else
			_movement.x -= _speed;
	}
	else if (_texture->Top() < _target.lock()->GetTexture()->GetTransform()->GetPos().y && _target.lock()->GetIsFalling() == false)
	{
		if (length >= _targetDistanceJumping)
		{
			if (_target.lock()->GetTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x)
				_movement.x += _speed;
			else
				_movement.x -= _speed;
		}

		Jump();
	}
	else if (_texture->Bottom() > _target.lock()->GetTexture()->Top())
	{
		_passFloor = true;
	}
	else if(_texture->Top() >= _target.lock()->GetTexture()->Bottom() && _texture->Bottom() <= _target.lock()->GetTexture()->Bottom())
	{
		if (_target.lock()->GetTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x && _reversed == true)
			ReverseTexture();
		else if (_target.lock()->GetTexture()->GetTransform()->GetPos().x < _texture->GetTransform()->GetPos().x && _reversed == false)
			ReverseTexture();

		Attack();
	}
	else
	{
		if (length >= _targetDistanceJumping)
		{
			if (_target.lock()->GetTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x)
				_movement.x += _speed;
			else
				_movement.x -= _speed;
		}
	}
}

void Monster::Jump()
{
	if (_isFalling == false)
		_jumpPower = _jumpPowerMax;
}

bool Monster::Damaged(Status status)
{
	if(_spawn == false)
		return false;

	Creature::Damaged(status);
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
