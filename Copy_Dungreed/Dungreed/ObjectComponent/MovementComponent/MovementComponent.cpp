#include "framework.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(Object* object)
	: ObjectComponent(object)
{
}

void MovementComponent::Update()
{
	if (_static)
		return;

	_onStair = false;
	_isFalling = false;

	if (GAME->GetPlaying())
	{
		_curJumpPower -= (_gravityPower * _gravityRatio) * DELTA_TIME;

		_moveDir.y += _curJumpPower;

		_owner->GetObjectTexture()->GetTransform()->GetPos() += (_moveDir * DELTA_TIME);
		_owner->GetObjectTexture()->Update();

		CollisionEvent();

		_curVelocity = (_owner->GetObjectTexture()->GetTransform()->GetPos() - _beforeMovePos) / (float)DELTA_TIME;

		_beforeMovePos = _owner->GetObjectTexture()->GetTransform()->GetPos();
		_moveDir = { 0,0 };

		if (_curVelocity.y != 0.f)
			_isFalling = true;

		_passFloor = false;
		_passTile = false;

		if (_movementEvent != nullptr)
			_movementEvent();
	}
}

void MovementComponent::Jump()
{
	_curJumpPower = _maxJumpPower;
}

void MovementComponent::SetBeforeMove(const Vector2& vec)
{
	_beforeMovePos = vec;
	_curVelocity = { 0,0 };
}

void MovementComponent::CollisionEvent()
{
	if (!_collision) return;

	vector<shared_ptr<Object>> collisions = GAME->GetCollisions(_owner->GetCollider(), Object::Object_Type::TILE);
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
	const float movedTop = _beforeMovePos.y + 
		(_owner->GetCollider()->GetHalfSize().y * _owner->GetCollider()->GetTransform()->GetScale().y);
	const float movedBottom = _beforeMovePos.y - 
		(_owner->GetCollider()->GetHalfSize().y * _owner->GetCollider()->GetTransform()->GetScale().y);
	const float movedRight = _beforeMovePos.x + 
		(_owner->GetCollider()->GetHalfSize().x * _owner->GetCollider()->GetTransform()->GetScale().x);
	const float movedLeft = _beforeMovePos.x - 
		(_owner->GetCollider()->GetHalfSize().x * _owner->GetCollider()->GetTransform()->GetScale().x);

	if (movedLeft != tile->GetCollider()->Right() && movedRight != tile->GetCollider()->Left())
	{
		if (_curVelocity.y <= 0 && movedBottom >= tile->GetCollider()->Top())
		{
			_owner->GetObjectTexture()->SetBottom(tile->GetCollider()->Top() - 
				(_owner->GetObjectTexture()->GetHalfSize().y - _owner->GetCollider()->GetHalfSize().y));

			_curJumpPower = 0.0f;
			return true;
		}
		if (movedTop <= tile->GetCollider()->Bottom())
		{
			_owner->GetObjectTexture()->SetTop(tile->GetCollider()->Bottom() + 
				(_owner->GetObjectTexture()->GetHalfSize().y - _owner->GetCollider()->GetHalfSize().y));

			_curJumpPower = 0.0f;
			return true;
		}
	}
	if (_curVelocity.x >= 0 && movedRight <= tile->GetCollider()->Left())
	{
		_owner->GetObjectTexture()->SetRight(tile->GetCollider()->Left() + 
			(_owner->GetObjectTexture()->GetHalfSize().x - _owner->GetCollider()->GetHalfSize().x));
		return true;
	}
	if (_curVelocity.x <= 0 && movedLeft >= tile->GetCollider()->Right())
	{
		_owner->GetObjectTexture()->SetLeft(tile->GetCollider()->Right() - 
			(_owner->GetObjectTexture()->GetHalfSize().x - _owner->GetCollider()->GetHalfSize().x));
		return true;
	}
	if (_onStair)
	{
		_owner->GetObjectTexture()->SetBottom(tile->GetCollider()->Top() - 
			(_owner->GetObjectTexture()->GetHalfSize().y - _owner->GetCollider()->GetHalfSize().y));
		_curJumpPower = 0.0f;
		return true;
	}

	_owner->GetObjectTexture()->SetBottom(tile->GetCollider()->Top() - 
		(_owner->GetObjectTexture()->GetHalfSize().y - _owner->GetCollider()->GetHalfSize().y));
	_curJumpPower = 0.0f;
	return true;
}

bool MovementComponent::TileFloorCollision(shared_ptr<Tile> tile)
{
	if (_passFloor)
		return false;

	const float movedBottom = _beforeMovePos.y - 
		(_owner->GetCollider()->GetHalfSize().y * _owner->GetCollider()->GetTransform()->GetScale().y);

	if (movedBottom >= tile->GetCollider()->Top())
	{
		_owner->GetObjectTexture()->SetBottom(tile->GetCollider()->Top() - 
			(_owner->GetObjectTexture()->GetHalfSize().y - _owner->GetCollider()->GetHalfSize().y));
		_curJumpPower = 0.0f;
		_passFloor = true;
		return true;
	}

	return false;
}

bool MovementComponent::TileLeftStairCollision(shared_ptr<Tile> tile)
{
	_onStair = true;

	if (_owner->GetCollider()->GetTransform()->GetWorldPos().x >= tile->GetObjectTexture()->Left() &&
		_owner->GetCollider()->GetTransform()->GetWorldPos().x <= tile->GetObjectTexture()->Right())
	{
		float x = _owner->GetPos().x - tile->GetCollider()->Right();
		float y = -x + tile->GetCollider()->Bottom();
		if (_owner->GetCollider()->Bottom() <= y)
		{
			_owner->GetObjectTexture()->SetBottom(y - 
				(_owner->GetObjectTexture()->GetHalfSize().y - _owner->GetCollider()->GetHalfSize().y));
			_passTile = true;
			_curJumpPower = 0.0f;
			return true;
		}
	}

	return false;
}

bool MovementComponent::TileRightStairCollision(shared_ptr<Tile> tile)
{
	_onStair = true;

	if (_owner->GetCollider()->GetTransform()->GetWorldPos().x >= tile->GetObjectTexture()->Left() &&
		_owner->GetCollider()->GetTransform()->GetWorldPos().x <= tile->GetObjectTexture()->Right())
	{
		float x = _owner->GetCollider()->GetWorldPos().x - tile->GetCollider()->Left();
		float y = x + tile->GetCollider()->Bottom();
		if (_owner->GetCollider()->Bottom() <= y)
		{
			_owner->GetObjectTexture()->SetBottom(y - 
				(_owner->GetObjectTexture()->GetHalfSize().y - _owner->GetCollider()->GetHalfSize().y));
			_passTile = true;
			_curJumpPower = 0.0f;
			return true;
		}
	}

	return false;
}