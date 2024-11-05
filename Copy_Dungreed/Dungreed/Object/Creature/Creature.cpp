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

	// ������ ����
	_damagedTime += DELTA_TIME;
	if (_damagedTime >= _damagedDuration)
		_buffer->_data.selected = 0;

	// ���� ƽ
	for (auto& wepaon : _inventory->GetWeaponSlot())
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
	auto curWeapon = GetCurWeapon();

	if (curWeapon != nullptr)
	{
		// ���⸦ �÷��̾�� ���� ����������
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

	// ���� PostRender
	auto curWeapon = GetCurWeapon();
	if (curWeapon != nullptr)
		curWeapon->PostRender();
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
	shared_ptr<Effect> deathEffect = MAKE_CREATURE_EFFECT(StageMap::Level::PUBLIC, 0);
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
	auto curWeapon = GetCurWeapon();
	if (curWeapon != nullptr)
		curWeapon->Attack();

	_anim->ChangeAnimation(Creature::Creature_State::ATTACK);
}

void Creature::Skill()
{
	// ���� ����ִ� ������ ��ų ���
	auto curWeapon = GetCurWeapon();
	if (curWeapon != nullptr)
		curWeapon->Skill();

	_anim->ChangeAnimation(Creature::Creature_State::SKILL);
}

void Creature::MoveLeft()
{
	// �������� �̵�
	_movementComponent->GetMoveDir().x -= _status._speed;
}

void Creature::MoveRight()
{
	// ���������� �̵�
	_movementComponent->GetMoveDir().x += _status._speed;
}

void Creature::Jump()
{
	// ���߿� ���� �ʴٸ� ����
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
