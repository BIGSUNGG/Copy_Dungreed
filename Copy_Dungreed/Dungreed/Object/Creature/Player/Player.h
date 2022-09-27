#pragma once
class Player : public Creature
{
public:
	Player(int level, int num);

	virtual void Update() override;

protected:
	virtual void Dash();
	virtual void Jump() override;

	virtual void MouseEvent();
	virtual void MovementEvent();
	virtual void InputEvent();

	virtual void DustEffect();
	virtual void DoubleJumpEffect();

protected:
	bool _doubleJumped = false;

	bool _dashSlow = false;
	float _dashSlowSpeed = 10000.0f;
	float _dashCurSpeed = 0.0f;
	float _dashSpeedMax = 2500.0f;
	float _dashRunTime = 0.0f;
	float _dashMaxTime = 0.025f;
	Vector2 _dashDirection = { 0,0 };

	float _dustRunTime = 0.25f;
	float _dustDelay = 0.25f;
};

