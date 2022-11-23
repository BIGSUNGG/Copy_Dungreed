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

	virtual float GetDamage(shared_ptr<Creature> enemy, shared_ptr<Item> weapon);
	virtual float GiveDamage(shared_ptr<Creature> target , shared_ptr<Item> weapon = nullptr);

	const bool& GetIsFalling() { return _isFalling; }
	const Creature_Status& GetStatus() { return _status; }
	Creature_Type& GetCreatureType() { return _creatureType; }
	shared_ptr<MovementComponent> GetMovementComponent() { return _movement; }

	virtual bool AddItem(shared_ptr<Item> weapon);
	virtual void SetSpawnPos(Vector2 pos) override;
	
	virtual void CollisionEvent();

	virtual void MoveCharacter();
	virtual void FallingEnd();
	virtual void Death();

public:
	virtual void MovementEvent() {}
	virtual void Attack();
	virtual void Skill();

	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void Jump();


protected:
	Creature_Type _creatureType = ENEMY;
	vector<shared_ptr<Weapon>> _weaponSlot;
	vector<shared_ptr<Accessory>> _accessorySlot;
	vector<shared_ptr<Item>> _itemSlot;

	shared_ptr<MovementComponent> _movement;

	int _curWeaponSlot = 0;

	Creature_Status _status;

	bool _dropGold = false;
	bool _isFalling = false;

	float _damagedRunTime = 0.1f;
	float _damagedRunTimeMax = 0.1f;

};

