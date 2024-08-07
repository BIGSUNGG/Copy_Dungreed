#include "framework.h"
#include "Creature.h"

Creature::Creature(int level, int num)
	: Object(level, num)
{
	_movement = make_shared<MovementComponent>(this);
	_movement->SetMovementEvent(bind(&Creature::MovementEvent, this));

	_objectType = Object::Object_Type::CREATURE;
	_weaponSlot.resize(1);
}

void Creature::Update()
{
	// 컴포넌트
	_movement->Update();

	Object::Update();

	// 데미지 버퍼
	_damagedTime += DELTA_TIME;
	if (_damagedTime >= _damagedDuration)
		_buffer->_data.selected = 0;

	// 무기 틱
	for (auto& wepaon : _weaponSlot)
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
	if (_weaponSlot[_curWeaponSlot] != nullptr)
	{
		// 무기를 플레이어보다 먼저 렌더링할지
		bool weaponRender = _weaponSlot[_curWeaponSlot]->GetFastRender();
		if (!weaponRender)
			_weaponSlot[_curWeaponSlot]->Render();

		Object::Render();

		if (weaponRender)
			_weaponSlot[_curWeaponSlot]->Render();
	}
	else
		Object::Render();
}

void Creature::PostRender()
{
	Object::PostRender();

	// 무기 PostRender
	if(_weaponSlot[_curWeaponSlot] != nullptr)
		_weaponSlot[_curWeaponSlot]->PostRender();
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
	shared_ptr<Effect> deathEffect = MAKE_CREATURE_EFFECT(Map::Level::PUBLIC, 0);
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
	if (_weaponSlot[_curWeaponSlot] != nullptr)
		_weaponSlot[_curWeaponSlot]->Attack();

	_anim->ChangeAnimation(Creature::Creature_State::ATTACK);
}

void Creature::Skill()
{
	// 현재 들고있는 무기의 스킬 사용
	if (_weaponSlot[_curWeaponSlot] != nullptr)
		_weaponSlot[_curWeaponSlot]->Skill();

	_anim->ChangeAnimation(Creature::Creature_State::SKILL);
}

void Creature::MoveLeft()
{
	// 왼쪽으로 이동
	_movement->GetMoveDir().x -= _status._speed;
}

void Creature::MoveRight()
{
	// 오른쪽으로 이동
	_movement->GetMoveDir().x += _status._speed;
}

void Creature::Jump()
{
	// 공중에 있지 않다면 점프
	if (_movement->IsFalling() == false)
		_movement->Jump();
}

void Creature::SetSpawnPos(Vector2 pos)
{
	Object::SetSpawnPos(pos);
	_movement->SetBeforeMove(pos);
}

bool Creature::AddItem(shared_ptr<Item> item)
{
	// 아이템 주인 설정
	item->SetOwner(dynamic_pointer_cast<Creature>(shared_from_this()));


	// 아이템 타입에 맞는 아이템 슬롯이 비어있다면 자동으로 장착
	bool added = false;
	switch (item->GetItemType())
	{
	case Item::WEAPON:
	{
		auto weapon = dynamic_pointer_cast<Weapon>(item);
		for (auto& slot : _weaponSlot)
		{
			if (slot == nullptr)
			{
				slot = weapon;
				added = true;
				break;
			}
		}
	}
		break;
	case Item::ACCESSORY:
	{
		auto accessory = dynamic_pointer_cast<Accessory>(item);
		for (auto& slot : _accessorySlot)
		{
			if (slot == nullptr)
			{
				slot = accessory;
				added = true;
				break;
			}
		}
	}
		break;
	case Item::NONE:
		break;
	default:
		break;
	}

	// 비어있는 슬롯이 없었다면
	if (added == false)
	{
		for (auto& slot : _itemSlot)
		{
			if (slot == nullptr)
			{
				slot = item;
				added = true;
				break;
			}
		}
	}

	return added;
}
