#include "framework.h"
#include "Creature.h"

Creature::Creature(int level, int num)
	: Object(level, num)
{
	_movement = make_shared<MovementComponent>(this);
	_movement->SetMovementEvent(bind(&Creature::MovementEvent, this));

	_renderOrder = 4.f;
	_objectType = Object::Object_Type::CREATURE;
	_weaponSlot.resize(1);
}

void Creature::Update()
{
	_damagedRunTime += DELTA_TIME;

	if (_damagedRunTime >= _damagedRunTimeMax)
		_buffer->_data.selected = 0;

	_movement->Update();

	Object::Update();

	for (auto& wepaon : _weaponSlot)
	{
		if (wepaon == nullptr)
			continue;

		wepaon->Update();
	}

	if (_texture->Top() <= CAMERA->GetLeftBottom().y)
		Death();
}

void Creature::Render()
{
	if (_weaponSlot[_curWeaponSlot] != nullptr)
	{
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

	if(_weaponSlot[_curWeaponSlot] != nullptr)
		_weaponSlot[_curWeaponSlot]->PostRender();
}

float Creature::TakeDamage(float baseDamage, shared_ptr<Creature> attacker)
{
	float damage = baseDamage + (attacker->GetStatus()._atk * 0.1f);
	_status._hp -= damage;

	if (_status._hp <= 0)
		Death();

	_damagedRunTime = 0.0f;

	return damage;
}

float Creature::GiveDamage(float baseDamage, shared_ptr<Creature> target)
{
	float attackDamage = target->TakeDamage(baseDamage, dynamic_pointer_cast<Creature>(shared_from_this()));
	return attackDamage;
}

void Creature::MoveCharacter()
{

}

void Creature::Death()
{
	_isActive = false;

	shared_ptr<Effect> deathEffect = MAKE_CREATURE_EFFECT(Map::Level::PUBLIC, 0);
	deathEffect->GetObjectTexture()->GetTransform()->GetPos() = _texture->GetTransform()->GetPos();

	GAME->AddEffect(deathEffect);

	if (_dropGold)
	{
		int gold = rand() % 3;
		if (gold == 0)
		{
			int goldCount = 3;	
			for (int i = 0; i < goldCount; i++)
			{
				int goldType = rand() % 4;
				if (goldType > 0)
					goldType = 0;
				else
					goldType = 1;

				auto dropGold = OBJ_MANAGER->GetGold(goldType);
				dropGold->SetPos(GetPos());
				float x = MathUtility::RandomFloat(-0.35f, 0.35f);
				Vector2 direction = { x, 1.f };
				dropGold->GetDashMovementComponent()->SetDirection(direction);
				dropGold->GetDashMovementComponent()->Dash();
				GAME->AddEctObject(dropGold);
			}
		}
	}

	for (auto& func : _deathEvent)
		func();

}

void Creature::Attack()
{
	if (_weaponSlot[_curWeaponSlot] != nullptr)
		_weaponSlot[_curWeaponSlot]->Attack();

	_anim->ChangeAnimation(Creature::Creature_State::ATTACK);
}

void Creature::Skill()
{
	if (_weaponSlot[_curWeaponSlot] != nullptr)
		_weaponSlot[_curWeaponSlot]->Skill();

	_anim->ChangeAnimation(Creature::Creature_State::SKILL);
}

void Creature::MoveLeft()
{
	_movement->GetMovement().x -= _status._speed;
}

void Creature::MoveRight()
{
	_movement->GetMovement().x += _status._speed;
}

void Creature::Jump()
{
	if (_movement->IsFalling() == false)
		_movement->Jump();
}

void Creature::CollisionEvent()
{

}

void Creature::SetSpawnPos(Vector2 pos)
{
	Object::SetSpawnPos(pos);
	_movement->SetBeforeMove(pos);
}


bool Creature::AddItem(shared_ptr<Item> item)
{
	bool add = false;

	switch (item->GetItemType())
	{
	case Item::WEAPON:
	{
		auto weapon = dynamic_pointer_cast<Weapon>(item);

		for (auto& slot : _weaponSlot)
		{
			if (slot == nullptr)
			{
				item->SetOwner(dynamic_pointer_cast<Creature>(shared_from_this()));
				slot = weapon;
				add = true;
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
				item->SetOwner(dynamic_pointer_cast<Creature>(shared_from_this()));
				slot = accessory;
				add = true;
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

	if (add == false)
	{
		for (auto& slot : _itemSlot)
		{
			if (slot == nullptr)
			{
				item->SetOwner(dynamic_pointer_cast<Creature>(shared_from_this()));
				slot = item;
				add = true;
				break;
			}
		}
	}

	return add;
}
