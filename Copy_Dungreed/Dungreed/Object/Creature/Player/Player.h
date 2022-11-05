#pragma once
class Player : public Creature
{
public:
	Player(int level, int num);

	virtual void Update() override;

	virtual float GetDamage(shared_ptr<Creature> enemy, shared_ptr<Item> weapon) override;

	const Dash_Info& GetDashInfo() { return _dash; }

	virtual void Dash();
	virtual void Jump() override;

	virtual void Attack();

	virtual void MoveLeft();
	virtual void MoveRight();

	virtual void SetPassFloor(const bool& pass) { _passFloor = pass; }
	virtual void SetCurWeaponSlot(const int& slot) { _curWeaponSlot = slot; }

	virtual void MouseEvent();

protected:
	virtual float GiveDamage(shared_ptr<Creature> target, shared_ptr<Item> weapon = nullptr);

	virtual void DashMovement();
	virtual void MovementEvent();

	virtual void StepSound();

	virtual void DustEffect();
	virtual void DoubleJumpEffect();

protected:
	Dash_Info _dash;
	float _weaponDirection = 0.0f;

	string _curStepSound;
	int _stepSound = 0;

	bool _doubleJumped = false;

	float _dustRunTime = 0.25f;
	const float _dustDelay = 0.25f;
};

