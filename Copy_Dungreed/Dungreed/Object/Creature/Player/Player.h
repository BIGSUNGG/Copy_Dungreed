#pragma once
class Player : public Creature
{
public:
	Player(int level, int num);

	virtual void Update() override;

	virtual float TakeDamage(float baseDamage, shared_ptr<Creature> attacker) override;
	virtual float GiveDamage(float baseDamage, shared_ptr<Creature> target) override;

	// 대시 시 호출
	virtual void Dash();
	virtual void Jump() override;

	virtual void Attack() override;	

	virtual void MoveLeft() override;
	virtual void MoveRight() override;
	// 오브젝트와 상호작용 시 호출
	virtual void Interaction();

	// 바닥 타일을 통과할지
	virtual void SetPassFloor(bool pass) { _movement->SetPassFloor(pass); }
	virtual void SetCurWeaponSlot(const int& slot) { _curWeaponSlot = slot; }

	virtual void StopMove();
	virtual void MouseEvent();

protected:
	// Etc 오브젝트와 관련된 이벤트
	virtual void CheckEtcEvent();

	// 대시와 관련된 이벤트
	virtual void DashMovement();
	virtual void MovementEvent() override;

	// 발자국 소리 실행
	virtual void StepSound();
	// 발자국 이펙트 실행
	virtual void DustEffect();

	//더블 점프 이펙트 실행
	virtual void DoubleJumpEffect();

public:
	// Getter Setter
	virtual void SetStatic(bool sta);

	const Dash_Info& GetDashInfo() { return _dashInfo; }

protected:
	shared_ptr<DashMovementComponent> _dashMovement;
	Dash_Info _dashInfo;

	float _goldMagnetLength = 200.f; // 골드를 끌어당기는 길이

	float _weaponDirection = 0.0f; // 무기를 들고 있는 방향

	string _curStepSound; // 현재 걷기 소리
	int _stepSound = 0;  // 현재 걷기 소리 번호

	bool _doubleJumped = false; // 더블 점프 했는지 (착지 시 초기화)

	float _dustTime = 0.25f; // 먼지 이펙트 남은 딜레이
	const float _dustDelay = 0.25f; // 걸을 때 먼지 이펙트를 스폰할 딜레이
};

