#pragma once
class Monster : public Creature
{
public:
	Monster(int level, int num);

	virtual void Update() override;

	virtual void SearchTarget();
	virtual void AI();
	
	virtual void MovementEvent();

protected:
	weak_ptr<Creature> _target;
	float _searchLength = 500.0f;
	float _targetDistance = 200.0f;
	bool search = false;
};

