#pragma once
class Creature : public Object , public std::enable_shared_from_this<Creature>
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
	const Vector2& GetVelocity() { return _velocity; }
	const Creature_Status& GetStatus() { return _status; }
	const Vector2& GetBeforeMovePos() { return _beforeMove; }
	Creature_Type& GetCreatureType() { return _creatureType; }

	virtual void AddItem(shared_ptr<Item> weapon);
	virtual void SetSpawnPos(Vector2 pos) override;
	
	virtual void CollisionEvent();

	virtual void TileCollison(shared_ptr<Tile> tile);
	virtual void TileBlockCollision(shared_ptr<Tile> tile);
	virtual void TileFloorCollision(shared_ptr<Tile> tile);
	virtual void TileLeftStairCollision(shared_ptr<Tile> tile);
	virtual void TileRightStairCollision(shared_ptr<Tile> tile);

	virtual void MovementEvent() {}
	virtual void MoveCharacter();
	virtual void FallingEnd();
	virtual void Death();

public:
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

	int _curWeaponSlot = 0;

	Vector2 _movement;
	Vector2 _beforeMove;
	Vector2 _velocity = { 0,0 };

	Creature_Status _status;

	float _jumpPower = 0.0f;
	float _jumpPowerMax = 1800.0f;

	float _gravityPower = 5000.0f;

	bool _isFalling = false;
	float _gravityRatio = 1.0f;

	float _damagedRunTime = 0.1f;
	float _damagedRunTimeMax = 0.1f;

	bool _passFloor = false;
	bool _passTile = false;
	bool _onStair = false;

};

