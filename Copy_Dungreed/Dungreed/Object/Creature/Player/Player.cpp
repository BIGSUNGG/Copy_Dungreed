#include "framework.h"
#include "Player.h"

Player::Player(int level, int num)
	: Creature(level, num)
{
	_damagedRunTimeMax = 0.2f;

	_creatureType = PLAYER;
	_weaponSlot.resize(2);

	_status.SetMaxHp(80);
	_status._atk = 25;

	INVENTORY->SetWeaponSlot(&_weaponSlot);
	INVENTORY->SetCurWeaponSlot(&_curWeaponSlot);

	SOUND->Add("ui-sound-13-dash", "Resource/Sound/Creature/Player/Dash/ui-sound-13-dash.wav");
	SOUND->Add("Jumping", "Resource/Sound/Creature/Player/Jump/Jumping.wav");
}

void Player::Update()
{
	_dash.Update();
	_dustRunTime += DELTA_TIME;

	MovementEvent();

	MouseEvent();

	InputEvent();
	
	Creature::Update();
}

bool Player::GetDamage(shared_ptr<Creature> enemy, shared_ptr<Item> weapon)
{
	const bool& damaged = Creature::GetDamage(enemy, weapon);

	if (_status._hp > 0)
	{
		_buffer->_data.selected = 2;
		_buffer->_data.value4 = 0.5f;
	}

	return damaged;
}

void Player::DustEffect()
{
	if (_dash._dashCurSpeed > 0)
		return;

	if (_dustRunTime >= _dustDelay)
	{
		_dustRunTime = 0.0f;
		shared_ptr<Effect> dust = MAKE_PLAYER_EFFECT(0);
		dust->GetObjectTexture()->GetTransform()->GetPos().x = _texture->GetTransform()->GetPos().x;
		dust->GetObjectTexture()->SetBottom(_texture->Bottom());

		if (_reversed)
			dust->GetObjectTexture()->ReverseToX();

		GAME->AddEffect(dust);
	}
}

void Player::DoubleJumpEffect()
{
	shared_ptr<Effect> doubleJump = MAKE_PLAYER_EFFECT(1);
	doubleJump->GetObjectTexture()->GetTransform()->GetPos().x = _texture->GetTransform()->GetPos().x;
	doubleJump->GetObjectTexture()->SetBottom(_texture->Bottom());

	if (_reversed)
		doubleJump->GetObjectTexture()->ReverseToX();

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

	if ((_velocity.y != 0 || _dash._dashCurSpeed > 0.0f) && _onStair == false)
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

	DashMovement();
}

void Player::InputEvent()
{
	if (_dash._dashCurSpeed <= 0)
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
			MoveLeft();
		if (KEY_PRESS('D'))
			MoveRight();
	}
	if (KEY_PRESS(VK_LBUTTON))
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
	if (_dash._dashCount > 0)
	{
		SOUND->Play("ui-sound-13-dash");
		_gravityRatio = 0.3f;
		_jumpPower = 0.0f;
		_dash.Reset();
		_dash._dashDirection = (MOUSE_WORLD_POS - _texture->GetTransform()->GetPos());
		_dash._dashDirection.Normalize();
	}
}

void Player::DashMovement()
{
	if (_dash._dashCurSpeed > 0.0f)
	{
		_movement += (_dash._dashDirection * _dash._dashCurSpeed);
		if (_dash._trailCount < _dash._trailCountMax)
		{
			_dash._trailTime += DELTA_TIME;
			if (_dash._trailTime > _dash._trailDelay)
			{
				++_dash._trailCount;
				_dash._trailTime = 0.0f;
				auto trail = make_shared<Effect_Trail>();
				auto quad = make_shared<Quad>(_texture->GetImageFile());
				trail->SetTexture(quad);
				trail->GetPos() = this->GetPos();
				if (_reversed)
					trail->ReverseTexture();
				GAME->AddEffect(trail);
			}
		}

		_isFalling = true;

		if (_dash._dashSlow)
		{
			_dash._dashCurSpeed -= _dash._dashSlowSpeed * DELTA_TIME;
		}
		else
		{
			_dash._dashRunTime += DELTA_TIME;

			if (_dash._dashRunTime >= _dash._dashRunTimeMax)
				_dash._dashSlow = true;
		}
	}
	else
		_gravityRatio = 1.0f;
}

void Player::Jump()
{
	if (_isFalling == false)
	{
		SOUND->Play("Jumping");
		_jumpPower = _jumpPowerMax;
		DustEffect();
	}
	else if (_doubleJumped == false)
	{
		SOUND->Play("Jumping");
		_jumpPower = _jumpPowerMax;
		_doubleJumped = true;
		DoubleJumpEffect();
	}
}

