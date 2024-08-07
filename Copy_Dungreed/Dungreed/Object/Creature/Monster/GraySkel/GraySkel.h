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
	float _targetAttackDistance = 100.0f; // 타겟이 해당 거리안에 있다면 공격
	float _targetJumpOrFallDistance = 20.0f; // 타겟이 해당 거리안에있고 위에 있다면 점프

};

