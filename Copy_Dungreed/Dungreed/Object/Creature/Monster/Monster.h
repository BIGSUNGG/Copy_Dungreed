#pragma once
class Monster : public Creature
{
public:
	Monster(int level, int num);

	virtual void Update() override;
	virtual void Render() override;

	virtual float TakeDamage(float baseDamage, shared_ptr<Creature> attacker) override;

protected:
	virtual void SearchTarget();
	virtual void AI();

	virtual void SpawnEffect();

	virtual void MovementEvent() override {}

public:
	// Getter Setter
	virtual void SetTarget(shared_ptr<Creature> target);

protected:
	weak_ptr<Creature> _target;
	bool _ai = false;
	bool search = false;
	float _searchLength = 500.0f;

	bool _spawn = false;

};

