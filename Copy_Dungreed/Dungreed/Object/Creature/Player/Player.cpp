#include "framework.h"
#include "Player.h"

Player::Player(int level, int num)
	: Creature(level, num)
{
	_dashMovement = make_shared<DashMovementComponent>(this);
	_dashMovement->SetDashMovementEvent(bind(&Player::DashMovement, this));
	_dashMovement->SetDashEndEvent([&]() {
		_movement->SetGravityRatio(1.f);
		_movement->SetIsFalling(true); 
		});
	_dashMovement->SetDashSlowDownEvent([&]() {_movement->SetGravityRatio(0.4f); });

	_damagedRunTimeMax = 0.2f;

	_creatureType = PLAYER;
	_weaponSlot.resize(2);
	_accessorySlot.resize(4);
	_itemSlot.resize(15);

	_status.SetMaxHp(80);
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
	_dashInfo.Update();
	_dustRunTime += DELTA_TIME;

	if (_weaponSlot[_curWeaponSlot] != nullptr)
		_weaponSlot[_curWeaponSlot]->SetShowTo(_weaponDirection);

	_dashMovement->Update();
	Creature::Update();
	CheckEctEvent();
}

float Player::TakeDamage(float baseDamage, shared_ptr<Creature> attacker)
{
	if (_buffer->_data.selected == 2)
		return false;

	float damage = Creature::TakeDamage(baseDamage, attacker);

	if (_status._hp > 0)
	{
		_buffer->_data.selected = 2;
		_buffer->_data.value4 = 0.5f;
	}

	return damage;
}

float Player::GiveDamage(float baseDamage, shared_ptr<Creature> target)
{
	float damage = Creature::GiveDamage(baseDamage, target);

	if (damage > 0)
	{
		shared_ptr<Effect_Number> effect = make_shared<Effect_Number>();
		effect->SetNumber(damage);
		effect->SetPos(target->GetPos());

		GAME->AddEffect(effect);
	}

	return damage;
}

void Player::DustEffect()
{
	if (_dashMovement->GetCurSpeed() > 0)
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

void Player::StopMove()
{
	_dashMovement->GetCurSpeed() = 0.f;
	_movement->GetMovement() = {0,0};
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

	if(_weaponSlot[_curWeaponSlot] != nullptr)
		_weaponDirection = (MOUSE_WORLD_POS - (_texture->GetTransform()->GetPos() + _weaponSlot[_curWeaponSlot]->GetOffset())).Angle();
}

void Player::SetStatic(bool sta)
{
	_movement->SetStatic(sta);
	_movement->GetMovement() = {0.f,0.f};
	_dashMovement->SetStatic(sta);
	_dashMovement->GetCurSpeed() = 0.f;
}

void Player::MovementEvent()
{
	if (_movement->GetVelocity().x != 0)
	{
		_anim->ChangeAnimation(Creature_State::RUN);
		if (_movement->IsFalling() == false)
		{
			StepSound();
			DustEffect();
		}
	}
	else
	{
		_anim->ChangeAnimation(Creature_State::IDLE);
	}

	if ((_movement->GetVelocity().y != 0 || _dashMovement->GetCurSpeed() > 0.0f) && _movement->IsOnStair() == false)
	{
		_anim->ChangeAnimation(Creature_State::JUMP);
	}
	else
	{
		if (_movement->IsFalling() == true)
			DustEffect();

		_doubleJumped = false;
	}
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
	if (_dashInfo._dashCount > 0)
	{
		SOUND->Play("ui-sound-13-dash");
		_movement->SetGravityRatio(0.2f);
		_movement->SetJumpPower(0.f);
		_dashInfo.Reset();
		Vector2 direction = (MOUSE_WORLD_POS - _texture->GetTransform()->GetPos());
		direction.Normalize();
		_dashMovement->SetDirection(direction);
		_dashMovement->Dash();
	}
}

void Player::CheckEctEvent()
{
	for (auto& object : GAME->GetObjects()[Object::ECT])
	{
		if(object == nullptr)
			continue;

		auto ect = dynamic_pointer_cast<Ect>(object);
		switch (ect->GetEctType())
		{
		case Ect::UNKNOWN:
			break;
		case Ect::ITEM:
			break;
		case Ect::BULLET:
			break;
		case Ect::CHEST:
			break;
		case Ect::DROP_ITEM:
		{
			if (_collider->IsCollision(object->GetCollider()))
			{
				auto dropItem = dynamic_pointer_cast<DropItem>(ect);
				dropItem->AddItemToCreature(this);
			}
		}
			break;
		case Ect::DROP_COIN:
		{
			auto dropGold = dynamic_pointer_cast<DropGold>(ect);
			if (_collider->IsCollision(object->GetCollider()))
				dropGold->AddCoinToIventory();
			else
			{
				Vector2 distance = this->GetPos() - ect->GetPos();
				if (distance.Length() <= _goldMagnetLength)
					dropGold->SetFollowCreature(this);
			}
		}
			break;
		default:
			break;
		}
	}
}

void Player::DashMovement()
{
	_movement->SetPassFloor(true);

	if (_dashInfo._trailCount < _dashInfo._trailCountMax)
	{
		_dashInfo._trailTime += DELTA_TIME;
		if (_dashInfo._trailTime > _dashInfo._trailDelay)
		{
			++_dashInfo._trailCount;
			_dashInfo._trailTime = 0.0f;
			auto trail = make_shared<Effect_Trail>();
			auto quad = make_shared<Quad>(_texture->GetImageFile());
			trail->SetTexture(quad);
			trail->GetPos() = this->GetPos();
			trail->SetAlpha(0.75f);
			trail->SetFadeRatio(3.f);
			if (_reversed)
				trail->ReverseTexture();
			trail->SetRenderOrder(3.6f);
			GAME->AddEffect(trail);
		}
	}
}

void Player::Jump()
{
	if (_dashMovement->GetCurSpeed() > 0)
		return;

	if (_movement->IsFalling() == false)
	{
		SOUND->Play("Jumping");
		_movement->Jump();
		DustEffect();
	}
	else if (_doubleJumped == false)
	{
		SOUND->Play("Jumping");
		_movement->Jump();
		_doubleJumped = true;
		DoubleJumpEffect();
	}
}

void Player::Attack()
{
	if (_dashMovement->GetCurSpeed() > 0)
		return;
	
	Creature::Attack();
}

void Player::MoveLeft()
{
	if (_dashMovement->GetCurSpeed() > 0)
		return;

	Creature::MoveLeft();
}

void Player::MoveRight()
{
	if (_dashMovement->GetCurSpeed() > 0)
		return;

	Creature::MoveRight();
}

void Player::Interaction()
{
	for (auto& object : GAME->GetObjects()[Object::ECT])
	{
		if (object == nullptr) continue;

		auto ect = dynamic_pointer_cast<Ect>(object);
		if(!ect->GetInteraction()) continue;

		float length = (GetPos() - ect->GetPos()).Length();
		if (length <= INVENTORY->GetInteractionDistance())
		{
			ect->Interaction();
			return;
		}
	}
}
