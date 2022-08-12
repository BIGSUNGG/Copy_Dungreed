#pragma once
class Player : public Creature
{
public:
	Player(int level, int num);

	virtual void Update() override;
	virtual void PostRender() override;

	virtual void DustEffect();
	virtual void DoubleJumpEffect();
	virtual void InputEvent();
	virtual void Jump();

protected:
	bool _doubleJumped = false;
	float _dustDelay = 0.0f;
};

