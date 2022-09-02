#include "framework.h"
#include "Creature.h"

Creature::Creature(int level, int num)
	: Object(level, num)
{
	_objectType = Object::Object_Type::CREATURE;
}

void Creature::Update()
{
	if (GAME->GetObjectUpdate())
	{
		if (_gravity)
			_jumpPower -= _gravityPower * DELTA_TIME;

		_movement.y += _jumpPower;

		if (GAME->GetObjectUpdate())
			MoveCharacter();

		_passFloor = false;
	}

	Object::Update();

	if (_weapon != nullptr)
		_weapon->Update();
}

void Creature::Render()
{
	if (_weapon != nullptr)
	{
		bool weaponRender = _weapon->GetFastRender();
		if (!weaponRender)
			_weapon->Render();

		Object::Render();

		if (weaponRender)
			_weapon->Render();
	}
	else
		Object::Render();
}

bool Creature::Damaged(Status status)
{
	_status._hp -= _status._atk;
	if (_status._hp <= 0)
		Death();

	return true;
}

void Creature::MoveCharacter()
{
	_texture->GetTransform()->GetPos() += (_movement * DELTA_TIME);

	_texture->Update();
	_collider->Update();

	vector<shared_ptr<Object>> collisions = GAME->GetCollisions(_collider, Object::Object_Type::TILE);

	for (auto& object : collisions)
	{
		CollisionEvent(object);
	}
	_velocity = (_texture->GetTransform()->GetPos() - _beforeMove) / (float)DELTA_TIME;

	_beforeMove = _texture->GetTransform()->GetPos();
	_movement = { 0,0 };
	Object::Update();
}

void Creature::Death()
{
	_isActive = false;

	shared_ptr<Effect> dieEffect = MAKE_CREATURE_EFFECT(Map::Level::PUBLIC, 0);
	dieEffect->GetTexture()->GetTransform()->GetPos() = _texture->GetTransform()->GetPos();

	GAME->AddEffect(dieEffect);
}

void Creature::Attack()
{
	if (_weapon != nullptr)
		_weapon->Attack();

	_anim->ChangeAnimation(State::ATTACK);
}

void Creature::CollisionEvent(shared_ptr<Object> object)
{
	switch (object->GetType())
	{
	case Object::BACKGROUND:
		break;
	case Object::WALL:
		break;
	case Object::TILE:
	{
		shared_ptr<Tile> tile = dynamic_pointer_cast<Tile>(object);
		TileCollison(tile);
	}
		break;
	case Object::CREATURE:
	{
		shared_ptr<Creature> creature = dynamic_pointer_cast<Creature>(object);
		CreatureCollision(creature);
	}
		break;
	case Object::EFFECT:
		break;
	default:
		break;
	}
}

void Creature::TileCollison(shared_ptr<Tile> tile)
{
	switch (tile->GetTileType())
	{
	case Tile::BLOCK:
		TileBlockCollision(tile);
		break;
	case Tile::FLOOR:
		break;
	case Tile::LEFT_STAIR:
		break;
	case Tile::RIGHT_STAIR:
		break;
	case Tile::CELLING:
		break;
	default:
		break;
	}
}

void Creature::TileBlockCollision(shared_ptr<Tile> tile)
{
	if (_passFloor == false)
	{
		if (tile->GetTexture()->Top() <= _beforeMove.y - (_texture->GetHalfSize().y * _texture->GetTransform()->GetScale().y) && _velocity.y <= 0)
		{
			_texture->SetBottom(tile->GetTexture()->Top());
			_jumpPower = 0.0f;
			_passFloor = true;
		}
	}
}

void Creature::CreatureCollision(shared_ptr<Creature> creature)
{
}

void Creature::SetOriginalPos(Vector2 pos)
{
	Object::SetOriginalPos(pos);
	_beforeMove = pos;
	_velocity = { 0,0 };
}


void Creature::SetWeapon(shared_ptr<Weapon> weapon)
{
	_weapon = weapon;
	_weapon->SetOwner(shared_from_this());
}
