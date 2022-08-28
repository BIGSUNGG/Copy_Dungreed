#pragma once
class Monster : public Creature
{
public:
	Monster(int level, int num);

	virtual void Update() override;

	virtual void SearchTarget();
	virtual void AI();
	virtual void Jump();
	virtual void Attack();

	virtual void MovementEvent();

protected:
	weak_ptr<Creature> _target;
	bool search = false;
	float _searchLength = 500.0f;

	float _targetDistance;
	const float _targetDistanceMin = 0.0f;
	const float _targetDistanceMax = 3.0f;
	const float _targetDistanceRatio = 100.0f;
};

