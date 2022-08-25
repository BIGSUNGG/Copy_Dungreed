#include "framework.h"
#include "Player.h"

Player::Player(int level, int num)
	: Creature(level, num)
{
	_creatureType = PLAYER;
}

void Player::Update()
{
	_dustRunTime += DELTA_TIME;

	MovementEvent();
	MouseEvent();

	InputEvent();

	if (_weapon != nullptr)
		_weapon->Update();

	Creature::Update();
}

void Player::Render()
{
	if (_weapon != nullptr)
		_weapon->Render();

	Creature::Render();
}

void Player::DustEffect()
{
	if (_dustRunTime >= _dustDelay)
	{
		_dustRunTime = 0.0f;
		shared_ptr<Effect> dust = MAKE_CREATURE_EFFECT(-1, 0);
		dust->GetTexture()->GetTransform()->GetPos().x = _texture->GetTransform()->GetPos().x;
		dust->GetTexture()->SetBottom(_texture->Bottom());

		if (_reversed)
			dust->GetTexture()->ReverseToX();

		GAME->AddEffect(dust);
	}
}

void Player::DoubleJumpEffect()
{
	shared_ptr<Effect> dust = MAKE_CREATURE_EFFECT(-1, 1);
	dust->GetTexture()->GetTransform()->GetPos().x = _texture->GetTransform()->GetPos().x;
	dust->GetTexture()->SetBottom(_texture->Bottom());

	if (_reversed)
		dust->GetTexture()->ReverseToX();

	GAME->AddEffect(dust);
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
}

void Player::MovementEvent()
{
	if (_velocity.x != 0)
	{
		_anim->ChangeAnimation(State::MOVE);
		if (_isFalling == false)
		{
			DustEffect();
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
		if (_isFalling == true)
			DustEffect();

		_doubleJumped = false;
		_isFalling = false;
	}
}

void Player::InputEvent()
{
	if (KEY_DOWN('W'))
	{
		Jump();
	}
	if (KEY_PRESS('S'))
	{
		if (KEY_DOWN(VK_SPACE))
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
	if (KEY_DOWN(VK_LBUTTON))
	{
		Attack();
	}
}

void Player::Attack()
{
	_weapon->Attack();
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

void Player::SetWeapon(shared_ptr<Item> weapon)
{
	_weapon = weapon;
	_weapon->SetOwner(shared_from_this());
}
