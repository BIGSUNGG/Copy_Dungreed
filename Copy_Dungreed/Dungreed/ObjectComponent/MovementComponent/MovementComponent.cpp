#include "framework.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(Object* object)
	: ObjectComponent(object)
{
}

void MovementComponent::Update()
{
	_onStair = false;
	_isFalling = false;

	if (GAME->GetPlaying())
	{
		_jumpPower -= (_gravityPower * _gravityRatio) * DELTA_TIME;

		_movement.y += _jumpPower;

		if (_movementEvent != nullptr)
			_movementEvent();

		if (GAME->GetPlaying())
		{
			_object->GetObjectTexture()->GetTransform()->GetPos() += (_movement * DELTA_TIME);
			_object->GetObjectTexture()->Update();

			CollisionEvent();

			_velocity = (_object->GetObjectTexture()->GetTransform()->GetPos() - _beforeMove) / (float)DELTA_TIME;

			_beforeMove = _object->GetObjectTexture()->GetTransform()->GetPos();
			_movement = { 0,0 };

			if (_velocity.y != 0.f)
				_isFalling = true;
		}

		_passFloor = false;
		_passTile = false;
	}
}

void MovementComponent::Jump()
{
	_jumpPower = _jumpPowerMax;
}

void MovementComponent::SetBeforeMove(const Vector2& vec)
{
	_beforeMove = vec;
	_velocity = { 0,0 };
}

void MovementComponent::CollisionEvent()
{
	if (!_collision) return;

	vector<shared_ptr<Object>> collisions = GAME->GetCollisions(_object->GetCollider(), Object::Object_Type::TILE);
	sort(collisions.begin(), collisions.end(), [](const shared_ptr<Object>& value1, const shared_ptr<Object>& value2)
		{
			auto temp1 = dynamic_pointer_cast<Tile>(value1);
			auto temp2 = dynamic_pointer_cast<Tile>(value2);

			if (temp1->GetTileType() > temp2->GetTileType())
				return true;

			return false;
		});

	bool successCollision = false;

	for (auto& object : collisions)
	{
		auto tile = dynamic_pointer_cast<Tile>(object);
		bool success = TileCollison(tile);
		if (!successCollision || success)
		{
			if (_collisionEvent != nullptr)
				_collisionEvent();
		}
	}
}

bool MovementComponent::TileCollison(shared_ptr<Tile> tile)
{
	if (_passTile)
		return false;

	switch (tile->GetTileType())
	{
	case Tile::BLOCK:
		return TileBlockCollision(tile);
		break;
	case Tile::FLOOR:
		return TileFloorCollision(tile);
		break;
	case Tile::LEFT_STAIR:
		return TileLeftStairCollision(tile);
		break;
	case Tile::RIGHT_STAIR:
		return TileRightStairCollision(tile);
		break;
	default:
		return false;
		break;
	}
}

bool MovementComponent::TileBlockCollision(shared_ptr<Tile> tile)
{
	const float movedTop = _beforeMove.y + 
		(_object->GetCollider()->GetHalfSize().y * _object->GetCollider()->GetTransform()->GetScale().y);
	const float movedBottom = _beforeMove.y - 
		(_object->GetCollider()->GetHalfSize().y * _object->GetCollider()->GetTransform()->GetScale().y);
	const float movedRight = _beforeMove.x + 
		(_object->GetCollider()->GetHalfSize().x * _object->GetCollider()->GetTransform()->GetScale().x);
	const float movedLeft = _beforeMove.x - 
		(_object->GetCollider()->GetHalfSize().x * _object->GetCollider()->GetTransform()->GetScale().x);

	if (movedLeft != tile->GetCollider()->Right() && movedRight != tile->GetCollider()->Left())
	{
		if (_velocity.y <= 0 && movedBottom >= tile->GetCollider()->Top())
		{
			_object->GetObjectTexture()->SetBottom(tile->GetCollider()->Top() - 
				(_object->GetObjectTexture()->GetHalfSize().y - _object->GetCollider()->GetHalfSize().y));

			_jumpPower = 0.0f;
			return true;
		}
		if (movedTop <= tile->GetCollider()->Bottom())
		{
			_object->GetObjectTexture()->SetTop(tile->GetCollider()->Bottom() + 
				(_object->GetObjectTexture()->GetHalfSize().y - _object->GetCollider()->GetHalfSize().y));

			_jumpPower = 0.0f;
			return true;
		}
	}
	if (_velocity.x >= 0 && movedRight <= tile->GetCollider()->Left())
	{
		_object->GetObjectTexture()->SetRight(tile->GetCollider()->Left() + 
			(_object->GetObjectTexture()->GetHalfSize().x - _object->GetCollider()->GetHalfSize().x));
		return true;
	}
	if (_velocity.x <= 0 && movedLeft >= tile->GetCollider()->Right())
	{
		_object->GetObjectTexture()->SetLeft(tile->GetCollider()->Right() - 
			(_object->GetObjectTexture()->GetHalfSize().x - _object->GetCollider()->GetHalfSize().x));
		return true;
	}
	if (_onStair)
	{
		_object->GetObjectTexture()->SetBottom(tile->GetCollider()->Top() - 
			(_object->GetObjectTexture()->GetHalfSize().y - _object->GetCollider()->GetHalfSize().y));
		_jumpPower = 0.0f;
		return true;
	}

	_object->GetObjectTexture()->SetBottom(tile->GetCollider()->Top() - 
		(_object->GetObjectTexture()->GetHalfSize().y - _object->GetCollider()->GetHalfSize().y));
	_jumpPower = 0.0f;
	return true;
}

bool MovementComponent::TileFloorCollision(shared_ptr<Tile> tile)
{
	if (_passFloor)
		return false;

	const float movedBottom = _beforeMove.y - 
		(_object->GetCollider()->GetHalfSize().y * _object->GetCollider()->GetTransform()->GetScale().y);

	if (movedBottom >= tile->GetCollider()->Top())
	{
		_object->GetObjectTexture()->SetBottom(tile->GetCollider()->Top() - 
			(_object->GetObjectTexture()->GetHalfSize().y - _object->GetCollider()->GetHalfSize().y));
		_jumpPower = 0.0f;
		_passFloor = true;
		return true;
	}

	return false;
}

bool MovementComponent::TileLeftStairCollision(shared_ptr<Tile> tile)
{
	_onStair = true;

	if (_object->GetCollider()->GetTransform()->GetWorldPos().x >= tile->GetObjectTexture()->Left() &&
		_object->GetCollider()->GetTransform()->GetWorldPos().x <= tile->GetObjectTexture()->Right())
	{
		float x = _object->GetPos().x - tile->GetCollider()->Right();
		float y = -x + tile->GetCollider()->Bottom();
		if (_object->GetCollider()->Bottom() <= y)
		{
			_object->GetObjectTexture()->SetBottom(y - 
				(_object->GetObjectTexture()->GetHalfSize().y - _object->GetCollider()->GetHalfSize().y));
			_passTile = true;
			_jumpPower = 0.0f;
			return true;
		}
	}

	return false;
}

bool MovementComponent::TileRightStairCollision(shared_ptr<Tile> tile)
{
	_onStair = true;

	if (_object->GetCollider()->GetTransform()->GetWorldPos().x >= tile->GetObjectTexture()->Left() &&
		_object->GetCollider()->GetTransform()->GetWorldPos().x <= tile->GetObjectTexture()->Right())
	{
		float x = _object->GetCollider()->GetWorldPos().x - tile->GetCollider()->Left();
		float y = x + tile->GetCollider()->Bottom();
		if (_object->GetCollider()->Bottom() <= y)
		{
			_object->GetObjectTexture()->SetBottom(y - 
				(_object->GetObjectTexture()->GetHalfSize().y - _object->GetCollider()->GetHalfSize().y));
			_passTile = true;
			_jumpPower = 0.0f;
			return true;
		}
	}

	return false;
}