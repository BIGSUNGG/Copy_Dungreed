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
	virtual bool AddItem(shared_ptr<Item> weapon);
	void AddOnDeathEvent(std::function<void()> Func) { _deathEvent.push_back(Func); }

	bool IsFalling() { return _movement->IsFalling(); }

	const Creature_Status& GetStatus() { return _status; }
	Creature_Type& GetCreatureType() { return _creatureType; }
	shared_ptr<MovementComponent> GetMovementComponent() { return _movement; }

	virtual void SetSpawnPos(Vector2 pos) override;

protected:
	Creature_Type _creatureType = ENEMY;

	int _curWeaponSlot = 0; // ���� ��� �ִ� ���� ���� ��ȣ
	vector<shared_ptr<Weapon>> _weaponSlot; // ���� ����
	vector<shared_ptr<Accessory>> _accessorySlot; // �Ǽ��縮 ����
	vector<shared_ptr<Item>> _itemSlot; // ������ ����

	shared_ptr<MovementComponent> _movement; // �̵� ������Ʈ

	Creature_Status _status; // ĳ���� ����

	float _damagedTime = 0.1f; // �������� ���� ǥ�� ���ӽð��� �󸶳� ��������
	float _damagedDuration = 0.1f; // �������� ���� ǥ�� ���ӽð�

	bool _ableDropGold = false; // ��� �� ��带 ��������
	vector<std::function<void()>> _deathEvent; // ��� �� ȣ���� �Լ�

};

