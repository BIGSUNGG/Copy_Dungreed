#include "framework.h"
#include "Player.h"

Player::Player(int level, int num)
	: Creature(level, num)
{
	_creatureType = PLAYER;
}

void Player::Update()
{
	if (_velocity.x != 0)
	{
		_anim->ChangeAnimation(State::MOVE);
		if (_isFalling == false)
		{
			if (_velocity.x > 0)
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
	if (_velocity.y != 0)
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
	_movement.y += _jumpPower;
	
	Creature::Update();
}

void Player::PostRender()
{
	ImGui::Text("%f , %f", _velocity.x, _velocity.y);

	Creature::PostRender();
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
			_passFloor = true;
		else
			_passFloor = false;
	}
	else if (KEY_UP('S'))
	{
		_passFloor = false;
	}
	if (KEY_PRESS('A'))
	{
		_movement.x -= _speed;
	}
	if (KEY_PRESS('D'))
	{
		_movement.x += _speed;
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
