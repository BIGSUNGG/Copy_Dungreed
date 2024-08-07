#include "framework.h"
#include "GraySkel.h"

GraySkel::GraySkel(int level, int num)
	: Monster(level, num)
{
	_status.SetMaxHp(80);
	_status._speed = 300.0f;

	_ableDropGold = true;
}

void GraySkel::Update()
{
	if (_weaponSlot[_curWeaponSlot] != nullptr)
	{
		float angle;

		if (_reverseTexture)
			angle = 1 * PI;
		else
			angle = 0;

		_weaponSlot[_curWeaponSlot]->SetShowTo(angle);
	}
	Monster::Update();
}

void GraySkel::AI()
{
	if (_weaponSlot[_curWeaponSlot]->GetAnimation()->GetCurAnim() == Creature::Creature_State::ATTACK && 
		_weaponSlot[_curWeaponSlot]->GetAnimation()->IsPlaying() == true)
		return;

	// Ÿ���� ������ �� �ִ� ���̺��� �ָ��ִٸ�
	float length = abs(_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x - _texture->GetTransform()->GetPos().x);
	if (length >= _targetAttackDistance)
	{		
		// Ÿ���� �����ʿ� �ִٸ�
		if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x) 
			MoveRight();
		// Ÿ���� ���ʿ� �ִٸ�
		else
			MoveLeft();
	}
	// Ÿ���� ���߿� �����ʰ� ���� �ִٸ�
	else if (_texture->Top() < _target.lock()->GetObjectTexture()->GetTransform()->GetPos().y && _target.lock()->IsFalling() == false)
	{
		// Ÿ���� �ٷ� ���� �����ʴٸ�
		if (length >= _targetJumpOrFallDistance)
		{						
			// Ÿ���� �����ʿ� �ִٸ�
			if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x)
				MoveRight();
			// Ÿ���� ���ʿ� �ִٸ�
			else 
				MoveLeft();
		}
		// Ÿ���� �ٷ� ���� �ִٸ�
		else 
			Jump();		
	}
	// Ÿ���� �Ʒ��� �ִٸ�
	else if (_texture->Bottom() > _target.lock()->GetObjectTexture()->Top())
	{
		_movement->SetPassFloor(true);
	}
	// Ÿ���� ���� �����ȿ� �ִٸ�
	else
	{
		// Ÿ���� �����ʿ� �ְ� ������ ���� �ִٸ�
		if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x > _texture->GetTransform()->GetPos().x && _reverseTexture == true)
			ReverseTexture();
		// Ÿ���� ���ʿ� �ְ� �������� ���� �ִٸ�
		else if (_target.lock()->GetObjectTexture()->GetTransform()->GetPos().x < _texture->GetTransform()->GetPos().x && _reverseTexture == false)
			ReverseTexture();
		
		// Ÿ�ٰ� ���� ���̿� �ִٸ�
		if (_collider->Bottom() >= _target.lock()->GetCollider()->Bottom())
			Attack();
	}
}

void GraySkel::Attack()
{
	_weaponSlot[_curWeaponSlot]->GetAnimation()->SetBeforeChangeFunc([=](std::pair<int,int> value) 
		{
			_weaponSlot[_curWeaponSlot]->GetObjectTexture()->GetTransform()->GetPos() = 
			Vector2(_weaponSlot[_curWeaponSlot]->GetObjectTexture()->Left(), _weaponSlot[_curWeaponSlot]->GetObjectTexture()->Bottom());
		});
	
	_weaponSlot[_curWeaponSlot]->GetAnimation()->SetAfterChangeFunc([=](std::pair<int, int> value) 
		{
			_weaponSlot[_curWeaponSlot]->GetObjectTexture()->SetLeft(_weaponSlot[_curWeaponSlot]->GetObjectTexture()->GetTransform()->GetPos().x);
			_weaponSlot[_curWeaponSlot]->GetObjectTexture()->SetBottom(_weaponSlot[_curWeaponSlot]->GetObjectTexture()->GetTransform()->GetPos().y);
		});

	Monster::Attack();
}

void GraySkel::MovementEvent()
{
	// �¿�� �̵� ���̶��
	if (_movement->GetVelocity().x != 0)
	{
		_anim->ChangeAnimation(Creature_State::RUN);

		// ���������� �̵� ���̶��
		if (_movement->GetVelocity().x > 0 && _reverseTexture == true && _movement->IsFalling() == false)
			ReverseTexture();
		// �������� �̵� ���̶��
		else if (_movement->GetVelocity().x < 0 && _reverseTexture == false && _movement->IsFalling() == false)
			ReverseTexture();
	}
	else // ������ �ִٸ�
	{
		_anim->ChangeAnimation(Creature_State::IDLE);
	}

	// �� �Ʒ��� �����̴� ���̶��
	if (_movement->GetVelocity().y != 0)
	{
		_anim->ChangeAnimation(Creature_State::JUMP);
	}
}
