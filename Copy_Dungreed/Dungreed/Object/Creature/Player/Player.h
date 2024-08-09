#pragma once
class Player : public Creature
{
public:
	Player(int level, int num);

	virtual void Update() override;

	virtual float TakeDamage(float baseDamage, shared_ptr<Creature> attacker) override;
	virtual float GiveDamage(float baseDamage, shared_ptr<Creature> target) override;

	// ��� �� ȣ��
	virtual void Dash();
	virtual void Jump() override;

	virtual void Attack() override;	

	virtual void MoveLeft() override;
	virtual void MoveRight() override;
	// ������Ʈ�� ��ȣ�ۿ� �� ȣ��
	virtual void Interaction();

	// �ٴ� Ÿ���� �������
	virtual void SetPassFloor(bool pass) { _movement->SetPassFloor(pass); }
	virtual void SetCurWeaponSlot(const int& slot) { _curWeaponSlot = slot; }

	virtual void StopMove();
	virtual void MouseEvent();

protected:
	// Etc ������Ʈ�� ���õ� �̺�Ʈ
	virtual void CheckEtcEvent();

	// ��ÿ� ���õ� �̺�Ʈ
	virtual void DashMovement();
	virtual void MovementEvent() override;

	// ���ڱ� �Ҹ� ����
	virtual void StepSound();
	// ���ڱ� ����Ʈ ����
	virtual void DustEffect();

	//���� ���� ����Ʈ ����
	virtual void DoubleJumpEffect();

public:
	// Getter Setter
	virtual void SetStatic(bool sta);

	const Dash_Info& GetDashInfo() { return _dashInfo; }

protected:
	shared_ptr<DashMovementComponent> _dashMovement;
	Dash_Info _dashInfo;

	float _goldMagnetLength = 200.f; // ��带 ������� ����

	float _weaponDirection = 0.0f; // ���⸦ ��� �ִ� ����

	string _curStepSound; // ���� �ȱ� �Ҹ�
	int _stepSound = 0;  // ���� �ȱ� �Ҹ� ��ȣ

	bool _doubleJumped = false; // ���� ���� �ߴ��� (���� �� �ʱ�ȭ)

	float _dustTime = 0.25f; // ���� ����Ʈ ���� ������
	const float _dustDelay = 0.25f; // ���� �� ���� ����Ʈ�� ������ ������
};

