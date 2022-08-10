#pragma once
class Player : public Creature
{
public:
	Player(int level, int num);

	virtual void Update() override;

	virtual void InputEvent();
	virtual void Jump();

protected:
	bool _doubleJumped = false;
};

