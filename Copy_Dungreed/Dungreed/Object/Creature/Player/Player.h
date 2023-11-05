#pragma once
class Player : public Creature
{
public:
	Player(int level, int num);

	virtual void Update() override;

	virtual float TakeDamage(float baseDamage, shared_ptr<Creature> attacker) override;
	virtual float GiveDamage(float baseDamage, shared_ptr<Creature> target) override;


	virtual void Dash();
	virtual void Jump() override;

	virtual void Attack();	

	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void Interaction();

	virtual void SetPassFloor(bool pass) { _movement->SetPassFloor(pass); }
	virtual void SetCurWeaponSlot(const int& slot) { _curWeaponSlot = slot; }

	virtual void StopMove();
	virtual void MouseEvent();

public:
	// Getter Setter
	virtual void SetStatic(bool sta);

	const Dash_Info& GetDashInfo() { return _dashInfo; }

protected:

	virtual void CheckEctEvent();
	virtual void DashMovement();
	virtual void MovementEvent();

	virtual void StepSound();

	virtual void DustEffect();
	virtual void DoubleJumpEffect();

protected:
	shared_ptr<DashMovementComponent> _dashMovement;
	Dash_Info _dashInfo;

	float _goldMagnetLength = 350.f;

	float _weaponDirection = 0.0f;

	string _curStepSound;
	int _stepSound = 0;

	bool _doubleJumped = false;

	float _dustRunTime = 0.25f;
	const float _dustDelay = 0.25f;
};

