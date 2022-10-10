#pragma once
class Player : public Creature
{
public:


public:
	Player(int level, int num);

	virtual void Update() override;

	const Dash_Info& GetDashInfo() { return _dash; }

protected:
	virtual void Dash();
	virtual void DashMovement();
	virtual void Jump() override;

	virtual void MouseEvent();
	virtual void MovementEvent();
	virtual void InputEvent();

	virtual void DustEffect();
	virtual void DoubleJumpEffect();

protected:
	bool _doubleJumped = false;

	Dash_Info _dash;

	float _dustRunTime = 0.25f;
	const float _dustDelay = 0.25f;
};

