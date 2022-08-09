#pragma once
class Player : public Creature
{
public:
	Player(int level, int num);

	virtual void Update() override;

	virtual void InputEvent();
	virtual void Jump();

protected:
	float _jumpPower = 0.0f;
	float _jumpPowerMax = 800.0f;
	float _gravity = 1200.0f;

	bool _isReversed = false;
	bool _doubleJumped = false;
};

