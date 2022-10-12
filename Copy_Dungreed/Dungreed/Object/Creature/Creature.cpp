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
	_damagedRunTime += DELTA_TIME;

	if (_damagedRunTime >= _damagedRunTimeMax)
		_buffer->_data.selected = 0;

	_onStair = false;

	if (GAME->GetPlaying())
	{
		_jumpPower -= (_gravityPower * _gravityRatio) * DELTA_TIME;

		_movement.y += _jumpPower;

		if (GAME->GetPlaying())
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

	if(_weaponSlot[_curWeaponSlot] != nullptr)
		_weaponSlot[_curWeaponSlot]->PostRender();
}

bool Creature::GetDamage(shared_ptr<Creature> enemy, shared_ptr<Item> weapon)
{
	_status._hp -= enemy->GetStatus()._atk;

	if (_status._hp <= 0)
		Death();

	_damagedRunTime = 0.0f;

	return true;
}

bool Creature::GiveDamage(shared_ptr<Creature> target, shared_ptr<Item> weapon)
{
	bool attackSuccess = target->GetDamage(shared_from_this(),weapon);
	return attackSuccess;
}

void Creature::MoveCharacter()
{
	_texture->GetTransform()->GetPos() += (_movement * DELTA_TIME);

	_texture->Update();
	_collider->Update();

	vector<shared_ptr<Object>> collisions = GAME->GetCollisions(_collider, Object::Object_Type::TILE);
	sort(collisions.begin(), collisions.end(), [](const shared_ptr<Object>& value1 , const shared_ptr<Object>& value2) 
		{
		auto temp1 = dynamic_pointer_cast<Tile>(value1);
		auto temp2 = dynamic_pointer_cast<Tile>(value2);

		if (temp1->GetTileType() > temp2->GetTileType())
			return true;
		
		return false;
		});	

	for (auto& object : collisions)
	{
		auto tile = dynamic_pointer_cast<Tile>(object);
		TileCollison(tile);
	}
	_velocity = (_texture->GetTransform()->GetPos() - _beforeMove) / (float)DELTA_TIME;

	if (_texture->Left() < MAP_MANAGER->GetCurMap()->GetLeftBottom().x)
		_texture->SetLeft(MAP_MANAGER->GetCurMap()->GetLeftBottom().x);
	else if (_texture->Right() > MAP_MANAGER->GetCurMap()->GetRightTop().x)
		_texture->SetRight(MAP_MANAGER->GetCurMap()->GetRightTop().x);
	else if (_texture->Top() > MAP_MANAGER->GetCurMap()->GetRightTop().y)
		_texture->SetTop(MAP_MANAGER->GetCurMap()->GetRightTop().y);
	else if (_texture->Bottom() < MAP_MANAGER->GetCurMap()->GetLeftBottom().y)
		Death();

	_beforeMove = _texture->GetTransform()->GetPos();
	_movement = { 0,0 };
}

void Creature::Death()
{
	_isActive = false;

	shared_ptr<Effect> deathEffect = MAKE_CREATURE_EFFECT(Map::Level::PUBLIC, 0);
	deathEffect->GetObjectTexture()->GetTransform()->GetPos() = _texture->GetTransform()->GetPos();

	GAME->AddEffect(deathEffect);
}

void Creature::Attack()
{
	if (_weaponSlot[_curWeaponSlot] != nullptr)
		_weaponSlot[_curWeaponSlot]->Attack();

	_anim->ChangeAnimation(State::ATTACK);
}

void Creature::MoveLeft()
{
	_movement.x -= _speed;
}

void Creature::MoveRight()
{
	_movement.x += _speed;
}

void Creature::Jump()
{
	if (_isFalling == false)
		_jumpPower = _jumpPowerMax;
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
	default:
		break;
	}
}	

void Creature::TileBlockCollision(shared_ptr<Tile> tile)
{
	float allowHeight = _speed * DELTA_TIME * 2;
		
	if (_onStair && _beforeMove.y - (_texture->GetHalfSize().y * _texture->GetTransform()->GetScale().y) + allowHeight && _jumpPower <= 0)
	{
		_texture->SetBottom(tile->GetCollider()->Top());
		_jumpPower = 0.0f;
	}
	else if (_onStair == false && _velocity.y >= 0 && _beforeMove.y - (_texture->GetHalfSize().y * _texture->GetTransform()->GetScale().y) >= tile->GetCollider()->Top())
	{
		_texture->SetBottom(tile->GetCollider()->Top());
		_jumpPower = 0.0f;
	}
	else if (_beforeMove.x + (_texture->GetHalfSize().x * _texture->GetTransform()->GetScale().x) <= tile->GetCollider()->Left())
	{
		_texture->SetRight(tile->GetCollider()->Left());
	}
	else if (_beforeMove.x - (_texture->GetHalfSize().x * _texture->GetTransform()->GetScale().x) >= tile->GetCollider()->Right())
	{
		_texture->SetLeft(tile->GetCollider()->Right());
	}
	else if (_onStair == false && _velocity.y < 0 && _beforeMove.y - (_texture->GetHalfSize().y * _texture->GetTransform()->GetScale().y) >= tile->GetCollider()->Top())
	{
		_texture->SetBottom(tile->GetCollider()->Top());
		_jumpPower = 0.0f;
	}
	else if (_beforeMove.y + (_texture->GetHalfSize().y * _texture->GetTransform()->GetScale().y) <= tile->GetCollider()->Bottom())
	{
		_texture->SetTop(tile->GetCollider()->Bottom());
		_jumpPower = 0.0f;
	}
}

void Creature::TileFloorCollision(shared_ptr<Tile> tile)
{
	if (_passFloor == false)
	{
		if (_beforeMove.y - (_texture->GetHalfSize().y * _texture->GetTransform()->GetScale().y) >= tile->GetCollider()->Top())
		{
			_texture->SetBottom(tile->GetCollider()->Top());
			_jumpPower = 0.0f;
			_passFloor = true;
		}
	}
}

void Creature::TileLeftStairCollision(shared_ptr<Tile> tile)
{	
	_onStair = true;

	if (_texture->GetTransform()->GetPos().x >= tile->GetObjectTexture()->Left() &&
		_texture->GetTransform()->GetPos().x <= tile->GetObjectTexture()->Right())
	{
		float x =  this->GetPos().x - tile->GetCollider()->Right();
		float y = -x + tile->GetCollider()->Bottom();
		if (_texture->Bottom() <= y)
		{
			_texture->SetBottom(y);
			_passTile = true;
			_jumpPower = 0.0f;
		}
	}
}

void Creature::TileRightStairCollision(shared_ptr<Tile> tile)
{
	_onStair = true;

	if (_texture->GetTransform()->GetPos().x >= tile->GetObjectTexture()->Left() &&
		_texture->GetTransform()->GetPos().x <= tile->GetObjectTexture()->Right())
	{
		float x = this->GetPos().x - tile->GetCollider()->Left();
		float y = x + tile->GetCollider()->Bottom();
		if (_texture->Bottom() <= y)
		{
			_texture->SetBottom(y);
			_passTile = true;
			_jumpPower = 0.0f;
		}
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
