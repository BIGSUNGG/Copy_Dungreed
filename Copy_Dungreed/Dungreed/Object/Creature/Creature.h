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

	// ������� ���� ��� ȣ��
	virtual float TakeDamage(float baseDamage, shared_ptr<Creature> attacker);
	// ������� �� ��� ȣ��
	virtual float GiveDamage(float baseDamage, shared_ptr<Creature> target);
	// ĳ���� ��� �� ȣ��
	virtual void Death();

public:
	// ������ ŉ�� �� ȣ��
	virtual bool GainItem(shared_ptr<Item> item);

	// ���� �� ȣ��
	virtual void Attack();
	// ��ų ��� �� ȣ��
	virtual void Skill();

	// �������� �̵�
	virtual void MoveLeft();
	// ���������� �̵�
	virtual void MoveRight();
	// ����
	virtual void Jump();
	// ĳ���� �̵��� ���õ� �̺�Ʈ
	virtual void MovementEvent() {}

public:
	// Getter Setter
	void AddOnDeathEvent(std::function<void()> Func) { _deathEvent.push_back(Func); }

	bool IsFalling() { return _movementComponent->IsFalling(); }

	const Creature_Status& GetStatus() { return _status; }
	Creature_Type& GetCreatureType() { return _creatureType; }
	shared_ptr<MovementComponent> GetMovementComponent() { return _movementComponent; }
	
	const shared_ptr<Inventory> GetInventory() const { return _inventory; }
	shared_ptr<Weapon> GetCurWeapon() { return _inventory->GetWeaponSlot()[_curWeaponSlot]; }
	int GetCurWeaponSlotIndex() { return _curWeaponSlot; }

	virtual void SetSpawnPos(Vector2 pos) override;

protected:
	Creature_Type _creatureType = ENEMY;

	int _curWeaponSlot = 0; // ���� ��� �ִ� ���� ���� ��ȣ
	
	shared_ptr<Inventory> _inventory;
	shared_ptr<MovementComponent> _movementComponent; // �̵� ������Ʈ

	Creature_Status _status; // ĳ���� ����

	float _damagedTime = 0.1f; // �������� ���� ǥ�� ���ӽð��� �󸶳� ��������
	float _damagedDuration = 0.1f; // �������� ���� ǥ�� ���ӽð�

	bool _ableDropGold = false; // ��� �� ��带 ��������
	vector<std::function<void()>> _deathEvent; // ��� �� ȣ���� �Լ�

};

