#pragma once
class Monster : public Creature
{
public:
	Monster(int level, int num);

	virtual void Update() override;
	virtual void Render() override;

	virtual void SetTarget(shared_ptr<Creature> target);
	virtual float TakeDamage(float baseDamage, shared_ptr<Creature> attacker) override;

protected:
	virtual void SearchTarget();
	virtual void AI();

	virtual void SpawnEffect();

	virtual void MovementEvent() override {}

protected:
	weak_ptr<Creature> _target;
	bool _ai = false;
	bool search = false;
	float _searchLength = 500.0f;

	bool _spawn = false;

};

