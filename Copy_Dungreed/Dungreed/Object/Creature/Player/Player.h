#pragma once
class Player : public Creature
{
public:
	Player(int level, int num);

	virtual void Update() override;

	virtual void DustEffect();
	virtual void DoubleJumpEffect();

	virtual void MouseEvent();
	virtual void MovementEvent();
	virtual void InputEvent();

	virtual void Dash();
	virtual void Jump();

protected:
	bool _doubleJumped = false;

	bool _dashSlow = false;
	float _dashSlowSpeed = 10000.0f;
	float _dashCurSpeed = 0.0f;
	float _dashSpeedMax = 2000.0f;
	float _dashRunTime = 0.0f;
	float _dashMaxTime = 0.075f;
	Vector2 _dashDirection = { 0,0 };

	float _dustRunTime = 0.25f;
	float _dustDelay = 0.25f;
};

