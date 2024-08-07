#pragma once
class Monster : public Creature
{
public:
	Monster(int level, int num);

	virtual void Update() override;
	virtual void Render() override;

	virtual float TakeDamage(float baseDamage, shared_ptr<Creature> attacker) override;

protected:
	// 타겟 탐색
	virtual void SearchTarget();
	// 몬스터 AI
	virtual void AI();

	// 타겟을 찾았을 경우 호출
	virtual void SpawnEffect();

	virtual void MovementEvent() override {}

public:
	// Getter Setter
	virtual void SetTarget(shared_ptr<Creature> target);

protected:
	weak_ptr<Creature> _target; // 현재 추적중인 타겟
	bool _enableAI = false; // AI가 활성화 되었는지
	float _searchLength = 500.0f; // 탐색 길이

	bool _spawn = false; // 스폰되었는지

};

