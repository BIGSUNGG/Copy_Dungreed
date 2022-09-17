#pragma once
class GraySkel : public Monster
{
public:
	GraySkel(int level, int num);

	void AI() override;

protected:
	float _targetDistanceGround = 200.0f;
	float _targetDistanceJumping = 20.0f;
};

