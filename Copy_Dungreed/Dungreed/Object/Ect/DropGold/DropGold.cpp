#include "framework.h"
#include "DropGold.h"

DropGold::DropGold(int type, int num)
	: Ect(type,num)
{
	_ectType = DROP_COIN;
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
	_renderOrder = 3.75f;
}

void DropGold::Update()
{
	if (_follow != nullptr)
	{
		Vector2 direction = _follow->GetPos() - this->GetPos();
		direction.Normalize();
		_movement->GetMovement() += direction * _followSpeed;
	}

	_dash->Update();
	_movement->Update();
	Ect::Update();
}

void DropGold::AddCoinToIventory()
{
	_isActive = false;
	INVENTORY->AddGold(_price);

	auto effect = make_shared<Effect_Number>();
	effect->SetNumber(_price);
	effect->SetPos(GAME->GetPlayer()->GetPos());
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
