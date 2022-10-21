#pragma once
class Player : public Creature
{
public:
	Player(int level, int num);

	virtual void Update() override;

	virtual bool GetDamage(shared_ptr<Creature> enemy, shared_ptr<Item> weapon) override;

	const Dash_Info& GetDashInfo() { return _dash; }

protected:
	virtual void Dash();
	virtual void DashMovement();
	virtual void Jump() override;

	virtual void MouseEvent();
	virtual void MovementEvent();
	virtual void InputEvent();

	virtual void StepSound();

	virtual void DustEffect();
	virtual void DoubleJumpEffect();

protected:
	int _stepSound = 0;
	bool _doubleJumped = false;

	Dash_Info _dash;
	string _curStepSound;

	float _dustRunTime = 0.25f;
	const float _dustDelay = 0.25f;
};

