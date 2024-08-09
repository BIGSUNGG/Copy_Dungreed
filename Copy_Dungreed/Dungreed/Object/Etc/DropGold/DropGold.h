#pragma once

class Creature;

class DropGold : public Etc
{
public:
	DropGold(int type, int num);

	virtual void Update() override;

	virtual void SetGoldValue(int value) { _goldValue = value; }

	virtual void AddGoldToIventory();
	virtual void SetFollowCreature(Creature* creature);

	shared_ptr<MovementComponent> GetMovementComponent() { return _movement; }
	shared_ptr<DashMovementComponent> GetDashMovementComponent() { return _dash; }

protected:
	shared_ptr<MovementComponent> _movement;
	shared_ptr<DashMovementComponent> _dash;
	Creature* _follow = nullptr;
	float _followSpeed = 1500.f;
	bool _canFollow = false;
	int _goldValue = 0.f;
};

