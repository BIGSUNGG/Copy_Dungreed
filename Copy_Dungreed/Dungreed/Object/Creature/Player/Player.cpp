#include "framework.h"
#include "Player.h"

Player::Player(int level, int num)
	: Creature(level, num)
{
	_creatureType = PLAYER;

	// DashMovement 초기화
	_dashMovement = make_shared<DashMovementComponent>(this);
	_dashMovement->SetDashMovementEvent(bind(&Player::DashMovement, this));
	_dashMovement->SetDashEndEvent([&]() {
		_movementComponent->SetGravityRatio(1.f);
		_movementComponent->SetIsFalling(true); 
		});
	_dashMovement->SetDashSlowDownEvent([&]() {_movementComponent->SetGravityRatio(0.4f); });
	_componentCollector->Add(_dashMovement);

	// DamagedDuration 초기화
	_damagedDuration = 0.2f;

	// 슬롯 초기화
	_inventory->SetWeaponSlotSize(2);
	_inventory->SetAccessorySlotSize(4);
	_inventory->SetItemSlotSize(15);

	// 캐릭터 상태 초기화
	_status.SetMaxHp(80);
	_status._speed = 450.0f;

	// 사운드 추가
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

	// 무기가 바라보는 방향 수정
	auto curWeapon = GetCurWeapon();
	if (curWeapon != nullptr)
		curWeapon->SetShowTo(_weaponDirection);

	_dashInfo.Update();

	CheckEtcEvent();
}

float Player::TakeDamage(float baseDamage, shared_ptr<Creature> attacker)
{
	// 데미지를 받았다면 _damagedDuration 동안 무적
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

	// 데미지를 주었다면
	if (damage > 0)
	{
		// 데미지 이펙트 추가
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
	// 마우스 위치가 왼쪽에 있다면
	if (_texture->GetTransform()->GetPos().x >= MOUSE_WORLD_POS.x)
	{
		// 캐릭터 텍스쳐가 왼쪽을 보도록
		if (_reverseTexture == false)
		{
			ReverseTexture();
		}
	}
	else if (_reverseTexture == true)
	{
		// 캐릭터 텍스쳐가 오른쪽을 보도록
		ReverseTexture();
	}


	// 플레이어가 커서를 바라보는 위치 구하기
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
	if (_movementComponent->GetVelocity().x != 0) // 좌우로 이동하고 있다면
	{
		_anim->ChangeAnimation(Creature_State::RUN);

		// 땅에서 걸어다닌다면
		if (_movementComponent->IsFalling() == false)
		{
			StepSound();
			DustEffect();
		}
	}
	else // 가만히 있다면
	{
		_anim->ChangeAnimation(Creature_State::IDLE);
	}

	// 계단에 있지않고 위 아래로 이동 중이라면
	if (_movementComponent->IsOnStair() == false && (_movementComponent->GetVelocity().y != 0 || _dashMovement->GetCurSpeed() > 0.0f))
	{
		_anim->ChangeAnimation(Creature_State::JUMP);
	}
	else // 땅에 있다면
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
		// 대시 소리 실행
		SOUND->Play("ui-sound-13-dash");

		// Movement 설정 
		_movementComponent->SetGravityRatio(0.2f);
		_movementComponent->SetJumpPower(0.f);

		// DashMovement 설정
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
			// 아이템과 닿았다면
			if (_collider->IsCollision(object->GetCollider()))
			{
				// 아이템 줍기
				auto dropItem = dynamic_pointer_cast<DropItem>(etc);
				dropItem->AddItemToCreature(this);
			}
		}
			break;
		case Etc::DROP_COIN:
		{
			auto dropGold = dynamic_pointer_cast<DropGold>(etc);
			// 골드와 닿았다면
			if (_collider->IsCollision(object->GetCollider()))
			{
				// 골드 추가
				dropGold->AddGoldToIventory();
			}
			else
			{
				// 골드가 골드를 끌어당기는 범위에 있다면 골드 끌어당기기
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

	// 대시 이펙트를 더 만들 수 있다면
	if (_dashInfo._trailCount < _dashInfo._trailCountMax)
	{
		// 대시 이펙트 딜레이가 지났다면
		_dashInfo._trailTime += DELTA_TIME;
		if (_dashInfo._trailTime > _dashInfo._trailDelay)
		{
			// 대시 이펙트 생성
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
	if (_dashMovement->GetCurSpeed() > 0) // 대시 중이라면
		return;

	
	if (_movementComponent->IsFalling() == false) // 땅에 있다면
	{
		// 점프 소리 실행
		SOUND->Play("Jumping");

		// 점프
		_movementComponent->Jump();

		// 먼지 이펙트 실행
		DustEffect();
	}
	else if (_doubleJumped == false) // 공중에 있고 더블 점프를 하지않았다면
	{
		// 점프 소리 실행
		SOUND->Play("Jumping");

		// 더블 점프 
		_movementComponent->Jump();
		_doubleJumped = true;

		// 더블 점프 이펙트
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

		// 상호작용한 거리에 있다면
		float length = (GetPos() - ect->GetPos()).Length();
		if (length <= INVENTORY->GetInteractionDistance())
		{
			ect->Interaction();
			return;
		}
	}
}
