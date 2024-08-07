#pragma once
class Ghost : public Monster
{
public:
	Ghost(int level, int num);

	virtual void Update() override;

protected:
	virtual void AI() override;
	virtual void MoveTo(shared_ptr<Object> object);

	virtual void Attack() override;

protected:
	float _targetDistance = 20.0f; // Ÿ�ٰ� ������ �Ÿ� 
	float _targetAttackDistance = 650.0f; // ���� ������ �Ÿ�

	Vector2 _attackDirection = { 0,0 }; // ���� ����
	bool _attack = false; // ���� ������
	float _attackDamage = 10.f; // ���� ������
	float _attackSpeed = 550.0f; // ���� �� �̵� �ӵ�
	float _attackWatitTime = 0.0f; // ���� �� ������
	const float _attackWaitDelay = 1.5f; // ���� �� ������
	float _attackTime = 0.0f; // ���� ���� ���� �ð�
	const float _attackDuration = 1.5f; // ���� ���� �ð�
	bool _giveDamage = false; // ���� ���� ���� �������� �־�����

};

