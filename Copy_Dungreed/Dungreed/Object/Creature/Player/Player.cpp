#include "framework.h"
#include "Player.h"

Player::Player(int level, int num)
	: Creature(level, num)
{
	_creatureType = PLAYER;

	// DashMovement �ʱ�ȭ
	_dashMovement = make_shared<DashMovementComponent>(this);
	_dashMovement->SetDashMovementEvent(bind(&Player::DashMovement, this));
	_dashMovement->SetDashEndEvent([&]() {
		_movementComponent->SetGravityRatio(1.f);
		_movementComponent->SetIsFalling(true); 
		});
	_dashMovement->SetDashSlowDownEvent([&]() {_movementComponent->SetGravityRatio(0.4f); });
	_componentCollector->Add(_dashMovement);

	// DamagedDuration �ʱ�ȭ
	_damagedDuration = 0.2f;

	// ���� �ʱ�ȭ
	_inventory->SetWeaponSlotSize(2);
	_inventory->SetAccessorySlotSize(4);
	_inventory->SetItemSlotSize(15);

	// ĳ���� ���� �ʱ�ȭ
	_status.SetMaxHp(80);
	_status._speed = 450.0f;

	// ���� �߰�
	SOUND->Add("ui-sound-13-dash", "Resource/Sound/Creature/Player/Dash/ui-sound-13-dash.wav");
	SOUND->Add("Jumping", "Resource/Sound/Creature/Player/Jump/Jumping.wav");

	SOUND->Add("step_lth1", "Resource/Sound/Creature/Player/Move/step_lth1.wav");
	SOUND->Add("step_lth2", "Resource/Sound/Creature/Player/Move/step_lth2.wav");
	SOUND->Add("step_lth33", "Resource/Sound/Creature/Player/Move/step_lth33.wav");
	SOUND->Add("step_lth4", "Resource/Sound/Creature/Player/Move/step_lth4.wav");
}

void Player::Update()
{
	Creature::Update();

	_dustTime += DELTA_TIME;

	// ���Ⱑ �ٶ󺸴� ���� ����
	auto curWeapon = GetCurWeapon();
	if (curWeapon != nullptr)
		curWeapon->SetShowTo(_weaponDirection);

	_dashInfo.Update();

	CheckEtcEvent();
}

float Player::TakeDamage(float baseDamage, shared_ptr<Creature> attacker)
{
	// �������� �޾Ҵٸ� _damagedDuration ���� ����
	if (_damagedTime < _damagedDuration)
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

	// �������� �־��ٸ�
	if (damage > 0)
	{
		// ������ ����Ʈ �߰�
		Vector2 targetPos = target->GetPos();
		targetPos.x += MathUtility::RandomFloat(-75, 75);
		targetPos.y += MathUtility::RandomFloat(-50, 50);

		shared_ptr<Effect_Number> effect = make_shared<Effect_Number>();
		effect->SetNumber(damage);
		effect->SetPos(targetPos);

		GAME->AddEffect(effect);
	}

	return damage;
}

void Player::DustEffect()
{
	if (_dashMovement->GetCurSpeed() > 0)
		return;

	if (_dustTime >= _dustDelay)
	{
		_dustTime = 0.0f;
		shared_ptr<Effect> dust = MAKE_PLAYER_EFFECT(0);
		dust->GetObjectTexture()->GetTransform()->GetPos().x = _texture->GetTransform()->GetPos().x;
		dust->GetObjectTexture()->SetBottom(_texture->Bottom());

		if (_reverseTexture)
			dust->GetObjectTexture()->ReverseToX();

		GAME->AddEffect(dust);
	}
}

void Player::DoubleJumpEffect()
{
	shared_ptr<Effect> doubleJump = MAKE_PLAYER_EFFECT(1);
	doubleJump->GetObjectTexture()->GetTransform()->GetPos().x = _texture->GetTransform()->GetPos().x;
	doubleJump->GetObjectTexture()->SetBottom(_texture->Bottom());

	if (_reverseTexture)
		doubleJump->GetObjectTexture()->ReverseToX();

	GAME->AddEffect(doubleJump);
}

void Player::StopMove()
{
	_dashMovement->GetCurSpeed() = 0.f;
	_movementComponent->GetMoveDir() = {0,0};
}

void Player::MouseEvent()
{
	// ���콺 ��ġ�� ���ʿ� �ִٸ�
	if (_texture->GetTransform()->GetPos().x >= MOUSE_WORLD_POS.x)
	{
		// ĳ���� �ؽ��İ� ������ ������
		if (_reverseTexture == false)
		{
			ReverseTexture();
		}
	}
	else if (_reverseTexture == true)
	{
		// ĳ���� �ؽ��İ� �������� ������
		ReverseTexture();
	}


	// �÷��̾ Ŀ���� �ٶ󺸴� ��ġ ���ϱ�
	auto curWeapon = GetCurWeapon();
	if(curWeapon != nullptr)
		_weaponDirection = (MOUSE_WORLD_POS - _texture->GetTransform()->GetPos()).Angle();
}

void Player::SetStatic(bool sta)
{
	_movementComponent->SetStatic(sta);
	_movementComponent->GetMoveDir() = {0.f,0.f};
	_dashMovement->SetStatic(sta);
	_dashMovement->GetCurSpeed() = 0.f;
}

void Player::MovementEvent()
{
	if (_movementComponent->GetVelocity().x != 0) // �¿�� �̵��ϰ� �ִٸ�
	{
		_anim->ChangeAnimation(Creature_State::RUN);

		// ������ �ɾ�ٴѴٸ�
		if (_movementComponent->IsFalling() == false)
		{
			StepSound();
			DustEffect();
		}
	}
	else // ������ �ִٸ�
	{
		_anim->ChangeAnimation(Creature_State::IDLE);
	}

	// ��ܿ� �����ʰ� �� �Ʒ��� �̵� ���̶��
	if (_movementComponent->IsOnStair() == false && (_movementComponent->GetVelocity().y != 0 || _dashMovement->GetCurSpeed() > 0.0f))
	{
		_anim->ChangeAnimation(Creature_State::JUMP);
	}
	else // ���� �ִٸ�
	{
		if (_movementComponent->IsFalling() == true)
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
		// ��� �Ҹ� ����
		SOUND->Play("ui-sound-13-dash");

		// Movement ���� 
		_movementComponent->SetGravityRatio(0.2f);
		_movementComponent->SetJumpPower(0.f);

		// DashMovement ����
		_dashInfo.Reset();
		Vector2 direction = (MOUSE_WORLD_POS - _texture->GetTransform()->GetPos());
		direction.Normalize();
		_dashMovement->SetDirection(direction);
		_dashMovement->Dash();
	}
}

void Player::CheckEtcEvent()
{
	for (auto& object : GAME->GetObjects()[Object::ETC])
	{
		if(object == nullptr)
			continue;

		auto etc = dynamic_pointer_cast<Etc>(object);
		switch (etc->GetEtcType())
		{
		case Etc::UNKNOWN:
			break;
		case Etc::ITEM:
			break;
		case Etc::BULLET:
			break;
		case Etc::CHEST:
			break;
		case Etc::DROP_ITEM:
		{
			// �����۰� ��Ҵٸ�
			if (_collider->IsCollision(object->GetCollider()))
			{
				// ������ �ݱ�
				auto dropItem = dynamic_pointer_cast<DropItem>(etc);
				dropItem->AddItemToCreature(this);
			}
		}
			break;
		case Etc::DROP_COIN:
		{
			auto dropGold = dynamic_pointer_cast<DropGold>(etc);
			// ���� ��Ҵٸ�
			if (_collider->IsCollision(object->GetCollider()))
			{
				// ��� �߰�
				dropGold->AddGoldToIventory();
			}
			else
			{
				// ��尡 ��带 ������� ������ �ִٸ� ��� �������
				Vector2 distance = this->GetPos() - etc->GetPos();
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
	_movementComponent->SetPassFloor(true);

	// ��� ����Ʈ�� �� ���� �� �ִٸ�
	if (_dashInfo._trailCount < _dashInfo._trailCountMax)
	{
		// ��� ����Ʈ �����̰� �����ٸ�
		_dashInfo._trailTime += DELTA_TIME;
		if (_dashInfo._trailTime > _dashInfo._trailDelay)
		{
			// ��� ����Ʈ ����
			++_dashInfo._trailCount;
			_dashInfo._trailTime = 0.0f;
			auto trail = make_shared<Effect_Trail>();
			auto quad = make_shared<Quad>(_texture->GetImageFile());
			trail->SetTexture(quad);
			trail->GetPos() = this->GetPos();
			trail->SetAlpha(0.75f);
			trail->SetFadeRatio(3.f);
			if (_reverseTexture)
				trail->ReverseTexture();
			GAME->AddEffect(trail);
		}
	}
}

void Player::Jump()
{	
	if (_dashMovement->GetCurSpeed() > 0) // ��� ���̶��
		return;

	
	if (_movementComponent->IsFalling() == false) // ���� �ִٸ�
	{
		// ���� �Ҹ� ����
		SOUND->Play("Jumping");

		// ����
		_movementComponent->Jump();

		// ���� ����Ʈ ����
		DustEffect();
	}
	else if (_doubleJumped == false) // ���߿� �ְ� ���� ������ �����ʾҴٸ�
	{
		// ���� �Ҹ� ����
		SOUND->Play("Jumping");

		// ���� ���� 
		_movementComponent->Jump();
		_doubleJumped = true;

		// ���� ���� ����Ʈ
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
	for (auto& object : GAME->GetObjects()[Object::ETC])
	{
		if (object == nullptr) continue;

		auto ect = dynamic_pointer_cast<Etc>(object);
		if(!ect->GetInteraction()) continue;

		// ��ȣ�ۿ��� �Ÿ��� �ִٸ�
		float length = (GetPos() - ect->GetPos()).Length();
		if (length <= INVENTORY->GetInteractionDistance())
		{
			ect->Interaction();
			return;
		}
	}
}
