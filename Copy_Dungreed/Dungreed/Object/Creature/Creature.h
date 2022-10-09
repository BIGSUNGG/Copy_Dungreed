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

public:
	Creature(int level, int num);

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	virtual bool GetDamage(shared_ptr<Creature> enemy, shared_ptr<Item> weapon);
	virtual bool GiveDamage(shared_ptr<Creature> target , shared_ptr<Item> weapon = nullptr);

	const bool& GetIsFalling() { return _isFalling; }
	const Vector2& GetVelocity() { return _velocity; }
	const Status& GetStatus() { return _status; }
	const Vector2& GetBeforeMovePos() { return _beforeMove; }
	Creature_Type& GetCreatureType() { return _creatureType; }

	virtual void AddWeapon(shared_ptr<Weapon> weapon);
	virtual void SetSpawnPos(Vector2 pos) override;
	
protected:
	virtual void CollisionEvent(shared_ptr<Object> objects);
	virtual void TileCollison(shared_ptr<Tile> tile);
	virtual void TileBlockCollision(shared_ptr<Tile> tile);
	virtual void TileFloorCollision(shared_ptr<Tile> tile);
	virtual void TileLeftStairCollision(shared_ptr<Tile> tile);
	virtual void TileRightStairCollision(shared_ptr<Tile> tile);
	virtual void CreatureCollision(shared_ptr<Creature> creature);

	virtual void MoveCharacter();
	virtual void Death();
	virtual void Attack();

	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void Jump();

protected:
	Creature_Type _creatureType = ENEMY;
	vector<shared_ptr<Weapon>> _weaponSlot;
	int _curWeaponSlot = 0;

	Vector2 _movement;
	Vector2 _beforeMove;
	Vector2 _velocity = { 0,0 };

	Status _status;

	float _speed = 450.0f;

	float _jumpPower = 0.0f;
	float _jumpPowerMax = 1800.0f;

	float _gravityPower = 5000.0f;

	float _damagedRunTime = 0.1f;
	const float _damagedRunTimeMax = 0.1f;

	bool _isFalling = false;
	bool _passFloor = false;
	bool _passTile = false;
	bool _onStair = false;
	float _gravityRatio = 1.0f;
};

