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
	_texture->GetTransform()->GetPos().y += _jumpPower * DELTA_TIME;

	_texture->Update();
	_collider->Update();
	vector<shared_ptr<Object>> collisions = GAME->GetCollisions(_collider, Object::Object_Type::TILE);
	if (_isPass == false)
	{
		if (collisions.size() > 0)
		{
			if (collisions.front()->GetTexture()->Top() <= _movedPos.y - (_texture->Top() - _texture->GetTransform()->GetPos().y) && _movementPos.y <= 0)
			{
				_texture->GetTransform()->GetPos().y = collisions.front()->GetTexture()->Top() + (_texture->Top() - _texture->GetTransform()->GetPos().y);
			}
		}
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
		{
			_isPass = true;
		}
	}
	else if (KEY_UP('S'))
	{
		_isPass = false;
	}
	if (KEY_PRESS('A'))
	{
		_texture->GetTransform()->GetPos().x -= _speed * DELTA_TIME;
	}
	if (KEY_PRESS('D'))
	{
		_texture->GetTransform()->GetPos().x += _speed * DELTA_TIME;
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
