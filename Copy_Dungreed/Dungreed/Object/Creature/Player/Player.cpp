#include "framework.h"
#include "Player.h"

Player::Player(int level, int num)
	: Creature(level, num)
{
	_damagedRunTimeMax = 0.2f;

	_creatureType = PLAYER;
	_weaponSlot.resize(2);
	_accessorySlot.resize(4);
	_itemSlot.resize(15);

	_status.SetMaxHp(80);
	_status._atk = 25;
	_status._speed = 450.0f;

	INVENTORY->SetWeaponSlot(&_weaponSlot);
	INVENTORY->SetCurWeaponSlot(&_curWeaponSlot);
	INVENTORY->SetAccessorySlot(&_accessorySlot);
	INVENTORY->SetItemSlot(&_itemSlot);

	SOUND->Add("ui-sound-13-dash", "Resource/Sound/Creature/Player/Dash/ui-sound-13-dash.wav");
	SOUND->Add("Jumping", "Resource/Sound/Creature/Player/Jump/Jumping.wav");

	SOUND->Add("step_lth1", "Resource/Sound/Creature/Player/Move/step_lth1.wav");
	SOUND->Add("step_lth2", "Resource/Sound/Creature/Player/Move/step_lth2.wav");
	SOUND->Add("step_lth33", "Resource/Sound/Creature/Player/Move/step_lth33.wav");
	SOUND->Add("step_lth4", "Resource/Sound/Creature/Player/Move/step_lth4.wav");
}

void Player::Update()
{
	_dash.Update();
	_dustRunTime += DELTA_TIME;

	if (_weaponSlot[_curWeaponSlot] != nullptr)
		_weaponSlot[_curWeaponSlot]->SetShowTo(_weaponDirection);

	Creature::Update();
}

bool Player::GetDamage(shared_ptr<Creature> enemy, shared_ptr<Item> weapon)
{
	if (_buffer->_data.selected == 2)
		return false;

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

	_weaponDirection = (MOUSE_WORLD_POS - (_texture->GetTransform()->GetPos() + _weaponSlot[_curWeaponSlot]->GetOffset())).Angle();
}

void Player::MovementEvent()
{
	if (_velocity.x != 0)
	{
		_anim->ChangeAnimation(Creature_State::RUN);
		if (_isFalling == false)
		{
			StepSound();
			DustEffect();
		}
	}
	else
	{
		_anim->ChangeAnimation(Creature_State::IDLE);
	}

	if ((_velocity.y != 0 || _dash._dashCurSpeed > 0.0f) && _onStair == false)
	{

		_anim->ChangeAnimation(Creature_State::JUMP);
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

void Player::StepSound()
{
	if (SOUND->IsPlaySound(_curStepSound) == false)
	{
		++_stepSound;

		if (_stepSound > 3)
			_stepSound = 0;

		switch (_stepSound)
		{
		case 0:
			_curStepSound = "step_lth1";
			break;
		case 1:
			_curStepSound = "step_lth2";
			break;
		case 2:
			_curStepSound = "step_lth33";
			break;
		case 3:
			_curStepSound = "step_lth4";
			break;
		default:
			break;
		}

		SOUND->Play(_curStepSound);
	}
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
		_passFloor = true;
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
				trail->SetAlpha(0.5f);
				trail->SetFadeRatio(1.5f);
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
	{
		_gravityRatio = 1.0f;
	}
}

void Player::Jump()
{
	if (_dash._dashCurSpeed > 0)
		return;

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

void Player::Attack()
{
	if (_dash._dashCurSpeed > 0)
		return;
	
	Creature::Attack();
}

void Player::MoveLeft()
{
	if (_dash._dashCurSpeed > 0)
		return;

	Creature::MoveLeft();
}

void Player::MoveRight()
{
	if (_dash._dashCurSpeed > 0)
		return;

	Creature::MoveRight();
}
