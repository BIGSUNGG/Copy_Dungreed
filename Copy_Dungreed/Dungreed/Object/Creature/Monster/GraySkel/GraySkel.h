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
	float _targetAttackDistance = 100.0f; // Ÿ���� �ش� �Ÿ��ȿ� �ִٸ� ����
	float _targetJumpOrFallDistance = 20.0f; // Ÿ���� �ش� �Ÿ��ȿ��ְ� ���� �ִٸ� ����

};

