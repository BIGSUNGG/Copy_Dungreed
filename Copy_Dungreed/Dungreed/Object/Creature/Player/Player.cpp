#include "framework.h"
#include "Player.h"

Player::Player(int level, int num)
	: Creature(level, num)
{
	_creatureType = PLAYER;
}

void Player::Update()
{


	if (_movementPos.x != 0)
	{
		_anim->ChangeAnimation(State::MOVE);
		if (_isFalling == false)
		{
			if (_movementPos.x > 0)
			{
				if (_isReversed == true)
				{
					_texture->ReverseTexture();
					_isReversed = false;
				}
			}
			else if (_isReversed == false)
			{
				_texture->ReverseTexture();
				_isReversed = true;
			}
		}
	}
	else
	{
		_anim->ChangeAnimation(State::IDLE);
	}
	if (_movementPos.y != 0)
	{
		_anim->ChangeAnimation(State::JUMP);
		_isFalling = true;
	}
	else
	{
		_doubleJumped = false;
		_isFalling = false;
		_jumpPower = 0.0f;
	}

	InputEvent();

	_jumpPower -= _gravity * DELTA_TIME;

	MoveCharacter(Vector2(0.0f, _jumpPower));

	_texture->Update();
	_collider->Update();
	vector<shared_ptr<Object>> collisions = GAME->GetCollisions(_collider, Object::Object_Type::TILE);

	for (auto& object : collisions)
	{
		CollisionEvent(object);
	}

	Creature::Update();
}

void Player::InputEvent()
{
	if (KEY_DOWN('W'))
	{
		Jump();
	}
	if (KEY_PRESS('S'))
	{
		if (KEY_PRESS(VK_SPACE))
			_isPass = true;
		else
			_isPass = false;
	}
	else if (KEY_UP('S'))
	{
		_isPass = false;
	}
	if (KEY_PRESS('A'))
	{
		MoveCharacter(Vector2(-_speed, 0.0f));
	}
	if (KEY_PRESS('D'))
	{
		MoveCharacter(Vector2(_speed, 0.0f));
	}
}

void Player::Jump()
{
	if (_isFalling == false)
	{
		_jumpPower = _jumpPowerMax;
	}
	else if (_doubleJumped == false)
	{
		_jumpPower = _jumpPowerMax;
		_doubleJumped = true;
	}
}
