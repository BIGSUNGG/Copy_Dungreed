#pragma once
class Monster : public Creature
{
public:
	Monster(int level, int num);

	virtual void Update() override;
	virtual void Render() override;

	virtual void SearchTarget();
	virtual void AI();
	virtual void Jump();

	virtual void SpawnEffect();

	virtual void MovementEvent();

protected:
	weak_ptr<Creature> _target;
	bool search = false;
	float _searchLength = 500.0f;

	float _targetDistanceGround;
	float _targetDistanceJumping = 20.0f;
	const float _targetDistanceMin = 0.0f;
	const float _targetDistanceMax = 3.0f;
	const float _targetDistanceRatio = 100.0f;

	bool _spawn = false;
	float _spawnDelay = 0.8f;
};

