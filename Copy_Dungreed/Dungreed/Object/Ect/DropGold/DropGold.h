#pragma once

class Creature;

class DropGold : public Ect
{
public:
	DropGold(int type, int num);

	virtual void Update() override;

	virtual void SetPirce(int price) { _price = price; }

	virtual void AddCoinToIventory();
	virtual void SetFollowCreature(Creature* creature);

	shared_ptr<MovementComponent> GetMovementComponent() { return _movement; }
	shared_ptr<DashMovementComponent> GetDashMovementComponent() { return _dash; }

protected:
	shared_ptr<MovementComponent> _movement;
	shared_ptr<DashMovementComponent> _dash;
	Creature* _follow = nullptr;
	float _followSpeed = 1500.f;
	bool _canFollow = false;
	int _price = 0.f;
};

