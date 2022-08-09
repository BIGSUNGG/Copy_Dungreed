#include "framework.h"
#include "Creature.h"

Creature::Creature(int level, int num)
	: Object(level, num)
{
	_objectType = Object::Object_Type::CREATURE;
}

void Creature::Update()
{
	_onBlock = false;

	_movementPos = _texture->GetTransform()->GetPos() - _movedPos;
	_movedPos = _texture->GetTransform()->GetPos();

	Object::Update();
}

void Creature::MoveCharacter(Vector2 pos)
{
	_texture->GetTransform()->GetPos() += pos * DELTA_TIME;
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
			if (_onBlock == false && _isPass == false)
			{
				if (object->GetTexture()->Top() <= _movedPos.y - (_texture->Top() - _texture->GetTransform()->GetPos().y) && _movementPos.y <= 0)
				{
					_texture->GetTransform()->GetPos().y = object->GetTexture()->Top() + (_texture->Top() - _texture->GetTransform()->GetPos().y);
					_onBlock = true;
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
