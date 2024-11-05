#include "framework.h"
#include "Creature.h"

Creature::Creature(int level, int num)
	: Object(level, num)
{
	_objectType = Object::Object_Type::CREATURE;

	_inventory = make_shared<Inventory>(this);
	_inventory->SetWeaponSlotSize(1);

	_movementComponent = make_shared<MovementComponent>(this);
	_movementComponent->SetMovementEvent(bind(&Creature::MovementEvent, this));
	_componentCollector->Add(_movementComponent);
}

void Creature::Update()
{
	Object::Update();

	// 데미지 버퍼
	_damagedTime += DELTA_TIME;
	if (_damagedTime >= _damagedDuration)
		_buffer->_data.selected = 0;

	// 무기 틱
	for (auto& wepaon : _inventory->GetWeaponSlot())
	{
		if (wepaon == nullptr)
			continue;

		wepaon->Update();
	}

	// 캐릭터가 맵 밖으로 벗어난다면
	if (_texture->Top() <= CAMERA->GetLeftBottom().y - 500)
		Death();
}

void Creature::Render()
{
	// 현재 들고 있는 무기 렌더링
	auto curWeapon = GetCurWeapon();

	if (curWeapon != nullptr)
	{
		// 무기를 플레이어보다 먼저 렌더링할지
		bool weaponRender = curWeapon->GetFastRender();

		if (!weaponRender)
			curWeapon->Render();

		Object::Render();

		if (weaponRender)
			curWeapon->Render();
	}
	else
		Object::Render();
}

void Creature::PostRender()
{
	Object::PostRender();

	// 무기 PostRender
	auto curWeapon = GetCurWeapon();
	if (curWeapon != nullptr)
		curWeapon->PostRender();
}

float Creature::TakeDamage(float baseDamage, shared_ptr<Creature> attacker)
{
	float damage = baseDamage;
	_status._hp -= damage;

	if (_status._hp <= 0) // 체력이 0이하일 시
		Death(); // 사망

	_damagedTime = 0.0f;

	return damage;
}

float Creature::GiveDamage(float baseDamage, shared_ptr<Creature> target)
{
	float attackDamage = target->TakeDamage(baseDamage, dynamic_pointer_cast<Creature>(shared_from_this()));
	return attackDamage;
}

void Creature::Death()
{
	// 오브젝트 비활성화
	_isActive = false;

	// 사망 이펙트 추가
	shared_ptr<Effect> deathEffect = MAKE_CREATURE_EFFECT(StageMap::Level::PUBLIC, 0);
	deathEffect->GetObjectTexture()->GetTransform()->GetPos() = _texture->GetTransform()->GetPos();
	GAME->AddEffect(deathEffect);

	// 골드를 드랍할 수 있는지
	if (_ableDropGold)
	{
		// 골드를 드랍할지 랜덤으로 구하기
		bool shouldDropGold = MathUtility::RandomInt(0, 100) <= 80 ? true : false;
		if (shouldDropGold)
		{
			// 골드 드랍
			int goldCount = MathUtility::RandomInt(2, 7);
			for (int i = 0; i < goldCount; i++)
			{
				// 골드 타입 구하기
				int goldType = MathUtility::RandomInt(0, 100) <= 85 ? 0 : 1;

				// 골드 오브젝트 만들기
				auto dropGold = OBJ_MANAGER->GetGold(goldType);
				dropGold->SetPos(GetPos());
				float x = MathUtility::RandomFloat(-0.35f, 0.35f);
				Vector2 direction = { x, 1.f };
				dropGold->GetDashMovementComponent()->SetDirection(direction);
				dropGold->GetDashMovementComponent()->Dash();
				GAME->AddEtcObject(dropGold);
			}
		}
	}

	// 사망 이벤트
	for (auto& func : _deathEvent)
		func();
}

void Creature::Attack()
{
	// 현재 들고있는 무기로 공격
	auto curWeapon = GetCurWeapon();
	if (curWeapon != nullptr)
		curWeapon->Attack();

	_anim->ChangeAnimation(Creature::Creature_State::ATTACK);
}

void Creature::Skill()
{
	// 현재 들고있는 무기의 스킬 사용
	auto curWeapon = GetCurWeapon();
	if (curWeapon != nullptr)
		curWeapon->Skill();

	_anim->ChangeAnimation(Creature::Creature_State::SKILL);
}

void Creature::MoveLeft()
{
	// 왼쪽으로 이동
	_movementComponent->GetMoveDir().x -= _status._speed;
}

void Creature::MoveRight()
{
	// 오른쪽으로 이동
	_movementComponent->GetMoveDir().x += _status._speed;
}

void Creature::Jump()
{
	// 공중에 있지 않다면 점프
	if (_movementComponent->IsFalling() == false)
		_movementComponent->Jump();
}

void Creature::SetSpawnPos(Vector2 pos)
{
	Object::SetSpawnPos(pos);
	_movementComponent->SetBeforeMove(pos);
}

bool Creature::GainItem(shared_ptr<Item> item)
{
	return _inventory->AddOrEquipItem(item).first != Slot_Type::NONE;
}
