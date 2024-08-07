#pragma once
class Creature : public Object
{
public:
	enum Creature_Type
	{
		PLAYER,
		ENEMY,
		BOSS,
		NPC,
	};

	enum Creature_State
	{
		IDLE,
		ATTACK,
		RUN,
		JUMP,
		DIE,
		SKILL,
	};

public:
	Creature(int level, int num);

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	// 대미지를 받을 경우 호출
	virtual float TakeDamage(float baseDamage, shared_ptr<Creature> attacker);
	// 대미지를 줄 경우 호출
	virtual float GiveDamage(float baseDamage, shared_ptr<Creature> target);
	// 캐릭터 사망 시 호출
	virtual void Death();

public:
	// 공격 시 호출
	virtual void Attack();
	// 스킬 사용 시 호출
	virtual void Skill();

	// 왼쪽으로 이동
	virtual void MoveLeft();
	// 오른쪽으로 이동
	virtual void MoveRight();
	// 점프
	virtual void Jump();
	// 캐릭터 이동에 관련된 이벤트
	virtual void MovementEvent() {}

public:
	// Getter Setter
	virtual bool AddItem(shared_ptr<Item> weapon);
	void AddOnDeathEvent(std::function<void()> Func) { _deathEvent.push_back(Func); }

	bool IsFalling() { return _movement->IsFalling(); }

	const Creature_Status& GetStatus() { return _status; }
	Creature_Type& GetCreatureType() { return _creatureType; }
	shared_ptr<MovementComponent> GetMovementComponent() { return _movement; }

	virtual void SetSpawnPos(Vector2 pos) override;

protected:
	Creature_Type _creatureType = ENEMY;

	int _curWeaponSlot = 0; // 현재 들고 있는 무기 슬롯 번호
	vector<shared_ptr<Weapon>> _weaponSlot; // 무기 슬롯
	vector<shared_ptr<Accessory>> _accessorySlot; // 악세사리 슬롯
	vector<shared_ptr<Item>> _itemSlot; // 아이템 슬롯

	shared_ptr<MovementComponent> _movement; // 이동 컴포넌트

	Creature_Status _status; // 캐릭터 상태

	float _damagedTime = 0.1f; // 데미지를 받은 표시 지속시간이 얼마나 지났는지
	float _damagedDuration = 0.1f; // 데미지를 받은 표시 지속시간

	bool _ableDropGold = false; // 사망 시 골드를 떨구는지
	vector<std::function<void()>> _deathEvent; // 사망 시 호출할 함수

};

