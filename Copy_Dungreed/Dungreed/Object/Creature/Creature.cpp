#include "framework.h"
#include "Creature.h"

Creature::Creature(int level, int num)
	: Object(level, num)
{
	_objectType = Object::Object_Type::CREATURE;
	_weaponSlot.resize(1);
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
		_passTile = false;
	}

	Object::Update();

	for (auto& weapon : _weaponSlot)
	{
		if (weapon != nullptr)
			weapon->Update();
	}
}

void Creature::Render()
{
	if (_weaponSlot[_curWeaponSlot] != nullptr)
	{
		bool weaponRender = _weaponSlot[_curWeaponSlot]->GetFastRender();
		if (!weaponRender)
			_weaponSlot[_curWeaponSlot]->Render();

		Object::Render();

		if (weaponRender)
			_weaponSlot[_curWeaponSlot]->Render();
	}
	else
		Object::Render();
}

void Creature::PostRender()
{
	Object::PostRender();

	_weaponSlot[_curWeaponSlot]->PostRender();
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
	if (_weaponSlot[_curWeaponSlot] != nullptr)
		_weaponSlot[_curWeaponSlot]->Attack();

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
	if (_passTile)
		return;

	switch (tile->GetTileType())
	{
	case Tile::BLOCK:
		TileBlockCollision(tile);
		break;
	case Tile::FLOOR:
		TileFloorCollision(tile);
		break;
	case Tile::LEFT_STAIR:
		TileLeftStairCollision(tile);
		break;
	case Tile::RIGHT_STAIR:
		TileRightStairCollision(tile);
		break;
	case Tile::CELLING:
		break;
	default:
		break;
	}
}

void Creature::TileBlockCollision(shared_ptr<Tile> tile)
{
	if (_beforeMove.y - (_texture->GetHalfSize().y * _texture->GetTransform()->GetScale().y) + 15.0f >= tile->GetCollider()->Top() && _velocity.y <= 0)
	{
		_texture->SetBottom(tile->GetCollider()->Top());
		_jumpPower = 0.0f;
	}
	else if (_beforeMove.y + (_texture->GetHalfSize().y * _texture->GetTransform()->GetScale().y) <= tile->GetCollider()->Bottom() && _velocity.y >= 0)
	{
		_texture->SetTop(tile->GetCollider()->Bottom());
		_jumpPower = 0.0f;
	}
	else if (_beforeMove.x + (_texture->GetHalfSize().x * _texture->GetTransform()->GetScale().x) <= tile->GetCollider()->Left() && _velocity.x >= 0)
	{
		_texture->SetRight(tile->GetCollider()->Left());
	}
	else if (_beforeMove.x - (_texture->GetHalfSize().x * _texture->GetTransform()->GetScale().x) >= tile->GetCollider()->Right() && _velocity.x <= 0)
	{
		_texture->SetLeft(tile->GetCollider()->Right());
	}
}

void Creature::TileFloorCollision(shared_ptr<Tile> tile)
{
	if (_passFloor == false)
	{
		if (_beforeMove.y - (_texture->GetHalfSize().y * _texture->GetTransform()->GetScale().y) >= tile->GetCollider()->Top() && _velocity.y <= 0)
		{
			_texture->SetBottom(tile->GetCollider()->Top());
			_jumpPower = 0.0f;
			_passFloor = true;
		}
	}
}

void Creature::TileLeftStairCollision(shared_ptr<Tile> tile)
{	
	if (_texture->GetTransform()->GetPos().x >= tile->GetTexture()->Left() && 
		_texture->GetTransform()->GetPos().x <= tile->GetTexture()->Right())
	{
		float x =  this->GetPos().x - tile->GetTexture()->Right();
		float y = -x;
		_texture->SetBottom(y + tile->GetTexture()->Bottom());
		_passTile = true;
		_jumpPower = 0.0f;
	}
}

void Creature::TileRightStairCollision(shared_ptr<Tile> tile)
{
	if (_texture->GetTransform()->GetPos().x >= tile->GetTexture()->Left() && 
		_texture->GetTransform()->GetPos().x <= tile->GetTexture()->Right())
	{
		float x = this->GetPos().x - tile->GetTexture()->Left();
		float y = x;
		_texture->SetBottom(y + tile->GetTexture()->Bottom());
		_passTile = true;
		_jumpPower = 0.0f;
	}
}

void Creature::CreatureCollision(shared_ptr<Creature> creature)
{
}

void Creature::SetSpawnPos(Vector2 pos)
{
	Object::SetSpawnPos(pos);
	_beforeMove = pos;
	_velocity = { 0,0 };
}


void Creature::AddWeapon(shared_ptr<Weapon> weapon)
{
	for (auto& slot : _weaponSlot)
	{
		if (slot == nullptr)
		{
			weapon->SetOwner(shared_from_this());
			slot = weapon;
			break;
		}
	}
}
