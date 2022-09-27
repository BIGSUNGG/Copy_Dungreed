#pragma once
class GraySkel : public Monster
{
public:
	GraySkel(int level, int num);

protected:
	void AI() override;

protected:
	float _targetDistanceGround = 100.0f;
	float _targetDistanceJumping = 20.0f;
};

