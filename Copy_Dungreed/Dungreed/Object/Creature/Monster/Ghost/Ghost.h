#pragma once
class Ghost : public Monster
{
public:
	Ghost(int level, int num);

	virtual void Update() override;

protected:
	virtual void CollisionEvent() override;

	virtual void AI() override;
	virtual void MoveTo(shared_ptr<Object> object);

	virtual void Attack() override;

protected:
	float _targetDistance = 20.0f;
	float _targetAttackDistance = 200.0f;

	Vector2 _attackDirection = { 0,0 };
	bool _attack = false;
	float _attackSpeed = 550.0f;
	float _attackWatitTime = 0.0f;
	float _attackRunTime = 0.0f;
	const float _attackWaitDelay = 1.5f;
	const float _attackDelay = 1.5f;

	bool _giveDamage = false;
};

