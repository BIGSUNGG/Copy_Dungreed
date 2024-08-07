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
	// ������Ʈ
	_movement->Update();

	Object::Update();

	// ������ ����
	_damagedTime += DELTA_TIME;
	if (_damagedTime >= _damagedDuration)
		_buffer->_data.selected = 0;

	// ���� ƽ
	for (auto& wepaon : _weaponSlot)
	{
		if (wepaon == nullptr)
			continue;

		wepaon->Update();
	}

	// ĳ���Ͱ� �� ������ ����ٸ�
	if (_texture->Top() <= CAMERA->GetLeftBottom().y - 500)
		Death();
}

void Creature::Render()
{
	// ���� ��� �ִ� ���� ������
	if (_weaponSlot[_curWeaponSlot] != nullptr)
	{
		// ���⸦ �÷��̾�� ���� ����������
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

	// ���� PostRender
	if(_weaponSlot[_curWeaponSlot] != nullptr)
		_weaponSlot[_curWeaponSlot]->PostRender();
}

float Creature::TakeDamage(float baseDamage, shared_ptr<Creature> attacker)
{
	float damage = baseDamage;
	_status._hp -= damage;

	if (_status._hp <= 0) // ü���� 0������ ��
		Death(); // ���

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
	// ������Ʈ ��Ȱ��ȭ
	_isActive = false;

	// ��� ����Ʈ �߰�
	shared_ptr<Effect> deathEffect = MAKE_CREATURE_EFFECT(Map::Level::PUBLIC, 0);
	deathEffect->GetObjectTexture()->GetTransform()->GetPos() = _texture->GetTransform()->GetPos();
	GAME->AddEffect(deathEffect);

	// ��带 ����� �� �ִ���
	if (_ableDropGold)
	{
		// ��带 ������� �������� ���ϱ�
		bool shouldDropGold = MathUtility::RandomInt(0, 100) <= 80 ? true : false;
		if (shouldDropGold)
		{
			// ��� ���
			int goldCount = MathUtility::RandomInt(2, 7);
			for (int i = 0; i < goldCount; i++)
			{
				// ��� Ÿ�� ���ϱ�
				int goldType = MathUtility::RandomInt(0, 100) <= 85 ? 0 : 1;

				// ��� ������Ʈ �����
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

	// ��� �̺�Ʈ
	for (auto& func : _deathEvent)
		func();
}

void Creature::Attack()
{
	// ���� ����ִ� ����� ����
	if (_weaponSlot[_curWeaponSlot] != nullptr)
		_weaponSlot[_curWeaponSlot]->Attack();

	_anim->ChangeAnimation(Creature::Creature_State::ATTACK);
}

void Creature::Skill()
{
	// ���� ����ִ� ������ ��ų ���
	if (_weaponSlot[_curWeaponSlot] != nullptr)
		_weaponSlot[_curWeaponSlot]->Skill();

	_anim->ChangeAnimation(Creature::Creature_State::SKILL);
}

void Creature::MoveLeft()
{
	// �������� �̵�
	_movement->GetMoveDir().x -= _status._speed;
}

void Creature::MoveRight()
{
	// ���������� �̵�
	_movement->GetMoveDir().x += _status._speed;
}

void Creature::Jump()
{
	// ���߿� ���� �ʴٸ� ����
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
	// ������ ���� ����
	item->SetOwner(dynamic_pointer_cast<Creature>(shared_from_this()));


	// ������ Ÿ�Կ� �´� ������ ������ ����ִٸ� �ڵ����� ����
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

	// ����ִ� ������ �����ٸ�
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
