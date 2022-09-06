#include "framework.h"
#include "Player.h"

Player::Player(int level, int num)
	: Creature(level, num)
{
	_creatureType = PLAYER;
	_weaponSlot.resize(2);
}

void Player::Update()
{
	_dustRunTime += DELTA_TIME;

	MovementEvent();

	MouseEvent();

	InputEvent();
	
	Creature::Update();
}

void Player::DustEffect()
{
	if (_dashCurSpeed > 0)
		return;

	if (_dustRunTime >= _dustDelay)
	{
		_dustRunTime = 0.0f;
		shared_ptr<Effect> dust = MAKE_PLAYER_EFFECT(0);
		dust->GetTexture()->GetTransform()->GetPos().x = _texture->GetTransform()->GetPos().x;
		dust->GetTexture()->SetBottom(_texture->Bottom());

		if (_reversed)
			dust->GetTexture()->ReverseToX();

		GAME->AddEffect(dust);
	}
}

void Player::DoubleJumpEffect()
{
	shared_ptr<Effect> doubleJump = MAKE_PLAYER_EFFECT(1);
	doubleJump->GetTexture()->GetTransform()->GetPos().x = _texture->GetTransform()->GetPos().x;
	doubleJump->GetTexture()->SetBottom(_texture->Bottom());

	if (_reversed)
		doubleJump->GetTexture()->ReverseToX();

	GAME->AddEffect(doubleJump);
}

void Player::MouseEvent()
{
	if (_texture->GetTransform()->GetPos().x >= MOUSE_WORLD_POS.x)
	{
		if (_reversed == false)
		{
			ReverseTexture();
		}
	}
	else if (_reversed == true)
	{
		ReverseTexture();
	}

	_weaponSlot[_curWeaponSlot]->SetShowTo((MOUSE_WORLD_POS - _texture->GetTransform()->GetPos()).Angle());
}

void Player::MovementEvent()
{
	if (_velocity.x != 0)
	{
		_anim->ChangeAnimation(State::RUN);
		if (_isFalling == false)
		{
			DustEffect();
		}
	}
	else
	{
		_anim->ChangeAnimation(State::IDLE);
	}

	if (_velocity.y != 0 || _dashCurSpeed > 0.0f)
	{
		_anim->ChangeAnimation(State::JUMP);
		_isFalling = true;
	}
	else
	{
		if (_isFalling == true)
			DustEffect();

		_doubleJumped = false;
		_isFalling = false;
	}

	if (_dashCurSpeed > 0.0f)
	{
		_movement += (_dashDirection * _dashCurSpeed);
		_isFalling = true;

		if (_dashSlow)
		{
			_dashCurSpeed -= _dashSlowSpeed * DELTA_TIME;
		}
		else
		{
			_dashRunTime += DELTA_TIME;

			if (_dashRunTime >= _dashMaxTime)
				_dashSlow = true;
		}
	}
	else
		_gravity = true;
}

void Player::InputEvent()
{
	if (_dashCurSpeed <= 0)
	{
		if (KEY_DOWN('W'))
			Jump();

		if (KEY_PRESS('S'))
		{
			if (KEY_DOWN(VK_SPACE))
				_passFloor = true;
			else
				_passFloor = false;
		}
		else if (KEY_UP('S'))
			_passFloor = false;

		if (KEY_PRESS('A'))
			_movement.x -= _speed;
		if (KEY_PRESS('D'))
			_movement.x += _speed;
	}
	if (KEY_DOWN(VK_LBUTTON))
		Attack();
	if (KEY_DOWN(VK_RBUTTON))
		Dash();
	if (KEY_DOWN('1'))
		_curWeaponSlot = 0;
	if (KEY_DOWN('2'))
		_curWeaponSlot = 1;
}

void Player::Dash()
{
	_dashSlow = false;
	_gravity = false;
	_dashRunTime = 0.0f;
	_jumpPower = 0.0f;
	_dashCurSpeed = _dashSpeedMax;
	_dashDirection = (MOUSE_WORLD_POS - _texture->GetTransform()->GetPos());
	_dashDirection.Normalize();
}

void Player::Jump()
{
	if (_isFalling == false)
	{
		_jumpPower = _jumpPowerMax;
		DustEffect();
	}
	else if (_doubleJumped == false)
	{
		_jumpPower = _jumpPowerMax;
		_doubleJumped = true;
		DoubleJumpEffect();
	}
}

