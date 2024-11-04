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
	auto curWeapon = GetCurWeapon();
	if (curWeapon != nullptr)
	{
		float angle;

		if (_reverseTexture)
			angle = 1 * PI;
		else
			angle = 0;

		curWeapon->SetShowTo(angle);
	}
	Monster::Update();
}

void GraySkel::AI()
{
	auto curWeapon = GetCurWeapon();
	if (curWeapon->GetAnimation()->GetCurAnim() == Creature::Creature_State::ATTACK &&
		curWeapon->GetAnimation()->IsPlaying() == true)
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
		_movementComponent->SetPassFloor(true);
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
	auto curWeapon = GetCurWeapon();

	// �ִϸ��̼� ���� �� ������Ʈ ��ġ ������
	curWeapon->GetAnimation()->SetBeforeChangeFunc([=](std::pair<int,int> value) 
		{
			curWeapon->GetObjectTexture()->GetTransform()->GetPos() = 
			Vector2(curWeapon->GetObjectTexture()->Left(), curWeapon->GetObjectTexture()->Bottom());
		});
	
	curWeapon->GetAnimation()->SetAfterChangeFunc([=](std::pair<int, int> value) 
		{
			curWeapon->GetObjectTexture()->SetLeft(curWeapon->GetObjectTexture()->GetTransform()->GetPos().x);
			curWeapon->GetObjectTexture()->SetBottom(curWeapon->GetObjectTexture()->GetTransform()->GetPos().y);
		});

	Monster::Attack();
}

void GraySkel::MovementEvent()
{
	// �¿�� �̵� ���̶��
	if (_movementComponent->GetVelocity().x != 0)
	{
		_anim->ChangeAnimation(Creature_State::RUN);

		// ���������� �̵� ���̶��
		if (_movementComponent->GetVelocity().x > 0 && _reverseTexture == true && _movementComponent->IsFalling() == false)
			ReverseTexture();
		// �������� �̵� ���̶��
		else if (_movementComponent->GetVelocity().x < 0 && _reverseTexture == false && _movementComponent->IsFalling() == false)
			ReverseTexture();
	}
	else // ������ �ִٸ�
	{
		_anim->ChangeAnimation(Creature_State::IDLE);
	}

	// �� �Ʒ��� �����̴� ���̶��
	if (_movementComponent->GetVelocity().y != 0)
	{
		_anim->ChangeAnimation(Creature_State::JUMP);
	}
}
