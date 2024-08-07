#include "framework.h"
#include "DropGold.h"

DropGold::DropGold(int type, int num)
	: Etc(type,num)
{
	_etcType = DROP_COIN;
	_movement = make_shared<MovementComponent>(this);
	_movement->SetGravityRatio(1.f);
	_movement->SetCollisionEvent([&]()
		{
		_dash->DashEnd();
		_canFollow = true;
		});
	_dash = make_shared<DashMovementComponent>(this);
	_dash->SetMaxSpeed(1500.f);
	_dash->SetSlowDownSpeed(1500.f);
}

void DropGold::Update()
{
	if (_follow != nullptr)
	{
		Vector2 direction = _follow->GetPos() - this->GetPos();
		direction.Normalize();
		_movement->GetMoveDir() += direction * _followSpeed;
	}

	_dash->Update();
	_movement->Update();
	Etc::Update();
}

void DropGold::AddCoinToIventory()
{
	_isActive = false;
	INVENTORY->IncreaseGold(_price);

	Vector2 targetPos = GAME->GetPlayer() ? GAME->GetPlayer()->GetPos() : Vector2::zero;
	targetPos.x += MathUtility::RandomFloat(-50.f, 50.f);
	targetPos.y += MathUtility::RandomFloat(-50.f, 50.f);

	auto effect = make_shared<Effect_Number>();
	effect->SetNumber(_price);
	effect->SetPos(targetPos);
	effect->SetColor({
		256.f / 256.f,
		256.f / 256.f,
		0.f,
		1.f
		});
	GAME->AddEffect(effect);
}

void DropGold::SetFollowCreature(Creature* creature)
{
	if (!_canFollow) 
		return;

	_movement->SetGravityRatio(0.f);
	_movement->SetCollision(false);
	_follow = creature;
}
