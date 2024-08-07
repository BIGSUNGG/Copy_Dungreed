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
	float _targetDistance = 20.0f; // 타겟과 유지할 거리 
	float _targetAttackDistance = 650.0f; // 공격 가능한 거리

	Vector2 _attackDirection = { 0,0 }; // 공겨 방향
	bool _attack = false; // 공격 중인지
	float _attackDamage = 10.f; // 공격 데미지
	float _attackSpeed = 550.0f; // 공격 시 이동 속도
	float _attackWatitTime = 0.0f; // 공격 전 딜레이
	const float _attackWaitDelay = 1.5f; // 공격 전 딜레이
	float _attackTime = 0.0f; // 현재 공격 지속 시간
	const float _attackDuration = 1.5f; // 공격 지속 시간
	bool _giveDamage = false; // 현재 공격 동안 데미지를 주었는지

};

