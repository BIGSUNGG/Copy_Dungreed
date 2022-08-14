#include "framework.h"
#include "Creature.h"

Creature::Creature(int level, int num)
	: Object(level, num)
{
	_objectType = Object::Object_Type::CREATURE;
}

void Creature::Update()
{
	_jumpPower -= _gravity * DELTA_TIME;
	_movement.y += _jumpPower;

	MoveCharacter(_movement);

	_passFloor = false;

	Object::Update();
}

void Creature::ImGuiRender()
{
	Object::ImGuiRender();
}

void Creature::MoveCharacter(Vector2 pos)
{
	_movement = { 0,0 };

	_texture->GetTransform()->GetPos() += (pos * DELTA_TIME);
	
	_texture->Update();
	_collider->Update();

	vector<shared_ptr<Object>> collisions = GAME->GetCollisions(_collider, Object::Object_Type::TILE);

	for (auto& object : collisions)
	{
		CollisionEvent(object);
	}

	_velocity = (_texture->GetTransform()->GetPos() - _beforeMove) / (float)DELTA_TIME;

	_beforeMove = _texture->GetTransform()->GetPos();
	Object::Update();
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
		shared_ptr<Tile> temp = dynamic_pointer_cast<Tile>(object);
		switch (temp->GetTileType())
		{
		case Tile::BLOCK:
			if (_passFloor == false)
			{
				if (object->GetTexture()->Top() <= _beforeMove.y - (_texture->GetHalfSize().y * _texture->GetTransform()->GetScale().y) && _velocity.y <= 0)
				{
					_texture->SetBottom(object->GetTexture()->Top());
					_jumpPower = 0.0f;
					_passFloor = true;
				}
			}
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
		break;
	case Object::CREATURE:
		break;
	case Object::EFFECT:
		break;
	default:
		break;
	}
}
