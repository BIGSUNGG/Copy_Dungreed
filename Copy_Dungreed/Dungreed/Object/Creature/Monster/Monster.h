#pragma once
class Monster : public Creature
{
public:
	Monster(int level, int num);

	virtual void Update() override;
	virtual void Render() override;

	virtual float TakeDamage(float baseDamage, shared_ptr<Creature> attacker) override;

protected:
	// Ÿ�� Ž��
	virtual void SearchTarget();
	// ���� AI
	virtual void AI();

	// Ÿ���� ã���� ��� ȣ��
	virtual void SpawnEffect();

	virtual void MovementEvent() override {}

public:
	// Getter Setter
	virtual void SetTarget(shared_ptr<Creature> target);

protected:
	weak_ptr<Creature> _target; // ���� �������� Ÿ��
	bool _enableAI = false; // AI�� Ȱ��ȭ �Ǿ�����
	float _searchLength = 500.0f; // Ž�� ����

	bool _spawn = false; // �����Ǿ�����

};

