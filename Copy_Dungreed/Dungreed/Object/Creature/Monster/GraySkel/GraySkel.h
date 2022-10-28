#pragma once
class GraySkel : public Monster
{
public:
	GraySkel(int level, int num);

	virtual void Update() override;

protected:
	virtual void AI() override;

	virtual void Attack() override;

	virtual void MovementEvent() override;

protected:
	float _targetDistanceGround = 100.0f;
	float _targetDistanceJumping = 20.0f;

};

